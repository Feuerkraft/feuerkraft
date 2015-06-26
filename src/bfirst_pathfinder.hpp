// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
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

#ifndef HEADER_BFIRST_PATHFINDER_HXX
#define HEADER_BFIRST_PATHFINDER_HXX

#include <list>
#include "field.hpp"
#include "pathfinder.hpp"

/** Breadth First Pathfinder */
class BFirstPathfinder
{
public:
  struct Node
  {
    bool visited;
    unsigned char parent;
    unsigned int  cost;
    short x;
    short y;
  };

  enum State { WORKING,
               NO_PATH_AVAILABLE,
               PATH_FOUND,
               ALREADY_ON_GOAL };
private:
  Field<int>& field;
  Field<Node> node_field;
  std::list<Node*> open_nodes;
  Pos start;
  Pos end;
  std::vector<Pos> path;

  State state;
public:
  BFirstPathfinder(Field<int>* arg_field);

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

// Local Variables:
// compile-command: "g++-3.2 -DTESTME -Wall -O2 bfirst_pathfinder.cpp  -o bfirst_pathfinder -lclanCore"
// End:

#endif

/* EOF */
