//  $Id: shortcut_pathfinder.hxx,v 1.2 2003/04/30 15:03:26 grumbel Exp $
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

#ifndef HEADER_SHORTCUT_PATHFINDER_HXX
#define HEADER_SHORTCUT_PATHFINDER_HXX

#include <queue>
#include <vector>
#include "field.hxx"
#include "pathfinder.hxx"

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
class ShortcutPathfinder
{
public:
  enum State { WORKING,
               NO_PATH_AVAILABLE, 
               PATH_FOUND, 
               ALREADY_ON_GOAL };

  struct Node {
#if 0
    bool visited;
    unsigned char parent;
    unsigned int  cost;

    short x;
    short y;
#else
    unsigned int visited : 1;
    /// If parent != PARENT_NONE then is in open
    unsigned int parent  : 3; 
    unsigned int cost    : 8;

    unsigned int x       : 8;
    unsigned int y       : 8;
#endif
  };

  struct PQComp
  {
    inline bool operator()(Node* a, Node* b) {
      return a->cost > b->cost;
    }
  };
private:
  Field<int>& field;
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
  ShortcutPathfinder(Field<int>* arg_field);
  
  void init(Pos& arg_start, Pos& arg_end);

  inline bool finished() {
    return state != WORKING;
  }

  bool is_path_node(int x, int y);

  std::vector<Pos>& get_path() { return path; }

  State get_state() { return state; }
  void construct_path();
  void make_neighbors_open(Node& cnode);
  void process_one_open_node();
  void add_to_open_nodes(Node& cnode);

  Node& resolve_parent(Node& node);

  void display();
};

#endif

// Local Variables:
// compile-command: "g++-3.2 -DTESTME -Wall -O2 shortcut_pathfinder.cxx  -o shortcut_pathfinder -lclanCore"
// End:

/* EOF */
