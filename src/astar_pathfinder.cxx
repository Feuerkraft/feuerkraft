//  $Id: astar_pathfinder.cxx,v 1.1 2003/04/29 19:37:02 grumbel Exp $
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
#include "astar_pathfinder.hxx"

AStarPathfinder::AStarPathfinder(Field<int>* arg_field)
  : field(*arg_field),
    node_field(field.get_width(), field.get_height())
{
}

void
AStarPathfinder::init(Pos& arg_start, Pos& arg_end)
{
  start = arg_start;
  end   = arg_end;

  if (start.x == end.x
      && start.y == end.y)
    {
      state = ALREADY_ON_GOAL;
      return;
    }

  for(int y = 0; y < node_field.get_height(); ++y)
    for(int x = 0; x < node_field.get_width(); ++x)
      {
        Node& node = node_field(x,y);
        node.visited = 0;
        node.x = x;
        node.y = y;
        node.parent = PARENT_NONE;
      }

  state = WORKING;

  Node& node = node_field(start.x, start.y);
  
  node.visited = 1;
  node.cost    = 0;
  node.parent  = PARENT_GOAL;

  make_neighbors_open(node);
}

bool
AStarPathfinder::finished()
{
  return state != WORKING;
}

void
AStarPathfinder::process_one_open_node()
{
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
AStarPathfinder::make_neighbors_open(Node& cnode)
{
  if (cnode.x > 0)
    {
      if (field(cnode.x - 1, cnode.y) == 0) // node is walkable
        {
          Node& west = node_field(cnode.x - 1, cnode.y);

          if (west.visited == 0 && west.parent == PARENT_NONE)
            {
              west.parent = PARENT_EAST;
              west.cost   = cnode.cost + 1;
              add_to_open_nodes(west);
            }
        }
    }

  if (int(cnode.x) < node_field.get_width()-1  && field(cnode.x+1, cnode.y) == 0)
    {
      Node& east = node_field(cnode.x + 1, cnode.y);
      if (east.visited == 0  && east.parent == PARENT_NONE) 
        {
          east.parent = PARENT_WEST;
          east.cost   = cnode.cost + 1;
          add_to_open_nodes(east);
        }
    }

  if (cnode.y > 0 && field(cnode.x, cnode.y - 1) == 0)
    {
      Node& north = node_field(cnode.x, cnode.y - 1);
      if (north.visited == 0  && north.parent == PARENT_NONE)
        {
          north.parent = PARENT_SOUTH;
          north.cost   = cnode.cost + 1;
          add_to_open_nodes(north);
        }
    }
  
  if (int(cnode.y) < node_field.get_height() - 1  && field(cnode.x, cnode.y+1) == 0)
    {
      Node& south = node_field(cnode.x, cnode.y + 1);
      if (south.visited == 0  && south.parent == PARENT_NONE)
        {
          south.parent = PARENT_NORTH;
          south.cost   = cnode.cost + 1;
          add_to_open_nodes(south);
        }
    }
}

void
AStarPathfinder::add_to_open_nodes(Node& cnode)
{
  assert(cnode.parent != PARENT_NONE);
  open_nodes.push(&cnode);
}

void
AStarPathfinder::display()
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
  std::cout << "OpenNodes: " << open_nodes.size() << std::endl;
  std::cout << "State: " << state << std::endl;
}

bool
AStarPathfinder::is_path_node(int x, int y)
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

AStarPathfinder::Node&
AStarPathfinder::resolve_parent(Node& node)
{
  if (node.parent == PARENT_NONE)
    {
      display();
      assert(false);
    }

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
AStarPathfinder::construct_path()
{
  //std::cout << "Construct path" << std::endl;
  // We construct the path reverse, so we start at the end
  Node& current_node = node_field(end.x, end.y);

  while(current_node.parent != PARENT_GOAL)
    {
      //std::cout << ">>> Node: " << current_node.x << " " << current_node.y << std::endl;

      path.push_back(Pos(current_node.x, current_node.y));
      current_node = resolve_parent(current_node);
    }
}

#ifdef TESTME
int main()
{
  CL_SetupCore::init();

  srand(time(NULL));
  Field<int> field(80, 50);

  unsigned int start_time = CL_System::get_time();
  unsigned int end_time;
  //for(int count = 0; count < 100; ++count)
  //{
  for(int y = 0; y < field.get_height(); ++y)
    for(int x = 0; x < field.get_width(); ++x)
      {
        field(x,y) = (rand()%20) > 5 ? 0 : 1;
      }

  AStarPathfinder pathfinder(&field);
  Pos start;
  Pos end;
  start.x = rand()%field.get_width();
  start.y = rand()%field.get_height();

  end.x = rand()%field.get_width();
  end.y = rand()%field.get_height();

  pathfinder.init(start, end);
  //pathfinder.display();

  //int i = 0;
  //std::cout << "Start: " << start.x << " " << start.y << std::endl;
  //std::cout << "End:   " << end.x << " " << end.y << std::endl;

  while(!pathfinder.finished())
    {
      for(int i = 0; i < 10 && !pathfinder.finished(); ++i)
        pathfinder.process_one_open_node();

      std::cout << "c" << std::endl;
      pathfinder.display();
      getchar();
    }
  end_time = CL_System::get_time();

  pathfinder.display();
      
  if (pathfinder.get_state() != AStarPathfinder::PATH_FOUND)
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

  //      getchar();
  //std::cout << "round: " << ++i << std::endl;
  //}
  std::cout << "Msec: " << end_time - start_time << std::endl;

  CL_SetupCore::deinit();
}
#endif

// Local Variables:
// compile-command: "g++-3.2 -DTESTME -Wall -O2 astar_pathfinder.cxx  -o astar_pathfinder -lclanCore"
// End:

/* EOF */
