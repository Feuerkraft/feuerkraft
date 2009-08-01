//  $Id: dijkstra_pathfinder.hpp,v 1.2 2003/06/03 14:11:22 grumbel Exp $
// 
//  Feuerkraft - A Tank Battle Game
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef HEADER_DIJKSTRA_PATHFINDER_HXX
#define HEADER_DIJKSTRA_PATHFINDER_HXX

#include <queue>
#include <vector>
#include "field.hpp"
#include "pathfinder.hpp"

/** Dijkstra Pathfinder */
class DijkstraPathfinder
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
    unsigned int parent  : 3;
    unsigned int cost    : 8;
    unsigned int x       : 8;
    unsigned int y       : 8;
#endif
  };

  struct PQComp
  {
    bool operator()(Node* a, Node* b) {
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
  std::vector<Pos> path;

  State state;
public:
  DijkstraPathfinder(Field<int>* arg_field);
  
  void init(Pos& arg_start, Pos& arg_end);

  bool finished();
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
// compile-command: "g++-3.2 -DTESTME -Wall -O2 dijkstra_pathfinder.cpp  -o dijkstra_pathfinder -lclanCore"
// End:

/* EOF */
