SUBDIRS = boost groundmap particles generic buildings

bindir=$(prefix)/games

bin_PROGRAMS = feuerkraft

LDADD = \
 groundmap/libfeuerkraft_groundmap.a \
 buildings/libfeuerkraft_buildings.a \
 generic/libfeuerkraft_generic.a 

feuerkraft_SOURCES = \
Collideable.hxx	 Energie.hxx	GameWorld.cxx	       KeyboardController.cxx  Tank.cxx	Turret.cxx \
Controllable.hxx  Explosion.cxx Explosion.hxx	GameWorld.hxx	       KeyboardController.hxx  Tank.hxx	Turret.hxx \
Controller.hxx	 Feuerkraft.cxx Projectile.cxx	\
Energie.cxx	 GameObj.hxx	 Projectile.hxx	\
Tree.cxx Tree.hxx TreeData.cxx TreeData.hxx Soldier.cxx Soldier.hxx \
Mine.hxx  Mine.cxx Shockwave.cxx Shockwave.hxx \
Controller.cxx Helicopter.cxx Helicopter.hxx Jeep.cxx Jeep.hxx Vehicle.hxx Vehicle.cxx \
Flag.cxx Flag.hxx View.cxx View.hxx Playfield.cxx Playfield.hxx \
VehicleView.cxx VehicleView.hxx Pathfinder.cxx Pathfinder.hxx Feuerkraft.hxx \
System.cxx System.hxx my_gettext.hxx StringConverter.hxx StringConverter.cxx \
Radar.hxx Radar.cxx GuiObj.hxx Screen.hxx Screen.cxx \
VehicleStatus.hxx  VehicleStatus.cxx \
Background.hxx Background.cxx Stone.hxx Stone.cxx \
Ambulance.hxx Ambulance.cxx \
GameObjData.hxx GameWorldData.hxx GameWorldData.cxx \
GameObjDataFactory.hxx GameObjDataFactory.cxx \
LevelMap.hxx LevelMap.cxx \
StartScreen.hxx StartScreen.cxx \
ViewProperties.hxx \
Guile.hxx Guile.cxx \
GameMission.hxx GameMission.cxx \
ResourceManager.hxx ResourceManager.cxx

# EOF #
