# Feuerkraft - A Tank Battle Game
# Copyright (C) 2015-2019 Ingo Ruhnke <grumbel@gmail.com>
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

cmake_minimum_required(VERSION 3.13)

# Source of truth: top-level VERSION file (e.g. "0.2.0-dev"), or
# -DPROJECT_VERSION_FULL=... from the packaging (Nix flake appends
# .<revCount>+g<rev>).
if(NOT DEFINED PROJECT_VERSION_FULL)
  file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" PROJECT_VERSION_FULL LIMIT_COUNT 1)
endif()

# project() expects a numeric-ish version; strip any -dev / +git suffix for it.
string(REGEX REPLACE "^([0-9]+(\\.[0-9]+)*)(.*)$" "\\1" PROJECT_VERSION_BASE "${PROJECT_VERSION_FULL}")
if(PROJECT_VERSION_BASE STREQUAL "")
  set(PROJECT_VERSION_BASE "0.0.0")
endif()

project(feuerkraft VERSION ${PROJECT_VERSION_BASE})

cmake_policy(SET CMP0078 OLD) # Swig
cmake_policy(SET CMP0086 OLD) # Swig

option(WARNINGS "Switch on extra warnings" OFF)
option(WERROR "Treat all warnings as errors" OFF)
option(BUILD_TESTS "Build test cases" OFF)

include(GNUInstallDirs)

# Compiled-in data directory (overridable with -DFEUERKRAFT_DATADIR=...)
if(NOT DEFINED FEUERKRAFT_DATADIR)
  set(FEUERKRAFT_DATADIR "${CMAKE_INSTALL_FULL_DATADIR}/${PROJECT_NAME}")
endif()
message(STATUS "FEUERKRAFT_DATADIR=${FEUERKRAFT_DATADIR}")
message(STATUS "PROJECT_VERSION_FULL=${PROJECT_VERSION_FULL}")

if(WARNINGS)
  set(WARNINGS_CXX_FLAGS
    -pedantic
    -Wall
    -Wextra
    -Wno-c++0x-compat
    -Wnon-virtual-dtor
    -Wcast-qual
    -Winit-self
    -Wno-unused-parameter
    -Winline
    # -Wshadow
    # -Weffc++
    # -Wconversion
    # -Wfloat-equal
    # -Wunreachable-code
    )
endif()

if(WERROR)
  set(WARNINGS_CXX_FLAGS ${WARNINGS_CXX_FLAGS}
    -Werror)
endif()

if (BUILD_TESTS)
  # add 'make test' target, use 'make test ARGS="-V"' or 'ctest -V' for verbose
  enable_testing()
endif(BUILD_TESTS)

include_directories(src/)
include_directories(src/scripting/)
include_directories(external/s7)

# Vendored s7 Scheme (ANSI C)
add_library(s7 STATIC external/s7/s7.c)
set_target_properties(s7 PROPERTIES C_STANDARD 11)
target_include_directories(s7 PUBLIC external/s7)


find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)

# SDL2 (destructive port away from ClanLib 1.0)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)
pkg_search_module(SDL2_MIXER REQUIRED SDL2_mixer)

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

add_executable(feuerkraft ${FEUERKRAFT_SOURCES})
target_compile_options(feuerkraft PRIVATE ${WARNINGS_CXX_FLAGS})
target_compile_definitions(feuerkraft PRIVATE
  FEUERKRAFT_DATADIR="${FEUERKRAFT_DATADIR}"
  FEUERKRAFT_VERSION="${PROJECT_VERSION_FULL}"
  PACKAGE_STRING="Feuerkraft ${PROJECT_VERSION_FULL}")
target_link_libraries(feuerkraft PRIVATE
  s7
  ${SDL2_LIBRARIES}
  ${SDL2_IMAGE_LIBRARIES}
  ${SDL2_MIXER_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
  m)
target_include_directories(feuerkraft SYSTEM PRIVATE
  ${SDL2_INCLUDE_DIRS}
  ${SDL2_IMAGE_INCLUDE_DIRS}
  ${SDL2_MIXER_INCLUDE_DIRS})

# Binary goes to bindir; data path is compiled in as FEUERKRAFT_DATADIR
install(TARGETS feuerkraft
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data/
  DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME})

install(FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/feuerkraft.svg
  DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps
  RENAME feuerkraft.svg)

install(FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/feuerkraft.desktop
  DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)

# EOF #
