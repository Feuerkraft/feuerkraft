noinst_LIBRARIES = libfeuerkraft_scripting.a

command_source = \
 ai_commands.cpp \
 ai_commands.hpp \
 ai_vehicle_commands.cpp \
 ai_vehicle_commands.hpp \
 building_commands.cpp   \
 building_commands.hpp   \
 clanlib_commands.hpp    \
 clanlib_commands.cpp    \
 comm_commands.cpp       \
 comm_commands.hpp       \
 display_commands.hpp    \
 display_commands.cpp    \
 debug_commands.hpp      \
 debug_commands.cpp      \
 effect_commands.cpp     \
 effect_commands.hpp     \
 gameobj_commands.cpp    \
 gameobj_commands.hpp    \
 game_commands.cpp       \
 game_commands.hpp       \
 input_commands.cpp      \
 input_commands.hpp      \
 menu_commands.cpp       \
 menu_commands.hpp       \
 object_commands.cpp     \
 object_commands.hpp     \
 player_commands.cpp     \
 player_commands.hpp     \
 sequence_commands.cpp   \
 sequence_commands.hpp   \
 sound_commands.cpp      \
 sound_commands.hpp      \
 trigger_commands.cpp    \
 trigger_commands.hpp    \
 vehicle_commands.cpp    \
 vehicle_commands.hpp    \
 script_helper.cpp       \
 script_helper.hpp

libfeuerkraft_scripting_a_SOURCES = \
 $(command_source) \
 feuerkraft_wrap.cpp

#lib_LTLIBRARIES = libguile-feuerkraft.la

#libguile_feuerkraft_la_SOURCES = feuerkraft_wrap.cpp
#libguile_feuerkraft_la_LIBADD = libfeuerkraft_scripting.a

# Include feuerkraft_wrap.cpp in case the user doesn't have swig installed
EXTRA_DIST = feuerkraft_wrap.cpp

feuerkraft_wrap.cpp: feuerkraft.i  $(command_source)
	$(SWIG) -guile -c++  -o $@ $<

# We override the default compile command to skip all the warnings
# that compiling the wrappers causes.
feuerkraft_wrap.o : feuerkraft_wrap.cpp
	$(CXX) -c -O2 -o $@ $<

# EOF #
