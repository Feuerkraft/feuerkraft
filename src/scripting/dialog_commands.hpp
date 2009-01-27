//  $Id: dialog_commands.hpp,v 1.2 2003/06/17 22:06:13 grumbel Exp $
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

#ifndef HEADER_DIALOG_COMMANDS_HXX
#define HEADER_DIALOG_COMMANDS_HXX

/** @addtogroup scripting */
//@{

/** Display a dialog window with \a text and call a callback once the
    dialog window was closed */
int  dialog_create(const char* text);

/** Add an answer choice to the dialog */
void dialog_add_choice(int dialog_id, const char* text, SCM callback);

//@}

#endif

/* EOF */
