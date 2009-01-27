//  $Id: keys.cpp,v 1.4 2003/10/31 23:24:41 grumbel Exp $
//
//  Feuerkraft - A Tank Battle Game
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

#include <string.h>
#include <ClanLib/display.h>
#include "keys.hpp"

#ifdef WIN32
#  define strcasecmp _stricmp
#endif

// FIXME: Not all keys CL_KEY_'s work on my X11, so I had to manually remove them!
const char* keyid2string(int id)
{
  switch (id)
    {
    case 1001: return "JOY_1";
    case 1002: return "JOY_2";
    case 1003: return "JOY_3";
    case 1004: return "JOY_4";

    case CL_MOUSE_LEFT: return "MOUSE_LEFT"; 
    case CL_MOUSE_RIGHT: return "MOUSE_RIGHT"; 
    case CL_MOUSE_MIDDLE: return "MOUSE_MIDDLE"; 
    case CL_MOUSE_WHEEL_UP: return "MOUSE_WHEEL_UP"; 
    case CL_MOUSE_WHEEL_DOWN: return "MOUSE_WHEEL_DOWN"; 
    case CL_MOUSE_XBUTTON1: return "MOUSE_XBUTTON1"; 
    case CL_MOUSE_XBUTTON2: return "MOUSE_XBUTTON2"; 

    case CL_KEY_BACKSPACE: return "KEY_BACKSPACE"; 
    case CL_KEY_TAB: return "KEY_TAB"; 
    case CL_KEY_CLEAR: return "KEY_CLEAR"; 
    case CL_KEY_RETURN: return "KEY_RETURN"; 
    case CL_KEY_MENU: return "KEY_MENU"; 
    case CL_KEY_PAUSE: return "KEY_PAUSE"; 
    case CL_KEY_KANJI: return "KEY_KANJI"; 
    case CL_KEY_ESCAPE: return "KEY_ESCAPE"; 
    case CL_KEY_SPACE: return "KEY_SPACE"; 
    case CL_KEY_PRIOR: return "KEY_PRIOR"; 
    case CL_KEY_NEXT: return "KEY_NEXT"; 
    case CL_KEY_END: return "KEY_END"; 
    case CL_KEY_HOME: return "KEY_HOME"; 
    case CL_KEY_LEFT: return "KEY_LEFT"; 
    case CL_KEY_UP: return "KEY_UP"; 
    case CL_KEY_RIGHT: return "KEY_RIGHT"; 
    case CL_KEY_DOWN: return "KEY_DOWN"; 
    case CL_KEY_SELECT: return "KEY_SELECT"; 
    case CL_KEY_PRINT: return "KEY_PRINT"; 
    case CL_KEY_EXECUTE: return "KEY_EXECUTE"; 
    case CL_KEY_INSERT: return "KEY_INSERT"; 
    case CL_KEY_DELETE: return "KEY_DELETE"; 
    case CL_KEY_HELP: return "KEY_HELP"; 
    case CL_KEY_0: return "KEY_0"; 
    case CL_KEY_1: return "KEY_1"; 
    case CL_KEY_2: return "KEY_2"; 
    case CL_KEY_3: return "KEY_3"; 
    case CL_KEY_4: return "KEY_4"; 
    case CL_KEY_5: return "KEY_5"; 
    case CL_KEY_6: return "KEY_6"; 
    case CL_KEY_7: return "KEY_7"; 
    case CL_KEY_8: return "KEY_8"; 
    case CL_KEY_9: return "KEY_9"; 
    case CL_KEY_A: return "KEY_A"; 
    case CL_KEY_B: return "KEY_B"; 
    case CL_KEY_C: return "KEY_C"; 
    case CL_KEY_D: return "KEY_D"; 
    case CL_KEY_E: return "KEY_E"; 
    case CL_KEY_F: return "KEY_F"; 
    case CL_KEY_G: return "KEY_G"; 
    case CL_KEY_H: return "KEY_H"; 
    case CL_KEY_I: return "KEY_I"; 
    case CL_KEY_J: return "KEY_J"; 
    case CL_KEY_K: return "KEY_K"; 
    case CL_KEY_L: return "KEY_L"; 
    case CL_KEY_M: return "KEY_M"; 
    case CL_KEY_N: return "KEY_N"; 
    case CL_KEY_O: return "KEY_O"; 
    case CL_KEY_P: return "KEY_P"; 
    case CL_KEY_Q: return "KEY_Q"; 
    case CL_KEY_R: return "KEY_R"; 
    case CL_KEY_S: return "KEY_S"; 
    case CL_KEY_T: return "KEY_T"; 
    case CL_KEY_U: return "KEY_U"; 
    case CL_KEY_V: return "KEY_V"; 
    case CL_KEY_W: return "KEY_W"; 
    case CL_KEY_X: return "KEY_X"; 
    case CL_KEY_Y: return "KEY_Y"; 
    case CL_KEY_Z: return "KEY_Z"; 
    case CL_KEY_NUMPAD0: return "KEY_NUMPAD0"; 
    case CL_KEY_NUMPAD1: return "KEY_NUMPAD1"; 
    case CL_KEY_NUMPAD2: return "KEY_NUMPAD2"; 
    case CL_KEY_NUMPAD3: return "KEY_NUMPAD3"; 
    case CL_KEY_NUMPAD4: return "KEY_NUMPAD4"; 
    case CL_KEY_NUMPAD5: return "KEY_NUMPAD5"; 
    case CL_KEY_NUMPAD6: return "KEY_NUMPAD6"; 
    case CL_KEY_NUMPAD7: return "KEY_NUMPAD7"; 
    case CL_KEY_NUMPAD8: return "KEY_NUMPAD8"; 
    case CL_KEY_NUMPAD9: return "KEY_NUMPAD9"; 
    case CL_KEY_F1: return "KEY_F1"; 
    case CL_KEY_F2: return "KEY_F2"; 
    case CL_KEY_F3: return "KEY_F3"; 
    case CL_KEY_F4: return "KEY_F4"; 
    case CL_KEY_F5: return "KEY_F5"; 
    case CL_KEY_F6: return "KEY_F6"; 
    case CL_KEY_F7: return "KEY_F7"; 
    case CL_KEY_F8: return "KEY_F8"; 
    case CL_KEY_F9: return "KEY_F9"; 
    case CL_KEY_F10: return "KEY_F10"; 
    case CL_KEY_F11: return "KEY_F11"; 
    case CL_KEY_F12: return "KEY_F12"; 
    case CL_KEY_F13: return "KEY_F13"; 
    case CL_KEY_F14: return "KEY_F14"; 
    case CL_KEY_F15: return "KEY_F15"; 
    case CL_KEY_F16: return "KEY_F16"; 
    case CL_KEY_F17: return "KEY_F17"; 
    case CL_KEY_F18: return "KEY_F18"; 
    case CL_KEY_F19: return "KEY_F19"; 
    case CL_KEY_F20: return "KEY_F20"; 
    case CL_KEY_F21: return "KEY_F21"; 
    case CL_KEY_F22: return "KEY_F22"; 
    case CL_KEY_F23: return "KEY_F23"; 
    case CL_KEY_F24: return "KEY_F24"; 
    case CL_KEY_NUMLOCK: return "KEY_NUMLOCK"; 
    case CL_KEY_SCROLL: return "KEY_SCROLL"; 
    case CL_KEY_LSHIFT: return "KEY_LSHIFT"; 
    case CL_KEY_RSHIFT: return "KEY_RSHIFT"; 
    case CL_KEY_LCONTROL: return "KEY_LCONTROL"; 
    case CL_KEY_RCONTROL: return "KEY_RCONTROL"; 
    case CL_KEY_LMENU: return "KEY_LMENU"; 
    case CL_KEY_RMENU: return "KEY_RMENU"; 
    default:
      return "<unknown>";
    }
}

