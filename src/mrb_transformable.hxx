#ifndef MRB_SFML_TRANSFORMABLE_PRIV_H
#define MRB_SFML_TRANSFORMABLE_PRIV_H

/* The following header is a templating header, use this header to patch
   Transformable classes */

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/Graphics/Transformable.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/graphics/transform.hxx"
#include "mrb/sfml/graphics/transformable.hxx"
#include "mrb/sfml/system/vector2.hxx"

/*
 * WARNING: DO NOT, and I repeat, DO NOT USE THIS FUNCTION ON NON-TRANSFORMABLE
 * OBJECTS.
 * HORRIBLE, HORRIBLE THINGS WILL HAPPEN.
 * This function bypasses mruby's data type checking and pulls the DATA_PTR
 * directly, the only check done, is an assertion on the pointer.
 */
template <class T>
static inline T*
get_transformable(mrb_state *mrb, mrb_value self)
{
  return cxx_mrb_data_get_ptr<T>(mrb, self);
}

template <class T>
static mrb_value
transformable_set_position(mrb_state *mrb, mrb_value self)
{
  mrb_value x;
  mrb_float y;
  mrb_int argc = mrb_get_args(mrb, "o|f", &x, &y);
  T *transformable = get_transformable<T>(mrb, self);
  if (argc == 1) {
    sf::Vector2f *v = static_cast<sf::Vector2f*>(mrb_data_get_ptr(mrb, x, &mrb_sfml_vector2f_type));
    transformable->setPosition(*v);
  } else if (argc == 2) {
    transformable->setPosition(mrb_to_flo(mrb, x), y);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected 1 or 2");
  }
  return self;
}

template <class T>
static mrb_value
transformable_set_rotation(mrb_state *mrb, mrb_value self)
{
  mrb_float angle;
  mrb_get_args(mrb, "f", &angle);
  T *transformable = get_transformable<T>(mrb, self);
  transformable->setRotation(angle);
  return self;
}

template <class T>
static mrb_value
transformable_set_scale(mrb_state *mrb, mrb_value self)
{
  mrb_value x;
  mrb_float y;
  mrb_int argc = mrb_get_args(mrb, "o|f", &x, &y);
  T *transformable = get_transformable<T>(mrb, self);
  if (argc == 1) {
    sf::Vector2f *v = static_cast<sf::Vector2f*>(mrb_data_get_ptr(mrb, x, &mrb_sfml_vector2f_type));
    transformable->setScale(*v);
  } else if (argc == 2) {
    transformable->setScale(mrb_to_flo(mrb, x), y);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected 1 or 2");
  }
  return self;
}

template <class T>
static mrb_value
transformable_set_origin(mrb_state *mrb, mrb_value self)
{
  mrb_value x;
  mrb_float y;
  mrb_int argc = mrb_get_args(mrb, "o|f", &x, &y);
  T *transformable = get_transformable<T>(mrb, self);
  if (argc == 1) {
    sf::Vector2f *v = static_cast<sf::Vector2f*>(mrb_data_get_ptr(mrb, x, &mrb_sfml_vector2f_type));
    transformable->setOrigin(*v);
  } else if (argc == 2) {
    transformable->setOrigin(mrb_to_flo(mrb, x), y);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected 1 or 2");
  }
  return self;
}

template <class T>
static mrb_value
transformable_get_position(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_vector2f_value(mrb, get_transformable<T>(mrb, self)->getPosition());
}

template <class T>
static mrb_value
transformable_get_rotation(mrb_state *mrb, mrb_value self)
{
  return mrb_float_value(mrb, get_transformable<T>(mrb, self)->getRotation());
}

template <class T>
static mrb_value
transformable_get_scale(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_vector2f_value(mrb, get_transformable<T>(mrb, self)->getScale());
}

template <class T>
static mrb_value
transformable_get_origin(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_vector2f_value(mrb, get_transformable<T>(mrb, self)->getOrigin());
}

template <class T>
static mrb_value
transformable_move(mrb_state *mrb, mrb_value self)
{
  mrb_value x;
  mrb_float y;
  mrb_int argc = mrb_get_args(mrb, "o|f", &x, &y);
  T *transformable = get_transformable<T>(mrb, self);
  if (argc == 1) {
    sf::Vector2f *v = static_cast<sf::Vector2f*>(mrb_data_get_ptr(mrb, x, &mrb_sfml_vector2f_type));
    transformable->move(*v);
  } else if (argc == 2) {
    transformable->move(mrb_to_flo(mrb, x), y);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected 1 or 2");
  }
  return self;
}

template <class T>
static mrb_value
transformable_rotate(mrb_state *mrb, mrb_value self)
{
  mrb_float angle;
  mrb_get_args(mrb, "f", &angle);
  T *transformable = get_transformable<T>(mrb, self);
  transformable->rotate(angle);
  return self;
}

template <class T>
static mrb_value
transformable_scale(mrb_state *mrb, mrb_value self)
{
  mrb_value x;
  mrb_float y;
  mrb_int argc = mrb_get_args(mrb, "o|f", &x, &y);
  T *transformable = get_transformable<T>(mrb, self);
  if (argc == 1) {
    sf::Vector2f *v = static_cast<sf::Vector2f*>(mrb_data_get_ptr(mrb, x, &mrb_sfml_vector2f_type));
    transformable->scale(*v);
  } else if (argc == 2) {
    transformable->scale(mrb_to_flo(mrb, x), y);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected 1 or 2");
  }
  return self;
}

template <class T>
static mrb_value
transformable_get_transform(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_transform_value(mrb, get_transformable<T>(mrb, self)->getTransform());
}

template <class T>
static mrb_value
transformable_get_inverse_transform(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_transform_value(mrb, get_transformable<T>(mrb, self)->getInverseTransform());
}

template <class T>
static inline void
transformable_bind_class(mrb_state *mrb, struct RClass *cls)
{
  mrb_define_method(mrb, cls, "set_position", transformable_set_position<T>, MRB_ARGS_ARG(1, 1));
  mrb_define_method(mrb, cls, "set_rotation", transformable_set_rotation<T>, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "set_scale",    transformable_set_scale<T>,    MRB_ARGS_ARG(1, 1));
  mrb_define_method(mrb, cls, "set_origin",   transformable_set_origin<T>,   MRB_ARGS_ARG(1, 1));

  mrb_define_method(mrb, cls, "get_position", transformable_get_position<T>, MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "get_rotation", transformable_get_rotation<T>, MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "get_scale",    transformable_get_scale<T>,    MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "get_origin",   transformable_get_origin<T>,   MRB_ARGS_NONE());

  mrb_define_method(mrb, cls, "move",         transformable_move<T>,         MRB_ARGS_ARG(1, 1));
  mrb_define_method(mrb, cls, "rotate",       transformable_rotate<T>,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "scale",        transformable_scale<T>,        MRB_ARGS_ARG(1, 1));

  mrb_define_method(mrb, cls, "get_transform", transformable_get_transform<T>, MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "get_inverse_transform", transformable_get_inverse_transform<T>, MRB_ARGS_NONE());

  mrb_define_alias(mrb, cls, "position", "get_position");
  mrb_define_alias(mrb, cls, "rotation", "get_rotation");
  mrb_define_alias(mrb, cls, "origin",   "get_origin");
}

#endif
