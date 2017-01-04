#ifndef MRB_SFML_SHADER_H
#define MRB_SFML_SHADER_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include "mrb/sfml/graphics/render_window.hxx"
#include "mrb/sfml/helpers.hxx"

MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_render_window_type;

template <> inline const mrb_data_type* mrb_get_sfml_window_type<sf::RenderWindow>() { return &mrb_sfml_render_window_type; }

static inline sf::RenderWindow*
mrb_sfml_render_window_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::RenderWindow*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_render_window_type));
}

#endif
