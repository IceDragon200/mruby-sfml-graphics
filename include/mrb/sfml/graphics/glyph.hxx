#ifndef MRB_SFML_GLYPH_H
#define MRB_SFML_GLYPH_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Graphics/Glyph.hpp>
#include "mrb/sfml/helpers.hxx"

MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_glyph_type;
MRB_SFML_EXTERN mrb_value mrb_sfml_glyph_value(mrb_state*, sf::Glyph);

static inline sf::Glyph*
mrb_sfml_glyph_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Glyph*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_glyph_type));
}

#endif
