#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/Graphics/CircleShape.hpp>
#include "mrb_circle_shape.hxx"
#include "mrb_shape.hxx"

static struct RClass *circle_shape_class;

static void
circle_shape_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    sf::CircleShape *circle_shape = static_cast<sf::CircleShape*>(ptr);
    delete circle_shape;
  }
}

extern "C" const struct mrb_data_type mrb_sfml_circle_shape_type = { "sf::CircleShape", circle_shape_free };

static inline sf::CircleShape*
get_circle_shape(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::CircleShape*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_circle_shape_type));
}

static mrb_value
circle_shape_initialize(mrb_state *mrb, mrb_value self)
{
  sf::CircleShape *circle_shape = new sf::CircleShape();
  mrb_data_init(self, circle_shape, &mrb_sfml_circle_shape_type);
  return self;
}

extern "C" void
mrb_sfml_circle_shape_init_bind(mrb_state *mrb, struct RClass *mod)
{
  circle_shape_class = mrb_define_class_under(mrb, mod, "CircleShape", mrb_class_get_under(mrb, mod, "Shape"));
  MRB_SET_INSTANCE_TT(circle_shape_class, MRB_TT_DATA);

  mrb_define_method(mrb, circle_shape_class, "initialize", circle_shape_initialize, MRB_ARGS_NONE());
  shape_bind_class<sf::CircleShape>(mrb, circle_shape_class);
}
