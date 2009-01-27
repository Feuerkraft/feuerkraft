SUBDIRS = editor groundmap input particles generic buildings scripting sound vehicles

bindir=$(prefix)/games

bin_PROGRAMS = feuerkraft

LDADD = \
 scripting/libfeuerkraft_scripting.a \
 editor/libfeuerkraft_editor.a \
 groundmap/libfeuerkraft_groundmap.a \
 buildings/libfeuerkraft_buildings.a \
 vehicles/libfeuerkraft_vehicles.a \
 generic/libfeuerkraft_generic.a     \
 input/libfeuerkraft_input.a     \
 particles/libfeuerkraft_particles.a \
 sound/libpingus_sound.a

feuerkraft_SOURCES = \
display/drawing_context.cpp \
display/scene_context.cpp \
alist.hpp \
alist.cpp \
ai_vehicle.hpp \
ai_vehicle.cpp \
ai_manager.hpp \
ai_manager.cpp \
ambulance.cpp \
ambulance.hpp \
background.cpp \
background.hpp \
command_line_arguments.hpp \
command_line_arguments.cpp \
color.hpp \
color.cpp \
controller_def.cpp \
controller_def.hpp \
communication_dialog.hpp \
communication_dialog.cpp \
collision_manager.hpp \
collision_manager.cpp \
display_manager.hpp \
display_manager.cpp \
energie.cpp \
energie.hpp \
explosion.cpp \
explosion.hpp \
feuerkraft.cpp \
feuerkraft.hpp \
feuerkraft_error.hpp \
field.hpp \
fonts.hpp \
fonts.cpp \
game_delta.cpp \
game_delta.hpp \
game_mission.cpp \
game_mission.hpp \
game_obj.hpp \
game_obj.cpp \
game_session.hpp \
game_session.cpp \
game_session_manager.hpp \
game_session_manager.cpp \
game_obj_manager.hpp \
game_obj_manager.cpp \
game_obj_data.hpp \
game_obj_factory.cpp \
game_obj_factory.hpp \
game_obj_data_factory.cpp \
game_obj_data_factory.hpp \
help.hpp \
help.cpp \
ipc.cpp \
ipc.hpp \
keys.hpp \
keys.cpp \
world_builder.hpp \
game_world_builder.cpp \
game_world_builder.hpp \
game_world.cpp \
game_world.hpp \
game_world_data.cpp \
game_world_data.hpp \
goal_manager.hpp \
goal_manager.cpp \
gui_obj.hpp \
guile.cpp \
guile.hpp \
keyboard_manager.hpp \
keyboard_manager.cpp \
level_map.cpp \
level_map.hpp \
line_segments.hpp \
line_segments.cpp \
marker.hpp \
marker.cpp \
math.hpp \
math.cpp \
message_buffer.hpp \
message_buffer.cpp \
menu.hpp \
menu.cpp \
menu_item.hpp \
menu_item.cpp \
menu_handle_mgr.hpp \
menu_handle_mgr.cpp \
handle_manager.hpp \
mine.cpp \
mine.hpp \
path_manager.cpp \
path_manager.hpp \
player.hpp \
player.cpp \
player_view.hpp \
player_view.cpp \
output_world_builder.hpp \
output_world_builder.cpp \
property.hpp \
property.cpp \
property_set.hpp \
property_set.cpp \
projectile.cpp \
projectile.hpp \
radar.cpp \
radar.hpp \
robot_tank.hpp \
robot_tank.cpp \
rocket.hpp \
rocket.cpp \
resource_manager.cpp \
resource_manager.hpp \
satchel_charge.hpp \
satchel_charge.cpp \
screen.cpp \
screen.hpp \
screenshot.hpp \
screenshot.cpp \
scm_functor.hpp \
scm_functor.cpp \
scm_sequence_hook.hpp \
scm_sequence_hook.cpp \
sequence_manager.hpp \
sequence_manager.cpp \
shockwave.cpp \
shockwave.hpp \
sexpr_world_reader.hpp \
sexpr_world_reader.cpp \
soldier.cpp \
soldier.hpp \
soldier_ai.cpp \
soldier_ai.hpp \
start_screen.cpp \
start_screen.hpp \
globals.hpp \
globals.cpp \
system.cpp \
system.hpp \
trigger_manager.hpp \
trigger_manager.cpp \
tree.cpp \
tree.hpp \
unit.hpp \
unit.cpp \
vector2d.hpp \
vector2d.cpp \
vehicle_ai.cpp \
vehicle_ai.hpp \
vehicle_status.cpp \
vehicle_status.hpp \
vehicle_view.cpp \
vehicle_view.hpp \
view.cpp \
view.hpp \
view_plugin.hpp \
view_properties.hpp \
z_pos_layers.hpp

STATIC_READLINE=
#STATIC_READLINE=-lguilereadline-v-12 -lreadline -lncurses

STATICBIN_LIBS = \
-L/usr/X11R6/lib/ \
-Wl,-Bstatic \
-lclanApp \
-lclanVorbis \
-lclanMikMod \
-lclanSound \
-lclanGL \
-lclanDisplay \
-lclanCore \
-lguile \
-lguile-ltdl \
$(STATIC_READLINE) \
-lqthreads \
-lcrypt \
-lHermes \
-lvorbis \
-logg \
-lmikmod \
-ljpeg \
-lpng12 \
-lz \
-lm \
-lX11 \
-lXxf86vm \
-lSM \
-lXt \
-lXext \
-lGLU \
-ldl \
-lX11 \
-lstdc++ \
-lgcc_eh \
-lgcc \
-Wl,-Bdynamic \
-lGL \
-lc

feuerkraft.static: $(feuerkraft_OBJECTS) $(feuerkraft_DEPENDENCIES) Makefile
	$(CXX) -nodefaultlibs $(CXXFLAGS)  -o $@ $(feuerkraft_OBJECTS) \
         $(feuerkraft_DEPENDENCIES) $(STATICBIN_LIBS) 

feuerkraft.static.comp: feuerkraft.static
	cp $< $@
	strip -s $@
	upx-ucl -q --best $@

docs:
	$(MAKE) -C ../doc/ docs

BROWSE:
	TMPFILE=`tempfile`; \
	find ./ -name "*.?pp" | sed "s/.\///" | grep -v "old/" | grep -v "feuerkraft_wrap.cpp" | \
          sort -t . -k 2 -r > $$TMPFILE; \
	ebrowse --files=$$TMPFILE; rm -v $$TMPFILE

.PHONY: BROWSE

# EOF #
