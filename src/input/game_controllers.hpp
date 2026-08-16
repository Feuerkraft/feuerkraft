// Feuerkraft - A Tank Battle Game
// Copyright (C) 2026 Ingo Ruhnke <grumbel@gmail.com>
//
// Thin registry around SDL_GameController so joystick-axis /
// joystick-button bindings in controller .scm files work without the
// old raw SDL_Joystick path.

#ifndef HEADER_GAME_CONTROLLERS_HXX
#define HEADER_GAME_CONTROLLERS_HXX

#include <SDL.h>

class GameControllers
{
public:
  /** Open (or return cached) controller by index. Returns nullptr if
   *  the index is out of range or not a GameController. */
  static SDL_GameController* get(int index);

  /** Number of joysticks that can be opened as game controllers. */
  static int count();

  /** Close all opened controllers (call on shutdown). */
  static void clear();

private:
  GameControllers();
};

#endif

/* EOF */
