#!/bin/sh

set -x

aclocal-1.7
automake-1.7 --add-missing

autoheader
autoconf

# Local Variables:
# compile-command: "./autogen.sh && ./configure"
# End:

# EOF #
