//  $Id: level_map.hxx,v 1.2 2003/04/19 23:17:52 grumbel Exp $
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

#ifndef LEVELMAP_HXX
#define LEVELMAP_HXX

#include "boost/dummy_ptr.hpp"
#include "gui_obj.hxx"

class GameWorld;

class LevelMap : public GuiObj
{
private:
  boost::dummy_ptr<GameWorld> world;
public:
  LevelMap (boost::dummy_ptr<GameWorld>);
  ~LevelMap ();

  void update (float delta);
  void draw (CL_GraphicContext* gc);
};

#endif

/* EOF */
