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

#include "input_recorder.hpp"

InputRecorder::InputRecorder(const std::string& filename)
  : out(filename.c_str())
{
  entry_counter = 0;
}

InputRecorder::~InputRecorder()
{
  out.close();
}

void
InputRecorder::record(const Controller& controller)
{
  InputEventLst lst = controller.get_events();

  if (!lst.empty())
    {
      out << "(entry " << entry_counter << std::endl;

      for (InputEventLst::iterator i = lst.begin(); i != lst.end(); ++i)
        {
          switch(i->type)
            {
            case AXIS_EVENT:
              out << "  (axis " << i->axis.name << " " << i->axis.get_pos() << ")" << std::endl;
              break;

            case BUTTON_EVENT:
              out << "  (button " << i->button.name << " " << i->button.down << ")" << std::endl;
              break;
            }
        }
      out << ")\n" << std::endl;
    }

  entry_counter += 1;
}

/* EOF */
