//  $Id: sequence_manager.hxx,v 1.3 2003/06/03 14:11:22 grumbel Exp $
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

#ifndef HEADER_SEQUENCE_MANAGER_HXX
#define HEADER_SEQUENCE_MANAGER_HXX

#include <vector>

class SequenceHook
{
private:
  int id;
public:
  SequenceHook();
  
  int  get_id() const { return id; }
  void set_id(int arg_id) { id = arg_id; }

  virtual void call() =0;
};

template<class Func>
class GenericSequenceHook : public SequenceHook
{
private:
  Func func;
public:
  GenericSequenceHook(Func arg_func) 
    : func(arg_func)
  {
  }

  virtual ~GenericSequenceHook() {}

  void call() { func(); }
};

/** */
class SequenceManager
{
private:
  int current_sequence_id;
  typedef std::vector<SequenceHook*> Hooks;
  Hooks hooks;

  static SequenceManager* current_; 
public:
  static SequenceManager* current() {
    if (current_) 
      return current_; 
    else
      return current_ = new SequenceManager();
  }

  SequenceManager();

  /** Start a sequenze and return an id, stuff that gets added to the
      sequence hook, will get called once the end_sequence is called
      with the returned id */
  int  start_sequence();

  /** End a sequence and call the hook accociated with sequence_id */
  void end_sequence(int sequence_id);

  void add_hook(SequenceHook* hook);
};

#endif

/* EOF */
