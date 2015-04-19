#ifndef MRB_SFML_SHAPE_PRIV_H
#define MRB_SFML_SHAPE_PRIV_H

#include <mruby.h>
#include <mruby/class.h>
#include "mrb_transformable.hxx"
#include "mrb_drawable.hxx"

extern "C" void mrb_sfml_shape_init_bind(mrb_state *mrb, struct RClass *mod);

template <class T>
static inline void
shape_bind_class(mrb_state *mrb, struct RClass *cls)
{
  drawable_bind_class<T>(mrb, cls);
  transformable_bind_class<T>(mrb, cls);
}

#endif
