AC_INIT(Feuerkraft, 0.1.1)
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR(src/feuerkraft.hxx)
AM_INIT_AUTOMAKE(dist-bzip2)

AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL

dnl AC_DISABLE_SHARED
dnl AC_PROG_LIBTOOL

AC_PROG_RANLIB

AC_LANG(C++)

dnl Checking for libraries

AC_PATH_PROG([SWIG], [swig], [nothing-found])
if test "x$SWIG" = "xnothing-found"; then
   AC_MSG_ERROR([You need Swig - http://www.swig.org to proceed.])
fi

AC_CHECK_LIB(qthreads, main)
AC_CHECK_LIB(guile, scm_boot_guile,, [
  echo "libguile is missing, you need Guile 1.6.x to compile Feuerkraft"
  exit
  ])

AC_CHECK_HEADER(guile/gh.h)

dnl FIXME: this is a hack for my local machine...
LIBS="$LIBS -L/usr/X11R6/lib/ -lXxf86vm"

AC_CHECK_LIB(clanCore, main,, [
	echo "ClanLib installed, but -lclanCore not found, run 'ldconfig' and try again,"
	echo "if that doesn't help have a look at the file config.log and look into"
	echo "the FAQ."
	exit
	])

AC_CHECK_LIB( clanApp,   main,, [
	echo "ClanLib installed, but -lclanCore not found, run 'ldconfig' and try again,"
	echo "if that doesn't help have a look at the file config.log and look into"
	echo "the FAQ."
	exit
	])

dnl AC_CHECK_LIB( clanSound,   main,, [
dnl 	echo "ClanLib is installed, but clanJPEG was not found. You probably"
dnl 	echo "forgot to compile clanJPEG, which is part of the ClanLib package"
dnl 	echo "or you need to run 'ldconfig'."
dnl 	echo "If you think you have everything correctly installed have a look at"
dnl 	echo "the file 'config.log' to see what went wrong"
dnl 	exit
dnl 	])

AC_CHECK_LIB( clanDisplay,   main,, [
	echo "ClanLib installed, but -lclanCore not found, run 'ldconfig' and try again,"
	echo "if that doesn't help have a look at the file config.log and look into"
	echo "the FAQ."
	exit
	])


AC_CHECK_LIB( clanGL,   main,, [
	echo "ClanLib installed, but -lclanCore not found, run 'ldconfig' and try again,"
	echo "if that doesn't help have a look at the file config.log and look into"
	echo "the FAQ."
	exit
	])

AC_CHECK_LIB( clanSound,   main)

AC_CHECK_LIB( clanMikMod,   main)
AC_CHECK_LIB( clanVorbis,   main)

AC_OUTPUT( Makefile
           doc/Makefile
           data/Makefile
           data/images/Makefile
           data/images/tiles/Makefile
           data/missions/Makefile
           src/Makefile
           src/groundmap/Makefile
           src/particles/Makefile
           src/scripting/Makefile
           src/buildings/Makefile
           src/sound/Makefile
           src/generic/Makefile)

dnl Local Variables:
dnl compile-command: "./autogen.sh && ./configure"
dnl End:

dnl EOF
