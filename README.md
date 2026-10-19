# FTEBroom — experimental FTE-native map editor

[English guide](ftebroom/README.md) · [Русское руководство](ftebroom/README.ru.md)

FTEBroom is an independent development branch exploring a map editor inside the FTE Quake engine. It combines FTE's editable map geometry and csaddon with a native Dear ImGui frontend. The goal is to bring the main ReyondBroom editing workflows into the engine.

**Status: prototype 0.1, not feature parity with ReyondBroom.** The first slice provides a native panel, numeric box creation, brush history, grid/view controls, and `.map` save/open commands. Existing csaddon scene tools remain available. Advanced geometry tools and physics have not been ported.

## Start here

- [Build and run on Windows](ftebroom/README.md#build-on-windows)
- [What to test first](ftebroom/README.md#first-test-checklist)
- [Architecture, research and staged roadmap](ftebroom/ARCHITECTURE.md)
- [Source](ftebroom/) and [third-party notices](ftebroom/THIRD-PARTY.md)

The rest of this repository retains ReyondBroom source as the reference implementation. Its existing Qt/CMake build does **not** build FTEBroom. Use the build script under `ftebroom/scripts/`.

This branch does not change the stable ReyondBroom branch or its releases. FTEBroom's new code is distributed under GPL-2.0-or-later; third-party components retain their respective licenses.
