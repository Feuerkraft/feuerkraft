noinst_LIBRARIES = libfeuerkraft_scripting.a

command_source = \
 ai_commands.cxx \
 ai_commands.hxx \
 ai_vehicle_commands.cxx \
 ai_vehicle_commands.hxx \
 building_commands.cxx   \
 building_commands.hxx   \
 clanlib_commands.hxx    \
 clanlib_commands.cxx    \
 comm_commands.cxx       \
 comm_commands.hxx       \
 display_commands.hxx    \
 display_commands.cxx    \
 debug_commands.hxx      \
 debug_commands.cxx      \
 effect_commands.cxx     \
 effect_commands.hxx     \
 gameobj_commands.cxx    \
 gameobj_commands.hxx    \
 game_commands.cxx       \
 game_commands.hxx       \
 input_commands.cxx      \
 input_commands.hxx      \
 menu_commands.cxx       \
 menu_commands.hxx       \
 object_commands.cxx     \
 object_commands.hxx     \
 player_commands.cxx     \
 player_commands.hxx     \
 sequence_commands.cxx   \
 sequence_commands.hxx   \
 sound_commands.cxx      \
 sound_commands.hxx      \
 trigger_commands.cxx    \
 trigger_commands.hxx    \
 vehicle_commands.cxx    \
 vehicle_commands.hxx    \
 script_helper.cxx       \
 script_helper.hxx

libfeuerkraft_scripting_a_SOURCES = \
 $(command_source) \
 feuerkraft_wrap.cxx

#lib_LTLIBRARIES = libguile-feuerkraft.la

#libguile_feuerkraft_la_SOURCES = feuerkraft_wrap.cxx
#libguile_feuerkraft_la_LIBADD = libfeuerkraft_scripting.a

# Include feuerkraft_wrap.cxx in case the user doesn't have swig installed
EXTRA_DIST = feuerkraft_wrap.cxx

feuerkraft_wrap.cxx: feuerkraft.i  $(command_source)
	$(SWIG) -guile -c++  -o $@ $<

# We override the default compile command to skip all the warnings
# that compiling the wrappers causes.
feuerkraft_wrap.o : feuerkraft_wrap.cxx
	$(CXX) -c -O2 -o $@ $<

# EOF #
