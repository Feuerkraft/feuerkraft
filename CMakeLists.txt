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
project(feuerkraft VERSION 0.2.0)

cmake_policy(SET CMP0078 OLD) # Swig
cmake_policy(SET CMP0086 OLD) # Swig

option(WARNINGS "Switch on extra warnings" OFF)
option(WERROR "Treat all warnings as errors" OFF)
option(BUILD_TESTS "Build test cases" OFF)

include(GNUInstallDirs)

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

find_package(Git)
if(GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git")
  execute_process(COMMAND ${GIT_EXECUTABLE} describe --tags --always HEAD
    OUTPUT_VARIABLE GIT_REPO_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE)

  execute_process(COMMAND ${GIT_EXECUTABLE} log -n 1 --pretty=%cd --date=format:%Y-%m-%d ${GIT_REPO_VERSION}
    OUTPUT_VARIABLE GIT_REPO_DATE
    OUTPUT_STRIP_TRAILING_WHITESPACE)
else()
  set(GIT_REPO_VERSION "${PROJECT_VERSION}")
  string(TIMESTAMP GIT_REPO_DATE "%Y-%m-%d")
endif()

include_directories(src/)
include_directories(src/scripting/)

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GUILE REQUIRED guile-2.2)
pkg_search_module(CLANCORE REQUIRED clanCore-1.0)
pkg_search_module(CLANAPP REQUIRED clanApp-1.0)
pkg_search_module(CLANDISPLAY REQUIRED clanDisplay-1.0)
pkg_search_module(CLANGL REQUIRED clanGL-1.0)
pkg_search_module(CLANSOUND REQUIRED clanSound-1.0)
pkg_search_module(CLANMIKMOD REQUIRED clanMikMod-1.0)
pkg_search_module(CLANVORBIS REQUIRED clanVorbis-1.0)

include_directories(${GUILE_INCLUDE_DIRS})
set_source_files_properties(src/scripting/feuerkraft.i PROPERTIES CPLUSPLUS ON)
swig_add_library(feuerkraft_wrap LANGUAGE guile SOURCES src/scripting/feuerkraft.i)
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

add_library(libfeuerkraft_scripting STATIC
  ${FEUERKRAFT_WRAP_GENERATED_SOURCES})

add_executable(feuerkraft ${FEUERKRAFT_SOURCES})
target_compile_options(feuerkraft PRIVATE ${WARNINGS_CXX_FLAGS})
target_link_libraries(feuerkraft PRIVATE
  libfeuerkraft_scripting
  ${GUILE_LIBRARIES}
  ${CLANCORE_LIBRARIES}
  ${CLANAPP_LIBRARIES}
  ${CLANDISPLAY_LIBRARIES}
  ${CLANGL_LIBRARIES}
  ${CLANSOUND_LIBRARIES}
  ${CLANMIKMOD_LIBRARIES}
  ${CLANVORBIS_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(feuerkraft SYSTEM PRIVATE
  ${GUILE_INCLUDE_DIRS}
  ${CLANCORE_INCLUDE_DIRS}
  ${CLANAPP_INCLUDE_DIRS}
  ${CLANDISPLAY_INCLUDE_DIRS}
  ${CLANGL_INCLUDE_DIRS}
  ${CLANSOUND_INCLUDE_DIRS}
  ${CLANMIKMOD_INCLUDE_DIRS}
  ${CLANVORBIS_INCLUDE_DIRS})

install(TARGETS feuerkraft RUNTIME
  DESTINATION ${CMAKE_INSTALL_LIBEXECDIR})

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/feuerkraft.sh.in
  ${CMAKE_BINARY_DIR}/feuerkraft.sh)

install(FILES
  ${CMAKE_BINARY_DIR}/feuerkraft.sh
  RENAME feuerkraft
  PERMISSIONS OWNER_EXECUTE OWNER_READ OWNER_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data/
  DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME})

install(FILES
  feuerkraft.svg
  DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps)

install(FILES
  feuerkraft.desktop
  DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)

configure_file(feuerkraft.appdata.xml.in ${CMAKE_CURRENT_BINARY_DIR}/feuerkraft.appdata.xml)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/feuerkraft.appdata.xml
  DESTINATION ${CMAKE_INSTALL_DATADIR}/metainfo)

if (BUILD_TESTS)
  add_test(NAME feuerkraft.appdata.xml
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND appstream-util validate-relax ${CMAKE_CURRENT_BINARY_DIR}/feuerkraft.appdata.xml)
endif(BUILD_TESTS)

# EOF #
