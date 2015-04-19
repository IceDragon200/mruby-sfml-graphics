#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/Graphics/Rect.hpp>
#include "mrb/sfml/graphics/rect.hxx"
#include "mrb/sfml/system/vector2.hxx"
#include "mrb/cxx/helpers.hxx"

static struct RClass *int_rect_class;
static struct RClass *float_rect_class;

template <typename T> static void
rect_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    sf::Rect<T> *rect = (sf::Rect<T>*)ptr;
    delete rect;
  }
}

extern "C" const struct mrb_data_type mrb_sfml_int_rect_type = { "sf::IntRect", rect_free<int> };
extern "C" const struct mrb_data_type mrb_sfml_float_rect_type = { "sf::FloatRect", rect_free<float> };

template <typename T>
static inline sf::Rect<T>*
get_rect(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Rect<T>*>(mrb_data_get_ptr(mrb, self, mrb_get_sfml_rect_type<T>()));
}

extern "C" mrb_value
mrb_sfml_float_rect_value(mrb_state *mrb, sf::FloatRect r)
{
  mrb_value result = mrb_obj_new(mrb, float_rect_class, 0, NULL);
  sf::FloatRect *target = get_rect<float>(mrb, result);
  *target = r;
  return result;
}

extern "C" mrb_value
mrb_sfml_int_rect_value(mrb_state *mrb, sf::IntRect r)
{
  mrb_value result = mrb_obj_new(mrb, int_rect_class, 0, NULL);
  sf::IntRect *target = get_rect<int>(mrb, result);
  *target = r;
  return result;
}

template <typename T> static mrb_value
rect_initialize(mrb_state* mrb, mrb_value self)
{
  sf::Rect<T> *rect;
  mrb_value o1;
  mrb_value o2;
  mrb_value o3;
  mrb_value o4;
  mrb_int argc = mrb_get_args(mrb, "oo|oo", &o1, &o2, &o3, &o4);
  if (argc == 0) {
    rect = new sf::Rect<T>();
  } else if (argc == 2) {
    sf::Vector2<T> v1 = *static_cast<sf::Vector2<T>*>(mrb_data_get_ptr(mrb, o1, mrb_get_sfml_vector2_type<T>()));
    sf::Vector2<T> v2 = *static_cast<sf::Vector2<T>*>(mrb_data_get_ptr(mrb, o2, mrb_get_sfml_vector2_type<T>()));
    rect = new sf::Rect<T>(v1, v2);
  } else if (argc == 4) {
    rect = new sf::Rect<T>(cxx_mrb_cast<T>(mrb, o1), cxx_mrb_cast<T>(mrb, o2), cxx_mrb_cast<T>(mrb, o3), cxx_mrb_cast<T>(mrb, o4));
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Expected, 0, 2 or 4");
    return self;
  }
  rect_free<T>(mrb, DATA_PTR(self));
  mrb_data_init(self, rect, mrb_get_sfml_rect_type<T>());
  return self;
}

template <typename T> static mrb_value
rect_initialize_copy(mrb_state* mrb, mrb_value self)
{
  sf::Rect<T> *other;
  mrb_get_args(mrb, "d", &other, mrb_get_sfml_rect_type<T>());
  rect_free<T>(mrb, DATA_PTR(self));
  mrb_data_init(self, new sf::Rect<T>(*other), mrb_get_sfml_rect_type<T>());
  return self;
}

template <typename T> static mrb_value
rect_get_left(mrb_state *mrb, mrb_value self)
{
  return cxx_mrb_numeric_value<T>(mrb, get_rect<T>(mrb, self)->left);
}

template <typename T> static mrb_value
rect_get_top(mrb_state *mrb, mrb_value self)
{
  return cxx_mrb_numeric_value<T>(mrb, get_rect<T>(mrb, self)->top);
}

template <typename T> static mrb_value
rect_get_width(mrb_state *mrb, mrb_value self)
{
  return cxx_mrb_numeric_value<T>(mrb, get_rect<T>(mrb, self)->width);
}

