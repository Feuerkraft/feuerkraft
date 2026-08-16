// Feuerkraft - A Tank Battle Game
// Copyright (C) 2026 Ingo Ruhnke <grumbel@gmail.com>

#ifndef HEADER_INPUT_BUTTON_GAME_CONTROLLER_HXX
#define HEADER_INPUT_BUTTON_GAME_CONTROLLER_HXX

#include <SDL.h>
#include "input_button.hpp"

/** Polls an SDL_GameController button. */
class InputButtonGameController : public InputButton
{
private:
  SDL_GameController* controller;
  SDL_GameControllerButton button;
  bool was_down;

public:
  InputButtonGameController(SDL_GameController* controller, int button_num);
  void update(float delta) override;
};

#endif

/* EOF */
