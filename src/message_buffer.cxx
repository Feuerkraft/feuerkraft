//  $Id: message_buffer.cxx,v 1.1 2003/06/05 21:17:11 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include "fonts.hxx"
#include "message_buffer.hxx"

MessageBuffer* MessageBuffer::current_ = 0;

MessageBuffer::MessageBuffer(int arg_x, int arg_y)
{
  current_ = this;
  x_pos = arg_x;
  y_pos = arg_y;
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
      y -= 25;
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
