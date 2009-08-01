//  $Id: message_buffer.cpp,v 1.3 2003/06/08 15:49:00 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "assert.hpp"
#include "fonts.hpp"
#include "message_buffer.hpp"

MessageBuffer* MessageBuffer::current_ = 0;

MessageBuffer::MessageBuffer(int arg_x, int arg_y)
{
  current_ = this;
  x_pos = arg_x;
  y_pos = arg_y;
}

MessageBuffer* 
MessageBuffer::current()
{
  AssertMsg(current_, "comm-* commands must not be called on script loading!");
  return current_;
}

void
MessageBuffer::add(const std::string& str)
{
  MessageBufferEntry entry;
  entry.display_time = 0;
  entry.message = str;
  buffer.push_back(entry);
}

void
MessageBuffer::draw(CL_GraphicContext& gc)
{
  int y = y_pos;

  for(Buffer::reverse_iterator i = buffer.rbegin(); i != buffer.rend(); ++i)
    {
      if (i->display_time < 5.0f)
        {
          if (i->display_time > 4.0f)
            Fonts::font.set_alpha(1.0f - (i->display_time - 4.0f));
          Fonts::font.set_alignment(origin_top_center);
          Fonts::font.draw(x_pos, y, i->message);
          Fonts::font.set_alpha(1.0f);
        }
      y -= Fonts::font.get_height() + 2;
    }
}

void
MessageBuffer::update(float delta)
{
  for(Buffer::iterator i = buffer.begin(); i != buffer.end(); ++i)
    {
      i->display_time += delta;
    }  
}

/* EOF */