int string2keyid(const char* key)
{
  if      (strcasecmp(key, "JOY_1") == 0) { return 1001; }
  else if (strcasecmp(key, "JOY_2") == 0) { return 1002; }
  else if (strcasecmp(key, "JOY_3") == 0) { return 1003; }
  else if (strcasecmp(key, "JOY_4") == 0) { return 1004; }

  else if (strcasecmp(key, "MOUSE_LEFT") == 0) { return CL_MOUSE_LEFT; }
  else if (strcasecmp(key, "MOUSE_RIGHT") == 0) { return CL_MOUSE_RIGHT; }
  else if (strcasecmp(key, "MOUSE_MIDDLE") == 0) { return CL_MOUSE_MIDDLE; }
  else if (strcasecmp(key, "MOUSE_WHEEL_UP") == 0) { return CL_MOUSE_WHEEL_UP; }
  else if (strcasecmp(key, "MOUSE_WHEEL_DOWN") == 0) { return CL_MOUSE_WHEEL_DOWN; }
  else if (strcasecmp(key, "MOUSE_XBUTTON1") == 0) { return CL_MOUSE_XBUTTON1; }
  else if (strcasecmp(key, "MOUSE_XBUTTON2") == 0) { return CL_MOUSE_XBUTTON2; }

  else if (strcasecmp(key, "KEY_BACKSPACE") == 0) { return CL_KEY_BACKSPACE; }
  else if (strcasecmp(key, "KEY_TAB") == 0) { return CL_KEY_TAB; }
  else if (strcasecmp(key, "KEY_CLEAR") == 0) { return CL_KEY_CLEAR; }
  else if (strcasecmp(key, "KEY_RETURN") == 0) { return CL_KEY_RETURN; }
  else if (strcasecmp(key, "KEY_SHIFT") == 0) { return CL_KEY_SHIFT; }
  else if (strcasecmp(key, "KEY_CONTROL") == 0) { return CL_KEY_CONTROL; }
  else if (strcasecmp(key, "KEY_MENU") == 0) { return CL_KEY_MENU; }
  else if (strcasecmp(key, "KEY_PAUSE") == 0) { return CL_KEY_PAUSE; }
  else if (strcasecmp(key, "KEY_KANJI") == 0) { return CL_KEY_KANJI; }
  else if (strcasecmp(key, "KEY_ESCAPE") == 0) { return CL_KEY_ESCAPE; }
  else if (strcasecmp(key, "KEY_SPACE") == 0) { return CL_KEY_SPACE; }
  else if (strcasecmp(key, "KEY_PRIOR") == 0) { return CL_KEY_PRIOR; }
  else if (strcasecmp(key, "KEY_NEXT") == 0) { return CL_KEY_NEXT; }
  else if (strcasecmp(key, "KEY_END") == 0) { return CL_KEY_END; }
  else if (strcasecmp(key, "KEY_HOME") == 0) { return CL_KEY_HOME; }
  else if (strcasecmp(key, "KEY_LEFT") == 0) { return CL_KEY_LEFT; }
  else if (strcasecmp(key, "KEY_UP") == 0) { return CL_KEY_UP; }
  else if (strcasecmp(key, "KEY_RIGHT") == 0) { return CL_KEY_RIGHT; }
  else if (strcasecmp(key, "KEY_DOWN") == 0) { return CL_KEY_DOWN; }
  else if (strcasecmp(key, "KEY_SELECT") == 0) { return CL_KEY_SELECT; }
  else if (strcasecmp(key, "KEY_PRINT") == 0) { return CL_KEY_PRINT; }
  else if (strcasecmp(key, "KEY_EXECUTE") == 0) { return CL_KEY_EXECUTE; }
  else if (strcasecmp(key, "KEY_INSERT") == 0) { return CL_KEY_INSERT; }
  else if (strcasecmp(key, "KEY_DELETE") == 0) { return CL_KEY_DELETE; }
  else if (strcasecmp(key, "KEY_HELP") == 0) { return CL_KEY_HELP; }
  else if (strcasecmp(key, "KEY_0") == 0) { return CL_KEY_0; }
  else if (strcasecmp(key, "KEY_1") == 0) { return CL_KEY_1; }
  else if (strcasecmp(key, "KEY_2") == 0) { return CL_KEY_2; }
  else if (strcasecmp(key, "KEY_3") == 0) { return CL_KEY_3; }
  else if (strcasecmp(key, "KEY_4") == 0) { return CL_KEY_4; }
  else if (strcasecmp(key, "KEY_5") == 0) { return CL_KEY_5; }
  else if (strcasecmp(key, "KEY_6") == 0) { return CL_KEY_6; }
  else if (strcasecmp(key, "KEY_7") == 0) { return CL_KEY_7; }
  else if (strcasecmp(key, "KEY_8") == 0) { return CL_KEY_8; }
  else if (strcasecmp(key, "KEY_9") == 0) { return CL_KEY_9; }
  else if (strcasecmp(key, "KEY_A") == 0) { return CL_KEY_A; }
  else if (strcasecmp(key, "KEY_B") == 0) { return CL_KEY_B; }
  else if (strcasecmp(key, "KEY_C") == 0) { return CL_KEY_C; }
  else if (strcasecmp(key, "KEY_D") == 0) { return CL_KEY_D; }
  else if (strcasecmp(key, "KEY_E") == 0) { return CL_KEY_E; }
  else if (strcasecmp(key, "KEY_F") == 0) { return CL_KEY_F; }
  else if (strcasecmp(key, "KEY_G") == 0) { return CL_KEY_G; }
  else if (strcasecmp(key, "KEY_H") == 0) { return CL_KEY_H; }
  else if (strcasecmp(key, "KEY_I") == 0) { return CL_KEY_I; }
  else if (strcasecmp(key, "KEY_J") == 0) { return CL_KEY_J; }
  else if (strcasecmp(key, "KEY_K") == 0) { return CL_KEY_K; }
  else if (strcasecmp(key, "KEY_L") == 0) { return CL_KEY_L; }
  else if (strcasecmp(key, "KEY_M") == 0) { return CL_KEY_M; }
  else if (strcasecmp(key, "KEY_N") == 0) { return CL_KEY_N; }
  else if (strcasecmp(key, "KEY_O") == 0) { return CL_KEY_O; }
  else if (strcasecmp(key, "KEY_P") == 0) { return CL_KEY_P; }
  else if (strcasecmp(key, "KEY_Q") == 0) { return CL_KEY_Q; }
  else if (strcasecmp(key, "KEY_R") == 0) { return CL_KEY_R; }
  else if (strcasecmp(key, "KEY_S") == 0) { return CL_KEY_S; }
  else if (strcasecmp(key, "KEY_T") == 0) { return CL_KEY_T; }
  else if (strcasecmp(key, "KEY_U") == 0) { return CL_KEY_U; }
  else if (strcasecmp(key, "KEY_V") == 0) { return CL_KEY_V; }
  else if (strcasecmp(key, "KEY_W") == 0) { return CL_KEY_W; }
  else if (strcasecmp(key, "KEY_X") == 0) { return CL_KEY_X; }
  else if (strcasecmp(key, "KEY_Y") == 0) { return CL_KEY_Y; }
  else if (strcasecmp(key, "KEY_Z") == 0) { return CL_KEY_Z; }
  else if (strcasecmp(key, "KEY_NUMPAD0") == 0) { return CL_KEY_NUMPAD0; }
  else if (strcasecmp(key, "KEY_NUMPAD1") == 0) { return CL_KEY_NUMPAD1; }
  else if (strcasecmp(key, "KEY_NUMPAD2") == 0) { return CL_KEY_NUMPAD2; }
  else if (strcasecmp(key, "KEY_NUMPAD3") == 0) { return CL_KEY_NUMPAD3; }
  else if (strcasecmp(key, "KEY_NUMPAD4") == 0) { return CL_KEY_NUMPAD4; }
  else if (strcasecmp(key, "KEY_NUMPAD5") == 0) { return CL_KEY_NUMPAD5; }
  else if (strcasecmp(key, "KEY_NUMPAD6") == 0) { return CL_KEY_NUMPAD6; }
  else if (strcasecmp(key, "KEY_NUMPAD7") == 0) { return CL_KEY_NUMPAD7; }
  else if (strcasecmp(key, "KEY_NUMPAD8") == 0) { return CL_KEY_NUMPAD8; }
  else if (strcasecmp(key, "KEY_NUMPAD9") == 0) { return CL_KEY_NUMPAD9; }
  else if (strcasecmp(key, "KEY_F1") == 0) { return CL_KEY_F1; }
  else if (strcasecmp(key, "KEY_F2") == 0) { return CL_KEY_F2; }
  else if (strcasecmp(key, "KEY_F3") == 0) { return CL_KEY_F3; }
  else if (strcasecmp(key, "KEY_F4") == 0) { return CL_KEY_F4; }
  else if (strcasecmp(key, "KEY_F5") == 0) { return CL_KEY_F5; }
  else if (strcasecmp(key, "KEY_F6") == 0) { return CL_KEY_F6; }
  else if (strcasecmp(key, "KEY_F7") == 0) { return CL_KEY_F7; }
  else if (strcasecmp(key, "KEY_F8") == 0) { return CL_KEY_F8; }
  else if (strcasecmp(key, "KEY_F9") == 0) { return CL_KEY_F9; }
  else if (strcasecmp(key, "KEY_F10") == 0) { return CL_KEY_F10; }
  else if (strcasecmp(key, "KEY_F11") == 0) { return CL_KEY_F11; }
  else if (strcasecmp(key, "KEY_F12") == 0) { return CL_KEY_F12; }
  else if (strcasecmp(key, "KEY_F13") == 0) { return CL_KEY_F13; }
  else if (strcasecmp(key, "KEY_F14") == 0) { return CL_KEY_F14; }
  else if (strcasecmp(key, "KEY_F15") == 0) { return CL_KEY_F15; }
  else if (strcasecmp(key, "KEY_F16") == 0) { return CL_KEY_F16; }
  else if (strcasecmp(key, "KEY_F17") == 0) { return CL_KEY_F17; }
  else if (strcasecmp(key, "KEY_F18") == 0) { return CL_KEY_F18; }
  else if (strcasecmp(key, "KEY_F19") == 0) { return CL_KEY_F19; }
  else if (strcasecmp(key, "KEY_F20") == 0) { return CL_KEY_F20; }
  else if (strcasecmp(key, "KEY_F21") == 0) { return CL_KEY_F21; }
  else if (strcasecmp(key, "KEY_F22") == 0) { return CL_KEY_F22; }
  else if (strcasecmp(key, "KEY_F23") == 0) { return CL_KEY_F23; }
  else if (strcasecmp(key, "KEY_F24") == 0) { return CL_KEY_F24; }
  else if (strcasecmp(key, "KEY_NUMLOCK") == 0) { return CL_KEY_NUMLOCK; }
  else if (strcasecmp(key, "KEY_SCROLL") == 0) { return CL_KEY_SCROLL; }
  else if (strcasecmp(key, "KEY_LSHIFT") == 0) { return CL_KEY_LSHIFT; }
  else if (strcasecmp(key, "KEY_RSHIFT") == 0) { return CL_KEY_RSHIFT; }
  else if (strcasecmp(key, "KEY_LCONTROL") == 0) { return CL_KEY_LCONTROL; }
  else if (strcasecmp(key, "KEY_RCONTROL") == 0) { return CL_KEY_RCONTROL; }
  else if (strcasecmp(key, "KEY_LMENU") == 0) { return CL_KEY_LMENU; }
  else if (strcasecmp(key, "KEY_RMENU") == 0) { return CL_KEY_RMENU; }
  else { return 0; }
}

/* EOF */
