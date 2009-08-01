//  $Id: message_buffer.hpp,v 1.2 2003/06/08 15:49:00 grumbel Exp $
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

#ifndef HEADER_MESSAGE_BUFFER_HXX
#define HEADER_MESSAGE_BUFFER_HXX

#include <vector>
#include "gui_obj.hpp"

struct MessageBufferEntry {
  std::string message;
  float display_time;
};

/** */
class MessageBuffer : public GuiObj
{
private:
  int x_pos;
  int y_pos;
  typedef std::vector<MessageBufferEntry> Buffer;
  Buffer buffer;
  static MessageBuffer* current_;
public:
  static MessageBuffer* current();

  MessageBuffer(int x, int y);
  
  void add(const std::string& );

  void draw(CL_GraphicContext& gc);
  void update(float delta);
private:
  MessageBuffer (const MessageBuffer&);
  MessageBuffer& operator= (const MessageBuffer&);
};

#endif

/* EOF */
