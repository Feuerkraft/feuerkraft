//  $Id: Pathfinder.hh,v 1.2 2001/04/27 19:43:15 grumbel Exp $
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

#ifndef PATHFINDER_HH
#define PATHFINDER_HH

#include <iostream>
#include <exception>
#include <string>
#include <list>

class Pathfinder
{
private:
  std::list<std::string> paths;
  typedef std::list<std::string>::iterator PathIter;

  std::list<std::string> significant_files;
  typedef std::list<std::string>::iterator SigFilesIter;

  char path_seperator;

public:
  struct FileNotFound : public std::exception {
    std::string filename;
    
    FileNotFound (const std::string& str) 
      : filename (str) {}

    virtual ~FileNotFound () throw () {}
  };
  
  Pathfinder ();
  ~Pathfinder ();

  /** Trim all trailing slashs '/' from a pathname and replace all
      '/' with path_seperator. */
  std::string trim (std::string str);
  
  /** Add significant files to search for, this can for example be the
      datafiles or the .scr files */
  void add_sig_files (const std::string& str);

  /** Search for all paths containing sigfiles */
  void search_for_paths ()
  {
    std::cout << "Search for Pathes not implemented" << std::endl;
  }

  /** Return the complete filename of the partial filename given by str */
  std::string find (const std::string& str);

  /** Return the pathname containing str */
  std::string find_path (const std::string& str);

  /** Add a path to the front, paths on the front are searched first. */
  void add_front (const std::string& str);

  /** Add a path to the back */
  void add_back (const std::string& str);

  /** Output all pathes which will be searched */
  void print ();
};

#endif

/* EOF */
