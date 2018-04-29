// Feuerkraft - A Tank Battle Game
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
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

#include <assert.h>
#include <libguile.h>
#include <ClanLib/Core/System/cl_assert.h>

#include "property.hpp"
#include "property_set.hpp"
#include "guile.hpp"

namespace Guile {
std::string
scm2string (SCM data)
{
  std::string str;

  if (scm_is_true(scm_string_p(data)))
    {
      char* tmpstr = scm_to_utf8_string(data);
      str = tmpstr;
      free(tmpstr);
    } else {
      SCM scmstr = scm_make_string(scm_from_int(0), SCM_UNDEFINED);
      SCM port = scm_mkstrport(SCM_INUM0, scmstr,
                               SCM_OPN | SCM_WRTNG, "scm_mkstrport");
      scm_display(data, port);
      char* tmpstr = scm_to_utf8_string(scmstr);
      str = tmpstr;
      free(tmpstr);
    }
  return str;
}

SCM vector2scm (const FloatVector2d& vec)
{
  /** If this causes throuble on WIN32, replace it with scm_cons() */
  return SCM_BOOL_F; /*scm_listify (scm_symbol2scm ("pos"),
                       scm_double2scm(vec.x),
                       scm_double2scm(vec.y),
                       scm_double2scm(vec.z),
                       SCM_UNDEFINED);*/
}

SCM pos2scm (int x, int y)
{
  return SCM_BOOL_F;/*scm_listify (scm_symbol2scm ("pos"),
                      scm_int2scm (x),
                      scm_int2scm (y),
                      SCM_UNDEFINED);*/
}

void pretty_print (std::ostream& stream, SCM obj)
{
  std::cout << "pretty_print" << std::endl;
  // FIXME: ...lalala..
  scm_write (obj, SCM_UNDEFINED);
  scm_newline (SCM_UNDEFINED);

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
  assert(scm_keyword_p(keyword));
  //puts("keyword2string: ");
  //scm_display(keyword);
  //scm_newline();
  //scm_display(scm_keyword_dash_symbol(keyword));
  //scm_newline();

  char* str = scm_to_utf8_string(scm_symbol_to_string(scm_keyword_to_symbol(keyword)));
  std::string ret = str + 1; // skip the dash
  free(str);
  return ret;
}

AList keywords2alist(SCM lst)
{
  AList alist;
  while(scm_is_true(scm_pair_p(lst)) && !scm_is_true(scm_null_p(scm_cdr(lst))))
    {
      SCM key  = scm_car(lst);
      SCM data = scm_cadr(lst);

      if (scm_is_false(scm_keyword_p(key)))
        {
          std::cout << "Skipping keyword: " << key << std::endl;
        }
      else
        {
          std::string keyword = Guile::keyword2string(key);
          if (scm_is_true(scm_string_p(data)))
            {
              alist.set_string(keyword,
                               Guile::scm2string(data));
            }
          else if (scm_is_true(scm_exact_p(data)))
            {
              alist.set_int(keyword,
                            scm_to_int(data));
            }
          else if (scm_is_true(scm_inexact_p(data)))
            {
              alist.set_float(keyword,
                              scm_to_double(data));
            }
          else if (scm_is_true(scm_boolean_p(data)))
            {
              alist.set_bool(keyword,
                             scm_to_bool(data));
            }
          else if (scm_is_true(scm_list_p(data)) && scm_ilength(data) == 2
                   && scm_is_true(scm_exact_p(scm_car(data)))
                   && scm_is_true(scm_exact_p(scm_cadr(data))))
            {
              IntVector2d vec;
              vec.x = scm_to_int(scm_car(data));
              vec.y = scm_to_int(scm_cadr(data));
              alist.set_int_vector2d(keyword,
                                     vec);
            }
          else if (scm_is_true(scm_symbol_p(data)))
            {
              alist.set_string(keyword,
                               Guile::symbol2string(data));
            }
          else
            {
              std::cout << "Guile: Error: Couldn't handle data" << std::endl;
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
  while(!scm_is_true(scm_null_p(lst)))
    {
      SCM key  = scm_caar(lst);
      SCM data = scm_cdar(lst);

      if (scm_is_true(scm_pair_p(data)) && scm_is_true(scm_null_p(scm_cdr(data))))
        data = scm_car(data);

      if (!scm_is_true(scm_symbol_p(key)))
        {
          std::cout << "Guile: Error: key not a symbol" << std::endl;
          scm_display(key, SCM_UNDEFINED);
          scm_newline(SCM_UNDEFINED);
        }
      else
        {
          if (scm_is_true(scm_string_p(data)))
            {
              alist.set_string(Guile::symbol2string(key),
                               Guile::scm2string(data));
            }
          else if (scm_is_true(scm_exact_p(data)))
            {
              alist.set_int(Guile::symbol2string(key),
                            scm_to_int(data));
            }
          else if (scm_is_true(scm_inexact_p(data)))
            {
              alist.set_float(Guile::symbol2string(key),
                              scm_to_double(data));
            }
          else if (scm_is_true(scm_boolean_p(data)))
            {
              alist.set_bool(Guile::symbol2string(key),
                             scm_to_bool(data));
            }
          else if (scm_is_true(scm_list_p(data)) && scm_ilength(data) == 2
                   && scm_is_true(scm_exact_p(scm_car(data)))
                   && scm_is_true(scm_exact_p(scm_cadr(data))))
            {
              IntVector2d vec;
              vec.x = scm_to_int(scm_car(data));
              vec.y = scm_to_int(scm_cadr(data));
              alist.set_int_vector2d(Guile::symbol2string(key),
                                     vec);
            }
          else if (scm_is_true(scm_symbol_p(data)))
            {
              alist.set_string(Guile::symbol2string(key),
                               Guile::symbol2string(data));
            }
          else
            {
              std::cout << "Guile: Error: Couldn't handle data" << std::endl;
              scm_display(data, SCM_UNDEFINED);
              scm_newline(SCM_UNDEFINED);
            }
        }

      lst = scm_cdr(lst);
    }
  return alist;
}

std::string symbol2string(SCM symbol)
{
  char* c_str = scm_to_utf8_string(scm_symbol_to_string(symbol));
  std::string str = c_str;
  free(c_str);
  return str;
}

void enter_repl()
{
  SCM func = scm_c_lookup("feuerkraft:repl");
  if (func != SCM_BOOL_F)
    {
      scm_call_0(scm_variable_ref(func));
    }
  else
    {
      std::cout << "### Error: feuerkraft.scm must be loaded to use the repl!" << std::endl;
    }
}

void scm2property(PropertySet& properties, const char* name, SCM value)
{
  if (scm_is_true(scm_string_p(value)))
    {
      properties.set_string(name, Guile::scm2string(value));
    }
  else if (scm_is_true(scm_boolean_p(value)))
    {
      properties.set_bool(name, scm_to_bool(value));
    }
  else if (scm_is_true(scm_exact_p(value)))
    {
      properties.set_int(name, scm_to_int(value));
    }
  else if (scm_is_true(scm_inexact_p(value)))
    {
      properties.set_float(name, scm_to_double(value));
    }
  else
    {
      std::cout << "Unhandled value" << std::endl;
    }
}

SCM  property2scm(const Property& property)
{
  switch(property.get_type())
    {
    case Property::T_INT:
      return scm_from_int(property.get_int());
      break;

    case Property::T_FLOAT:
      return scm_from_double(property.get_float());
      break;

    case Property::T_BOOL:
      return scm_from_bool(property.get_bool());
      break;

    case Property::T_STRING:
      return scm_from_utf8_string(property.get_string().c_str());
      break;

    default:
      std::cout << "Guile: Unhandled property type" << std::endl;
      return SCM_UNSPECIFIED;
      break;
    }
}

void enable_debug()
{
#if 0 // OLD Guile
  SCM_DEVAL_P = 1;
  SCM_BACKTRACE_P = 1;
  SCM_RECORD_POSITIONS_P = 1;
  SCM_RESET_DEBUG_MODE;
#else
  if (false)
  {
    scm_c_eval_string("(debug-enable 'debug)"
                      "(debug-enable 'backtrace)"
                      "(read-enable  'positions)");
  }
#endif
}

/** Disable all debugging */
void disable_debug()
{
  if (false)
  {
    scm_c_eval_string("(debug-disable 'debug)"
                      "(debug-disable 'backtrace)"
                      "(read-disable  'positions)");
  }
}

void enable_readline()
{
#ifdef WITH_STATIC_READLINE
  std::cout << "Loading readline... " << std::endl;
  scm_init_readline();
#endif

  scm_c_eval_string("(use-modules (ice-9 readline))"
                    "(activate-readline)");
}

} // namespace Guile

/* EOF */
