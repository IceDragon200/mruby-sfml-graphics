#ifndef MRB_SFML_SHAPE_PRIV_H
#define MRB_SFML_SHAPE_PRIV_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/graphics/texture.hxx"
#include "mrb/sfml/graphics/color.hxx"
#include "mrb/sfml/graphics/rect.hxx"
#include "mrb_transformable.hxx"
#include "mrb_drawable.hxx"
#include "mrb/sfml/helpers.hxx"

MRB_SFML_EXTERN void mrb_sfml_shape_init_bind(mrb_state *mrb, struct RClass *mod);

/*
 * WARNING: DO NOT, and I repeat, DO NOT USE THIS FUNCTION ON NON-SHAPE
 * OBJECTS.
 * HORRIBLE, HORRIBLE THINGS WILL HAPPEN.
 * This function bypasses mruby's data type checking and pulls the DATA_PTR
 * directly, the only check done, is an assertion on the pointer.
 */
template <class T>
static inline T*
get_shape(mrb_state *mrb, mrb_value self)
{
  return cxx_mrb_data_get_ptr<T>(mrb, self);
}

static inline sf::Texture*
get_texture(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Texture*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_texture_type));
}

template <class T>
static mrb_value
shape_set_texture(mrb_state *mrb, mrb_value self)
{
  sf::Texture *texture;
  mrb_value texture_obj;
  mrb_bool reset_rect;
  T *shape;
  mrb_int argc = mrb_get_args(mrb, "o|b", &texture_obj, &reset_rect);
  shape = get_shape<T>(mrb, self);
  texture = get_texture(mrb, texture_obj);
  if (argc == 1) {
    shape->setTexture(texture);
  } else if (argc == 2) {
    shape->setTexture(texture, reset_rect);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected 1 or 2");
  }
  /* Keeps the texture alive as long as the Sprite exists */
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "__sfml_texture"), texture_obj);
  return self;
  return self;
}

template <class T>
static mrb_value
shape_set_texture_rect(mrb_state *mrb, mrb_value self)
{
  sf::IntRect *rect;
  mrb_get_args(mrb, "d", &rect, &mrb_sfml_int_rect_type);
  get_shape<T>(mrb, self)->setTextureRect(*rect);
  return self;
}

template <class T>
static mrb_value
shape_set_fill_color(mrb_state *mrb, mrb_value self)
{
  sf::Color *color;
  mrb_get_args(mrb, "d", &color, &mrb_sfml_color_type);
  get_shape<T>(mrb, self)->setFillColor(*color);
  return self;
}

template <class T>
static mrb_value
shape_set_outline_color(mrb_state *mrb, mrb_value self)
{
  sf::Color *color;
  mrb_get_args(mrb, "d", &color, &mrb_sfml_color_type);
  get_shape<T>(mrb, self)->setOutlineColor(*color);
  return self;
}

template <class T>
static mrb_value
shape_set_outline_thickness(mrb_state *mrb, mrb_value self)
{
  mrb_float thickness;
  mrb_get_args(mrb, "f", &thickness);
  get_shape<T>(mrb, self)->setOutlineThickness(thickness);
  return self;
}

template <class T>
static mrb_value
shape_get_texture(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "__sfml_texture"));
}

template <class T>
static mrb_value
shape_get_texture_rect(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_int_rect_value(mrb, get_shape<T>(mrb, self)->getTextureRect());
}

template <class T>
static mrb_value
shape_get_fill_color(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_color_value(mrb, get_shape<T>(mrb, self)->getFillColor());
}

template <class T>
static mrb_value
shape_get_outline_color(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_color_value(mrb, get_shape<T>(mrb, self)->getOutlineColor());
}

template <class T>
static mrb_value
shape_get_outline_thickness(mrb_state *mrb, mrb_value self)
{
  return mrb_float_value(mrb, get_shape<T>(mrb, self)->getOutlineThickness());
}

template <class T>
static mrb_value
shape_get_point_count(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(get_shape<T>(mrb, self)->getPointCount());
}

template <class T>
static mrb_value
shape_get_point(mrb_state *mrb, mrb_value self)
{
  mrb_int index;
  mrb_get_args(mrb, "i", &index);
  return mrb_sfml_vector2f_value(mrb, get_shape<T>(mrb, self)->getPoint(index));
}

template <class T>
static mrb_value
shape_get_local_bounds(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_float_rect_value(mrb, get_shape<T>(mrb, self)->getLocalBounds());
}

template <class T>
static mrb_value
shape_get_global_bounds(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_float_rect_value(mrb, get_shape<T>(mrb, self)->getGlobalBounds());
}

template <class T>
static inline void
shape_bind_class(mrb_state *mrb, struct RClass *cls)
{
  drawable_bind_class<T>(mrb, cls);
  transformable_bind_class<T>(mrb, cls);
  mrb_define_method(mrb, cls, "set_texture",           shape_set_texture<T>,           MRB_ARGS_ARG(1, 1));
  mrb_define_method(mrb, cls, "set_texture_rect",      shape_set_texture_rect<T>,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "set_fill_color",        shape_set_fill_color<T>,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "set_outline_color",     shape_set_outline_color<T>,     MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "set_outline_thickness", shape_set_outline_thickness<T>, MRB_ARGS_REQ(1));

  mrb_define_method(mrb, cls, "get_texture",           shape_get_texture<T>,           MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "get_texture_rect",      shape_get_texture_rect<T>,      MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "get_fill_color",        shape_get_fill_color<T>,        MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "get_outline_color",     shape_get_outline_color<T>,     MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "get_outline_thickness", shape_get_outline_thickness<T>, MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "get_point_count",       shape_get_point_count<T>,       MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "get_point",             shape_get_point<T>,             MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "get_local_bounds",      shape_get_local_bounds<T>,      MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "get_global_bounds",     shape_get_global_bounds<T>,     MRB_ARGS_NONE());

  mrb_define_alias(mrb, cls, "texture=", "set_texture");
  mrb_define_alias(mrb, cls, "texture_rect=", "set_texture_rect");
  mrb_define_alias(mrb, cls, "fill_color=", "set_fill_color");
  mrb_define_alias(mrb, cls, "outline_color=", "set_outline_color");
  mrb_define_alias(mrb, cls, "outline_thickness=", "set_outline_thickness");

  mrb_define_alias(mrb, cls, "texture", "get_texture");
  mrb_define_alias(mrb, cls, "texture_rect", "get_texture_rect");
  mrb_define_alias(mrb, cls, "fill_color", "get_fill_color");
  mrb_define_alias(mrb, cls, "outline_color", "get_outline_color");
  mrb_define_alias(mrb, cls, "outline_thickness", "get_outline_thickness");
  mrb_define_alias(mrb, cls, "point_count", "get_point_count");
  mrb_define_alias(mrb, cls, "point_at", "get_point");
  mrb_define_alias(mrb, cls, "local_bounds", "get_local_bounds");
  mrb_define_alias(mrb, cls, "global_bounds", "get_global_bounds");
}

#endif
