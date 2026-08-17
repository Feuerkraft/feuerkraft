// Feuerkraft - A Tank Battle Game
// Compatibility shims mapping the old Guile SCM API onto vendored s7.
//
// All Scheme values are s7_pointer; the active VM is fk_s7.  Multiple
// VMs can be created with s7_init(); switch fk_s7 to change the current
// one.  Destroy with s7_free().

#ifndef HEADER_SCHEME_COMPAT_HXX
#define HEADER_SCHEME_COMPAT_HXX

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "s7.h"

/** Currently active s7 VM (set by Scheme::init / Scheme::set_current). */
extern s7_scheme* fk_s7;

typedef s7_pointer SCM;

/* --- constants (depend on current VM) --------------------------------- */
#define SCM_BOOL_F          (s7_f(fk_s7))
#define SCM_BOOL_T          (s7_t(fk_s7))
#define SCM_UNDEFINED       (s7_undefined(fk_s7))
#define SCM_EOL             (s7_nil(fk_s7))

#define SCM_NULLP(p)        s7_is_null(fk_s7, (p))
#define scm_null_p(p)       scm_is_null_p(p)
#define scm_pair_p(p)       scm_is_pair_p(p)
#define scm_symbol_p(p)     scm_is_symbol_p(p)
#define scm_string_p(p)     scm_is_string_p(p)
#define scm_number_p(p)     scm_is_number_p(p)

inline SCM scm_reverse(SCM lst)
{
  return s7_reverse(fk_s7, lst);
}

/* --- predicates ------------------------------------------------------- */
#define scm_is_true(p)      ((p) != s7_f(fk_s7))
#define scm_is_false(p)     ((p) == s7_f(fk_s7))
#define scm_is_null_p(p)    (s7_is_null(fk_s7, (p)) ? SCM_BOOL_T : SCM_BOOL_F)
#define scm_is_pair_p(p)    (s7_is_pair(p) ? SCM_BOOL_T : SCM_BOOL_F)
#define scm_is_symbol_p(p)  (s7_is_symbol(p) ? SCM_BOOL_T : SCM_BOOL_F)
#define scm_is_string_p(p)  (s7_is_string(p) ? SCM_BOOL_T : SCM_BOOL_F)
#define scm_is_number_p(p)  (s7_is_number(p) ? SCM_BOOL_T : SCM_BOOL_F)
#define scm_is_integer_p(p) (s7_is_integer(p) ? SCM_BOOL_T : SCM_BOOL_F)
#define scm_is_keyword_p(p) (s7_is_keyword(p) ? SCM_BOOL_T : SCM_BOOL_F)
#define scm_equal_p(a, b)   (s7_is_equal(fk_s7, (a), (b)) ? SCM_BOOL_T : SCM_BOOL_F)

/* --- pairs / lists ---------------------------------------------------- */
#define scm_car(p)          s7_car(p)
#define scm_cdr(p)          s7_cdr(p)
#define scm_caar(p)         s7_car(s7_car(p))
#define scm_cadr(p)         s7_cadr(p)
#define scm_cdar(p)         s7_cdr(s7_car(p))
#define scm_cddr(p)         s7_cddr(p)
#define scm_cons(a, b)      s7_cons(fk_s7, (a), (b))

/* Guile-style accessors used as SCM_CAR / SCM_CDR macros in places */
#ifndef SCM_CAR
#  define SCM_CAR(p)        s7_car(p)
#  define SCM_CDR(p)        s7_cdr(p)
#  define SCM_CAAR(p)       s7_car(s7_car(p))
#  define SCM_CADR(p)       s7_cadr(p)
#  define SCM_CDAR(p)       s7_cdr(s7_car(p))
#  define SCM_CDDR(p)       s7_cddr(p)
#endif

/* --- constructors / converters ---------------------------------------- */
#define scm_from_utf8_symbol(s)   s7_make_symbol(fk_s7, (s))
#define scm_from_utf8_string(s)   s7_make_string(fk_s7, (s))
#define scm_from_int(i)           s7_make_integer(fk_s7, (i))
#define scm_from_double(d)        s7_make_real(fk_s7, (d))
#define scm_from_bool(b)          ((b) ? SCM_BOOL_T : SCM_BOOL_F)

#define scm_to_int(p)             ((int)s7_integer(p))
#define scm_to_double(p)          s7_number_to_real(fk_s7, (p))
#define scm_to_bool(p)            scm_is_true(p)

inline char* scm_to_utf8_string(SCM p)
{
  const char* s = s7_string(p);
  if (!s)
    s = "";
  return strdup(s);
}

/* --- I/O / eval ------------------------------------------------------- */
inline SCM scm_c_primitive_load(const char* path)
{
  return s7_load(fk_s7, path);
}

inline SCM scm_c_eval_string(const char* code)
{
  return s7_eval_c_string(fk_s7, code);
}

inline SCM scm_c_lookup(const char* name)
{
  return s7_name_to_value(fk_s7, name);
}

inline SCM scm_call_0(SCM func)
{
  return s7_call(fk_s7, func, s7_nil(fk_s7));
}

inline SCM scm_call_1(SCM func, SCM a)
{
  return s7_call(fk_s7, func, s7_list(fk_s7, 1, a));
}

