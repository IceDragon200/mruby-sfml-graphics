#ifndef MRB_SFML_BLEND_MODE_H
#define MRB_SFML_BLEND_MODE_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Graphics/BlendMode.hpp>
#include "mrb/sfml/helpers.hxx"

MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_blend_mode_type;
MRB_SFML_EXTERN mrb_value mrb_sfml_blend_mode_value(mrb_state*, sf::BlendMode);

static inline sf::BlendMode*
mrb_sfml_blend_mode_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::BlendMode*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_blend_mode_type));
}

#endif
