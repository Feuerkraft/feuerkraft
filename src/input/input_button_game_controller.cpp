// Feuerkraft - A Tank Battle Game
// Copyright (C) 2026 Ingo Ruhnke <grumbel@gmail.com>

#include "input_button_game_controller.hpp"

InputButtonGameController::InputButtonGameController(SDL_GameController* controller_,
                                                     int button_num)
  : controller(controller_),
    button(static_cast<SDL_GameControllerButton>(button_num)),
    was_down(false)
{
}

void
InputButtonGameController::update(float /*delta*/)
{
  if (!controller)
    return;

  bool down = SDL_GameControllerGetButton(controller, button) != 0;
  if (down && !was_down)
    button_down();
  else if (!down && was_down)
    button_up();
  was_down = down;
}

/* EOF */
