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
alist.hxx \
alist.cxx \
ai_vehicle.hxx \
ai_vehicle.cxx \
ai_manager.hxx \
ai_manager.cxx \
ambulance.cxx \
ambulance.hxx \
background.cxx \
background.hxx \
command_line_arguments.hxx \
command_line_arguments.cxx \
color.hxx \
color.cxx \
communication_dialog.hxx \
communication_dialog.cxx \
collision_manager.hxx \
collision_manager.cxx \
display_manager.hxx \
display_manager.cxx \
energie.cxx \
energie.hxx \
explosion.cxx \
explosion.hxx \
feuerkraft.cxx \
feuerkraft.hxx \
field.hxx \
fonts.hxx \
fonts.cxx \
game_delta.cxx \
game_delta.hxx \
game_mission.cxx \
game_mission.hxx \
game_obj.hxx \
game_obj.cxx \
game_session.hxx \
game_session.cxx \
game_session_manager.hxx \
game_session_manager.cxx \
game_obj_manager.hxx \
game_obj_manager.cxx \
game_obj_data.hxx \
game_obj_factory.cxx \
game_obj_factory.hxx \
game_obj_data_factory.cxx \
game_obj_data_factory.hxx \
help.hxx \
help.cxx \
ipc.cxx \
ipc.hxx \
keys.hxx \
keys.cxx \
world_builder.hxx \
game_world_builder.cxx \
game_world_builder.hxx \
game_world.cxx \
game_world.hxx \
game_world_data.cxx \
game_world_data.hxx \
goal_manager.hxx \
goal_manager.cxx \
gui_obj.hxx \
guile.cxx \
guile.hxx \
keyboard_manager.hxx \
keyboard_manager.cxx \
level_map.cxx \
level_map.hxx \
line_segments.hxx \
line_segments.cxx \
marker.hxx \
marker.cxx \
math.hxx \
math.cxx \
message_buffer.hxx \
message_buffer.cxx \
menu.hxx \
menu.cxx \
menu_item.hxx \
menu_item.cxx \
menu_handle_mgr.hxx \
menu_handle_mgr.cxx \
handle_manager.hxx \
mine.cxx \
mine.hxx \
path_manager.cxx \
path_manager.hxx \
player.hxx \
player.cxx \
player_view.hxx \
player_view.cxx \
output_world_builder.hxx \
output_world_builder.cxx \
property.hxx \
property.cxx \
property_set.hxx \
property_set.cxx \
projectile.cxx \
projectile.hxx \
radar.cxx \
radar.hxx \
robot_tank.hxx \
robot_tank.cxx \
rocket.hxx \
rocket.cxx \
resource_manager.cxx \
resource_manager.hxx \
satchel_charge.hxx \
satchel_charge.cxx \
screen.cxx \
screen.hxx \
screenshot.hxx \
screenshot.cxx \
scm_functor.hxx \
scm_functor.cxx \
scm_sequence_hook.hxx \
scm_sequence_hook.cxx \
sequence_manager.hxx \
sequence_manager.cxx \
shockwave.cxx \
shockwave.hxx \
sexpr_world_reader.hxx \
sexpr_world_reader.cxx \
soldier.cxx \
soldier.hxx \
soldier_ai.cxx \
soldier_ai.hxx \
start_screen.cxx \
start_screen.hxx \
globals.hxx \
globals.cxx \
string_converter.cxx \
string_converter.hxx \
system.cxx \
system.hxx \
trigger_manager.hxx \
trigger_manager.cxx \
tree.cxx \
tree.hxx \
unit.hxx \
unit.cxx \
vector2d.hxx \
vector2d.cxx \
vehicle_ai.cxx \
vehicle_ai.hxx \
vehicle_status.cxx \
vehicle_status.hxx \
vehicle_view.cxx \
vehicle_view.hxx \
view.cxx \
view.hxx \
view_plugin.hxx \
view_properties.hxx \
z_pos_layers.hxx

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
	find ./ -name "*.?xx" | sed "s/.\///" | grep -v "old/" | grep -v "feuerkraft_wrap.cxx" | \
          sort -t . -k 2 -r > $$TMPFILE; \
	ebrowse --files=$$TMPFILE; rm -v $$TMPFILE

.PHONY: BROWSE

# EOF #
