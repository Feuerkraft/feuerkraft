// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
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

#ifndef FIELD_HXX
#define FIELD_HXX

#include <vector>
#include <assert.h>

template<class T>
class Field
{
private:
  int width;
  int height;
  std::vector<T> data;
public:
  typedef typename std::vector<T>::iterator  iterator;

  iterator begin() { return data.begin(); }
  iterator end()   { return data.end(); }

  Field (int arg_width, int arg_height)
    : width (arg_width), height (arg_height)
  {
    data.resize (width * height);
  }

  void resize (int arg_width, int arg_height)
  {
    width  = arg_width;
    height = arg_height;
    data.resize (width * height);
  }

  T& operator () (int x, int y) {
    assert(x >= 0 && x < width && y >= 0 && y < height);
    return data[width * y + x];
  }

  int get_width() const {
    return width;
  }

  int get_height() const {
    return height;
  }
};

#endif

/* EOF */
