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

#include <iostream>
#include <sstream>
#include "../message_buffer.hpp"
#include "../communication_dialog.hpp"
#include "comm_commands.hpp"

void
comm_send_message(int color, const char* str)
{
  std::stringstream s;
  s << color << ": '" << str << "'" << std::endl;
  std::cout << "### " << str << std::endl;
  MessageBuffer::current()->add(s.str());
}

void
comm_unit_message(int unit, const char* str)
{
  CommunicationDialog::current()->send(unit, str);
}

/* EOF */
