// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef TURRET_HH
#define TURRET_HH

class Tank;

class Turret : public GameObj
{
private:
  Tank* tank;

  CL_Sprite fire_sur;
  CL_Sprite sur;
  CL_Sprite shadow;

  // The angle of the turent relative to the tank in radians
  float orientation;

  bool fireing;
  int  reloading;
  int  reloading_speed;

public:
  Turret (Tank*, int reloading_speed, std::string, std::string);
  ~Turret ();

  void draw (View& view);
  void update (float);

  void increase_angle (float delta);

  void start_fire ();
  void stop_fire ();

  void set_absolute_orientation (float orientation);
  void set_relative_orientation (float orientation);

private:
  Turret(const Turret&);
  Turret& operator=(const Turret&);
};

#endif // TURRET_HH

// EOF
