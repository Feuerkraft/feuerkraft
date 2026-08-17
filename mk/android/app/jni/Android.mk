LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../SDL/include \
	$(LOCAL_PATH)/../SDL/include/SDL2 \
	$(LOCAL_PATH) \
	$(LOCAL_PATH)/buildings \
	$(LOCAL_PATH)/display \
	$(LOCAL_PATH)/generic \
	$(LOCAL_PATH)/groundmap \
	$(LOCAL_PATH)/input \
	$(LOCAL_PATH)/particles \
	$(LOCAL_PATH)/scripting \
	$(LOCAL_PATH)/sound \
	$(LOCAL_PATH)/vehicles \
	$(LOCAL_PATH)/../s7

LOCAL_SRC_FILES := \
	ai_manager.cpp \
	ai_vehicle.cpp \
	alist.cpp \
	ambulance.cpp \
	background.cpp \
	buildings/ammotent.cpp \
	buildings/building.cpp \
	buildings/building_manager.cpp \
	buildings/building_map.cpp \
	buildings/building_map_data.cpp \
	buildings/building_type_manager.cpp \
	buildings/custom_building.cpp \
	buildings/fuelstation.cpp \
	buildings/headquarter.cpp \
	buildings/tower.cpp \
	buildings/tower_ai.cpp \
	buildings/wall.cpp \
	buildings/wall_door.cpp \
	collision_manager.cpp \
	color.cpp \
	command_line_arguments.cpp \
	communication_dialog.cpp \
	controller_def.cpp \
	display/drawing_context.cpp \
	display/scene_context.cpp \
	display.cpp \
	display_manager.cpp \
	energie.cpp \
	explosion.cpp \
	feuerkraft.cpp \
	fonts.cpp \
	game_delta.cpp \
	game_mission.cpp \
	game_obj.cpp \
	game_obj_data_factory.cpp \
	game_obj_factory.cpp \
	game_obj_manager.cpp \
	game_session.cpp \
	game_session_manager.cpp \
	game_world.cpp \
	game_world_builder.cpp \
	game_world_data.cpp \
	generic/random.cpp \
	globals.cpp \
	goal_manager.cpp \
	groundmap/grid_map.cpp \
	groundmap/grid_map_data.cpp \
	groundmap/grid_tile.cpp \
	groundmap/grid_tile_data.cpp \
	groundmap/grid_tile_generator.cpp \
	groundmap/ground_map_data.cpp \
	groundmap/ground_map_data_factory.cpp \
	groundmap/ground_type.cpp \
	groundmap/multi_ground_map.cpp \
	groundmap/multi_ground_map_data.cpp \
	groundmap/sprite_tile.cpp \
	groundmap/sprite_tile_data.cpp \
	groundmap/tile_data_factory.cpp \
	groundmap/tile_map.cpp \
	groundmap/tile_map_data.cpp \
	guile.cpp \
	help.cpp \
	input/axis_button.cpp \
	input/axis_factory.cpp \
	input/button_axis.cpp \
	input/button_factory.cpp \
	input/controller.cpp \
	input/game_controllers.cpp \
	input/input_axis_input_device.cpp \
	input/input_button_game_controller.cpp \
	input/input_button_input_device.cpp \
	input/input_manager.cpp \
	input/input_manager_custom.cpp \
	input/input_manager_impl.cpp \
	input/input_manager_player.cpp \
	input/input_recorder.cpp \
	input/multi_button.cpp \
	ipc.cpp \
	keyboard_manager.cpp \
	keys.cpp \
	level_map.cpp \
	line_segments.cpp \
	marker.cpp \
	math.cpp \
	menu.cpp \
	menu_handle_mgr.cpp \
	menu_item.cpp \
	message_buffer.cpp \
	mine.cpp \
	output_world_builder.cpp \
	particles/fire_emitter.cpp \
	particles/fire_particle.cpp \
	particles/rocket_smoke_particle.cpp \
	particles/smoke_emitter.cpp \
	path_manager.cpp \
	player.cpp \
	player_view.cpp \
	projectile.cpp \
	property.cpp \
	property_set.cpp \
	radar.cpp \
	resource_manager.cpp \
	robot_tank.cpp \
	rocket.cpp \
	satchel_charge.cpp \
	scheme.cpp \
	scm_functor.cpp \
	scm_sequence_hook.cpp \
	screen.cpp \
	screenshot.cpp \
	scripting/ai_commands.cpp \
	scripting/ai_vehicle_commands.cpp \
	scripting/building_commands.cpp \
	scripting/clanlib_commands.cpp \
	scripting/comm_commands.cpp \
	scripting/debug_commands.cpp \
	scripting/display_commands.cpp \
	scripting/effect_commands.cpp \
	scripting/game_commands.cpp \
	scripting/gameobj_commands.cpp \
	scripting/input_commands.cpp \
	scripting/menu_commands.cpp \
	scripting/object_commands.cpp \
	scripting/player_commands.cpp \
	scripting/script_helper.cpp \
	scripting/sequence_commands.cpp \
	scripting/sound_commands.cpp \
	scripting/trigger_commands.cpp \
	scripting/vehicle_commands.cpp \
	sequence_manager.cpp \
	sexpr_world_reader.cpp \
	shockwave.cpp \
	soldier.cpp \
	soldier_ai.cpp \
	sound/sound.cpp \
	sound/sound_dummy.cpp \
	sound/sound_real.cpp \
	sound/sound_res_mgr.cpp \
	sprite.cpp \
	start_screen.cpp \
	system.cpp \
	tree.cpp \
	trigger_manager.cpp \
	unit.cpp \
	vector2d.cpp \
	vehicle_ai.cpp \
	vehicle_status.cpp \
	vehicle_view.cpp \
	vehicles/helicopter.cpp \
	vehicles/jeep.cpp \
	vehicles/rotor.cpp \
	vehicles/tank.cpp \
	vehicles/turret.cpp \
	vehicles/vehicle.cpp \
	view.cpp \
	../s7/s7.c \
	img_stb_min.c

# SDL2 (+ optional mixer) prebuilt by nix/android.nix
FEUERKRAFT_ENABLE_SOUND ?= 1
ifeq ($(FEUERKRAFT_ENABLE_SOUND),1)
# Images via stb (img_stb_min.c + SDL_image.h shim); no libSDL2_image.so
LOCAL_SHARED_LIBRARIES := SDL2 SDL2_mixer
else
LOCAL_CFLAGS += -DNOSOUND
LOCAL_CPPFLAGS += -DNOSOUND
LOCAL_SHARED_LIBRARIES := SDL2
endif

LOCAL_LDLIBS := -llog -landroid -lz -lGLESv2

LOCAL_CFLAGS += -DUSE_SDL2 -D__ANDROID__ -DFEUERKRAFT_DATADIR=\".\" -std=c11
LOCAL_CPPFLAGS += -DUSE_SDL2 -D__ANDROID__ -DFEUERKRAFT_DATADIR=\".\" -std=c++17
ifndef FEUERKRAFT_VERSION
FEUERKRAFT_VERSION := 0.2.0-dev
endif
LOCAL_CFLAGS += -DFEUERKRAFT_VERSION=\"$(FEUERKRAFT_VERSION)\"
LOCAL_CPPFLAGS += -DFEUERKRAFT_VERSION=\"$(FEUERKRAFT_VERSION)\"

LOCAL_CPP_FEATURES := exceptions rtti

include $(BUILD_SHARED_LIBRARY)

