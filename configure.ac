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

dnl -------------------------
dnl Check for Maintainer Mode
dnl -------------------------
AC_MSG_CHECKING(for maintainer mode)
AC_ARG_ENABLE(maintainer-mode, AC_HELP_STRING([--enable-maintainer-mode], [Enable maintainer mode]),, enable_maintainer_mode="no")

if test "$enable_maintainer_mode" != "no"; then
    CXXFLAGS="$CXXFLAGS -g -O0 -Wall -Werror"
    AC_MSG_RESULT([enabled])
else
    AC_MSG_RESULT([disabled])
fi

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

REQUIRED_CLANLIB_VERSION="0.7.4"

PKG_CHECK_MODULES(FEUERKRAFT_DEPS,
 [
  clanCore-0.7    >= $REQUIRED_CLANLIB_VERSION
  clanApp-0.7     >= $REQUIRED_CLANLIB_VERSION
  clanDisplay-0.7 >= $REQUIRED_CLANLIB_VERSION
  clanGL-0.7      >= $REQUIRED_CLANLIB_VERSION
  clanSound-0.7   >= $REQUIRED_CLANLIB_VERSION
  clanMikMod-0.7  >= $REQUIRED_CLANLIB_VERSION
  clanVorbis-0.7  >= $REQUIRED_CLANLIB_VERSION
  ],
 [CXXFLAGS="$CXXFLAGS $FEUERKRAFT_DEPS_CFLAGS"
  LIBS="$LIBS $FEUERKRAFT_DEPS_LIBS"])

INPUT_CFLAGS=$FEUERKRAFT_CFLAGS
INPUT_LIBS=$FEUERKRAFT_LIBS
AC_SUBST(INPUT_CFLAGS)
AC_SUBST(INPUT_LIBS)

dnl FIXME: Check for optional libraries is missing
AC_DEFINE(HAVE_LIBCLANSOUND,  1, [clanSound is present])
AC_DEFINE(HAVE_LIBCLANMIKMOD, 1, [clanMikMod is present])
AC_DEFINE(HAVE_LIBCLANVORBIS, 1, [clanVorbis is present])

AC_OUTPUT( Makefile
           doc/Makefile
           data/Makefile
           data/images/Makefile
           data/images/tiles/Makefile
           data/missions/Makefile
           src/Makefile
           src/editor/Makefile
           src/groundmap/Makefile
           src/vehicles/Makefile
           src/particles/Makefile
           src/scripting/Makefile
           src/input/Makefile
           src/buildings/Makefile
           src/sound/Makefile
           src/generic/Makefile)

dnl Local Variables:
dnl compile-command: "./autogen.sh && ./configure"
dnl End:

dnl EOF
