//  $Id$
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

#include <ClanLib/Display/display.h>
#include "fonts.hxx"
#include "unit.hxx"
#include "view.hxx"
#include "game_obj_manager.hxx"
#include "communication_dialog.hxx"

CommunicationDialog* CommunicationDialog::current_ = 0;

CommunicationDialog::CommunicationDialog()
{
  current_ = this;

}

CommunicationDialog::~CommunicationDialog()
{
}

void
CommunicationDialog::draw (CL_GraphicContext& gc)
{
  for(Messages::iterator i = messages.begin(); i != messages.end(); ++i)
    {
      Unit* unit = dynamic_cast<Unit*>(GameObjManager::current()->get_object_by_id(i->first));
      if (unit)
        {
          CL_Font font = Fonts::font;
          CL_Rect bbox = font.bounding_rect(0, 0, i->second);

          FloatVector2d unit_pos   = View::current()->world_to_screen(unit->get_pos());
          FloatVector2d dialog_pos = unit_pos + FloatVector2d(0, - 50-bbox.get_height());

          CL_Display::draw_line((int)unit_pos.x,   (int)unit_pos.y-40,
                                (int)dialog_pos.x, (int)dialog_pos.y+20,
                                CL_Color(0,0,0, 100));

          CL_Display::draw_line((int)unit_pos.x,   (int)unit_pos.y-40,
                                (int)dialog_pos.x-20, (int)dialog_pos.y+20,
                                CL_Color(0,0,0, 100));

          CL_Display::fill_rect(CL_Rect(CL_Point(int(dialog_pos.x - bbox.get_width()/2),
                                                 int(dialog_pos.y - bbox.get_height())),
                                        CL_Size(bbox.get_width()  + 20, 
                                                bbox.get_height() + 20)),
                                //CL_Color(85,85,0, 230));
                                CL_Color(0,0,0, 100));

          font.set_alignment(origin_bottom_center);
          font.draw(int(dialog_pos.x+10), int(dialog_pos.y+10), i->second);
        }
    }
}

void
CommunicationDialog::send(int unit_id, const std::string& message)
{
  messages[unit_id] = message;
}

void
CommunicationDialog::update (float delta)
{
  
}

/* EOF */
