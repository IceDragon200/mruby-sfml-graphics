#ifndef MRB_SFML_BLEND_MODE_H
#define MRB_SFML_BLEND_MODE_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Graphics/BlendMode.hpp>

extern "C" const struct mrb_data_type mrb_sfml_blend_mode_type;
extern "C" mrb_value mrb_sfml_blend_mode_value(mrb_state*, sf::BlendMode);

static inline sf::BlendMode*
mrb_sfml_blend_mode_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::BlendMode*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_blend_mode_type));
}

#endif
