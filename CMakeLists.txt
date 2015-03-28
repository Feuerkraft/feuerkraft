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

set(FEUERKRAFT_SOURCES
  src/editor/editor.cpp

  src/buildings/ammotent.cpp
  src/buildings/building.cpp
  src/buildings/building_manager.cpp
  src/buildings/building_map.cpp
  src/buildings/building_map_data.cpp
  src/buildings/building_type_manager.cpp
  src/buildings/custom_building.cpp
  src/buildings/fuelstation.cpp
  src/buildings/headquarter.cpp
  src/buildings/tower.cpp
  src/buildings/tower_ai.cpp
  src/buildings/wall.cpp
  src/buildings/wall_door.cpp

  src/vehicles/tank.cpp
  src/vehicles/helicopter.cpp
  src/vehicles/jeep.cpp
  src/vehicles/turret.cpp
  src/vehicles/rotor.cpp
  src/vehicles/vehicle.cpp
  src/generic/random.cpp


  src/input/axis_button.cpp
  src/input/axis_factory.cpp
  src/input/button_axis.cpp
  src/input/button_factory.cpp
  src/input/controller.cpp
  src/input/input_axis_input_device.cpp
  src/input/input_button_input_device.cpp
  src/input/input_manager.cpp
  src/input/input_manager_custom.cpp
  src/input/input_manager_impl.cpp
  src/input/input_manager_player.cpp
  src/input/input_recorder.cpp
  src/input/multi_button.cpp
  src/particles/fire_particle.cpp
  src/particles/fire_emitter.cpp
  src/particles/rocket_smoke_particle.cpp
  src/particles/smoke_emitter.cpp

  src/scripting/ai_commands.cpp
  src/scripting/ai_vehicle_commands.cpp
  src/scripting/building_commands.cpp
  src/scripting/clanlib_commands.cpp
  src/scripting/comm_commands.cpp
  src/scripting/debug_commands.cpp
  src/scripting/display_commands.cpp
  src/scripting/effect_commands.cpp
  src/scripting/game_commands.cpp
  src/scripting/gameobj_commands.cpp
  src/scripting/input_commands.cpp
  src/scripting/menu_commands.cpp
  src/scripting/object_commands.cpp
  src/scripting/player_commands.cpp
  src/scripting/script_helper.cpp
  src/scripting/sequence_commands.cpp
  src/scripting/sound_commands.cpp
  src/scripting/trigger_commands.cpp
  src/scripting/vehicle_commands.cpp

  src/sound/sound.cpp
  src/sound/sound_dummy.cpp
  src/sound/sound_real.cpp
  src/sound/sound_res_mgr.cpp

  src/groundmap/grid_map.cpp
  src/groundmap/grid_map_data.cpp
  src/groundmap/grid_tile.cpp
  src/groundmap/grid_tile_data.cpp
  src/groundmap/grid_tile_generator.cpp
  src/groundmap/ground_map_data.cpp
  src/groundmap/ground_map_data_factory.cpp
  src/groundmap/ground_type.cpp
  src/groundmap/multi_ground_map.cpp
  src/groundmap/multi_ground_map_data.cpp
  src/groundmap/sprite_tile.cpp
  src/groundmap/sprite_tile_data.cpp
  src/groundmap/tile_data_factory.cpp
  src/groundmap/tile_map.cpp
  src/groundmap/tile_map_data.cpp

  src/ai_manager.cpp
  src/ai_vehicle.cpp
  src/alist.cpp
  src/ambulance.cpp
  src/background.cpp
  src/collision_manager.cpp
  src/color.cpp
  src/command_line_arguments.cpp
  src/communication_dialog.cpp
  src/controller_def.cpp
  src/display/drawing_context.cpp
  src/display/scene_context.cpp
  src/display_manager.cpp
  src/energie.cpp
  src/explosion.cpp
  src/feuerkraft.cpp
  src/fonts.cpp
  src/game_delta.cpp
  src/game_mission.cpp
  src/game_obj.cpp
  src/game_obj_data_factory.cpp
  src/game_obj_factory.cpp
  src/game_obj_manager.cpp
  src/game_session.cpp
  src/game_session_manager.cpp
  src/game_world.cpp
  src/game_world_builder.cpp
  src/game_world_data.cpp
  src/globals.cpp
  src/goal_manager.cpp
  src/guile.cpp
  src/help.cpp
  src/ipc.cpp
  src/keyboard_manager.cpp
  src/keys.cpp
  src/level_map.cpp
  src/line_segments.cpp
  src/marker.cpp
  src/math.cpp
  src/menu.cpp
  src/menu_handle_mgr.cpp
  src/menu_item.cpp
  src/message_buffer.cpp
  src/mine.cpp
  src/output_world_builder.cpp
  src/path_manager.cpp
  src/player.cpp
  src/player_view.cpp
  src/projectile.cpp
  src/property.cpp
  src/property_set.cpp
  src/radar.cpp
  src/resource_manager.cpp
  src/robot_tank.cpp
  src/rocket.cpp
  src/satchel_charge.cpp
  src/scm_functor.cpp
  src/scm_sequence_hook.cpp
  src/screen.cpp
  src/screenshot.cpp
  src/sequence_manager.cpp
  src/sexpr_world_reader.cpp
  src/shockwave.cpp
  src/soldier.cpp
  src/soldier_ai.cpp
  src/start_screen.cpp
  src/system.cpp
  src/tree.cpp
  src/trigger_manager.cpp
  src/unit.cpp
  src/vector2d.cpp
  src/vehicle_ai.cpp
  src/vehicle_status.cpp
  src/vehicle_view.cpp
  src/view.cpp

  ${FEUERKRAFT_WRAP_GENERATED_SOURCES})

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
