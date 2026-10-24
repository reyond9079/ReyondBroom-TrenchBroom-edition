# ReyondBroom TrenchBroom edition

**A standalone 3D level editor for brush-based games.** Build spaces, shape architecture, texture surfaces and place gameplay entities in one workspace—from a first room to a detailed playable map.

[![Download for Windows x64](https://img.shields.io/badge/Download_for_Windows_x64-0078D4?style=for-the-badge&logo=windows&logoColor=white)](https://github.com/reyond9079/ReyondBroom-TrenchBroom-edition/releases/latest/download/ReyondBroom-Windows.zip)
[![Download for Linux x86_64](https://img.shields.io/badge/Download_for_Linux_x86__64-FCC624?style=for-the-badge&logo=linux&logoColor=black)](https://github.com/reyond9079/ReyondBroom-TrenchBroom-edition/releases/latest/download/ReyondBroom-Linux-x86_64.AppImage)

**English** · [Русский](README.ru.md) · [Illustrated handbook](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/) · [Full reference](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/reference.html) · [Releases and checksums](https://github.com/reyond9079/ReyondBroom-TrenchBroom-edition/releases/latest)

## What ReyondBroom adds

Compared with the base TrenchBroom 2026.2 editor, ReyondBroom includes the following additional tools and workflows. Each link opens illustrated usage instructions.

| Feature | What you can do |
| --- | --- |
| [Convex Bevel](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#bevel) | Round edges, vertices or the outside boundary of selected faces. Adjust radius/offset, segments and convex profile, with per-brush Clamp and preview directly in the scene. |
| [Fracture](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#fracture) | Split a brush into 2–128 seeded Voronoi fragments, set the cut material, separate the pieces and optionally create individual `func_wall` entities. |
| [Perforate](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#perforate) | Create random polygonal through-holes with configurable count, contour sides, diameter range and spacing; optionally retain and select matching `func_wall` plugs. |
| [Settle](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#settle) | Drop and arrange brushes with Bullet physics, friction, bounce and an initial kick. Collide with scene brushes and Quake 3 patches, then apply the result as static map geometry. |
| [Terrain](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#terrain), [Sculpt](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#sculpt) and [Rock](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#rock) | Generate terrain and rocks, then reshape terrain with sculpting controls. |
| [Polygon Cut / Spawn](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#polygon-cut) | Draw polygonal outlines to cut existing geometry or create new volumes. |
| [Inset](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#inset), [Spin](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#spin) and [Bezier Bend](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#bezier-bend) | Inset surfaces, generate chains of rotated extrusions and bend grouped geometry along a curve. |
| [Subdivision](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#subdivision), [Subtract 2](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#subtract-2) and [Convert Triang Brushes](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#convert-triang) | Add geometry divisions, use an alternative subtraction workflow and convert triangulated brush structures. |
| [Arrays](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#array-line) and [Symmetry](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#symmetry) | Create linear, radial and randomized arrangements and maintain symmetric copies. |
| [Grid Rotation](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#grid-rotation), [Auto Integer Snap](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#snap-integer) and [XYZ editing](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#xyz) | Align work to a rotated grid, snap geometry to integer coordinates and edit exact positions. |
| [Prefab Collections](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#prefabs) and [EntityList](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#entity-list) | Reuse saved assemblies and find placed entities in a dedicated list. |
| [Material and entity browser controls](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#material-browser) | Adjust browser previews, load texture folders and choose a WAD export palette. |
| [Quake previews](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#lighting) and [Spawn Master](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#spawn-master) | Preview lighting, sky, doors, buttons, lifts, trains and intermission cameras; generate teleport-closet spawning setups. |
| [Unity Sync](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#unity-sync) | Export map geometry and textures into a Unity prefab with configurable scale. |

Bevel produces convex brushes only. Fracture's **No collide** option creates `func_wall` entities; it does **not** disable Settle collisions. Game previews are approximate and do not replace testing a compiled map.

![ReyondBroom: convex Bevel preview in the map viewport](docs/captures/reyond/bevel-preview.png)

## Build the whole level

- **Edit in 3D and 2D.** Create brush primitives, move vertices, edges and faces, clip, extrude, sweep, scale and shear. Work with Quake 3 patches and control points in supported map formats.
- **Shape architecture and terrain.** Draw polygon cuts and volumes, inset faces, bend groups, extrude curved chains, subdivide surfaces, sculpt terrain and generate rocks.
- **Round and break geometry.** Bevel face boundaries, edges or vertices with radius, segments, convex profiles and Clamp. Fracture solids into seeded fragments, perforate surfaces and settle pieces with gravity and collisions.
- **Repeat and align.** Place linear, radial or random arrays, synchronize symmetric copies, rotate the grid, snap vertices to integers and enter exact XYZ coordinates.
- **Texture and organize.** Edit UV alignment, browse materials, load texture folders, choose WAD export palettes, place prefabs and navigate with EntityList. Groups, linked groups and layers keep large maps manageable.
- **Preview and export.** Inspect approximate Quake lighting, sky, moving entities and train routes. Configure external compilers, inspect issues and leak traces, launch the game or synchronize geometry and textures to Unity.

ReyondBroom is independently maintained, with its own releases and documentation. It installs as a complete application; another editor is not required.

## Get started

1. **Install.** On Windows, extract the entire ZIP and run `TrenchBroom.exe`—the current executable filename. Keep its resources and DLLs. On Linux, make the AppImage executable and launch it; use `--appimage-extract-and-run` if FUSE is unavailable.
2. **Choose your game.** Create a map, select a compatible format, and configure the game directory, mod and entity definitions. Game data and compilation tools are supplied separately.
3. **Build a room.** Start with a floor, four walls and a ceiling. Add a player start and a light, apply materials and save.
4. **Compile and test.** Configure **Run → Compile** with your game's tools. Inspect the result in the engine before adding detail.

[Follow the illustrated first-map walkthrough →](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#first-room)

Windows x64 and Linux x86_64 binaries are available. The Linux AppImage is built and tested on Ubuntu 24.04; older distributions are not verified. A macOS binary is not provided in the current release.

## Learn the tools

| What you want to do | Guide |
| --- | --- |
| Navigate, select, build and texture | [Start here](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#start) |
| Round edges and corners | [Bevel](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#bevel) |
| Break a wall and place rubble | [Fracture](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#fracture) · [Settle](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#settle) |
| Cut random through-holes | [Perforate](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#perforate) |
| Generate terrain and curved structures | [Terrain](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#terrain) · [Bezier Bend](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#bezier-bend) · [Spin](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#spin) |
| Repeat modules and reuse assets | [Array](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#array-line) · [Symmetry](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#symmetry) · [Prefabs](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#prefabs) |
| Compile, diagnose and export | [Compilation](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#compile) · [Unity Sync](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/#unity-sync) |

The handbook has matching English and Russian chapters, screenshots, searchable navigation, steps and limitations. The full technical reference covers the core editor, expressions and game configuration in English. [Documentation sources and local build instructions](docs/README.md) are included.

## Games and formats

Game configurations cover Quake, Quake 2, Quake 3, Hexen 2, Daikatana and custom engines. Map formats, materials, entity classes and patch support depend on the selected configuration. Quake Standard and Valve 220 workflows are supported. Choose a format your compiler accepts; a viewport preview does not replace testing the compiled map.

## Development and reference

Development takes place on **ReyondBroom**. See [BUILD.md](BUILD.md), [CONTRIBUTING.md](CONTRIBUTING.md) and [AGENTS.md](AGENTS.md) for build instructions and repository conventions.

Source projects and image provenance are recorded once in [Sources and licenses](https://reyond9079.github.io/ReyondBroom-TrenchBroom-edition/sources.html). The editor is distributed under [GPL-3.0-or-later](LICENSE.txt); source notices and [third-party licenses](THIRD_PARTY_NOTICES.md) are retained.
