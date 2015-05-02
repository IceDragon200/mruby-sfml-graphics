#ifndef MRB_SFML_COLOR_H
#define MRB_SFML_COLOR_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Graphics/Color.hpp>

extern "C" const struct mrb_data_type mrb_sfml_color_type;
extern "C" mrb_value mrb_sfml_color_value(mrb_state*, sf::Color);

static inline sf::Color*
mrb_sfml_color_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Color*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_color_type));
}

#endif
