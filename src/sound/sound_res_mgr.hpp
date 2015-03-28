//  $Id: sound_res_mgr.hpp,v 1.2 2003/06/03 14:11:22 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_SOUND_RES_MGR_HXX
#define HEADER_PINGUS_SOUND_RES_MGR_HXX

#include <map>

class CL_SoundBuffer;

typedef CL_SoundBuffer* SoundHandle;

/** */
class SoundResMgr
{
private:
  typedef std::map<std::string, CL_SoundBuffer*> SoundMap;
  static SoundMap sound_map;

public:
  static SoundHandle load(const std::string& name);

private:
  SoundResMgr (const SoundResMgr&);
  SoundResMgr& operator= (const SoundResMgr&);
};

#endif

/* EOF */
