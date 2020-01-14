#ifndef MRB_CXX_HELPERS_H
#define MRB_CXX_HELPERS_H

#include <vector>
#include <string>
#include <stdlib.h>
#include <cassert>
#include <mruby.h>
#include <mruby/array.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/string.h>
#include <mruby/variable.h>

typedef void (*mrb_data_free_func)(mrb_state *mrb, void*);

template <typename T> static inline mrb_value cxx_mrb_ary_new_vector(mrb_state*, std::vector<T>);
template <typename T> static inline mrb_value cxx_mrb_numeric_value(mrb_state*, T);
template <typename T> static inline T cxx_mrb_cast(mrb_state*, mrb_value);
template <typename T> static inline T cxx_mrb_get_arg(mrb_state*);

/*
 * Converts a vector of strings to a ruby array of strings
 */
template <>
inline mrb_value
cxx_mrb_ary_new_vector<std::string>(mrb_state* mrb, std::vector<std::string> vect)
{
  mrb_value result = mrb_ary_new_capa(mrb, vect.size());
  for (size_t i = 0; i < vect.size(); ++i) {
    mrb_ary_push(mrb, result, mrb_str_new_cstr(mrb, vect[i].c_str()));
  }
  return result;
}

template <typename T>
static void
cxx_mrb_data_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    T *data = static_cast<T*>(ptr);
    delete data;
  }
}

template <typename T>
static void
cxx_mrb_data_free_value(mrb_state *mrb, mrb_value self)
{
  cxx_mrb_data_free<T>(mrb, DATA_PTR(self));
}

static inline void
cxx_mrb_ensure_type_data(mrb_state *mrb, mrb_value self)
{
  if (mrb_type(self) != MRB_TT_DATA) {
    mrb_check_type(mrb, self, MRB_TT_DATA);
  }
}

template <typename T>
static inline T*
cxx_mrb_data_get_ptr(mrb_state *mrb, mrb_value self)
{
  cxx_mrb_ensure_type_data(mrb, self);
  T *object = static_cast<T*>(DATA_PTR(self));
  assert(object);
  return object;
}

template <> inline float
cxx_mrb_cast<float>(mrb_state *mrb, mrb_value value)
{
  return static_cast<float>(mrb_to_flo(mrb, value));
}

template <> inline int
cxx_mrb_cast<int>(mrb_state *mrb, mrb_value value)
{
  return static_cast<int>(mrb_int(mrb, value));
}

template <> inline unsigned int
cxx_mrb_cast<unsigned int>(mrb_state *mrb, mrb_value value)
{
  return static_cast<unsigned int>(mrb_int(mrb, value));
}

template <> inline mrb_value
cxx_mrb_numeric_value<float>(mrb_state *mrb, float value)
{
  return mrb_float_value(mrb, static_cast<mrb_float>(value));
}

template <> inline mrb_value
cxx_mrb_numeric_value<int>(mrb_state *mrb, int value)
{
  return mrb_fixnum_value(static_cast<mrb_int>(value));
}

template <> inline mrb_value
cxx_mrb_numeric_value<unsigned int>(mrb_state *mrb, unsigned int value)
{
  return mrb_fixnum_value(static_cast<mrb_int>(value));
}

template <> inline float
cxx_mrb_get_arg<float>(mrb_state *mrb)
{
  mrb_float value;
  mrb_get_args(mrb, "f", &value);
  return static_cast<float>(value);
}

template <> inline int
cxx_mrb_get_arg<int>(mrb_state *mrb)
{
  mrb_int value;
  mrb_get_args(mrb, "i", &value);
  return static_cast<int>(value);
}

template <> inline unsigned int
cxx_mrb_get_arg<unsigned int>(mrb_state *mrb)
{
  mrb_int value;
  mrb_get_args(mrb, "i", &value);
  return static_cast<unsigned int>(value);
}

template <> inline bool
cxx_mrb_get_arg<bool>(mrb_state *mrb)
{
  mrb_bool value;
  mrb_get_args(mrb, "b", &value);
  return static_cast<bool>(value);
}

#endif
