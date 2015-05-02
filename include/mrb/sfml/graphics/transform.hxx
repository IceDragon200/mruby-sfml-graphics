#ifndef MRB_SFML_TRANSFORM_H
#define MRB_SFML_TRANSFORM_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Graphics/Transform.hpp>

extern "C" const struct mrb_data_type mrb_sfml_transform_type;
extern "C" mrb_value mrb_sfml_transform_value(mrb_state*, sf::Transform);

static inline sf::Transform*
mrb_sfml_transform_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Transform*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_transform_type));
}

#endif
