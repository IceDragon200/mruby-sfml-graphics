#ifndef MRB_SFML_GLYPH_H
#define MRB_SFML_GLYPH_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Graphics/Glyph.hpp>

extern "C" const struct mrb_data_type mrb_sfml_glyph_type;
extern "C" mrb_value mrb_sfml_glyph_value(mrb_state*, sf::Glyph);

static inline sf::Glyph*
mrb_sfml_glyph_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Glyph*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_glyph_type));
}

#endif
