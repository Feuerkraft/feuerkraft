#!/bin/sh

set -e

export slibs="\
/usr/local/lib/libSphriteLibGL.a \
/usr/local/lib/libclanGL.a \
/usr/local/lib/libclanPNG.a \
/usr/local/lib/libclanJPEG.a \
/usr/local/lib/libclanVorbis.a \
/usr/local/lib/libclanGUI.a \
/usr/local/lib/libclanApp.a \
/usr/local/lib/libclanSound.a \
/usr/local/lib/libclanDisplay.a \
/usr/local/lib/libclanCore.a \
/usr/local/lib/libHermes.a \
/usr/lib/libguile.a \
/usr/lib/libltdl.a \
/usr/lib/libqthreads.a"

export dlibs="-L/usr/X11R6/lib/ \
-lz \
-ljpeg \
-lpng \
-lpthread \
-lm \
-lXext \
-lX11 \
-lXxf86vm \
-lSM \
-lXt \
-lGLU \
-lGL \
-ldl \
-lX11 \
"


g++ -I.. -O2 -Wall  -o feuerkraft  GameWorld.o KeyboardController.o Tank.o Turret.o Explosion.o Feuerkraft.o JoystickController.o Projectile.o Energie.o Tree.o TreeData.o Soldier.o Mine.o Shockwave.o Controller.o Helicopter.o Jeep.o Vehicle.o Flag.o View.o Playfield.o VehicleView.o Pathfinder.o System.o StringConverter.o Radar.o Screen.o VehicleStatus.o Background.o Stone.o Ambulance.o GameWorldData.o GameObjDataFactory.o LevelMap.o StartScreen.o groundmap/libfeuerkraft_groundmap.a  buildings/libfeuerkraft_buildings.a  generic/libfeuerkraft_generic.a $slibs $dlibs

#upx-ucl feuerkraft

# EOF #