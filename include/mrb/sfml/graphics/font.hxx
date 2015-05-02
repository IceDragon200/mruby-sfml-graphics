#ifndef MRB_SFML_FONT_H
#define MRB_SFML_FONT_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Graphics/Font.hpp>

extern "C" const struct mrb_data_type mrb_sfml_font_type;

static inline sf::Font*
mrb_sfml_font_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Font*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_font_type));
}

#endif
