//  $Id: ai_vehicle_commands.hxx,v 1.1 2003/05/01 20:56:39 grumbel Exp $
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

#ifndef HEADER_AI_VEHICLE_COMMANDS_HXX
#define HEADER_AI_VEHICLE_COMMANDS_HXX

int  ai_vehicle_create(int x, int y);
void ai_vehicle_drive_to(int object_id, int x, int y);
void ai_vehicle_clear_orders(int object_id);

#endif

/* EOF */
