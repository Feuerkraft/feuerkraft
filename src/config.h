#ifndef FEUERKRAFT_CONFIG_H
#define FEUERKRAFT_CONFIG_H

/* FEUERKRAFT_VERSION and PACKAGE_STRING are normally injected by CMake
   (-DFEUERKRAFT_VERSION=... -DPACKAGE_STRING=...). Fallbacks for non-CMake
   builds only. */
#ifndef FEUERKRAFT_VERSION
#  define FEUERKRAFT_VERSION "0.2.0-dev"
#endif

#ifndef PACKAGE_STRING
#  define PACKAGE_STRING "Feuerkraft " FEUERKRAFT_VERSION
#endif

/* FEUERKRAFT_DATADIR is normally injected by CMake (-DFEUERKRAFT_DATADIR=...).
   Uncomment a default here only for non-CMake builds. */
/* #define FEUERKRAFT_DATADIR "/usr/local/share/feuerkraft" */

#endif
