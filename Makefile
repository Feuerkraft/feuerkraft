##  Feuerkraft - A tank battle game
##  Copyright (C) 2010 Ingo Ruhnke <grumbel@gmail.com>
##
##  This program is free software: you can redistribute it and/or modify
##  it under the terms of the GNU General Public License as published by
##  the Free Software Foundation, either version 3 of the License, or
##  (at your option) any later version.
##  
##  This program is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##  GNU General Public License for more details.
##  
##  You should have received a copy of the GNU General Public License
##  along with this program.  If not, see <http://www.gnu.org/licenses/>.

DESTDIR = 
PREFIX  = "/usr/local"
DATADIR = "${PREFIX}/share/feuerkraft"
BINDIR  = "${PREFIX}/bin"

build/feuerkraft:
	scons

clean:
	scons -c
	rm -rf .sconf_temp/
	rm -f .sconsign.dblite

install: install-exec install-data

install-exec: build/feuerkraft
	install -D feuerkraft "${DESTDIR}${BINDIR}/feuerkraft"

install-data:
	cd data/; \
	find -type f \( \
	-name "*.feu" -o \
	-name "*.jpg" -o \
	-name "*.png" -o \
	-name "*.scm" -o \
	-name "*.scr" -o \
	-name "*.tga" -o \
	-name "*.wav" -o \
	-name "*.xml" \) \
	-exec install -D {} ${DESTDIR}${DATADIR}/{} \;

.PHONY : clean install install-exec install-data

# EOF #
