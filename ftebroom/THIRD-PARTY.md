# Third-party notices / Сторонние компоненты

- FTE Quake and csaddon: https://github.com/fte-team/fteqw — GPL-2.0-or-later. Copied csaddon sources preserve original notices; see FTE-LICENSE.txt. Changes: FTEBroom command routing, box creation and Redo dispatch fix.
- Dear ImGui: https://github.com/ocornut/imgui — MIT, Copyright (c) 2014-2025 Omar Cornut. The build copies its complete license into the output.
- ReyondBroom/TrenchBroom reference source retains the repository's existing licenses. The new FTEBroom implementation is GPL-2.0-or-later.
- GCC runtime components statically linked into the plugin are covered by their licenses and GCC Runtime Library Exception. See https://www.gnu.org/licenses/gcc-exception-3.1.html.

The build uses a user-supplied FTE binary. Its version may differ from the pinned SDK. Preserve corresponding engine source and all applicable third-party notices when distributing that binary; do not label the SDK checkout as its corresponding source unless it matches.

Сборка использует предоставленный бинарник FTE. Для его распространения нужны соответствующие именно ему исходники и лицензии. Закреплённая версия SDK не обязательно совпадает с версией бинарника.

The default engine build applies patches/preserve-brush-surface-metadata.patch to the pinned source. Bundled source archives include the base source; the adjacent patch records the engine modification. PNG, JPEG and zlib libraries retain their included upstream notices. / Сборка движка включает патч сохранения метаданных; исходники состоят из базового архива и прилагаемого патча.
