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
- [x] Replace `CL_System::get_time()` (and related timing) with `SDL_GetTicks()` via `System::get_time/sleep/keep_alive/get_exe_path`
- [x] Replace `CL_CommandLine` usage in `command_line_arguments.cpp` with a simple argv parser
- [x] Remove `CL_Error` catch in main; other CL_Error sites remain for later phases
- [x] Replace `CL_String::to` in system.cpp with `std::to_string`
- [x] Remove `CL_SetupCore/Display/GL` from main and pathfinder test mains; SDL_Init used instead
- [ ] Remaining `CL_Error` in ResourceManager and elsewhere
- [ ] Full removal of leftover ClanLib includes still present in many translation units

### Phase 3 – Window, main loop, Display
- [x] Create SDL_Window + SDL_Renderer in `Feuerkraft::init`
- [x] Introduce `Display` facade (width/height/clear/flip/fullscreen)
- [x] Make `Color` independent of ClanLib (SDL_Color conversion)
- [x] Wire `Display` into main and game_session (width/height/flip)
- [x] Port DrawingContext primitives (line/rect/fill/circle/arc) to SDL_Renderer
- [x] Port DrawingRequest / geometry types (Pointf, Vector3f, Rect)
- [x] Simplify SceneContext::render to color buffer via SDL (lightmap deferred)
- [ ] Adapt full event pumping (`SDL_PollEvent`) — partial stubs in game_session
- [ ] Screenshot support
- [ ] Re-enable lightmap/highlight compositing under SDL if desired

### Phase 4 – Input
- [x] Minimal Signal/Slot replacement (`signal.hpp`)
- [x] InputButton / InputAxis / KeyboardManager off ClanLib signals
- [x] SDL event pump in game_session (key down/up → KeyboardManager)
- [x] input_button_input_device / input_axis_input_device on SDL
- [x] ButtonFactory / AxisFactory use SDL scancodes / joysticks
- [ ] Richer key name coverage and joystick button wiring

### Phase 5 – Graphics core
- [x] `CL_Color` → independent `Color` class (done in Phase 3)
- [x] Geometry types (Pointf/Vector3f/Rect) for display layer
- [x] `CL_Sprite` → `Sprite` (SDL_Texture, multi-frame, rotation, alpha, scale)
- [x] DrawingContext/DrawingRequest/SceneContext on SDL (Phase 3)
- [ ] `CL_Font` → proper bitmap/TTF font (currently stubbed)
- [ ] Port remaining View drawing helpers & HUD
- [ ] Re-enable sprite draw path in DrawingContext

### Phase 6 – Resource Manager & Assets
- [x] Rewrite `ResourceManager` to parse ClanLib resource XML subset and load via SDL2_image
- [x] `get_sprite()` returns `Sprite`
- [ ] Font loading
- [ ] Guile-side resource access if any

### Phase 7 – Sound
- [x] Replace ClanLib sound with SDL2_mixer (`sound_real`, `sound_res_mgr`)
- [ ] Proper chunk lifetime / caching polish
- [ ] Ensure all sound assets resolve under the new path layout

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

- Phases 1–7 largely in place (window, display, drawing, sprites,
  resources, signals, input backends, sound).
- Remaining work: fonts, groundmap/pixel buffers, screenshot,
  DisplayManager drawing, and clearing residual ClanLib includes.
