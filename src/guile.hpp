// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// Helper functions on top of the s7 compatibility layer (formerly Guile).

#ifndef GUILE_HXX
#define GUILE_HXX

#include <string>
#include <iostream>

#include "scheme_compat.hpp"
#include "vector2d.hpp"
#include "alist.hpp"

class Property;
class PropertySet;

/** Scheme helper functions (name kept for call-site compatibility). */
namespace Guile {

std::string scm2string (SCM data);
SCM vector2scm (const FloatVector2d& vec);
SCM pos2scm (int x, int y);
SCM symbol_value_pair (const std::string&, float);
void pretty_print (std::ostream& s, SCM obj);
bool equal_p(SCM a, SCM b);
SCM symbol2scm(const char* str);
std::string keyword2string(SCM keyword);
std::string symbol2string(SCM symbol);
void enter_repl();
void scm2property(PropertySet& properties, const char* name, SCM value);
SCM  property2scm(const Property& property);
AList scm2alist(SCM lst);
AList keywords2alist(SCM lst);
void enable_debug();
void disable_debug();
void enable_readline();

} // namespace Guile

#endif

/* EOF */
