//  $Id: pathfinder.cxx,v 1.4 2003/04/29 11:46:06 grumbel Exp $
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

#include <iostream>
#include <unistd.h>
#include "pathfinder.hxx"

Pathfinder::Pathfinder(Field<int>* arg_field)
  : field(*arg_field),
    node_field(field.get_width(), field.get_height())
{
}

void
Pathfinder::init(Pos& arg_start, Pos& arg_end)
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
        node.open    = 0;
        node.x = x;
        node.y = y;
      }

  state = WORKING;

  Node& node = node_field(start.x, start.y);
  
  node.visited = 1;
  node.cost    = 0;
  node.parent  = PARENT_NONE;

  make_neighbors_open(node);
}

bool
Pathfinder::finished()
{
  return state != WORKING;
}

void
Pathfinder::process_one_open_node()
{
  if (open_nodes.empty())
    {
      state = NO_PATH_AVAILABLE;
      return;
    }
  else
    {
      Node& cnode = *open_nodes.front();
      open_nodes.pop_front();

      assert(cnode.visited == 0);

      cnode.visited = 1;
      cnode.cost    = 1;
 
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
Pathfinder::make_neighbors_open(Node& cnode)
{ // Fixme no bound handling
  if (cnode.x > 0  && field(cnode.x-1, cnode.y) == 0)
    {
      Node& east = node_field(cnode.x - 1, cnode.y);
      if (east.visited == 0)
        add_to_open_nodes(east);
    }

  if (int(cnode.x) < node_field.get_width()-1  && field(cnode.x+1, cnode.y) == 0)
    {
      Node& west = node_field(cnode.x + 1, cnode.y);
      if (west.visited == 0)
        add_to_open_nodes(west);
    }

  if (cnode.y > 0 && field(cnode.x, cnode.y - 1) == 0)
    {
      Node& north = node_field(cnode.x, cnode.y - 1);
      if (north.visited == 0)
        add_to_open_nodes(north);
    }
  
  if (int(cnode.y) < node_field.get_height()-1   && field(cnode.x, cnode.y+1) == 0)
    {
      Node& south = node_field(cnode.x, cnode.y + 1);
      if (south.visited == 0)
        add_to_open_nodes(south);
    }
}

void
Pathfinder::add_to_open_nodes(Node& cnode)
{
  if (cnode.open == 0)
    {
      cnode.open = 1;
      open_nodes.push_back(&cnode);
    }
}

void
Pathfinder::display()
{
  std::cout << "c" << std::endl;
  for(int y = 0; y < node_field.get_height(); ++y)
    {
      for(int x = 0; x < node_field.get_width(); ++x)
        {
          if (x == start.x && y == start.y)
            std::cout << " S";
          else if (x == end.x && y == end.y)
            std::cout << " G";
          else if (field(x,y) != 0)
            std::cout << " O";
          else if (node_field(x,y).visited)
            std::cout << " .";
          else
            std::cout << " _";
      }
      std::cout << std::endl;
    }
  std::cout << "OpenNodes: " << open_nodes.size() << std::endl;
  std::cout << "State: " << state << std::endl;
}

void
Pathfinder::construct_path()
{
}

#ifdef TESTME
int main()
{
  Field<int> field(30, 30);

  for(int y = 0; y < field.get_height(); ++y)
    for(int x = 0; x < field.get_width(); ++x)
      {
        field(x,y) = (rand()%20) > 5 ? 0 : 1;
      }

  Pathfinder pathfinder(&field);
  Pos start;
  Pos end;
  start.x = 10;
  start.y = 10;

  end.x = 20;
  end.y = 20;

  pathfinder.init(start, end);
  pathfinder.display();

  int i = 0;
  while(!pathfinder.finished())
    {
      pathfinder.process_one_open_node();
      pathfinder.display();
      std::cout << "round: " << ++i << std::endl;
      getchar();
    }
  
  pathfinder.display();
}
#endif

/* EOF */
