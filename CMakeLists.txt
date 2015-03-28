# Feuerkraft - A Tank Battle Game
# Copyright (C) 2015 Ingo Ruhnke <grumbel@gmx.de>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.0)
project(feuerkraft VERSION 0.2.0)

set(WARNINGS 0 CACHE BOOL "Switch on extra warnings")

if(WARNINGS)
  set(WARNINGS_CXX_FLAGS
    -pedantic -Wall -Wextra -Wno-c++0x-compat -Wnon-virtual-dtor -Weffc++
    -Wconversion -Werror -Wshadow -Wcast-qual -Winit-self -Wno-unused-parameter)
  # -Winline -Wfloat-equal -Wunreachable-code
endif()

include_directories(src/)
include_directories(src/scripting/)

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GUILE REQUIRED guile-1.8)
pkg_search_module(CLANCORE REQUIRED clanCore-1.0)
pkg_search_module(CLANAPP REQUIRED clanApp-1.0)
pkg_search_module(CLANDISPLAY REQUIRED clanDisplay-1.0)
pkg_search_module(CLANGL REQUIRED clanGL-1.0)
pkg_search_module(CLANSOUND REQUIRED clanSound-1.0)
pkg_search_module(CLANMIKMOD REQUIRED clanMikMod-1.0)
pkg_search_module(CLANVORBIS REQUIRED clanVorbis-1.0)

set_source_files_properties(src/scripting/feuerkraft.i PROPERTIES CPLUSPLUS ON)
swig_add_module(feuerkraft_wrap guile src/scripting/feuerkraft.i)
set(FEUERKRAFT_WRAP_GENERATED_SOURCES ${swig_generated_file_fullname})

file(GLOB FEUERKRAFT_SOURCES
  src/*.cpp
  src/buildings/*.cpp
  src/display/*.cpp
  src/generic/*.cpp
  src/groundmap/*.cpp
  src/input/*.cpp
  src/particles/*.cpp
  src/scripting/*.cpp
  src/sound/*.cpp
  src/vehicles/*.cpp)
list(APPEND FEUERKRAFT_SOURCES ${FEUERKRAFT_WRAP_GENERATED_SOURCES})

add_executable(feuerkraft ${FEUERKRAFT_SOURCES})
target_link_libraries(feuerkraft PRIVATE
  ${GUILE_LIBRARIES}
  ${CLANCORE_LIBRARIES}
  ${CLANAPP_LIBRARIES}
  ${CLANDISPLAY_LIBRARIES}
  ${CLANGL_LIBRARIES}
  ${CLANSOUND_LIBRARIES}
  ${CLANMIKMOD_LIBRARIES}
  ${CLANVORBIS_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(feuerkraft PRIVATE
  ${GUILE_INCLUDE_DIRS}
  ${CLANCORE_INCLUDE_DIRS}
  ${CLANAPP_INCLUDE_DIRS}
  ${CLANDISPLAY_INCLUDE_DIRS}
  ${CLANGL_INCLUDE_DIRS}
  ${CLANSOUND_INCLUDE_DIRS}
  ${CLANMIKMOD_INCLUDE_DIRS}
  ${CLANVORBIS_INCLUDE_DIRS})

# EOF #
