// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "start_screen.hpp"
#include "resource_manager.hpp"
#include "display.hpp"
#include "color.hpp"

StartScreen::StartScreen()
  : logo(resources->get_sprite("feuerkraft/logo")),
    endlogo(resources->get_sprite("feuerkraft/endlogo")),
    display_time(0),
    logo_mode(S_STARTLOGO)
{
}

StartScreen::~StartScreen()
{
}

void
StartScreen::draw()
{
  if (logo_mode == S_STARTLOGO)
    {
      if (display_time <= 2.0f)
	logo.set_alpha(display_time / 2.0f);
      else
	logo.set_alpha(1.0f);

      logo.draw(Display::get_width() / 2,
		Display::get_height() / 2);
    }
  else if (logo_mode == S_FADETOGAME)
    {
      logo.set_alpha(1.0f - (display_time / 2.0f));
      logo.draw(Display::get_width() / 2,
		Display::get_height() / 2);
    }
  else if (logo_mode == S_ENDLOGO)
    {
      if (display_time <= 2.0f)
	endlogo.set_alpha(display_time / 2.0f);
      else
	endlogo.set_alpha(1.0f);

      endlogo.draw(Display::get_width() / 2,
		   Display::get_height() / 2);
    }
  else if (logo_mode == S_FADETOBLACK)
    {
      endlogo.set_alpha(1.0f);
      endlogo.draw(Display::get_width() / 2,
		   Display::get_height() / 2);

      Display::fill_rect(0, 0, Display::get_width(), Display::get_height(),
			 Color(0, 0, 0, int(255.0f * display_time / 2.0f)));
    }
}

void
StartScreen::update(float delta)
{
  display_time += delta;

  if (logo_mode == S_STARTLOGO && display_time > 4.0f)
    {
      logo_mode = S_FADETOGAME;
      display_time = 0;
    }
  else if (logo_mode == S_FADETOGAME && display_time > 2.0f)
    {
      logo_mode = S_GAME;
      display_time = 0;
    }
  else if (logo_mode == S_ENDLOGO && display_time > 4.0f)
    {
      logo_mode = S_FADETOBLACK;
      display_time = 0;
    }
  else if (logo_mode == S_FADETOBLACK && display_time >= 2.0f)
    {
      logo_mode = S_QUIT;
    }
}

bool
StartScreen::done()
{
  return logo_mode == S_QUIT || logo_mode == S_GAME;
}

/* EOF */
