//  $Id: shortcut_pathfinder.hpp,v 1.4 2003/06/03 14:11:22 grumbel Exp $
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

#ifndef HEADER_SHORTCUT_PATHFINDER_HXX
#define HEADER_SHORTCUT_PATHFINDER_HXX

#include <queue>
#include <vector>
#include "field.hpp"
#include "pathfinder.hpp"

struct Node {
  unsigned int visited : 1;
  /// If parent != PARENT_NONE then is in open
  unsigned int parent  : 3; 
  unsigned int cost    : 8;

  unsigned int x       : 8;
  unsigned int y       : 8;
};

/** Shortcut Pathfinder, it works like this:
    1. add all neightbours from the start node to open_nodes
    2. for next node in open_nodes
    -  check if goal node
    -  add all neightbours to open_nodes
    3. goto 2

    The open_nodes PQ is shorted after the distance from the node to
    the goal node, thus it is heading streight to the target node, but
    unlike AStar or Shortcut it doesn't take the cost correctly into
    account and it is only able to find a short path, not neccessarily
    the shortest.

    Average Speed of this pathfinder is ~.2msec for a 256x256 grid.
*/
template<class FieldType,
         class Walkable,
         class Cost>
class ShortcutPathfinder
{
public:
  enum State { WORKING,
               NO_PATH_AVAILABLE, 
               PATH_FOUND, 
               ALREADY_ON_GOAL };

  struct PQComp
  {
    inline bool operator()(Node* a, Node* b) {
      return a->cost > b->cost;
    }
  };
private:
  FieldType& field;
  Walkable walkable;
  Cost     cost;
  Field<Node> node_field;
  typedef std::priority_queue<Node*,
                              std::vector<Node*>, 
                              PQComp> OpenNodes;
  OpenNodes open_nodes;

  Pos start;
  Pos end;
  int rounds;
  int max_rounds;
  std::vector<Pos> path;

  std::vector<Node*> dirty_nodes;

  State state;
public:
  ShortcutPathfinder(FieldType* arg_field, const Walkable& arg_walkable, const Cost& arg_cost)
    : field(*arg_field),
      walkable(arg_walkable),
      cost(arg_cost),
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

  void init(Pos& arg_start, Pos& arg_end)
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

    // clean the node_field
    for(typename std::vector<Node*>::iterator i = dirty_nodes.begin(); i != dirty_nodes.end(); ++i)
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

  inline bool finished() 
  {
    return state != WORKING;
  }

  bool is_path_node(int x, int y)
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

  std::vector<Pos>& get_path() { return path; }

  State get_state() { return state; }
  
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
        if (walkable(field(cnode.x - 1, cnode.y))) // node is walkable
          {
            Node& west = node_field(cnode.x - 1, cnode.y);

            if (west.visited == 0 && west.parent == PARENT_NONE)
              {
                west.parent = PARENT_EAST;
                //west.cost   = cnode.cost + 1;
                west.cost = cost(west);
                add_to_open_nodes(west);
              }
          }
      }

    if (int(cnode.x) != node_field.get_width()-1  && walkable(field(cnode.x+1, cnode.y)))
      {
        Node& east = node_field(cnode.x + 1, cnode.y);
        if (east.visited == 0  && east.parent == PARENT_NONE) 
          {
            east.parent = PARENT_WEST;
            //east.cost   = cnode.cost + 1;
            east.cost     = cost(east);
            add_to_open_nodes(east);
          }
      }

    if (cnode.y != 0 && walkable(field(cnode.x, cnode.y - 1)))
      {
        Node& north = node_field(cnode.x, cnode.y - 1);
        if (north.visited == 0  && north.parent == PARENT_NONE)
          {
            north.parent = PARENT_SOUTH;
            //north.cost   = cnode.cost + 1;
            north.cost     = cost(north);
            add_to_open_nodes(north);
          }
      }
  
    if (int(cnode.y) != node_field.get_height() - 1  && walkable(field(cnode.x, cnode.y+1)))
      {
        Node& south = node_field(cnode.x, cnode.y + 1);
        if (south.visited == 0  && south.parent == PARENT_NONE)
          {
            south.parent = PARENT_NORTH;
            //south.cost   = cnode.cost + 1;
            south.cost     = cost(south);
            add_to_open_nodes(south);
          }
      }
  }
  
  inline void process_one_open_node()
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

  inline void add_to_open_nodes(Node& cnode)
  {
    assert(cnode.parent != PARENT_NONE);
    dirty_nodes.push_back(&cnode);
    open_nodes.push(&cnode);
  }

  Node&
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

  void display()
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
            if (!walkable(field(x,y)))
              std::cout << "X";
            else
              {
                //std::cout << " .,-nmlIFB"[cost(node_field(x,y))];
              }

            if (x == start.x && y == start.y)
              std::cout << "S";
            else if (x == end.x && y == end.y)
              std::cout << "G";
            else if (is_path_node(x,y))
              std::cout << "#";
            else if (node_field(x,y).visited)
              std::cout << ",";
            else
              std::cout << " ";
          }
        std::cout << std::endl;
      }
    //std::cout << "OpenNodes: " << open_nodes.size() << std::endl;
    //std::cout << "State: " << state << std::endl;
  }

};

#endif

// Local Variables:
// compile-command: "g++-3.2 -DTESTME -Wall -O2 shortcut_pathfinder.cpp  -o shortcut_pathfinder -lclanCore"
// End:

/* EOF */
