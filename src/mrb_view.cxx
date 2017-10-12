#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/Graphics/View.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/graphics/view.hxx"
#include "mrb/sfml/system/vector2.hxx"
#include "mrb/sfml/graphics/rect.hxx"
#include "mrb/sfml/graphics/transform.hxx"
#include "mrb_view.hxx"

static mrb_data_free_func view_free = cxx_mrb_data_free<sf::View>;
MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_view_type = { "sf::View", view_free };

static mrb_value
view_initialize(mrb_state *mrb, mrb_value self)
{
  sf::View *view;
  sf::Vector2f center;
  sf::Vector2f size;
  sf::FloatRect rectangle;
  mrb_value a, b;
  mrb_int argc = mrb_get_args(mrb, "|oo", &a, &b);
  if (argc == 0) {
    view = new sf::View();
  } else if (argc == 1) {
    rectangle = *mrb_sfml_float_rect_ptr(mrb, a);
    view = new sf::View(rectangle);
  } else if (argc == 2) {
    center = *mrb_sfml_vector2f_ptr(mrb, a);
    size = *mrb_sfml_vector2f_ptr(mrb, b);
    view = new sf::View(center, size);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "wrong argument count (expected 0..2)");
    return self;
  }
  view_free(mrb, DATA_PTR(self));
  mrb_data_init(self, view, &mrb_sfml_view_type);
  return self;
}

static mrb_value
view_set_center(mrb_state *mrb, mrb_value self)
{
  sf::Vector2f center;
  mrb_value a, b;
  mrb_int argc = mrb_get_args(mrb, "|oo", &a, &b);
  sf::View *view = mrb_sfml_view_ptr(mrb, self);
  mrb_float x;
  mrb_float y;
  if (argc == 1) {
    center = *mrb_sfml_vector2f_ptr(mrb, a);
    view->setCenter(center);
  } else if (argc == 2) {
    x = mrb_to_flo(mrb, a);
    y = mrb_to_flo(mrb, b);
    view->setCenter((float)x, (float)y);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "wrong argument count (expected 1..2)");
  }
  return self;
}

static mrb_value
view_set_size(mrb_state *mrb, mrb_value self)
{
  sf::Vector2f size;
  mrb_value a, b;
  mrb_int argc = mrb_get_args(mrb, "|oo", &a, &b);
  sf::View *view = mrb_sfml_view_ptr(mrb, self);
  mrb_float x;
  mrb_float y;
  if (argc == 1) {
    size = *mrb_sfml_vector2f_ptr(mrb, a);
    view->setSize(size);
  } else if (argc == 2) {
    x = mrb_to_flo(mrb, a);
    y = mrb_to_flo(mrb, b);
    view->setSize((float)x, (float)y);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "wrong argument count (expected 1..2)");
  }
  return self;
}

static mrb_value
view_set_rotation(mrb_state *mrb, mrb_value self)
{
  mrb_float rotation;
  mrb_get_args(mrb, "f", &rotation);
  sf::View *view = mrb_sfml_view_ptr(mrb, self);
  view->setRotation((float)rotation);
  return self;
}

static mrb_value
view_set_viewport(mrb_state *mrb, mrb_value self)
{
  sf::FloatRect *float_rect;
  mrb_get_args(mrb, "d", &float_rect, mrb_get_sfml_rect_type<float>());
  sf::View *view = mrb_sfml_view_ptr(mrb, self);
  view->setViewport(*float_rect);
  return self;
}

static mrb_value
view_reset(mrb_state *mrb, mrb_value self)
{
  sf::FloatRect *float_rect;
  mrb_get_args(mrb, "d", &float_rect, mrb_get_sfml_rect_type<float>());
  sf::View *view = mrb_sfml_view_ptr(mrb, self);
  view->reset(*float_rect);
  return self;
}

static mrb_value
view_get_center(mrb_state *mrb, mrb_value self)
{
  sf::View *view = mrb_sfml_view_ptr(mrb, self);
  return mrb_sfml_vector2f_value(mrb, view->getCenter());
}

static mrb_value
view_get_size(mrb_state *mrb, mrb_value self)
{
  sf::View *view = mrb_sfml_view_ptr(mrb, self);
  return mrb_sfml_vector2f_value(mrb, view->getSize());
}

