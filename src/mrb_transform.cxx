#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/Graphics/Transform.hpp>
#include "mrb/sfml/graphics/transform.hxx"
#include "mrb/sfml/system/vector2.hxx"
#include "mrb/sfml/graphics/rect.hxx"

static struct RClass *transform_class;

static void
transform_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    sf::Transform *transform = (sf::Transform*)ptr;
    delete transform;
  }
}

extern "C" const struct mrb_data_type mrb_sfml_transform_type = { "sf::Transform", transform_free };

static inline sf::Transform*
get_transform(mrb_state *mrb, mrb_value self)
{
  return (sf::Transform*)mrb_data_get_ptr(mrb, self, &mrb_sfml_transform_type);
}

static inline sf::Vector2f*
get_vector2f(mrb_state *mrb, mrb_value self)
{
  return (sf::Vector2f*)mrb_data_get_ptr(mrb, self, &mrb_sfml_vector2f_type);
}

extern "C" mrb_value
mrb_sfml_transform_value(mrb_state *mrb, sf::Transform transform)
{
  mrb_value result = mrb_obj_new(mrb, transform_class, 0, NULL);
  sf::Transform *target = get_transform(mrb, result);
  *target = transform;
  return result;
}

static mrb_value
transform_initialize(mrb_state *mrb, mrb_value self)
{
  sf::Transform *transform;
  mrb_float a, b, c, d, e, f, g, h, i;
  mrb_int argc = mrb_get_args(mrb, "|fffffffff", &a, &b, &c, &d, &e, &f, &g, &h, &i);
  if (argc == 0) {
    transform = new sf::Transform();
  } else if (argc == 9) {
    transform = new sf::Transform(a, b, c, d, e, f, g, h, i);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected 0 or 9.");
    return self;
  }
  mrb_data_init(self, transform, &mrb_sfml_transform_type);
  return self;
}

static mrb_value
transform_get_inverse(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_transform_value(mrb, get_transform(mrb, self)->getInverse());
}

static mrb_value
transform_transform_point(mrb_state *mrb, mrb_value self)
{
  sf::Transform *transform;
  mrb_value obj;
  mrb_float y;
  mrb_int argc = mrb_get_args(mrb, "o|f", &obj, &y);
  transform = get_transform(mrb, self);
  if (argc == 1) {
    return mrb_sfml_vector2f_value(mrb, transform->transformPoint(*get_vector2f(mrb, obj)));
  } else if (argc == 2) {
    return mrb_sfml_vector2f_value(mrb, transform->transformPoint(mrb_to_flo(mrb, obj), y));
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected 1 or 2");
  }
  /* should never reach here */
  return self;
}

static mrb_value
transform_transform_rect(mrb_state *mrb, mrb_value self)
{
  sf::FloatRect *rect;
  mrb_get_args(mrb, "d", &rect, &mrb_sfml_float_rect_type);
  return mrb_sfml_float_rect_value(mrb, get_transform(mrb, self)->transformRect(*rect));
}

static mrb_value
transform_combine(mrb_state *mrb, mrb_value self)
{
  sf::Transform *trns;
  mrb_get_args(mrb, "d", &trns, &mrb_sfml_transform_type);
  return mrb_sfml_transform_value(mrb, get_transform(mrb, self)->combine(*trns));
}

static mrb_value
transform_translate(mrb_state *mrb, mrb_value self)
{
  sf::Transform *transform;
  mrb_value obj;
  mrb_float y;
  mrb_int argc = mrb_get_args(mrb, "o|f", &obj, &y);
  transform = get_transform(mrb, self);
  if (argc == 1) {
    return mrb_sfml_transform_value(mrb, transform->translate(*get_vector2f(mrb, obj)));
  } else if (argc == 2) {
    return mrb_sfml_transform_value(mrb, transform->translate(mrb_to_flo(mrb, obj), y));
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected 1 or 2");
  }
  /* should never reach here */
  return self;
}

static mrb_value
transform_rotate(mrb_state *mrb, mrb_value self)
{
  sf::Transform *transform;
  mrb_float angle;
  mrb_value obj;
  mrb_float y;
  mrb_int argc = mrb_get_args(mrb, "f|of", &angle, &obj, &y);
  transform = get_transform(mrb, self);
  if (argc == 1) {
    return mrb_sfml_transform_value(mrb, transform->rotate(angle));
  } else if (argc == 2) {
    return mrb_sfml_transform_value(mrb, transform->rotate(angle, *get_vector2f(mrb, obj)));
  } else if (argc == 3) {
    return mrb_sfml_transform_value(mrb, transform->rotate(angle, mrb_to_flo(mrb, obj), y));
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected 1, 2 or 3");
  }
  return mrb_nil_value();
}

