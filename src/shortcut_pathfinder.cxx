//  $Id: shortcut_pathfinder.cxx,v 1.2 2003/04/30 15:03:26 grumbel Exp $
//
//  Pingus - A free Lemmings clone
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

ShortcutPathfinder::ShortcutPathfinder(Field<int>* arg_field)
  : field(*arg_field),
    node_field(field.get_width(), field.get_height())
{
  for(int y = 0; y < node_field.get_height(); ++y)
    for(int x = 0; x < node_field.get_width(); ++x)
      {
        Node& node = node_field(x,y);
        node.visited = 0;
        node.parent  = PARENT_NONE;
        node.cost    = 0;
        node.x = x;
        node.y = y;
      }  
}

void
ShortcutPathfinder::init(Pos& arg_start, Pos& arg_end)
{
  max_rounds = 300;
  rounds = 0;
  start = arg_start;
  end   = arg_end;

  path.clear();

  if (start.x == end.x
      && start.y == end.y)
    {
      state = ALREADY_ON_GOAL;
      return;
    }

  //memset(&*node_field.begin(), 0, sizeof(Node));
  
  // initing node_field
  for(std::vector<Node*>::iterator i = dirty_nodes.begin(); i != dirty_nodes.end(); ++i)
    {
      Node& node = *(*i);
      node.visited = 0;
      node.parent  = PARENT_NONE;
      node.cost    = 0;
    }
  dirty_nodes.clear();

  open_nodes = OpenNodes();

  state = WORKING;

  Node& node = node_field(start.x, start.y);
  
  node.visited = 1;
  node.cost    = 0;
  node.parent  = PARENT_GOAL;

  make_neighbors_open(node);
}

inline 
void
ShortcutPathfinder::process_one_open_node()
{
  if (++rounds == max_rounds)
    {
      state = NO_PATH_AVAILABLE;
      return;
    }

  if (open_nodes.empty())
    {
      state = NO_PATH_AVAILABLE;
      return;
    }
  else
    {
      Node& cnode = *open_nodes.top();
      open_nodes.pop();

      assert(cnode.visited == 0);
      cnode.visited = 1;
      
      // Goal reached
      if (int(cnode.x) == end.x && int(cnode.y) == end.y)
        {
          construct_path();
          state = PATH_FOUND;
          return;
        }
     
      make_neighbors_open(cnode);
    }
}

void
ShortcutPathfinder::make_neighbors_open(Node& cnode)
{
  // FIXME: We don't handle neightbors with smaller cost here
  /*
    if n' is in Open
    and n'.cost < = newcost
    continue
  */
  if (cnode.x != 0)
    {
      if (field(cnode.x - 1, cnode.y) == 0) // node is walkable
        {
          Node& west = node_field(cnode.x - 1, cnode.y);

          if (west.visited == 0 && west.parent == PARENT_NONE)
            {
              west.parent = PARENT_EAST;
              //west.cost   = cnode.cost + 1;
              west.cost = int(PosDistance(Pos(cnode.x - 1, cnode.y), end));
              add_to_open_nodes(west);
            }
        }
    }

  if (int(cnode.x) != node_field.get_width()-1  && field(cnode.x+1, cnode.y) == 0)
    {
      Node& east = node_field(cnode.x + 1, cnode.y);
      if (east.visited == 0  && east.parent == PARENT_NONE) 
        {
          east.parent = PARENT_WEST;
          //east.cost   = cnode.cost + 1;
          east.cost     = int(PosDistance(Pos(cnode.x + 1, cnode.y), end));
          add_to_open_nodes(east);
        }
    }

  if (cnode.y != 0 && field(cnode.x, cnode.y - 1) == 0)
    {
      Node& north = node_field(cnode.x, cnode.y - 1);
      if (north.visited == 0  && north.parent == PARENT_NONE)
        {
          north.parent = PARENT_SOUTH;
          //north.cost   = cnode.cost + 1;
          north.cost     = int(PosDistance(Pos(cnode.x, cnode.y-1), end));
          add_to_open_nodes(north);
        }
    }
  
  if (int(cnode.y) != node_field.get_height() - 1  && field(cnode.x, cnode.y+1) == 0)
    {
      Node& south = node_field(cnode.x, cnode.y + 1);
      if (south.visited == 0  && south.parent == PARENT_NONE)
        {
          south.parent = PARENT_NORTH;
          //south.cost   = cnode.cost + 1;
          south.cost     = int(PosDistance(Pos(cnode.x, cnode.y+1), end));
          add_to_open_nodes(south);
        }
    }
}

