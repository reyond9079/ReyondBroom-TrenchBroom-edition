#!/usr/bin/env python3
"""Package runtime files only, from a deployed directory or an existing release ZIP."""
import argparse
import hashlib
from pathlib import Path, PurePosixPath
import zipfile

RUNTIME_DIRS = {
    'defaults', 'docs', 'fonts', 'games', 'generic', 'iconengines',
    'imageformats', 'images', 'licenses', 'manual', 'networkinformation',
    'platforms', 'shader', 'styles', 'stylesheets', 'tls', 'translations', 'update',
}
RUNTIME_FILES = {'TrenchBroom.exe', 'vc_redist.x64.exe', 'build-info.json',
                 'LICENSE.txt', 'Bullet-LICENSE.txt', 'AppIcon.ico',
                 'DocIcon.ico', 'WindowIcon.ico'}
BUILD_SUFFIXES = {'.pdb', '.pch', '.obj', '.lib', '.exp', '.ilk', '.cmake'}
REQUIRED = {'TrenchBroom.exe', 'build-info.json', 'LICENSE.txt',
            'Bullet-LICENSE.txt', 'Qt6Core.dll', 'Qt6Gui.dll', 'Qt6Widgets.dll',
            'platforms/qwindows.dll', 'manual/index.html'}


def include(name):
    path = PurePosixPath(name)
    if path.is_absolute() or '..' in path.parts or '\\' in name:
        raise ValueError(f'Unsafe package path: {name}')
    if path.suffix.lower() in BUILD_SUFFIXES:
        return False
    if len(path.parts) > 1:
        return path.parts[0] in RUNTIME_DIRS
    return name in RUNTIME_FILES or path.suffix.lower() in {'.dll', '.md'}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    source = parser.add_mutually_exclusive_group(required=True)
    source.add_argument('--directory', type=Path)
    source.add_argument('--source-zip', type=Path)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    output = args.output.resolve()
    if args.source_zip and args.source_zip.resolve() == output:
        parser.error('Source and output ZIP must differ')
    output.parent.mkdir(parents=True, exist_ok=True)
    source_hashes = {}
    excluded = 0
    with zipfile.ZipFile(output, 'w', zipfile.ZIP_DEFLATED, compresslevel=9) as target:
        def copy(name, data):
            source_hashes[name] = hashlib.sha256(data).digest()
            target.writestr(name, data)
        if args.source_zip:
            with zipfile.ZipFile(args.source_zip) as archive:
                for item in archive.infolist():
                    if item.is_dir():
                        continue
                    if include(item.filename):
                        copy(item.filename, archive.read(item))
                    else:
                        excluded += item.file_size
        else:
            root = args.directory.resolve()
            for path in sorted(root.rglob('*')):
                if path.is_file() and path.resolve() != output:
                    name = path.relative_to(root).as_posix()
                    if include(name):
                        copy(name, path.read_bytes())
                    else:
                        excluded += path.stat().st_size
    with zipfile.ZipFile(output) as archive:
        names = set(archive.namelist())
        missing = REQUIRED - names
        if missing:
            raise ValueError(f'Missing runtime files: {sorted(missing)}')
        for directory in ('defaults', 'fonts', 'games', 'images', 'shader', 'stylesheets', 'licenses'):
            if not any(name.startswith(directory + '/') for name in names):
                raise ValueError(f'Missing resource directory: {directory}')
        for name, digest in source_hashes.items():
            if hashlib.sha256(archive.read(name)).digest() != digest:
                raise ValueError(f'Packaged bytes changed: {name}')
        unpacked = sum(item.file_size for item in archive.infolist())
    digest = hashlib.sha256(output.read_bytes()).hexdigest()
    output.with_name(output.name + '.sha256').write_text(
        f'{digest}  {output.name}\n', encoding='utf-8')
    print(f'Validated {len(source_hashes)} runtime files; ZIP {output.stat().st_size:,} bytes; '
          f'unpacked {unpacked:,} bytes; excluded {excluded:,} build bytes.')


if __name__ == '__main__':
    main()
