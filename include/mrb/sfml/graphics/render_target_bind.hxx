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
#include "mrb/sfml/graphics/render_states.hxx"
#include "mrb/sfml/system/vector2.hxx"

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
  mrb_int argc = mrb_get_args(mrb, "|d", &color, &mrb_sfml_color_type);
  if (argc == 0) {
    get_render_target<T>(mrb, self)->clear();
  } else if (argc == 1) {
    assert(color);
    get_render_target<T>(mrb, self)->clear(*color);
  } else {
    mrb_raise(mrb, E_RUNTIME_ERROR, "expected 0 or 1 arguments");
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
static mrb_value
render_target_map_pixel_to_coords(mrb_state *mrb, mrb_value self)
{
  sf::Vector2i *vec;
  sf::View *view;
  mrb_get_args(mrb, "d|d", &vec, &mrb_sfml_vector2i_type, &view, &mrb_sfml_view_type);
  if (view) {
    return mrb_sfml_vector2f_value(mrb, get_render_target<T>(mrb, self)->mapPixelToCoords(*vec, *view));
  } else {
    return mrb_sfml_vector2f_value(mrb, get_render_target<T>(mrb, self)->mapPixelToCoords(*vec));
  }
}

template <class T>
static mrb_value
render_target_map_coords_to_pixel(mrb_state *mrb, mrb_value self)
{
  sf::Vector2f *vec;
  sf::View *view = NULL;
  mrb_get_args(mrb, "d|d", &vec, &mrb_sfml_vector2f_type, &view, &mrb_sfml_view_type);
  if (view) {
    return mrb_sfml_vector2i_value(mrb, get_render_target<T>(mrb, self)->mapCoordsToPixel(*vec, *view));
  } else {
    return mrb_sfml_vector2i_value(mrb, get_render_target<T>(mrb, self)->mapCoordsToPixel(*vec));
  }
}

template <class T>
static mrb_value
render_target_draw(mrb_state *mrb, mrb_value self)
{
  mrb_value drawable_obj;
  sf::Drawable *drawable;
  sf::RenderStates *render_states = NULL;
  mrb_get_args(mrb, "o|d", &drawable_obj, &render_states, &mrb_sfml_render_states_type);
  drawable = cxx_mrb_data_get_ptr<sf::Drawable>(mrb, drawable_obj);
  if (render_states) {
    get_render_target<T>(mrb, self)->draw(*drawable);
  } else {
    get_render_target<T>(mrb, self)->draw(*drawable, *render_states);
  }
  return self;
}

template <class T>
static mrb_value
render_target_get_size(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_vector2u_value(mrb, get_render_target<T>(mrb, self)->getSize());
}

template <class T>
static mrb_value
render_target_push_gl_states(mrb_state *mrb, mrb_value self)
{
  get_render_target<T>(mrb, self)->pushGLStates();
  return self;
}

template <class T>
static mrb_value
render_target_pop_gl_states(mrb_state *mrb, mrb_value self)
{
  get_render_target<T>(mrb, self)->popGLStates();
  return self;
}

template <class T>
static mrb_value
render_target_reset_gl_states(mrb_state *mrb, mrb_value self)
{
  get_render_target<T>(mrb, self)->resetGLStates();
  return self;
}

template <class T>
static inline void
mrb_sfml_render_target_bind_class(mrb_state *mrb, struct RClass *cls)
{
  mrb_define_method(mrb, cls, "clear",               render_target_clear<T>,               MRB_ARGS_OPT(1));
  mrb_define_method(mrb, cls, "set_view",            render_target_set_view<T>,            MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "get_view",            render_target_get_view<T>,            MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "get_viewport",        render_target_get_viewport<T>,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "map_pixel_to_coords", render_target_map_pixel_to_coords<T>, MRB_ARGS_ARG(1, 1));
  mrb_define_method(mrb, cls, "map_coords_to_pixel", render_target_map_coords_to_pixel<T>, MRB_ARGS_ARG(1, 1));
  mrb_define_method(mrb, cls, "draw",                render_target_draw<T>,                MRB_ARGS_ARG(1, 1));
  mrb_define_method(mrb, cls, "get_size",            render_target_get_size<T>,            MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "push_gl_states",      render_target_push_gl_states<T>,      MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "pop_gl_states",       render_target_pop_gl_states<T>,       MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "reset_gl_states",     render_target_reset_gl_states<T>,     MRB_ARGS_NONE());

  mrb_define_alias(mrb, cls, "view=", "set_view");
  mrb_define_alias(mrb, cls, "view", "get_view");
  mrb_define_alias(mrb, cls, "size", "get_size");
}

#endif
