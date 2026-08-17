// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// Scheme helpers implemented on s7.

#include <cassert>
#include <cstdlib>
#include <iostream>

#include "property.hpp"
#include "property_set.hpp"
#include "guile.hpp"

namespace Guile {

std::string
scm2string (SCM data)
{
  if (scm_is_true(scm_is_string_p(data)))
    {
      char* tmp = scm_to_utf8_string(data);
      std::string str = tmp ? tmp : "";
      free(tmp);
      return str;
    }

  char* s = s7_object_to_c_string(fk_s7, data);
  std::string str = s ? s : "";
  free(s);
  return str;
}

SCM vector2scm (const FloatVector2d& /*vec*/)
{
  return SCM_BOOL_F;
}

SCM pos2scm (int /*x*/, int /*y*/)
{
  return SCM_BOOL_F;
}

SCM symbol_value_pair (const std::string& /*name*/, float /*value*/)
{
  return SCM_BOOL_F;
}

void pretty_print (std::ostream& /*stream*/, SCM obj)
{
  scm_display(obj, SCM_UNDEFINED);
  scm_newline(SCM_UNDEFINED);
}

bool equal_p(SCM a, SCM b)
{
  return scm_is_true(scm_equal_p(a, b));
}

SCM symbol2scm(const char* str)
{
  return scm_from_utf8_symbol(str);
}

std::string keyword2string(SCM keyword)
{
  assert(scm_is_true(scm_keyword_p(keyword)));
  SCM sym = scm_keyword_to_symbol(keyword);
  return symbol2string(sym);
}

AList keywords2alist(SCM lst)
{
  AList alist;
  while (scm_is_true(scm_is_pair_p(lst)) && !scm_is_true(scm_is_null_p(scm_cdr(lst))))
    {
      SCM key  = scm_car(lst);
      SCM data = scm_cadr(lst);

      if (scm_is_false(scm_keyword_p(key)))
        {
          std::cout << "Skipping non-keyword key\n";
        }
      else
        {
          std::string keyword = Guile::keyword2string(key);
          if (scm_is_true(scm_is_string_p(data)))
            alist.set_string(keyword, Guile::scm2string(data));
          else if (scm_is_true(scm_exact_p(data)))
            alist.set_int(keyword, scm_to_int(data));
          else if (scm_is_true(scm_inexact_p(data)))
            alist.set_float(keyword, scm_to_double(data));
          else if (scm_is_true(scm_boolean_p(data)))
            alist.set_bool(keyword, scm_to_bool(data));
          else if (scm_is_true(scm_list_p(data)) && scm_ilength(data) == 2
                   && scm_is_true(scm_exact_p(scm_car(data)))
                   && scm_is_true(scm_exact_p(scm_cadr(data))))
            {
              IntVector2d vec;
              vec.x = scm_to_int(scm_car(data));
              vec.y = scm_to_int(scm_cadr(data));
              alist.set_int_vector2d(keyword, vec);
            }
          else if (scm_is_true(scm_is_symbol_p(data)))
            alist.set_string(keyword, Guile::symbol2string(data));
          else
            {
              std::cout << "Guile: Error: Couldn't handle keyword data\n";
              scm_display(data, SCM_UNDEFINED);
              scm_newline(SCM_UNDEFINED);
            }
        }
      lst = scm_cddr(lst);
    }
  return alist;
}

AList scm2alist(SCM lst)
{
  AList alist;
  while (!scm_is_true(scm_is_null_p(lst)))
    {
      if (!scm_is_true(scm_is_pair_p(lst)))
        break;
      SCM item = scm_car(lst);
      if (scm_is_true(scm_is_pair_p(item)))
        {
          SCM key  = scm_car(item);
          SCM data = scm_cdr(item);
          // Allow (key . value) or (key value ...)
          if (scm_is_true(scm_is_pair_p(data)))
            data = scm_car(data);

          if (scm_is_true(scm_is_symbol_p(key)))
            {
              if (scm_is_true(scm_is_string_p(data)))
                alist.set_string(Guile::symbol2string(key), Guile::scm2string(data));
              else if (scm_is_true(scm_exact_p(data)))
                alist.set_int(Guile::symbol2string(key), scm_to_int(data));
              else if (scm_is_true(scm_inexact_p(data)))
                alist.set_float(Guile::symbol2string(key), scm_to_double(data));
              else if (scm_is_true(scm_boolean_p(data)))
                alist.set_bool(Guile::symbol2string(key), scm_to_bool(data));
              else if (scm_is_true(scm_list_p(data)) && scm_ilength(data) == 2
                       && scm_is_true(scm_exact_p(scm_car(data)))
                       && scm_is_true(scm_exact_p(scm_cadr(data))))
                {
                  IntVector2d vec;
                  vec.x = scm_to_int(scm_car(data));
                  vec.y = scm_to_int(scm_cadr(data));
                  alist.set_int_vector2d(Guile::symbol2string(key), vec);
                }
              else if (scm_is_true(scm_is_symbol_p(data)))
                alist.set_string(Guile::symbol2string(key), Guile::symbol2string(data));
              else
                {
                  std::cout << "Guile: Error: Couldn't handle data\n";
                  scm_display(data, SCM_UNDEFINED);
                  scm_newline(SCM_UNDEFINED);
                }
            }
        }
      lst = scm_cdr(lst);
    }
  return alist;
}

std::string symbol2string(SCM symbol)
{
  const char* n = s7_symbol_name(symbol);
  return n ? std::string(n) : std::string();
}

void enter_repl()
{
  std::cout << "### REPL not available under s7 embed yet\n";
}

void scm2property(PropertySet& properties, const char* name, SCM value)
{
  if (scm_is_true(scm_is_string_p(value)))
    properties.set_string(name, Guile::scm2string(value));
  else if (scm_is_true(scm_boolean_p(value)))
    properties.set_bool(name, scm_to_bool(value));
  else if (scm_is_true(scm_exact_p(value)))
    properties.set_int(name, scm_to_int(value));
  else if (scm_is_true(scm_inexact_p(value)))
    properties.set_float(name, scm_to_double(value));
  else
    std::cout << "Unhandled property value\n";
}

SCM property2scm(const Property& property)
{
  switch (property.get_type())
    {
    case Property::T_INT:
      return scm_from_int(property.get_int());
    case Property::T_FLOAT:
      return scm_from_double(property.get_float());
    case Property::T_BOOL:
      return scm_from_bool(property.get_bool());
    case Property::T_STRING:
      return scm_from_utf8_string(property.get_string().c_str());
    default:
      return SCM_BOOL_F;
    }
}

void enable_debug() {}
void disable_debug() {}
void enable_readline() {}

} // namespace Guile

/* EOF */
