#ifndef MRB_SFML_RENDER_STATES_H
#define MRB_SFML_RENDER_STATES_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Graphics/RenderStates.hpp>
#include "mrb/sfml/helpers.hxx"

MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_render_states_type;

static inline sf::RenderStates*
mrb_sfml_render_states_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::RenderStates*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_render_states_type));
}

#endif
