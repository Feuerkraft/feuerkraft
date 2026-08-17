// Feuerkraft - A Tank Battle Game
// Copyright (C) 2026 Ingo Ruhnke <grumbel@gmail.com>
//
// s7 VM lifetime and scripting primitive registration.

#include "scheme_compat.hpp"
#include "scripting/game_commands.hpp"
#include "scripting/ai_commands.hpp"
#include "scripting/display_commands.hpp"
#include "scripting/sound_commands.hpp"
#include "scripting/comm_commands.hpp"
#include "scripting/debug_commands.hpp"
#include "scripting/effect_commands.hpp"
#include "scripting/menu_commands.hpp"
#include "scripting/player_commands.hpp"
#include "scripting/trigger_commands.hpp"
#include "scripting/vehicle_commands.hpp"
#include "scripting/building_commands.hpp"
#include "scripting/gameobj_commands.hpp"
#include "scripting/input_commands.hpp"
#include "scripting/object_commands.hpp"
#include "scripting/sequence_commands.hpp"
#include "scripting/ai_vehicle_commands.hpp"

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

/* --- thin C wrappers for s7_define_function --------------------------- */

static s7_pointer g_game_pause(s7_scheme* /*sc*/, s7_pointer /*args*/)
{
  game_pause();
  return s7_t(fk_s7);
}

static s7_pointer g_game_quit(s7_scheme* /*sc*/, s7_pointer /*args*/)
{
  game_quit();
  return s7_t(fk_s7);
}

static s7_pointer g_game_load(s7_scheme* sc, s7_pointer args)
{
  if (s7_is_string(s7_car(args)))
    game_load(s7_string(s7_car(args)));
  return s7_t(sc);
}

static s7_pointer g_game_save(s7_scheme* sc, s7_pointer args)
{
  if (s7_is_string(s7_car(args)))
    game_save(s7_string(s7_car(args)));
  return s7_t(sc);
}

static s7_pointer g_comm_send_message(s7_scheme* sc, s7_pointer args)
{
  int color = (int)s7_integer(s7_car(args));
  const char* str = s7_string(s7_cadr(args));
  if (str)
    comm_send_message(color, str);
  return s7_t(sc);
}

static s7_pointer g_display_show_levelmap(s7_scheme* sc, s7_pointer /*args*/)
{
  display_show_levelmap();
  return s7_t(sc);
}

static s7_pointer g_display_hide_levelmap(s7_scheme* sc, s7_pointer /*args*/)
{
  display_hide_levelmap();
  return s7_t(sc);
}

static s7_pointer g_effect_add_explosion(s7_scheme* sc, s7_pointer args)
{
  int x = (int)s7_integer(s7_car(args));
  int y = (int)s7_integer(s7_cadr(args));
  effect_add_explosion(x, y);
  return s7_t(sc);
}

void
register_bindings()
{
  if (!fk_s7)
    return;

  s7_define_function(fk_s7, "game-pause", g_game_pause, 0, 0, false,
                     "(game-pause) pause the game");
  s7_define_function(fk_s7, "game-quit", g_game_quit, 0, 0, false,
                     "(game-quit) quit the game");
  s7_define_function(fk_s7, "game-load", g_game_load, 1, 0, false,
                     "(game-load filename) load a mission");
  s7_define_function(fk_s7, "game-save", g_game_save, 1, 0, false,
                     "(game-save filename) save the game");
  s7_define_function(fk_s7, "comm-send-message", g_comm_send_message, 2, 0, false,
                     "(comm-send-message color text)");
  s7_define_function(fk_s7, "display-show-levelmap", g_display_show_levelmap, 0, 0, false,
                     "(display-show-levelmap)");
  s7_define_function(fk_s7, "display-hide-levelmap", g_display_hide_levelmap, 0, 0, false,
                     "(display-hide-levelmap)");
  s7_define_function(fk_s7, "effect-add-explosion", g_effect_add_explosion, 2, 0, false,
                     "(effect-add-explosion x y)");

  /* Further primitives are registered as their call sites are ported. */
}

} // namespace Scheme

/* EOF */
