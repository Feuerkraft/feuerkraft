//  $Id: menu_commands.cxx,v 1.1 2003/06/05 21:18:20 grumbel Exp $
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

#include "menu_commands.hxx"

void
menu_display(int menu_id)
{
}

void
menu_hide()
{
  
}

int
menu_create()
{
  return 0;
}

int
menu_add_item(int menu_id, const char* label, SCM func)
{
  return 0;
}

int
menu_add_submenu_item(int menu_id, const char* label, int sub_menu_id)
{
  return 0;
}

void
menu_remove_item(int menu_id, int item_id)
{
}

/* EOF */
