# FTEBroom subtree

This independent prototype lives under ftebroom/. Build it with scripts/build-windows.ps1; the parent Qt/CMake targets are reference code, not its build system. New source comments are English. Maintain English docs first and matching Russian translations. Preserve upstream licenses. Use isolated copies for runtime tests and never write test maps into an existing game installation. Validate geometry/history/map round-trips when changing QC, and inspect actual engine screenshots when changing the renderer.
