// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef HEADER_FEUERKRAFT_IPC_HXX
#define HEADER_FEUERKRAFT_IPC_HXX

#include <fstream>
#include <string>

/** Provides a named pipe that other processes can use to communicate
    with Feuerkraft */
class IPC
{
private:
  std::string filename;
  int stream_fd;
public:
  /** Create a named pipe with \a filename */
  IPC(const std::string& arg_filename);
  ~IPC();

  /** Look at the pipe to see if any information is waiting to be
      read */
  void update();
private:
  bool something_to_read();
};

#endif

/* EOF */
