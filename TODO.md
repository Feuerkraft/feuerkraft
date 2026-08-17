# Feuerkraft porting TODO

Infrastructure under `mk/` and `nix/` is adapted from
[SuperTux Milestone 1](https://github.com/SuperTux-Origins/supertux-milestone1)
and [Pingus](https://github.com/Pingus/pingus) (same layout and scripts).

## Done

- [x] Vendor `mk/wasm`, `mk/android`, `mk/r36s`, `nix/{wasm,android,r36s}.nix`
- [x] Emscripten-aware CMake (`SDL2_ROOT`, `EMSCRIPTEN_LINK_FLAGS`, `.html` suffix)
- [x] WASM frame loop via `emscripten_set_main_loop` + `GameSessionManager::tick()`
- [x] Shell stubs (`fk_emscripten_*`) for `mk/wasm/shell.html`
- [x] Separate `packages.s7` derivation
- [x] Flake packages: `feuerkraft`, `feuerkraft-wasm`, `feuerkraft-win64/32`
- [x] Android.mk lists Feuerkraft sources + s7; build-apk copies `external/s7`

## In progress / next

- [x] Fix `stb_image.h` fixed-output hash in flake and enable `feuerkraft-android`
- [x] Android SDK: `config.allowUnfree` + `android_sdk.accept_license` (SuperTux/Pingus pattern)
- [x] First successful `nix build .#feuerkraft-wasm`
- [x] R36S: ArkOS sysroot + `feuerkraft-r36s` / PortMaster packages in flake
- [ ] Windows: verify MinGW link + DLL staging; add `S7` build under mingw
- [x] Android: stb_image shim in APK (no libSDL2_image); RWops for assets
- [x] WASM datadir: prefer `/data` under Emscripten; Android uses `.`
- [ ] Optional: IDBFS for save games under Emscripten

## Build commands

```bash
nix build .#feuerkraft              # native Linux
nix build .#feuerkraft-wasm         # wasm32 + HTML (needs emscripten)
nix run .#feuerkraft-wasm           # serve + open browser
nix build .#feuerkraft-win64        # MinGW-w64 cross from Linux
nix build .#feuerkraft-android
# nix build .#feuerkraft-r36s       # after arkos-sysroot available
```

See also: `mk/wasm/README.md`, `mk/android/README.md`, `mk/r36s/CROSSCOMPILE.md`.
