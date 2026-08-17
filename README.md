Feuerkraft
==========

Feuerkraft is an incomplete 2D top-down tank battle game with some
inspiration from games like GTA or Operation Flashpoint. It is not in
a playable state, but it allows you to run around and get into
vehicles.

The Feuerkraft webpage is located at:

* https://feuerkraft.github.io


Compilation
-----------

Feuerkraft requires SDL2, SDL2_image and SDL2_mixer. Scheme scripting uses vendored s7 (external/s7).

On a typical Debian/Ubuntu system:

    sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev \
                         cmake pkg-config

Compilation is done via `cmake`:

    mkdir build
    cd build
    cmake ..
    make

Install (optional):

    cmake --install . --prefix /usr/local

The data directory is compiled in as `FEUERKRAFT_DATADIR` (default:
`$prefix/share/feuerkraft`). Override at configure time with
`-DFEUERKRAFT_DATADIR=/path/to/data`, or at runtime with `--datadir`.

Or with Nix:

    nix build
    # or
    nix develop


Port status
-----------

The game has been ported from ClanLib 1.0 to **SDL2** (SDL2_image,
SDL2_mixer). ClanLib is no longer required at build or run time.

Running (from the build directory, with data available):

    ./feuerkraft --datadir ../data

Optional gamepad config:

    ./feuerkraft --datadir ../data \
        --controller ../data/controller/gamepad.scm

See `TODO.md` for optional follow-ups.


Screenshots
-----------

![Screenshot](http://feuerkraft.github.io/images/screenshot-12.jpg)
