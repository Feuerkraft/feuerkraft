//  $Id: shortcut_pathfinder.cxx,v 1.4 2003/06/03 14:11:22 grumbel Exp $
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

#include <ClanLib/core.h>
#include <iostream>
#include <unistd.h>
#include "shortcut_pathfinder.hxx"

struct NodeCost;
struct NodeWalkable;

typedef ShortcutPathfinder<Field<int>, NodeWalkable, NodeCost> MyPathfinder;

struct NodeWalkable {
  inline bool operator()(int a) {
    return a > 0;
  };
};

struct NodeCost {
  Pos goal;

  NodeCost(Pos& goal) 
    : goal(goal)
  {
  }

  inline int operator()(Node& node) {
    return int(PosDistance(Pos(node.x, node.y), goal));
  };
};

void generate_map(Field<int>& field)
{
  for(int y = 0; y < field.get_height(); ++y)
    for(int x = 0; x < field.get_width(); ++x)
      {
        field(x,y) = rand()%10;
      }

  // Map smoothing
  for(int count = 0; count < 3; ++count)
    for(int y = 1; y < field.get_height()-1; ++y)
      for(int x = 1; x < field.get_width()-1; ++x)
        {
          field(x,y) = (field(x-1,y) + field(x+1,y) + field(x,y-1) + field(x,y+1))/4;
        }
}

#ifdef TESTME
/*
  .2msec for 256x256 grid
*/
int main()
{
  CL_SetupCore::init();

  srand(time(NULL));
  Field<int> field(50, 30);

  unsigned int start_time = CL_System::get_time();
  unsigned int end_time;

  generate_map(field);

  MyPathfinder pathfinder(&field, NodeWalkable(), NodeCost(goal));

  Pos start;
  Pos end;

  for(int count = 0; count < 1000; ++count)
    {
      start.x = rand()%field.get_width();
      start.y = rand()%field.get_height();
  
      end.x = rand()%field.get_width();
      end.y = rand()%field.get_height();
      
      pathfinder.init(start, end);
      //pathfinder.display();

      //int i = 0;
      //std::cout << "Start: " << start.x << " " << start.y << std::endl;
      //std::cout << "End:   " << end.x << " " << end.y << std::endl;

      int rounds = 0;
      while(!pathfinder.finished())
        {
          //for(int i = 0; i < 10 && !pathfinder.finished(); ++i)
          pathfinder.process_one_open_node();
          ++rounds;
          //std::cout << "c" << std::endl;
          //pathfinder.display();
          //getchar();
        }

      std::cout << "c" << std::endl;
      pathfinder.display();
      std::cout << "Rounds: " << rounds << std::endl;
      getchar();
     
      //pathfinder.display();
      
      /*
        if (pathfinder.get_state() != ShortcutPathfinder::PATH_FOUND)
        {
        std::cout << "No Path could be found" << std::endl;
        }
        else
        {
        std::cout << "Found path" << std::endl;
        std::vector<Pos>& path = pathfinder.get_path();
        for (std::vector<Pos>::iterator i = path.begin(); i != path.end(); ++i)
        {
        std::cout << "[" << i->x << ", " << i->y << "] ";
        }       
        std::cout << std::endl;
        }
      */

      //      getchar();
      //std::cout << "round: " << ++i << std::endl;
    }
  end_time = CL_System::get_time();
  std::cout << "Msec: " << end_time - start_time << std::endl;

  CL_SetupCore::deinit();
}
#elif TESTME2
int main()
{
  CL_SetupCore::init();

  srand(time(NULL));
  Field<int> field(256, 256);

  generate_map(field);

  MyPathfinder pathfinder(&field, NodeWalkable(), NodeCost());

  Pos start;
  Pos end;

  unsigned int start_time = CL_System::get_time();
  unsigned int end_time;


  for(int count = 0; count < 1000; ++count)
    {
      start.x = rand()%field.get_width();
      start.y = rand()%field.get_height();
  
      end.x = rand()%field.get_width();
      end.y = rand()%field.get_height();

      pathfinder.init(start, end);
    
      while(!pathfinder.finished())
        {
          pathfinder.process_one_open_node();
        }
      //std::cout << "State: " << rounds << " " << pathfinder.get_state() << std::endl;
    }
  end_time = CL_System::get_time();
  std::cout << "Msec: " << end_time - start_time << std::endl;

  CL_SetupCore::deinit();
}
#endif

// Local Variables:
// compile-command: "g++-3.2 -DTESTME -g -Wall -O2 shortcut_pathfinder.cxx  -o shortcut_pathfinder -lclanCore"
// End:

/* EOF */
