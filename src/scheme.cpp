// Feuerkraft - A Tank Battle Game
// Copyright (C) 2026 Ingo Ruhnke <grumbel@gmail.com>
//
// s7 VM lifetime and scripting primitive registration.

#include "scheme_compat.hpp"

#include "scripting/ai_commands.hpp"
#include "scripting/ai_vehicle_commands.hpp"
#include "scripting/building_commands.hpp"
#include "scripting/clanlib_commands.hpp"
#include "scripting/comm_commands.hpp"
#include "scripting/debug_commands.hpp"
#include "scripting/display_commands.hpp"
#include "scripting/effect_commands.hpp"
#include "scripting/game_commands.hpp"
#include "scripting/gameobj_commands.hpp"
#include "scripting/input_commands.hpp"
#include "scripting/menu_commands.hpp"
#include "scripting/object_commands.hpp"
#include "scripting/player_commands.hpp"
#include "scripting/sequence_commands.hpp"
#include "scripting/sound_commands.hpp"
#include "scripting/trigger_commands.hpp"
#include "scripting/vehicle_commands.hpp"

s7_scheme* fk_s7 = nullptr;

namespace Scheme {

s7_scheme*
create_vm()
{
  return s7_init();
}

void
destroy_vm(s7_scheme* sc)
{
  if (!sc)
    return;
  if (fk_s7 == sc)
    fk_s7 = nullptr;
  s7_free(sc);
}

void
set_current(s7_scheme* sc)
{
  fk_s7 = sc;
}

void
init()
{
  if (!fk_s7)
    fk_s7 = s7_init();
  s7_define_variable(fk_s7, "*fk-protect*", s7_nil(fk_s7));
  register_bindings();
}

void
deinit()
{
  if (fk_s7)
    {
      s7_free(fk_s7);
      fk_s7 = nullptr;
    }
}

/* Helper macros to cut down wrapper boilerplate. */
#define ARG0()
#define ARG1() s7_car(args)
#define ARG2() s7_cadr(args)
#define ARG3() s7_caddr(args)
#define ARG4() s7_cadddr(args)

static s7_pointer arg_nth(s7_pointer args, int n)
{
  while (n-- > 0 && s7_is_pair(args))
    args = s7_cdr(args);
  return s7_is_pair(args) ? s7_car(args) : s7_nil(fk_s7);
}

/* ---- game ---------------------------------------------------------- */
static s7_pointer g_game_pause(s7_scheme* sc, s7_pointer) { game_pause(); return s7_t(sc); }
static s7_pointer g_game_quit(s7_scheme* sc, s7_pointer)  { game_quit();  return s7_t(sc); }
static s7_pointer g_game_load(s7_scheme* sc, s7_pointer args)
{
  if (s7_is_string(ARG1())) game_load(s7_string(ARG1()));
  return s7_t(sc);
}
static s7_pointer g_game_save(s7_scheme* sc, s7_pointer args)
{
  if (s7_is_string(ARG1())) game_save(s7_string(ARG1()));
  return s7_t(sc);
}

/* ---- ai ------------------------------------------------------------ */
static s7_pointer g_ai_goto(s7_scheme* sc, s7_pointer args)
{
  ai_goto((int)s7_integer(ARG1()), (float)s7_number_to_real(sc, ARG2()),
          (float)s7_number_to_real(sc, ARG3()));
  return s7_t(sc);
}
static s7_pointer g_ai_stop(s7_scheme* sc, s7_pointer args)
{ ai_stop((int)s7_integer(ARG1())); return s7_t(sc); }
static s7_pointer g_ai_has(s7_scheme* sc, s7_pointer args)
{ return ai_has((int)s7_integer(ARG1())) ? s7_t(sc) : s7_f(sc); }
static s7_pointer g_ai_attach(s7_scheme* sc, s7_pointer args)
{ ai_attach((int)s7_integer(ARG1())); return s7_t(sc); }
static s7_pointer g_ai_dettach(s7_scheme* sc, s7_pointer args)
{ ai_dettach((int)s7_integer(ARG1())); return s7_t(sc); }

/* ---- ai vehicle ---------------------------------------------------- */
static s7_pointer g_ai_vehicle_create(s7_scheme* sc, s7_pointer args)
{ return s7_make_integer(sc, ai_vehicle_create((int)s7_integer(ARG1()), (int)s7_integer(ARG2()))); }
static s7_pointer g_ai_vehicle_wait(s7_scheme* sc, s7_pointer args)
{ ai_vehicle_wait((int)s7_integer(ARG1()), (float)s7_number_to_real(sc, ARG2())); return s7_t(sc); }
static s7_pointer g_ai_vehicle_drive_to(s7_scheme* sc, s7_pointer args)
{ ai_vehicle_drive_to((int)s7_integer(ARG1()), (int)s7_integer(ARG2()), (int)s7_integer(ARG3())); return s7_t(sc); }
static s7_pointer g_ai_vehicle_clear_orders(s7_scheme* sc, s7_pointer args)
{ ai_vehicle_clear_orders((int)s7_integer(ARG1())); return s7_t(sc); }

/* ---- building ------------------------------------------------------ */
static s7_pointer g_building_create(s7_scheme* sc, s7_pointer args)
{ return s7_make_integer(sc, building_create((int)s7_integer(ARG1()), (int)s7_integer(ARG2()), (int)s7_integer(ARG3()))); }
static s7_pointer g_building_get_property(s7_scheme* sc, s7_pointer args)
{ return building_get_property((int)s7_integer(ARG1()), s7_string(ARG2())); }
static s7_pointer g_building_set_property(s7_scheme* sc, s7_pointer args)
{ building_set_property((int)s7_integer(ARG1()), s7_string(ARG2()), ARG3()); return s7_t(sc); }
static s7_pointer g_building_remove(s7_scheme* sc, s7_pointer args)
{ building_remove((int)s7_integer(ARG1())); return s7_t(sc); }
static s7_pointer g_building_get_tile(s7_scheme* sc, s7_pointer args)
{ return s7_make_integer(sc, building_get_tile((int)s7_integer(ARG1()), (int)s7_integer(ARG2()))); }
static s7_pointer g_building_get(s7_scheme* sc, s7_pointer args)
{ return s7_make_integer(sc, building_get((int)s7_integer(ARG1()), (int)s7_integer(ARG2()))); }
static s7_pointer g_building_create_type(s7_scheme* sc, s7_pointer args)
{ return s7_make_integer(sc, building_create_type(s7_string(ARG1()), ARG2())); }
static s7_pointer g_building_get_type_from_name(s7_scheme* sc, s7_pointer args)
{ return s7_make_integer(sc, building_get_type_from_name(s7_string(ARG1()))); }

/* ---- comm ---------------------------------------------------------- */
static s7_pointer g_comm_send_message(s7_scheme* sc, s7_pointer args)
{ if (s7_is_string(ARG2())) comm_send_message((int)s7_integer(ARG1()), s7_string(ARG2())); return s7_t(sc); }
static s7_pointer g_comm_unit_message(s7_scheme* sc, s7_pointer args)
{ if (s7_is_string(ARG2())) comm_unit_message((int)s7_integer(ARG1()), s7_string(ARG2())); return s7_t(sc); }

/* ---- debug --------------------------------------------------------- */
static s7_pointer g_debug_set_flag(s7_scheme* sc, s7_pointer args)
{ debug_set_flag(s7_string(ARG1()), s7_boolean(sc, ARG2())); return s7_t(sc); }
static s7_pointer g_debug_get_flag(s7_scheme* sc, s7_pointer args)
{ return debug_get_flag(s7_string(ARG1())) ? s7_t(sc) : s7_f(sc); }

/* ---- display ------------------------------------------------------- */
static s7_pointer g_display_levelmap_visible(s7_scheme* sc, s7_pointer)
{ return display_levelmap_visible() ? s7_t(sc) : s7_f(sc); }
static s7_pointer g_display_show_levelmap(s7_scheme* sc, s7_pointer)
{ display_show_levelmap(); return s7_t(sc); }
static s7_pointer g_display_hide_levelmap(s7_scheme* sc, s7_pointer)
{ display_hide_levelmap(); return s7_t(sc); }
static s7_pointer g_display_show_help(s7_scheme* sc, s7_pointer)
{ display_show_help(); return s7_t(sc); }
static s7_pointer g_display_hide_help(s7_scheme* sc, s7_pointer)
{ display_hide_help(); return s7_t(sc); }

/* ---- effect -------------------------------------------------------- */
static s7_pointer g_effect_add_explosion(s7_scheme* sc, s7_pointer args)
{ effect_add_explosion((int)s7_integer(ARG1()), (int)s7_integer(ARG2())); return s7_t(sc); }

/* ---- gameobj ------------------------------------------------------- */
static s7_pointer g_gameobj_get_property(s7_scheme* sc, s7_pointer args)
{ return gameobj_get_property((int)s7_integer(ARG1()), s7_string(ARG2())); }
static s7_pointer g_gameobj_set_property(s7_scheme* sc, s7_pointer args)
{ gameobj_set_property((int)s7_integer(ARG1()), s7_string(ARG2()), ARG3()); return s7_t(sc); }
static s7_pointer g_gameobj_properties(s7_scheme* sc, s7_pointer args)
{ return gameobj_properties((int)s7_integer(ARG1())); }
static s7_pointer g_gameobj_create(s7_scheme* sc, s7_pointer args)
{ return s7_make_integer(sc, gameobj_create((int)s7_integer(ARG1()), ARG2())); }
static s7_pointer g_gameobj_remove(s7_scheme* sc, s7_pointer args)
{ gameobj_remove((int)s7_integer(ARG1())); return s7_t(sc); }
static s7_pointer g_gameobj_get_all(s7_scheme* sc, s7_pointer)
{ return gameobj_get_all(); }
static s7_pointer g_gameobj_is_helicopter(s7_scheme* sc, s7_pointer args)
{ return gameobj_is_helicopter((int)s7_integer(ARG1())) ? s7_t(sc) : s7_f(sc); }
static s7_pointer g_gameobj_is_vehicle(s7_scheme* sc, s7_pointer args)
{ return gameobj_is_vehicle((int)s7_integer(ARG1())) ? s7_t(sc) : s7_f(sc); }
static s7_pointer g_gameobj_is_unit(s7_scheme* sc, s7_pointer args)
{ return gameobj_is_unit((int)s7_integer(ARG1())) ? s7_t(sc) : s7_f(sc); }
static s7_pointer g_gameobj_is_soldier(s7_scheme* sc, s7_pointer args)
{ return gameobj_is_soldier((int)s7_integer(ARG1())) ? s7_t(sc) : s7_f(sc); }
static s7_pointer g_satchel_detonate(s7_scheme* sc, s7_pointer args)
{ satchel_detonate((int)s7_integer(ARG1())); return s7_t(sc); }

/* ---- input --------------------------------------------------------- */
static s7_pointer g_input_register_callback(s7_scheme* sc, s7_pointer args)
{ input_register_callback(s7_string(ARG1()), ARG2()); return s7_t(sc); }
static s7_pointer g_input_get_mouse_x(s7_scheme* sc, s7_pointer)
{ return s7_make_integer(sc, input_get_mouse_x()); }
static s7_pointer g_input_get_mouse_y(s7_scheme* sc, s7_pointer)
{ return s7_make_integer(sc, input_get_mouse_y()); }
static s7_pointer g_input_get_mouse_world_x(s7_scheme* sc, s7_pointer)
{ return s7_make_real(sc, input_get_mouse_world_x()); }
static s7_pointer g_input_get_mouse_world_y(s7_scheme* sc, s7_pointer)
{ return s7_make_real(sc, input_get_mouse_world_y()); }

/* ---- menu ---------------------------------------------------------- */
static s7_pointer g_menu_create(s7_scheme* sc, s7_pointer)
{ return s7_make_integer(sc, menu_create()); }
static s7_pointer g_menu_show(s7_scheme* sc, s7_pointer args)
{ menu_show((int)s7_integer(ARG1())); return s7_t(sc); }
static s7_pointer g_menu_hide(s7_scheme* sc, s7_pointer)
{ menu_hide(); return s7_t(sc); }
static s7_pointer g_menu_visible(s7_scheme* sc, s7_pointer)
{ return menu_visible() ? s7_t(sc) : s7_f(sc); }
static s7_pointer g_menu_add_item(s7_scheme* sc, s7_pointer args)
{ return s7_make_integer(sc, menu_add_item((int)s7_integer(ARG1()), s7_string(ARG2()), ARG3())); }
static s7_pointer g_menu_add_submenu_item(s7_scheme* sc, s7_pointer args)
{ return s7_make_integer(sc, menu_add_submenu_item((int)s7_integer(ARG1()), s7_string(ARG2()), (int)s7_integer(ARG3()))); }
static s7_pointer g_menu_remove_item(s7_scheme* sc, s7_pointer args)
{ menu_remove_item((int)s7_integer(ARG1()), (int)s7_integer(ARG2())); return s7_t(sc); }

/* ---- object -------------------------------------------------------- */
static s7_pointer g_object_remove(s7_scheme* sc, s7_pointer args)
{ object_remove((int)s7_integer(ARG1())); return s7_t(sc); }

/* ---- player -------------------------------------------------------- */
static s7_pointer g_player_set_current_unit(s7_scheme* sc, s7_pointer args)
{ player_set_current_unit((int)s7_integer(ARG1())); return s7_t(sc); }
static s7_pointer g_player_get_current_unit(s7_scheme* sc, s7_pointer)
{ return s7_make_integer(sc, player_get_current_unit()); }
static s7_pointer g_player_get_soldier(s7_scheme* sc, s7_pointer)
{ return s7_make_integer(sc, player_get_soldier()); }
static s7_pointer g_player_set_soldier(s7_scheme* sc, s7_pointer args)
{ player_set_soldier((int)s7_integer(ARG1())); return s7_t(sc); }

/* ---- sequence ------------------------------------------------------ */
static s7_pointer g_sequence_start(s7_scheme* sc, s7_pointer)
{ return s7_make_integer(sc, sequence_start()); }
static s7_pointer g_sequence_end(s7_scheme* sc, s7_pointer args)
{ sequence_end((int)s7_integer(ARG1())); return s7_t(sc); }
static s7_pointer g_sequence_add_hook(s7_scheme* sc, s7_pointer args)
{ sequence_add_hook(ARG1()); return s7_t(sc); }

/* ---- sound --------------------------------------------------------- */
static s7_pointer g_sound_play_music(s7_scheme* sc, s7_pointer args)
{ if (s7_is_string(ARG1())) sound_play_music(s7_string(ARG1())); return s7_t(sc); }
static s7_pointer g_sound_stop_music(s7_scheme* sc, s7_pointer)
{ sound_stop_music(); return s7_t(sc); }
static s7_pointer g_sound_play_sound(s7_scheme* sc, s7_pointer args)
{ return s7_make_integer(sc, s7_is_string(ARG1()) ? sound_play_sound(s7_string(ARG1())) : -1); }
static s7_pointer g_sound_stop_sound(s7_scheme* sc, s7_pointer args)
{ sound_stop_sound((int)s7_integer(ARG1())); return s7_t(sc); }

/* ---- trigger ------------------------------------------------------- */
static s7_pointer g_trigger_add_timed(s7_scheme* sc, s7_pointer args)
{ trigger_add_timed((float)s7_number_to_real(sc, ARG1()), ARG2()); return s7_t(sc); }
static s7_pointer g_trigger_add_tile(s7_scheme* sc, s7_pointer args)
{ trigger_add_tile((int)s7_integer(ARG1()), (int)s7_integer(ARG2()), ARG3()); return s7_t(sc); }
static s7_pointer g_trigger_add_region(s7_scheme* sc, s7_pointer args)
{
  trigger_add_region((int)s7_integer(ARG1()), (int)s7_integer(ARG2()),
                     (int)s7_integer(ARG3()), (int)s7_integer(arg_nth(args, 3)),
                     arg_nth(args, 4));
  return s7_t(sc);
}

/* ---- vehicle ------------------------------------------------------- */
static s7_pointer g_vehicle_set_fuel(s7_scheme* sc, s7_pointer args)
{ vehicle_set_fuel((int)s7_integer(ARG1())); return s7_t(sc); }
static s7_pointer g_vehicle_get_fuel(s7_scheme* sc, s7_pointer)
{ return s7_make_integer(sc, vehicle_get_fuel()); }
static s7_pointer g_vehicle_get_weapon(s7_scheme* sc, s7_pointer args)
{ return s7_make_integer(sc, vehicle_get_weapon((int)s7_integer(ARG1()))); }
static s7_pointer g_vehicle_set_position(s7_scheme* sc, s7_pointer args)
{ vehicle_set_position((int)s7_integer(ARG1()), (int)s7_integer(ARG2()), (int)s7_integer(ARG3())); return s7_t(sc); }
static s7_pointer g_vehicle_find_nearest(s7_scheme* sc, s7_pointer args)
{
  return s7_make_integer(sc, vehicle_find_nearest(
    (float)s7_number_to_real(sc, ARG1()),
    (float)s7_number_to_real(sc, ARG2()),
    (float)s7_number_to_real(sc, ARG3())));
}
static s7_pointer g_helicopter_start_or_land(s7_scheme* sc, s7_pointer args)
{ helicopter_start_or_land((int)s7_integer(ARG1())); return s7_t(sc); }

/* ---- clanlib leftovers --------------------------------------------- */
static s7_pointer g_clanlib_get_post_keep_alive_func(s7_scheme* sc, s7_pointer)
{ return clanlib_get_post_keep_alive_func(); }
static s7_pointer g_clanlib_set_post_keep_alive_func(s7_scheme* sc, s7_pointer args)
{ clanlib_set_post_keep_alive_func(ARG1()); return s7_t(sc); }
static s7_pointer g_clanlib_call_post_keep_alive_func(s7_scheme* sc, s7_pointer)
{ clanlib_call_post_keep_alive_func(); return s7_t(sc); }

void
register_bindings()
{
  if (!fk_s7)
    return;

  s7_scheme* sc = fk_s7;

#define DEF(name, fn, req, opt, rest, doc) \
  s7_define_function(sc, name, fn, req, opt, rest, doc)

  DEF("game-pause", g_game_pause, 0, 0, false, "(game-pause)");
  DEF("game-quit",  g_game_quit,  0, 0, false, "(game-quit)");
  DEF("game-load",  g_game_load,  1, 0, false, "(game-load filename)");
  DEF("game-save",  g_game_save,  1, 0, false, "(game-save filename)");

  DEF("ai-goto",    g_ai_goto,    3, 0, false, "(ai-goto handle x y)");
  DEF("ai-stop",    g_ai_stop,    1, 0, false, "(ai-stop handle)");
  DEF("ai-has",     g_ai_has,     1, 0, false, "(ai-has handle)");
  DEF("ai-attach",  g_ai_attach,  1, 0, false, "(ai-attach handle)");
  DEF("ai-dettach", g_ai_dettach, 1, 0, false, "(ai-dettach handle)");

  DEF("ai-vehicle-create",       g_ai_vehicle_create,       2, 0, false, "(ai-vehicle-create x y)");
  DEF("ai-vehicle-wait",         g_ai_vehicle_wait,         2, 0, false, "(ai-vehicle-wait id seconds)");
  DEF("ai-vehicle-drive-to",     g_ai_vehicle_drive_to,     3, 0, false, "(ai-vehicle-drive-to id x y)");
  DEF("ai-vehicle-clear-orders", g_ai_vehicle_clear_orders, 1, 0, false, "(ai-vehicle-clear-orders id)");

  DEF("building-create",            g_building_create,            3, 0, false, "(building-create type x y)");
  DEF("building-get-property",      g_building_get_property,      2, 0, false, "(building-get-property handle name)");
  DEF("building-set-property",      g_building_set_property,      3, 0, false, "(building-set-property handle name value)");
  DEF("building-remove",            g_building_remove,            1, 0, false, "(building-remove handle)");
  DEF("building-get-tile",          g_building_get_tile,          2, 0, false, "(building-get-tile x y)");
  DEF("building-get",               g_building_get,               2, 0, false, "(building-get x y)");
  DEF("building-create-type",       g_building_create_type,       2, 0, false, "(building-create-type name lst)");
  DEF("building-get-type-from-name",g_building_get_type_from_name,1, 0, false, "(building-get-type-from-name name)");

  DEF("comm-send-message", g_comm_send_message, 2, 0, false, "(comm-send-message color text)");
  DEF("comm-unit-message", g_comm_unit_message, 2, 0, false, "(comm-unit-message unit text)");

  DEF("debug-set-flag", g_debug_set_flag, 2, 0, false, "(debug-set-flag name value)");
  DEF("debug-get-flag", g_debug_get_flag, 1, 0, false, "(debug-get-flag name)");

  DEF("display-levelmap-visible", g_display_levelmap_visible, 0, 0, false, "(display-levelmap-visible)");
  DEF("display-show-levelmap",    g_display_show_levelmap,    0, 0, false, "(display-show-levelmap)");
  DEF("display-hide-levelmap",    g_display_hide_levelmap,    0, 0, false, "(display-hide-levelmap)");
  DEF("display-show-help",        g_display_show_help,        0, 0, false, "(display-show-help)");
  DEF("display-hide-help",        g_display_hide_help,        0, 0, false, "(display-hide-help)");

  DEF("effect-add-explosion", g_effect_add_explosion, 2, 0, false, "(effect-add-explosion x y)");

  DEF("gameobj-get-property",  g_gameobj_get_property,  2, 0, false, "(gameobj-get-property handle name)");
  DEF("gameobj-set-property",  g_gameobj_set_property,  3, 0, false, "(gameobj-set-property handle name value)");
  DEF("gameobj-properties",    g_gameobj_properties,    1, 0, false, "(gameobj-properties handle)");
  DEF("gameobj-create",        g_gameobj_create,        2, 0, false, "(gameobj-create type-id lst)");
  DEF("gameobj-remove",        g_gameobj_remove,        1, 0, false, "(gameobj-remove handle)");
  DEF("gameobj-get-all",       g_gameobj_get_all,       0, 0, false, "(gameobj-get-all)");
  DEF("gameobj-is-helicopter", g_gameobj_is_helicopter, 1, 0, false, "(gameobj-is-helicopter handle)");
  DEF("gameobj-is-vehicle",    g_gameobj_is_vehicle,    1, 0, false, "(gameobj-is-vehicle handle)");
  DEF("gameobj-is-unit",       g_gameobj_is_unit,       1, 0, false, "(gameobj-is-unit handle)");
  DEF("gameobj-is-soldier",    g_gameobj_is_soldier,    1, 0, false, "(gameobj-is-soldier handle)");
  DEF("satchel-detonate",      g_satchel_detonate,      1, 0, false, "(satchel-detonate handle)");

  DEF("input-register-callback", g_input_register_callback, 2, 0, false, "(input-register-callback key func)");
  DEF("input-get-mouse-x",       g_input_get_mouse_x,       0, 0, false, "(input-get-mouse-x)");
  DEF("input-get-mouse-y",       g_input_get_mouse_y,       0, 0, false, "(input-get-mouse-y)");
  DEF("input-get-mouse-world-x", g_input_get_mouse_world_x, 0, 0, false, "(input-get-mouse-world-x)");
  DEF("input-get-mouse-world-y", g_input_get_mouse_world_y, 0, 0, false, "(input-get-mouse-world-y)");

  DEF("menu-create",          g_menu_create,          0, 0, false, "(menu-create)");
  DEF("menu-show",            g_menu_show,            1, 0, false, "(menu-show id)");
  DEF("menu-hide",            g_menu_hide,            0, 0, false, "(menu-hide)");
  DEF("menu-visible",         g_menu_visible,         0, 0, false, "(menu-visible)");
  DEF("menu-add-item",        g_menu_add_item,        3, 0, false, "(menu-add-item id label func)");
  DEF("menu-add-submenu-item",g_menu_add_submenu_item,3, 0, false, "(menu-add-submenu-item id label sub-id)");
  DEF("menu-remove-item",     g_menu_remove_item,     2, 0, false, "(menu-remove-item menu-id item-id)");

  DEF("object-remove", g_object_remove, 1, 0, false, "(object-remove id)");

  DEF("player-set-current-unit", g_player_set_current_unit, 1, 0, false, "(player-set-current-unit handle)");
  DEF("player-get-current-unit", g_player_get_current_unit, 0, 0, false, "(player-get-current-unit)");
  DEF("player-get-soldier",      g_player_get_soldier,      0, 0, false, "(player-get-soldier)");
  DEF("player-set-soldier",      g_player_set_soldier,      1, 0, false, "(player-set-soldier handle)");

  DEF("sequence-start",    g_sequence_start,    0, 0, false, "(sequence-start)");
  DEF("sequence-end",      g_sequence_end,      1, 0, false, "(sequence-end id)");
  DEF("sequence-add-hook", g_sequence_add_hook, 1, 0, false, "(sequence-add-hook func)");

  DEF("sound-play-music", g_sound_play_music, 1, 0, false, "(sound-play-music name)");
  DEF("sound-stop-music", g_sound_stop_music, 0, 0, false, "(sound-stop-music)");
  DEF("sound-play-sound", g_sound_play_sound, 1, 0, false, "(sound-play-sound name)");
  DEF("sound-stop-sound", g_sound_stop_sound, 1, 0, false, "(sound-stop-sound handle)");

  DEF("trigger-add-timed",  g_trigger_add_timed,  2, 0, false, "(trigger-add-timed seconds func)");
  DEF("trigger-add-tile",   g_trigger_add_tile,   3, 0, false, "(trigger-add-tile x y func)");
  DEF("trigger-add-region", g_trigger_add_region, 5, 0, false, "(trigger-add-region x1 y1 x2 y2 func)");

  DEF("vehicle-set-fuel",        g_vehicle_set_fuel,        1, 0, false, "(vehicle-set-fuel fuel)");
  DEF("vehicle-get-fuel",        g_vehicle_get_fuel,        0, 0, false, "(vehicle-get-fuel)");
  DEF("vehicle-get-weapon",      g_vehicle_get_weapon,      1, 0, false, "(vehicle-get-weapon number)");
  DEF("vehicle-set-position",    g_vehicle_set_position,    3, 0, false, "(vehicle-set-position handle x y)");
  DEF("vehicle-find-nearest",    g_vehicle_find_nearest,    3, 0, false, "(vehicle-find-nearest x y max-distance)");
  DEF("helicopter-start-or-land",g_helicopter_start_or_land,1, 0, false, "(helicopter-start-or-land handle)");

  DEF("clanlib-get-post-keep-alive-func",  g_clanlib_get_post_keep_alive_func,  0, 0, false, "");
  DEF("clanlib-set-post-keep-alive-func",  g_clanlib_set_post_keep_alive_func,  1, 0, false, "");
  DEF("clanlib-call-post-keep-alive-func", g_clanlib_call_post_keep_alive_func, 0, 0, false, "");

#undef DEF
}

} // namespace Scheme

/* EOF */
