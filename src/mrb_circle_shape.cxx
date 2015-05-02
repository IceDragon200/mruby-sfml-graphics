#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/Graphics/CircleShape.hpp>
#include "mrb_circle_shape.hxx"
#include "mrb_shape.hxx"

static struct RClass *circle_shape_class;
static mrb_data_free_func circle_shape_free = cxx_mrb_data_free<sf::CircleShape>;

extern "C" const struct mrb_data_type mrb_sfml_circle_shape_type = { "sf::CircleShape", circle_shape_free };

static inline sf::CircleShape*
get_circle_shape(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::CircleShape*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_circle_shape_type));
}

static mrb_value
circle_shape_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_float radius;
  mrb_int point_count;
  mrb_int argc = mrb_get_args(mrb, "|fi", &radius, &point_count);
  sf::CircleShape *circle_shape;
  if (argc == 0) {
    circle_shape = new sf::CircleShape();
  } else if (argc == 1) {
    circle_shape = new sf::CircleShape(radius);
  } else if (argc == 2) {
    circle_shape = new sf::CircleShape(radius, point_count);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected 0, 1 or 2");
    return mrb_nil_value();
  }
  circle_shape_free(mrb, DATA_PTR(self));
  mrb_data_init(self, circle_shape, &mrb_sfml_circle_shape_type);
  return self;
}

static mrb_value
circle_shape_set_radius(mrb_state *mrb, mrb_value self)
{
  mrb_float radius;
  mrb_get_args(mrb, "f", &radius);
  get_circle_shape(mrb, self)->setRadius(radius);
  return self;
}

static mrb_value
circle_shape_get_radius(mrb_state *mrb, mrb_value self)
{
  return mrb_float_value(mrb, get_circle_shape(mrb, self)->getRadius());
}

static mrb_value
circle_shape_set_point_count(mrb_state *mrb, mrb_value self)
{
  mrb_int points;
  mrb_get_args(mrb, "i", &points);
  get_circle_shape(mrb, self)->setPointCount(points);
  return self;
}

extern "C" void
mrb_sfml_circle_shape_init_bind(mrb_state *mrb, struct RClass *mod)
{
  circle_shape_class = mrb_define_class_under(mrb, mod, "CircleShape", mrb_class_get_under(mrb, mod, "Shape"));
  MRB_SET_INSTANCE_TT(circle_shape_class, MRB_TT_DATA);

  mrb_define_method(mrb, circle_shape_class, "initialize", circle_shape_initialize, MRB_ARGS_ANY());
  shape_bind_class<sf::CircleShape>(mrb, circle_shape_class);
  mrb_define_method(mrb, circle_shape_class, "set_radius",      circle_shape_set_radius, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, circle_shape_class, "get_radius",      circle_shape_get_radius, MRB_ARGS_NONE());
  mrb_define_method(mrb, circle_shape_class, "set_point_count", circle_shape_set_point_count, MRB_ARGS_REQ(1));

  mrb_define_alias(mrb, circle_shape_class, "radius=", "set_radius");
  mrb_define_alias(mrb, circle_shape_class, "radius", "get_radius");
  mrb_define_alias(mrb, circle_shape_class, "point_count=", "set_point_count");
}