inline void
ShortcutPathfinder::add_to_open_nodes(Node& cnode)
{
  assert(cnode.parent != PARENT_NONE);
  dirty_nodes.push_back(&cnode);
  open_nodes.push(&cnode);
}

void
ShortcutPathfinder::display()
{
  //std::cout << "c" << std::endl;
  for(int y = 0; y < node_field.get_height(); ++y)
    {
      for(int x = 0; x < node_field.get_width(); ++x)
        {
          if (0)
            {
              if (node_field(x,y).parent == PARENT_SOUTH)
                std::cout << "s";
              else if (node_field(x,y).parent == PARENT_WEST)
                std::cout << "w";
              else if (node_field(x,y).parent == PARENT_EAST)
                std::cout << "e";
              else if (node_field(x,y).parent == PARENT_NORTH)
                std::cout << "n";
              else
                std::cout << " ";
            }
          if (is_path_node(x,y))
            std::cout << "#";
          else
            std::cout << " ";

          if (x == start.x && y == start.y)
            std::cout << "S";
          else if (x == end.x && y == end.y)
            std::cout << "G";
          else if (field(x,y) != 0)
            std::cout << "O";
          else if (node_field(x,y).visited)
            std::cout << ".";
          else
            std::cout << " ";
        }
      std::cout << std::endl;
    }
  //std::cout << "OpenNodes: " << open_nodes.size() << std::endl;
  //std::cout << "State: " << state << std::endl;
}

bool
ShortcutPathfinder::is_path_node(int x, int y)
{
  if (path.empty()) 
    return false;
  else
    {
      for (std::vector<Pos>::iterator i = path.begin(); i != path.end(); ++i)
        {
          if (i->x == x && i->y == y)
            return true;
        }
      return false;
    }
}

ShortcutPathfinder::Node&
ShortcutPathfinder::resolve_parent(Node& node)
{
  assert(node.parent != PARENT_NONE);

  switch(node.parent)
    {
    case PARENT_NORTH:
      return node_field(node.x, node.y - 1);
    case PARENT_SOUTH:
      return node_field(node.x, node.y + 1);
    case PARENT_EAST:
      return node_field(node.x + 1, node.y);
    case PARENT_WEST:
      return node_field(node.x - 1, node.y);
    default:
      assert(!"resolve path error");
    }
  assert(!"resolve path error2");
  return *(Node*)0;
}

void
ShortcutPathfinder::construct_path()
{
  //std::cout << "Construct path" << std::endl;
  // We construct the path reverse, so we start at the end
  Node current_node = node_field(end.x, end.y);

  while(current_node.parent != PARENT_GOAL)
    {
      //std::cout << ">>> Node: " << current_node.x << " " << current_node.y << std::endl;

      path.push_back(Pos(current_node.x, current_node.y));
      current_node = resolve_parent(current_node);
    }
  //std::cout << "OPenNodes: " << open_nodes.size() << std::endl;
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

  for(int y = 0; y < field.get_height(); ++y)
    for(int x = 0; x < field.get_width(); ++x)
      {
        field(x,y) = (rand()%100) > 30 ? 0 : 1;
      }

  ShortcutPathfinder pathfinder(&field);

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

  for(int y = 0; y < field.get_height(); ++y)
    for(int x = 0; x < field.get_width(); ++x)
      {
        field(x,y) = (rand()%100) > 20 ? 0 : 1;
      }

  ShortcutPathfinder pathfinder(&field);

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
