noinst_LIBRARIES = libfeuerkraft_scripting.a

command_source = ai_vehicle_commands.cxx \
 ai_vehicle_commands.hxx \
 sequence_commands.hxx   \
 sequence_commands.cxx   \
 effect_commands.cxx     \
 effect_commands.hxx     \
 object_commands.hxx     \
 object_commands.cxx     \
 trigger_commands.hxx     \
 trigger_commands.cxx

libfeuerkraft_scripting_a_SOURCES = \
 $(command_source) \
 feuerkraft_wrap.cxx

#lib_LTLIBRARIES = libguile-feuerkraft.la

#libguile_feuerkraft_la_SOURCES = feuerkraft_wrap.cxx
#libguile_feuerkraft_la_LIBADD = libfeuerkraft_scripting.a

feuerkraft_wrap.cxx: feuerkraft.i  $(command_source)
	$(SWIG) -guile -c++  -o $@ $<

# EOF #