template <typename T> static mrb_value
rect_get_height(mrb_state *mrb, mrb_value self)
{
  return cxx_mrb_numeric_value<T>(mrb, get_rect<T>(mrb, self)->height);
}

template <typename T> static mrb_value
rect_set_top(mrb_state *mrb, mrb_value self)
{
  get_rect<T>(mrb, self)->top = cxx_mrb_get_arg<T>(mrb);
  return self;
}

template <typename T> static mrb_value
rect_set_left(mrb_state *mrb, mrb_value self)
{
  get_rect<T>(mrb, self)->left = cxx_mrb_get_arg<T>(mrb);
  return self;
}

template <typename T> static mrb_value
rect_set_width(mrb_state *mrb, mrb_value self)
{
  get_rect<T>(mrb, self)->width = cxx_mrb_get_arg<T>(mrb);
  return self;
}

template <typename T> static mrb_value
rect_set_height(mrb_state *mrb, mrb_value self)
{
  get_rect<T>(mrb, self)->height = cxx_mrb_get_arg<T>(mrb);
  return self;
}

template <typename T>
static mrb_value
rect_contains(mrb_state *mrb, mrb_value self)
{
  mrb_value a, b;
  mrb_int argc = mrb_get_args(mrb, "o|o", &a, &b);
  sf::Rect<T> const *rect = get_rect<T>(mrb, self);
  if (argc == 1) {
    sf::Vector2<T> vect = *(static_cast<sf::Vector2<T>*>(mrb_data_get_ptr(mrb, a, mrb_get_sfml_vector2_type<T>())));
    return mrb_bool_value(rect->contains(vect));
  } else {
    return mrb_bool_value(rect->contains(cxx_mrb_cast<T>(mrb, a), cxx_mrb_cast<T>(mrb, b)));
  }
}

template <typename T>
static mrb_value
rect_intersects(mrb_state *mrb, mrb_value self)
{
  mrb_value a, b;
  mrb_int argc = mrb_get_args(mrb, "o|o", &a, &b);
  sf::Rect<T> const *rect = get_rect<T>(mrb, self);
  if (argc == 1) {
    sf::Rect<T> const *other = get_rect<T>(mrb, a);
    return mrb_bool_value(rect->intersects(*other));
  } else {
    sf::Rect<T> const *rect_a = get_rect<T>(mrb, a);
    sf::Rect<T> *rect_b = get_rect<T>(mrb, b);
    return mrb_bool_value(rect->intersects(*rect_a, *rect_b));
  }
}

template <typename T> static void
rect_bind_class(mrb_state *mrb, struct RClass *cls)
{
  mrb_define_method(mrb, cls, "initialize",      rect_initialize<T>,      MRB_ARGS_ANY());
  mrb_define_method(mrb, cls, "initialize_copy", rect_initialize_copy<T>, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "top",             rect_get_top<T>,         MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "left",            rect_get_left<T>,        MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "width",           rect_get_width<T>,       MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "height",          rect_get_height<T>,      MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "top=",            rect_set_top<T>,         MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "left=",           rect_set_left<T>,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "width=",          rect_set_width<T>,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "height=",         rect_set_height<T>,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "contains?",       rect_contains<T>,        MRB_ARGS_ARG(1,1));
  mrb_define_method(mrb, cls, "contains?",       rect_intersects<T>,      MRB_ARGS_ARG(1,1));
}

extern "C" void
mrb_sfml_rect_init_bind(mrb_state *mrb, struct RClass *mod)
{
  int_rect_class = mrb_define_class_under(mrb, mod, "IntRect", mrb->object_class);
  MRB_SET_INSTANCE_TT(int_rect_class, MRB_TT_DATA);
  rect_bind_class<int>(mrb, int_rect_class);

  float_rect_class = mrb_define_class_under(mrb, mod, "FloatRect", mrb->object_class);
  MRB_SET_INSTANCE_TT(float_rect_class, MRB_TT_DATA);
  rect_bind_class<float>(mrb, float_rect_class);
}
