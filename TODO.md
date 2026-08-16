# Feuerkraft SDL2 Port TODO

## Overview

Port Feuerkraft from ClanLib 1.0 to SDL2 (with SDL2_image / SDL2_mixer as needed).
This is a **destructive** port: all ClanLib support and dependencies will be removed.
Guile + SWIG scripting remains.

ClanLib is used extensively (~765 references). Main categories of usage:

- **Core / System**: `CL_SetupCore`, `CL_System::get_time()`, command line parsing, errors, strings
- **Display / Window**: `CL_DisplayWindow`, `CL_Display`, `CL_SetupDisplay`, `CL_SetupGL` (OpenGL backend)
- **Graphics primitives**: `CL_Sprite`, `CL_Surface`, `CL_Font`, `CL_Color` / `CL_Colorf`, `CL_Rect`, `CL_Vector` / `CL_Pointf`, `CL_GraphicContext`, `CL_PixelBuffer`
- **Drawing abstraction**: custom `DrawingContext` + `DrawingRequest` hierarchy that currently targets `CL_GraphicContext`
- **Resource system**: `CL_ResourceManager` loading `data/feuerkraft.xml` + `data/tiles.xml` (sprites, surfaces, fonts defined in ClanLib resource XML)
- **Input**: `CL_Keyboard`, `CL_Mouse`, `CL_Joystick` + signal/slot system (`CL_Slot`, `CL_Signal_*`) wired into a custom InputManager / controller abstraction
- **Sound**: `CL_SoundOutput`, `CL_SoundBuffer`, MikMod + Vorbis providers via ClanLib

Top symbols by frequency: `CL_Sprite` (81), `CL_Display` (57), `CL_Color` (49), `CL_System` (30), `CL_GraphicContext` (28), ...

## Recommended Port Order

Work in small, focused commits. Keep the tree buildable as long as possible (or at least compilable with stubs). Prefer clean abstractions over quick hacks; refactor when complexity grows.

### Phase 0 – Preparation / Tracking (this commit)
- [x] Create `TODO.md` and capture analysis + plan
- [ ] Inventory all ClanLib headers/includes and create a mapping table (ClanLib → SDL2)
- [ ] Decide graphics backend: SDL_Renderer (simpler, 2D-friendly) vs. raw OpenGL/SDL_GL (closer to original ClanLib-GL path). **Prefer SDL_Renderer + SDL2_image** unless performance/features force GL.
- [ ] Decide resource strategy: parse existing ClanLib `.xml` resource files, or convert assets to a simpler format (directory of PNGs + metadata) and rewrite ResourceManager.

### Phase 1 – Build system & skeleton
- [x] Update `CMakeLists.txt`: drop all `clan*-1.0` pkg-config modules; add `SDL2`, `SDL2_image`, `SDL2_mixer` (and keep Guile/SWIG/Threads)
- [x] Update `flake.nix` accordingly (remove clanlib input). `flake.lock` will be regenerated on next `nix flake update`.
- [x] Remove `external/clanlib` submodule / references
- [x] Update `README.md` and `src/config.h`
- [ ] Make the project compile with stubs or minimal SDL2 window (main still exits quickly) — blocked on actual ClanLib API removal (Phase 2+)

### Phase 2 – Core / System replacements
- [ ] Replace `CL_System::get_time()` (and related timing) with `SDL_GetTicks()` / `SDL_GetPerformanceCounter`
- [ ] Replace `CL_CommandLine` usage in `command_line_arguments.cpp`
- [ ] Replace `CL_Error` / exception handling
- [ ] Replace string helpers (`CL_String`, etc.) with `std::string` / C++11 utilities
- [ ] Remove all `CL_SetupCore` / `CL_SetupDisplay` / `CL_SetupGL` / `CL_SetupSound` init/deinit calls

