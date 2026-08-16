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

Feuerkraft requires SDL2, SDL2_image, SDL2_mixer and Guile 3.x.

On a typical Debian/Ubuntu system:

    sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev \
                         guile-3.0-dev swig cmake pkg-config

Compilation is done via `cmake`:

    mkdir build
    cd build
    cmake ..
    make

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
