//  $Id: StartScreen.hxx,v 1.1 2002/03/28 23:53:32 grumbel Exp $
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

#ifndef STARTSCREEN_HXX
#define STARTSCREEN_HXX

#include <SphriteLib/sphritelib.h>

/** FIXME: Mega ugly peace of code, should be replaced with something better */
class StartScreen
{
private:
  Sprite logo;
  Sprite endlogo;
  float display_time;
public:
  typedef enum { S_STARTLOGO, 
		 S_FADETOGAME,
		 S_GAME,
		 S_ENDLOGO,
		 S_FADETOBLACK,
		 S_QUIT } LogoMode;
  LogoMode logo_mode;
  
public:
  StartScreen ();
  ~StartScreen ();
  
  void draw ();
  void update (float delta);
  bool done ();
};

#endif

/* EOF */
