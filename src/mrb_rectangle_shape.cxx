#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb_rectangle_shape.hxx"
#include "mrb_shape.hxx"

static struct RClass *rectangle_shape_class;

static void
rectangle_shape_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    sf::RectangleShape *rectangle_shape = static_cast<sf::RectangleShape*>(ptr);
    delete rectangle_shape;
  }
}

extern "C" const struct mrb_data_type mrb_sfml_rectangle_shape_type = { "sf::RectangleShape", rectangle_shape_free };

static inline sf::RectangleShape*
get_rectangle_shape(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::RectangleShape*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_rectangle_shape_type));
}

static mrb_value
rectangle_shape_initialize(mrb_state *mrb, mrb_value self)
{
  sf::RectangleShape *rectangle_shape;
  sf::Vector2f *size;
  mrb_int argc = mrb_get_args(mrb, "|d", &size, &mrb_sfml_vector2f_type);
  if (argc == 0) {
    rectangle_shape = new sf::RectangleShape();
  } else if (argc == 1) {
    rectangle_shape = new sf::RectangleShape(*size);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected 0, or 1");
    return self;
  }
  rectangle_shape_free(mrb, DATA_PTR(self));
  mrb_data_init(self, rectangle_shape, &mrb_sfml_rectangle_shape_type);
  return self;
}

static mrb_value
rectangle_shape_set_size(mrb_state *mrb, mrb_value self)
{
  sf::Vector2f *size;
  mrb_get_args(mrb, "d", &size, &mrb_sfml_vector2f_type);
  get_rectangle_shape(mrb, self)->setSize(*size);
  return self;
}

static mrb_value
rectangle_shape_get_size(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_vector2f_value(mrb, get_rectangle_shape(mrb, self)->getSize());
}

extern "C" void
mrb_sfml_rectangle_shape_init_bind(mrb_state *mrb, struct RClass *mod)
{
  rectangle_shape_class = mrb_define_class_under(mrb, mod, "RectangleShape", mrb_class_get_under(mrb, mod, "Shape"));
  MRB_SET_INSTANCE_TT(rectangle_shape_class, MRB_TT_DATA);

  mrb_define_method(mrb, rectangle_shape_class, "initialize",    rectangle_shape_initialize, MRB_ARGS_ARG(0,1));
  shape_bind_class<sf::RectangleShape>(mrb, rectangle_shape_class);
  mrb_define_method(mrb, rectangle_shape_class, "set_size",      rectangle_shape_set_size, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rectangle_shape_class, "get_size",      rectangle_shape_get_size, MRB_ARGS_NONE());

  mrb_define_alias(mrb, rectangle_shape_class, "size=", "set_size");
  mrb_define_alias(mrb, rectangle_shape_class, "size", "get_size");
}
