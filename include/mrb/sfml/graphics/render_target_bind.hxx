#ifndef MRB_SFML_RENDER_TARGET_BIND_H
#define MRB_SFML_RENDER_TARGET_BIND_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/graphics/color.hxx"
#include "mrb/sfml/graphics/view.hxx"
#include "mrb/sfml/graphics/rect.hxx"

template <class T>
static inline T*
get_render_target(mrb_state *mrb, mrb_value self)
{
  return cxx_mrb_data_get_ptr<T>(mrb, self);
}

template <class T>
static mrb_value
render_target_clear(mrb_state *mrb, mrb_value self)
{
  sf::Color *color = NULL;
  mrb_get_args(mrb, "|d", &color, &mrb_sfml_color_type);
  if (color) {
    get_render_target<T>(mrb, self)->clear(*color);
  } else {
    get_render_target<T>(mrb, self)->clear();
  }
  return self;
}

template <class T>
static mrb_value
render_target_set_view(mrb_state *mrb, mrb_value self)
{
  mrb_value view_obj;
  mrb_get_args(mrb, "o", &view_obj);
  get_render_target<T>(mrb, self)->setView(*mrb_sfml_view_ptr(mrb, view_obj));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "__sfml_view"), view_obj);
  return self;
}

template <class T>
static mrb_value
render_target_get_view(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "__sfml_view"));
}

template <class T>
static mrb_value
render_target_get_viewport(mrb_state *mrb, mrb_value self)
{
  sf::View *view;
  mrb_get_args(mrb, "d", &view, &mrb_sfml_view_type);
  return mrb_sfml_int_rect_value(mrb, get_render_target<T>(mrb, self)->getViewport(*view));
}

template <class T>
static inline void
mrb_sfml_render_target_bind_class(mrb_state *mrb, struct RClass *cls)
{
  mrb_define_method(mrb, cls, "clear",    render_target_clear<T>,    MRB_ARGS_OPT(1));
  mrb_define_method(mrb, cls, "set_view", render_target_set_view<T>, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "get_view", render_target_get_view<T>, MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "get_viewport", render_target_get_viewport<T>, MRB_ARGS_REQ(1));
}

#endif
