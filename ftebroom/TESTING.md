# Prototype checks

The smoke test intentionally compares complete exported face records, including texture axes and optional metadata. Do not weaken it to ignore differing surface flags: older FTE binaries can emit uninitialized flags even when geometry looks correct. A binary is not qualified for this preview until the complete round-trip passes.

The screenshot check verifies actual FTE/ImGui rendering. It is not a substitute for clicking controls, cancelling dialogs and checking focus. The user checklist in README covers those remaining interactive checks.

## Recorded verification, 2026-10-19

- Native Windows x64 plugin compiled with MinGW GCC 15.2; csaddon compiled with pinned FTEQCC, zero warnings.
- Actual FTE/OpenGL screenshot confirms readable ImGui, grid floor and generated cube on NVIDIA RTX 4060 Laptop GPU.
- The full export regression failed on the old supplied engine and on the unpatched pinned engine. The pinned engine plus the included two-field copy patch passes: 12 faces after create, 6 after undo, and identical complete face records after redo, rejected invalid input and reload.
- Manual pointer/keyboard focus, dialog cancellation and Windows scaling checks remain for the first user test. No parity claim is made for advanced tools or Q2/Q3 document metadata.