### Phase 3 – Window, main loop, Display
- [ ] Create SDL_Window + SDL_Renderer (or GL context) in `Feuerkraft::init`
- [ ] Replace `CL_DisplayWindow` / `CL_Display::*` (clear, flip, get_width/height, etc.)
- [ ] Adapt main loop / event pumping (`CL_Display` event handling → `SDL_PollEvent`)
- [ ] Screenshot support (`CL_PixelBuffer` → SDL_Surface / SDL_RenderReadPixels)

### Phase 4 – Input
- [ ] Replace ClanLib keyboard/mouse/joystick + signal/slot wiring
- [ ] Keep the existing high-level `InputManager` / controller / axis / button abstraction; only replace the backend that feeds it
- [ ] Map SDL scancodes / mouse buttons / joystick axes to the existing controller scheme
- [ ] Remove `CL_Slot` / `CL_Signal_*` dependency (either implement a tiny signal or switch to std::function / direct calls)

### Phase 5 – Graphics core
- [ ] Introduce thin wrappers or replace:
  - `CL_Color` → simple struct or SDL_Color
  - `CL_Rect` / `CL_Pointf` / `CL_Vector` → own math or SDL_Rect / custom
  - `CL_Sprite` → texture + frame data (SDL_Texture + metadata)
  - `CL_Surface` / `CL_PixelBuffer` → SDL_Surface / SDL_Texture
  - `CL_Font` → SDL_ttf or bitmap font / existing font resources
- [ ] Port `DrawingContext` + `DrawingRequest` hierarchy to target SDL_Renderer (or GL)
- [ ] Port `View`, `SceneContext`, `DisplayManager`, HUD elements (radar, energy, messages, …)
- [ ] Handle blending, rotation, scaling, z-ordering that ClanLib sprites provided

### Phase 6 – Resource Manager & Assets
- [ ] Rewrite `ResourceManager` to load sprites/surfaces/fonts without ClanLib
- [ ] Decide on resource format (keep XML and parse, or convert assets once)
- [ ] Ensure `data/images/`, tiles, etc. load correctly via SDL2_image
- [ ] Update any Guile-side resource access if present

### Phase 7 – Sound
- [ ] Replace ClanLib sound with SDL2_mixer
- [ ] Port `sound_real.cpp` / `sound_res_mgr` (music + SFX, volume, stop, etc.)
- [ ] Drop MikMod/Vorbis ClanLib providers; use SDL2_mixer’s built-in support (or libmodplug / etc. if needed)

### Phase 8 – Remaining game objects & polish
- [ ] Sweep remaining `CL_*` usages in vehicles, buildings, particles, projectiles, AI, pathfinders, menus, screens, …
- [ ] Fix compilation warnings / clean includes
- [ ] Verify basic gameplay loop (drive around, enter vehicles, basic rendering)
- [ ] Update README, desktop file, packaging as needed
- [ ] Remove all ClanLib traces from the tree

### Phase 9 – Cleanup & finalisation
- [ ] Dead code removal, consistent style
- [ ] Ensure Nix flake and CMake both produce a working binary
- [ ] Final testing / screenshots

## Notes / Pitfalls

- ClanLib 1.0 resource XML format is proprietary to that era; parsing it may be non-trivial. Converting the handful of sprite definitions to a simpler format is likely cleaner.
- The custom `DrawingContext` is a good place to hide the backend; keep the rest of the game talking to it.
- Input already has a nice abstraction layer – only the lowest backend needs replacement.
- Pathfinders and some tools call `CL_SetupCore::init()` themselves for standalone timing; clean those up.
- Guile/SWIG bindings may expose some ClanLib types; audit `src/scripting/`.
- Prefer modern C++ (C++17) where it simplifies the port, but stay consistent with existing style.
- Nix store is read-only; when copying from it adjust permissions.

## Current Status

- TODO + port plan committed.
- Phase 1 (build system) largely done: CMake and flake now depend on SDL2 / SDL2_image / SDL2_mixer instead of ClanLib. Submodule removed. Source still contains ClanLib API calls, so the binary does not yet link/run — that is the work of subsequent phases.
