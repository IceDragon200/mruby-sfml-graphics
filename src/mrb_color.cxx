#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/Graphics/Color.hpp>
#include "mrb_color.hxx"
#include "mrb/sfml/graphics/color.hxx"

static struct RClass *color_class;

static void
color_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    sf::Color *color = (sf::Color*)ptr;
    delete color;
  }
}

extern "C" const struct mrb_data_type mrb_sfml_color_type = { "sf::Color", color_free };

static inline sf::Color*
get_color(mrb_state *mrb, mrb_value self)
{
  return (sf::Color*)mrb_data_get_ptr(mrb, self, &mrb_sfml_color_type);
}

extern "C" mrb_value
mrb_sfml_color_value(mrb_state *mrb, sf::Color color)
{
  mrb_value result = mrb_obj_new(mrb, color_class, 0, NULL);
  sf::Color *target = get_color(mrb, result);
  *target = color;
  return result;
}

static mrb_value
color_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_int r, g, b, a;
  mrb_int argc = mrb_get_args(mrb, "|iiii", &r, &g, &b, &a);
  sf::Color *color;
  if (argc == 0) {
    color = new sf::Color();
  } else if (argc == 3) {
    color = new sf::Color(r, g, b);
  } else if (argc == 4) {
    color = new sf::Color(r, g, b, a);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Expected 0, 3, or 4");
    return self;
  }
  color_free(mrb, DATA_PTR(self));
  mrb_data_init(self, color, &mrb_sfml_color_type);
  return self;
}

static mrb_value
color_initialize_copy(mrb_state *mrb, mrb_value self)
{
  sf::Color *other;
  mrb_get_args(mrb, "d", &other, &mrb_sfml_color_type);
  mrb_data_init(self, new sf::Color(*other), &mrb_sfml_color_type);
  return self;
}

static mrb_value
color_get_r(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(get_color(mrb, self)->r);
}

static mrb_value
color_get_g(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(get_color(mrb, self)->g);
}

static mrb_value
color_get_b(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(get_color(mrb, self)->b);
}

static mrb_value
color_get_a(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(get_color(mrb, self)->a);
}

static mrb_value
color_set_r(mrb_state *mrb, mrb_value self)
{
  mrb_int v;
  mrb_get_args(mrb, "i", &v);
  get_color(mrb, self)->r = v;
  return self;
}

static mrb_value
color_set_g(mrb_state *mrb, mrb_value self)
{
  mrb_int v;
  mrb_get_args(mrb, "i", &v);
  get_color(mrb, self)->g = v;
  return self;
}

static mrb_value
color_set_b(mrb_state *mrb, mrb_value self)
{
  mrb_int v;
  mrb_get_args(mrb, "i", &v);
  get_color(mrb, self)->b = v;
  return self;
}

static mrb_value
color_set_a(mrb_state *mrb, mrb_value self)
{
  mrb_int v;
  mrb_get_args(mrb, "i", &v);
  get_color(mrb, self)->a = v;
  return self;
}

static mrb_value
color_eq(mrb_state *mrb, mrb_value self)
{
  sf::Color *other;
  sf::Color *col;
  mrb_get_args(mrb, "d", &other, &mrb_sfml_color_type);
  col = get_color(mrb, self);
  return mrb_bool_value(*col == *other);
}

static mrb_value
color_add(mrb_state *mrb, mrb_value self)
{
  sf::Color *other;
  sf::Color *col;
  mrb_get_args(mrb, "d", &other, &mrb_sfml_color_type);
  col = get_color(mrb, self);
  return mrb_sfml_color_value(mrb, *col + *other);
}

static mrb_value
color_sub(mrb_state *mrb, mrb_value self)
{
  sf::Color *other;
  sf::Color *col;
  mrb_get_args(mrb, "d", &other, &mrb_sfml_color_type);
  col = get_color(mrb, self);
  return mrb_sfml_color_value(mrb, *col - *other);
}

static mrb_value
color_mul(mrb_state *mrb, mrb_value self)
{
  sf::Color *other;
  sf::Color *col;
  mrb_get_args(mrb, "d", &other, &mrb_sfml_color_type);
  col = get_color(mrb, self);
  return mrb_sfml_color_value(mrb, *col * *other);
}

extern "C" void
mrb_sfml_color_init_bind(mrb_state *mrb, struct RClass *mod)
{
  color_class = mrb_define_class_under(mrb, mod, "Color", mrb->object_class);
  MRB_SET_INSTANCE_TT(color_class, MRB_TT_DATA);

  mrb_define_method(mrb, color_class, "initialize", color_initialize, MRB_ARGS_ARG(0,4));
  mrb_define_method(mrb, color_class, "initialize_copy", color_initialize_copy, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, color_class, "r", color_get_r, MRB_ARGS_NONE());
  mrb_define_method(mrb, color_class, "g", color_get_g, MRB_ARGS_NONE());
  mrb_define_method(mrb, color_class, "b", color_get_b, MRB_ARGS_NONE());
  mrb_define_method(mrb, color_class, "a", color_get_a, MRB_ARGS_NONE());
  mrb_define_method(mrb, color_class, "r=", color_set_r, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, color_class, "g=", color_set_g, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, color_class, "b=", color_set_b, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, color_class, "a=", color_set_a, MRB_ARGS_REQ(1));

  mrb_define_method(mrb, color_class, "==", color_eq, MRB_ARGS_REQ(1));

  mrb_define_method(mrb, color_class, "+", color_add, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, color_class, "-", color_sub, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, color_class, "*", color_mul, MRB_ARGS_REQ(1));
}
