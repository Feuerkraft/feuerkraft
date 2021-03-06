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

#ifndef BUILDING_HXX
#define BUILDING_HXX

#include "../alist.hpp"

// Begin: Forward declarations
class GameWorld;
class Projectile;
class Radar;
class PropertySet;
class View;
class Radar;
// End: Forward declarations

class Building
{
private:
  int id;
  void register_properties();

protected:
  PropertySet* properties;

  /** Position in units of tiles */
  int x_pos;
  /** Position in units of tiles */
  int y_pos;

public:
  Building (const AList& lst);
  virtual ~Building ();

  PropertySet* get_properties() { return properties; }

  void set_id(int i) { id = i; }
  int  get_id() { return id; }

  // Draw the object onto the screen
  virtual void draw (View& view) =0;

  virtual void draw_energie (View& view) {}

  virtual void draw_radar (Radar& radar);

  // Update the object once a game loop
  virtual void update (float) =0;

  int get_x_pos () { return x_pos; }
  int get_y_pos () { return y_pos; }

  /** Returns the width which this building will take on the BuildingMap */
  virtual int get_map_width () =0;

  /** Returns the height which this building will take on the BuildingMap */
  virtual int get_map_height () =0;

  virtual void collide (Projectile*) {}

  virtual void collide (int energie) {}

  /** is_at() can be overwritten to provide a more detailed building
      'resolution', so that buildings can be subgrid large
      FIXME: Looks a bit hack like and doesn't work at polygon level  */
  virtual bool is_at (float x, float y) { return true; }

  /** If returns false the building is temporary inactive and will be
      'removed' from the collision map */
  virtual bool is_active() { return true; }

  /** If returns true the building will act normal, when returning
      false the building will 'disapear' from the collision map
   */
  virtual bool alive () { return true; }

private:
  Building(const Building&);
  Building& operator=(const Building&);
};

#endif

/* EOF */
