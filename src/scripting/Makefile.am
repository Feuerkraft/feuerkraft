noinst_LIBRARIES = libfeuerkraft_scripting.a

libfeuerkraft_scripting_a_SOURCES = \
 ai_vehicle_commands.cxx \
 ai_vehicle_commands.hxx \
 feuerkraft_wrap.cxx

#lib_LTLIBRARIES = libguile-feuerkraft.la

#libguile_feuerkraft_la_SOURCES = feuerkraft_wrap.cxx
#libguile_feuerkraft_la_LIBADD = libfeuerkraft_scripting.a

feuerkraft_wrap.cxx: feuerkraft.i ai_vehicle_commands.hxx
	swig -guile -c++  -o $@ $<

# EOF #