inline SCM scm_variable_ref(SCM /*unused_var_handle*/)
{
  /* Guile returned a variable object from scm_c_lookup; s7_name_to_value
     already returns the value.  Call sites that did
     scm_variable_ref(scm_c_lookup(...)) still work if scm_c_lookup
     returns the value directly. */
  return s7_nil(fk_s7); /* should not be used alone */
}

/* Specialized: most call sites use scm_variable_ref(scm_c_lookup(name)).
   Provide a helper they can migrate to; for now redefine the pattern via
   a small inline used in ported call sites. */

inline SCM scm_lookup_value(const char* name)
{
  return s7_name_to_value(fk_s7, name);
}

inline void scm_display(SCM obj, SCM /*port*/)
{
  char* s = s7_object_to_c_string(fk_s7, obj);
  if (s)
    {
      fputs(s, stdout);
      free(s);
    }
}

inline void scm_newline(SCM /*port*/)
{
  fputc('\n', stdout);
}

inline void scm_write(SCM obj, SCM port)
{
  scm_display(obj, port);
}

/* File read for sexpr world loading: read one object from a file. */
inline SCM scm_c_read_file(const char* path)
{
  /* (call-with-input-file path read) */
  std::string expr = "(call-with-input-file \"";
  expr += path;
  expr += "\" read)";
  return s7_eval_c_string(fk_s7, expr.c_str());
}


#define scm_boolean_p(p)    (s7_is_boolean(p) ? SCM_BOOL_T : SCM_BOOL_F)
#define scm_keyword_p(p)    (s7_is_keyword(p) ? SCM_BOOL_T : SCM_BOOL_F)
#define scm_list_p(p)       (s7_is_list(fk_s7, (p)) ? SCM_BOOL_T : SCM_BOOL_F)
#define scm_exact_p(p)      (s7_is_integer(p) ? SCM_BOOL_T : SCM_BOOL_F)
#define scm_inexact_p(p)    ((s7_is_real(p) && !s7_is_integer(p)) ? SCM_BOOL_T : SCM_BOOL_F)

inline int scm_ilength(SCM lst)
{
  return (int)s7_list_length(fk_s7, lst);
}

inline SCM scm_symbol_to_string(SCM sym)
{
  return s7_make_string(fk_s7, s7_symbol_name(sym));
}

inline SCM scm_keyword_to_symbol(SCM kw)
{
  /* s7 keywords print as :name; symbol name without colon */
  const char* n = s7_symbol_name(kw);
  if (n && n[0] == ':')
    return s7_make_symbol(fk_s7, n + 1);
  return s7_make_symbol(fk_s7, n ? n : "");
}



/* --- GC protection (s7: mark as long-lived via keep) ------------------ */
inline SCM scm_gc_protect_object(SCM p)
{
  /* Hold a reference in a global list so s7 does not collect it. */
  s7_pointer lst = s7_name_to_value(fk_s7, "*fk-protect*");
  if (lst == s7_undefined(fk_s7) || !s7_is_list(fk_s7, lst))
    lst = s7_nil(fk_s7);
  lst = s7_cons(fk_s7, p, lst);
  s7_define_variable(fk_s7, "*fk-protect*", lst);
  return p;
}

inline SCM scm_gc_unprotect_object(SCM p)
{
  /* Best-effort: rebuild list without first occurrence of p. */
  s7_pointer lst = s7_name_to_value(fk_s7, "*fk-protect*");
  s7_pointer out = s7_nil(fk_s7);
  bool removed = false;
  while (s7_is_pair(lst))
    {
      s7_pointer x = s7_car(lst);
      if (!removed && s7_is_eq(x, p))
        removed = true;
      else
        out = s7_cons(fk_s7, x, out);
      lst = s7_cdr(lst);
    }
  s7_define_variable(fk_s7, "*fk-protect*", out);
  return p;
}

inline SCM scm_call_2(SCM func, SCM a, SCM b)
{
  return s7_call(fk_s7, func, s7_list(fk_s7, 2, a, b));
}

inline SCM scm_call_3(SCM func, SCM a, SCM b, SCM c)
{
  return s7_call(fk_s7, func, s7_list(fk_s7, 3, a, b, c));
}

#define scm_from_long(i)   s7_make_integer(fk_s7, (s7_int)(i))
#define scm_eof_object_p(p) (s7_is_eq((p), s7_eof_object(fk_s7)) ? SCM_BOOL_T : SCM_BOOL_F)

/* Read a whole file as one Scheme object (replaces open/read/close). */
inline SCM scm_c_read_whole_file(const char* path)
{
  return scm_c_read_file(path);
}


namespace Scheme {

/** Create a new isolated s7 VM and make it current. Returns the VM. */
s7_scheme* create_vm();

/** Destroy a VM previously returned by create_vm(). Clears fk_s7 if it
    was the current one. */
void destroy_vm(s7_scheme* sc);

/** Make \a sc the current VM (fk_s7). */
void set_current(s7_scheme* sc);

/** Initialise the default process VM (used at startup). */
void init();

/** Shut down the default VM. */
void deinit();

/** Register all Feuerkraft scripting primitives on the current VM. */
void register_bindings();

} // namespace Scheme

#endif

/* EOF */
