//  $Id: ipc.cpp,v 1.1 2003/06/04 13:16:17 grumbel Exp $
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

#include <stdexcept>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

#include "ipc.hpp"

IPC::IPC(const std::string& arg_filename)
  : filename(arg_filename)
{
  if (mkfifo(filename.c_str(), S_IREAD | S_IWRITE) != 0)
    {
      throw std::runtime_error(strerror(errno));
    }

  if ((stream_fd = open(filename.c_str(), O_RDONLY)) == -1)
    {
      throw std::runtime_error(strerror(errno));
    }
}

IPC::~IPC()
{
  close(stream_fd);
  unlink(filename.c_str());
}

void 
IPC::update()
{
  if (something_to_read())
    {
      const ssize_t bufsize = 4096;
      char buf[bufsize];
      std::stringstream complete_buf;

      ssize_t read_size;
      do
        {
          read_size = read(stream_fd, buf, bufsize);

          complete_buf.write(buf, read_size);
        }
      while (read_size == bufsize);

      // Reopen the stream for a new bunch of input
      close(stream_fd);
      if ((stream_fd = open(filename.c_str(), O_RDONLY)) == -1)
        {
          throw std::runtime_error(strerror(errno));
        }

      std::cout << "[[[\n" 
                << complete_buf.str() 
                << "]]]\n";
    }
}

bool
IPC::something_to_read()
{
  fd_set fset;
  struct timeval timeout;

  FD_ZERO(&fset);
  FD_SET(stream_fd, &fset);

  timeout.tv_sec = 0;
  timeout.tv_usec = 0;

  return (select (FD_SETSIZE, &fset, NULL, NULL, &timeout) > 0);
}

/* EOF */
