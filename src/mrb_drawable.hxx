#ifndef MRB_SFML_DRAWABLE_PRIV_H
#define MRB_SFML_DRAWABLE_PRIV_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <SFML/Graphics/Drawable.hpp>

/*
 * WARNING: DO NOT, and I repeat, DO NOT USE THIS FUNCTION ON NON-DRAWABLE
 * OBJECTS.
 * HORRIBLE, HORRIBLE THINGS WILL HAPPEN.
 * This function bypasses mruby's data type checking and pulls the DATA_PTR
 * directly, the only check done, is an assertion on the pointer.
 */
template <class T>
static inline T*
get_drawable(mrb_state *mrb, mrb_value self)
{
  T *drawable = static_cast<T*>(DATA_PTR(self));
  assert(drawable);
  return drawable;
}

template <class T>
static inline void
drawable_bind_class(mrb_state *mrb, struct RClass *cls)
{
  //
}

#endif
