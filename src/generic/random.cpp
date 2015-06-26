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

#include <stdlib.h>
#include "random.hpp"

float
Random::frand (float max)
{
  return (float(::rand ()) / RAND_MAX) * max;
}

float
Random::frand (float min, float max)
{
  return frand(max - min) + min;
}

int
Random::rand (int max)
{
  return ::rand() % max;
}

int
Random::rand (int min, int max)
{
  return ::rand () % (max - min) + min;
}

/* EOF */
