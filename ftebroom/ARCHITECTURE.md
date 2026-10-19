# Architecture and research

[Русский](ARCHITECTURE.ru.md)

## Source baselines

- [FTE engine and csaddon](https://github.com/fte-team/fteqw/tree/f937b9d88f71fc4429db5fe56c6a98d922711b2e), pinned SDK/csaddon commit `f937b9d88f71fc4429db5fe56c6a98d922711b2e`.
- [Dear ImGui 1.91.9b](https://github.com/ocornut/imgui/tree/f5befd2d29e66809cd1110a152e375a7f1981f06).
- [ReyondBroom reference](https://github.com/reyond9079/ReyondBroom/tree/08e26168364629c968875215803a4d9720714223).

The default engine is built from the pinned source plus the included metadata patch. An optional user-supplied binary is a separate dependency and must be qualified independently. The build records its SHA256.

## What csaddon provides

`csaddon.src` compiles an addon VM, loaded by FTE as `csaddon.dat`. `csfixups.qc` links shared VM state. `csaddon.qc` wraps scene rendering, routes input and switches editor modes. `editor_brushes.qc` implements brush selection and tool dispatch; brush utility/history files implement geometry operations and undo/redo. Other editors provide lights, entities, terrain and particles. Camera spline support is conditional.

The engine exposes `brush_create`, `brush_get`, `brush_getfacepoints`, `brush_delete` and patch operations. Editable brushes are plane-based convex solids. `mapedit maps/name.map` starts without normal game code and retains editable source geometry. `mod_terrain_save "" name` exports the current map to `maps/name.map`. A loaded BSP follows a different saving path (entity export); it is not an interchangeable editable document.

Existing capabilities are foundations, not proof of production-ready ReyondBroom parity. History, patches, materials and entity association need independent round-trip fixtures before migration claims.

## First implementation

`native/ftebroom.cpp` is a native FTE plugin. It obtains Core, Command, Cvar, 2D and Input interfaces. Dear ImGui receives MenuEvent input and draws through FTE's renderer-independent `Image2dQuad` API. ImGui triangles are clipped against command clip rectangles on the CPU and submitted as degenerate quads. This avoids a second graphics context and avoids tying the frontend to OpenGL. Vulkan/D3D behavior remains untested.

The plugin uploads a font atlas and explicitly loads its UI material: `LoadImageData` does not itself provide a usable shader handle in this FTE implementation. The plugin checks interface availability before loading. The small type declarations before `plugin.h` accommodate unused engine API types in the upstream plugin header; they are not substitute implementations of those APIs.

The panel sends commands and cvars to csaddon. `ftebroom_box` validates dimensions, builds six planes, initializes texture coordinates, adds the brush through existing history and selects it. Redo dispatch is corrected from the upstream accidental undo call. File names are restricted to prevent command/path injection; open and overwrite require confirmation.

Input is deliberately modal for this slice. A menu-focus panel is simpler to integrate, but does not give the final editor's simultaneous viewport and panel behavior. FTE's own update prompts remain under engine control.

## Next stages and acceptance gates

1. **Foundation (current):** buildable plugin/addon, box, history, map export/reopen. Gate: automated geometry round-trip and manual input/scaling checks.
2. **Editor shell:** persistent scene panel, input ownership via ImGui capture flags, camera focus, selection model, entity/material browser and explicit dirty state. Gate: no input leaks; non-destructive cancel and restart recovery.
3. **Core map workflow:** plane/vertex/edge editing, clipping, CSG, entities and patches with tested material coordinates. Gate: representative Quake/Valve220/Q3 fixtures preserve semantics after save/reload.
4. **Procedural geometry:** Fracture, Perforate, Bevel and arrays, one tool at a time. Port algorithms independently of Qt; expose atomic transactions to csaddon. Gate: valid convex outputs, volume/intersection checks, texture invariance and deterministic seeds.
5. **Physics:** Bullet-driven Settle with brush and tessellated patch collision. Gate: repeatable settling, collision filtering, no tunnelling in documented bounds, cancellable preview and one-step undo.
6. **Delivery:** Linux and Windows builds from pinned engine source, automated packaging, license/source bundles, performance and large-map tests.

## Risks

- FTE and ReyondBroom use different geometry, document, entity and history models. Copying Qt dialogs or whole model libraries into QC would not solve those differences.
- QC/native boundaries need explicit ownership and transaction rules; hundreds of VM calls per face can become expensive.
- Coplanar planes, tiny bevel faces, grid snapping and numerical tolerances can invalidate convex brushes.
- MAP dialects, shader names and UV mapping must be tested rather than inferred from appearance.
- FTE plugin API revisions and render restarts can invalidate assumptions or resources. Current preview targets the tested Windows/OpenGL combination.
- Save/open currently has confirmation but no dirty-state tracking or crash recovery. Startup camera positioning uses delayed commands and is provisional.
- CPU triangle clipping and per-triangle submission are sufficient for a small panel, not a demonstrated large-editor rendering budget.

### Engine correction

The round-trip regression exposed an upstream omission in Terr_Brush_Insert: surfaceflags and surfacevalue were not copied into the stored face. The bundled patch copies both fields alongside texture coordinates. The build applies it to the pinned engine source. Keep the patch together with the base source archive when rebuilding. This fixes uninitialized export metadata; it does not add missing Q2/Q3 metadata to the QC face API.

