//  $Id: FeuerkraftOptions.hxx,v 1.1 2002/04/07 16:28:21 grumbel Exp $
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

#ifndef FEUERKRAFTOPTIONS_HXX
#define FEUERKRAFTOPTIONS_HXX

#include <string>

/** This class holds all the options that can be set on startup or
    probally at runtime. Options include things like disable/enable
    sound, screen size, effects etc.
    
    FIXME: Runtime changes of options should use signals or something like that
*/
class FeuerkraftOptions { 
private:
  int screen_width;
  int screen_height;
  std::string config_file;
  
public:
  FeuerkraftOptions ();
  ~FeuerkraftOptions ();
  
  void parse_args (int argc, char** argv);
  void parse_config_file (const std::string& filename);

  /*--- Options ----*/

  /** Show the intro screen */
  bool show_intro ();

  /** Show the outro screen */
  bool show_outro ();

  /** Return the width of the screen */
  int get_screen_width ();

  /** Return the height of the screen */
  int get_screen_height ();
  
  /** Return the name of the config file to read (default:
      ~/.feuerkraft/config) */
  std::string get_config_file ();
};

#endif

/* EOF */
