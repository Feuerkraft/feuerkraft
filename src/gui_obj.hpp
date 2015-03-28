//  $Id: gui_obj.hpp,v 1.3 2003/06/03 14:11:22 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef GUIOBJ_HH
#define GUIOBJ_HH

class CL_GraphicContext;

class GuiObj
{
private:

public:
  GuiObj() {}
  virtual ~GuiObj() {}
  virtual void draw (CL_GraphicContext& gc) =0;
  virtual void update (float delta) =0;
};

#endif

/* EOF */
