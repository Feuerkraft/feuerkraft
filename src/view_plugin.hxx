//  $Id: view_plugin.hxx,v 1.2 2003/05/18 21:15:06 grumbel Exp $
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef VIEWPLUGIN_HXX
#define VIEWPLUGIN_HXX

/** A plugin for the View class. The View plugin provides information
    on the position and rotation that the View class should take.
    
    Transition of on changes of get_pos() is done in the View class
    itself (FIXME: should probally be placed in this class?!)
 */
class ViewPlugin
{
private:

public:
  /** Return the rotation that the View should take */
  virtual float get_rotation () =0;
  
  /** Return the position that the View should take */
  virtual FloatVector2d get_pos () =0;

  /** Return true if the View class should make a smooth translation
      between changes of the View or should make hard changes. */
  virtual bool smooth () { return true; }
};

#endif

/* EOF */
