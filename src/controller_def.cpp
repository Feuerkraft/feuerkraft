// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
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

#include "controller_def.hpp"

int
ControllerDef::get_button_count()
{
  return 4;
}

int
ControllerDef::get_axis_count()
{
  return 3;
}

std::string
ControllerDef::button_id2name(int id)
{
  switch (id)
    {
    case PRIMARY_FIRE_BUTTON:
      return "primary-button";
    case SECONDARY_FIRE_BUTTON:
      return "secondary-button";
    case USE_BUTTON:
      return "use-button";
    case MENU_BUTTON:
      return "menu-button";
    default:
      return "unknown";
    }
}

int
ControllerDef::button_name2id(const std::string& name)
{
  if      (name == "primary-button")
    return PRIMARY_FIRE_BUTTON;
  else if (name == "secondary-button")
    return SECONDARY_FIRE_BUTTON;
  else if (name == "use-button")
    return USE_BUTTON;
  else if (name == "menu-button")
    return MENU_BUTTON;
  else
    return -1;
}

std::string
ControllerDef::axis_id2name(int id)
{
  switch (id)
    {
    case ORIENTATION_AXIS:
      return "orientation-axis";
    case ACCELERATE_AXIS:
      return "accelerate-axis";
    case STRAFE_AXIS:
      return "strafe-axis";
    default:
      return "unknown";
    }
}

int
ControllerDef::axis_name2id(const std::string& name)
{
  if (name == "orientation-axis")
    return ORIENTATION_AXIS;
  else if (name == "accelerate-axis")
    return ACCELERATE_AXIS;
  else if (name == "strafe-axis")
    return STRAFE_AXIS;
  else
    return -1;
}

/* EOF */