static mrb_value
view_get_rotation(mrb_state *mrb, mrb_value self)
{
  sf::View *view = mrb_sfml_view_ptr(mrb, self);
  return mrb_float_value(mrb, (mrb_float)view->getRotation());
}

static mrb_value
view_get_viewport(mrb_state *mrb, mrb_value self)
{
  sf::View *view = mrb_sfml_view_ptr(mrb, self);
  return mrb_sfml_float_rect_value(mrb, view->getViewport());
}

static mrb_value
view_move(mrb_state *mrb, mrb_value self)
{
  sf::Vector2f size;
  mrb_value a, b;
  mrb_int argc = mrb_get_args(mrb, "|oo", &a, &b);
  sf::View *view = mrb_sfml_view_ptr(mrb, self);
  mrb_float x;
  mrb_float y;
  if (argc == 1) {
    size = *mrb_sfml_vector2f_ptr(mrb, a);
    view->move(size);
  } else if (argc == 2) {
    x = mrb_to_flo(mrb, a);
    y = mrb_to_flo(mrb, b);
    view->move((float)x, (float)y);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "wrong argument count (expected 1..2)");
  }
  return self;
}

static mrb_value
view_rotate(mrb_state *mrb, mrb_value self)
{
  mrb_float angle;
  mrb_get_args(mrb, "f", &angle);
  sf::View *view = mrb_sfml_view_ptr(mrb, self);
  view->rotate((float)angle);
  return self;
}

static mrb_value
view_zoom(mrb_state *mrb, mrb_value self)
{
  mrb_float factor;
  mrb_get_args(mrb, "f", &factor);
  sf::View *view = mrb_sfml_view_ptr(mrb, self);
  view->zoom((float)factor);
  return self;
}

static mrb_value
view_get_transform(mrb_state *mrb, mrb_value self)
{
  sf::View *view = mrb_sfml_view_ptr(mrb, self);
  return mrb_sfml_transform_value(mrb, view->getTransform());
}

static mrb_value
view_get_inverse_transform(mrb_state *mrb, mrb_value self)
{
  sf::View *view = mrb_sfml_view_ptr(mrb, self);
  return mrb_sfml_transform_value(mrb, view->getInverseTransform());
}

MRB_SFML_EXTERN void
mrb_sfml_view_init_bind(mrb_state *mrb, struct RClass *mod)
{
  struct RClass *view_class = mrb_define_class_under(mrb, mod, "View", mrb->object_class);
  MRB_SET_INSTANCE_TT(view_class, MRB_TT_DATA);

  mrb_define_method(mrb, view_class, "initialize",            view_initialize,            MRB_ARGS_ARG(0,2));
  mrb_define_method(mrb, view_class, "set_center",            view_set_center,            MRB_ARGS_ARG(1,1));
  mrb_define_method(mrb, view_class, "set_size",              view_set_size,              MRB_ARGS_ARG(1,1));
  mrb_define_method(mrb, view_class, "set_rotation",          view_set_rotation,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, view_class, "set_viewport",          view_set_viewport,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, view_class, "reset",                 view_reset,                 MRB_ARGS_REQ(1));
  mrb_define_method(mrb, view_class, "get_center",            view_get_center,            MRB_ARGS_NONE());
  mrb_define_method(mrb, view_class, "get_size",              view_get_size,              MRB_ARGS_NONE());
  mrb_define_method(mrb, view_class, "get_rotation",          view_get_rotation,          MRB_ARGS_NONE());
  mrb_define_method(mrb, view_class, "get_viewport",          view_get_viewport,          MRB_ARGS_NONE());
  mrb_define_method(mrb, view_class, "move",                  view_move,                  MRB_ARGS_ARG(1,1));
  mrb_define_method(mrb, view_class, "rotate",                view_rotate,                MRB_ARGS_REQ(1));
  mrb_define_method(mrb, view_class, "zoom",                  view_zoom,                  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, view_class, "get_transform",         view_get_transform,         MRB_ARGS_NONE());
  mrb_define_method(mrb, view_class, "get_inverse_transform", view_get_inverse_transform, MRB_ARGS_NONE());
}