static mrb_value
transform_scale(mrb_state *mrb, mrb_value self)
{
  sf::Transform *transform;
  mrb_float scale_y, center_x, center_y;
  mrb_value obj;
  mrb_int argc = mrb_get_args(mrb, "o|fff", &obj, &scale_y, &center_x, &center_y);
  transform = get_transform(mrb, self);
  if (argc == 1) {
    return mrb_sfml_transform_value(mrb, transform->scale(*get_vector2f(mrb, obj)));
  } else if (argc == 2) {
    return mrb_sfml_transform_value(mrb, transform->scale(mrb_to_flo(mrb, obj), scale_y));
  } else if (argc == 4) {
    return mrb_sfml_transform_value(mrb, transform->scale(mrb_to_flo(mrb, obj), scale_y, center_x, center_y));
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected 1, 2 or 4");
  }
  return mrb_nil_value();
}

static mrb_value
transform_mul(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;
  mrb_get_args(mrb, "o", &obj);
  mrb_check_type(mrb, obj, MRB_TT_DATA);
  if (DATA_TYPE(obj) == &mrb_sfml_transform_type) {
    return mrb_sfml_transform_value(mrb, (*get_transform(mrb, self)) * (*get_transform(mrb, obj)));
  } else if (DATA_TYPE(obj) == &mrb_sfml_vector2f_type) {
    return mrb_sfml_vector2f_value(mrb, (*get_transform(mrb, self)) * (*get_vector2f(mrb, obj)));
  } else {
    mrb_raise(mrb, E_TYPE_ERROR, "Expected SFML::Vector2f or SFML::Transform");
  }
  return mrb_nil_value();
}

static mrb_value
transform_aref(mrb_state *mrb, mrb_value self)
{
  mrb_int x, y;
  mrb_int argc = mrb_get_args(mrb, "i|i", &x, &y);
  if (argc == 1) {
    if (x < 0 || 16 < x) {
      mrb_raise(mrb, E_INDEX_ERROR, "Index out of range (expected 0...16).");
    }
    return mrb_float_value(mrb, get_transform(mrb, self)->getMatrix()[x]);
  } else if (argc == 2) {
    if (x < 0 || 4 < x || y < 0 || 4 < y) {
      mrb_raise(mrb, E_INDEX_ERROR, "Index out of range (expected 0...4).");
    }
    return mrb_float_value(mrb, get_transform(mrb, self)->getMatrix()[x + y * 4]);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected 1 or 2");
  }
  return mrb_nil_value();
}

extern "C" void
mrb_sfml_transform_init_bind(mrb_state *mrb, struct RClass *mod)
{
  transform_class = mrb_define_class_under(mrb, mod, "Transform", mrb->object_class);
  MRB_SET_INSTANCE_TT(transform_class, MRB_TT_DATA);

  mrb_define_method(mrb, transform_class, "initialize",      transform_initialize,      MRB_ARGS_ARG(0,9));
  mrb_define_method(mrb, transform_class, "get_inverse",     transform_get_inverse,     MRB_ARGS_NONE());
  mrb_define_method(mrb, transform_class, "transform_point", transform_transform_point, MRB_ARGS_ARG(1,1));
  mrb_define_method(mrb, transform_class, "transform_rect",  transform_transform_rect,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, transform_class, "combine",         transform_combine,         MRB_ARGS_REQ(1));
  mrb_define_method(mrb, transform_class, "translate",       transform_translate,       MRB_ARGS_ARG(1,1));
  mrb_define_method(mrb, transform_class, "rotate",          transform_rotate,          MRB_ARGS_ARG(1,2));
  mrb_define_method(mrb, transform_class, "scale",           transform_scale,           MRB_ARGS_ARG(1,3));
  mrb_define_method(mrb, transform_class, "*",               transform_mul,             MRB_ARGS_REQ(1));

  mrb_define_method(mrb, transform_class, "[]",              transform_aref,            MRB_ARGS_ARG(1, 1));
}
