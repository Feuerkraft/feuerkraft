//  $Id: pathfinder.hxx,v 1.3 2003/04/29 11:46:06 grumbel Exp $
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

#ifndef HEADER_PATHFINDER_HXX
#define HEADER_PATHFINDER_HXX

#include <list>
#include "field.hxx"

enum { PARENT_NONE,
       PARENT_NORTH,
       PARENT_SOUTH,
       PARENT_EAST,
       PARENT_WEST }; 

struct Node
{
  unsigned int visited :  1;
  unsigned int open    :  1;
  unsigned int parent  :  3;
  unsigned int cost    : 10;
  unsigned int x       :  8;
  unsigned int y       :  8;
};

struct Pos {
  int x;
  int y;
};

/** */
class Pathfinder
{
public:
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

  State state;
public:
  Pathfinder(Field<int>* arg_field);
  
  void init(Pos& arg_start, Pos& arg_end);

  bool finished();

  std::vector<Pos> get_path();

  State get_state() { return state; }
  void construct_path();
  void make_neighbors_open(Node& cnode);
  void process_one_open_node();
  void add_to_open_nodes(Node& cnode);

  void display();
};

#endif

/* EOF */
