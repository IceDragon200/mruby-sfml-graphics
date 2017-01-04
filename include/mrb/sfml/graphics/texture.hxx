#ifndef MRB_SFML_TEXTURE_H
#define MRB_SFML_TEXTURE_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Graphics/Texture.hpp>
#include "mrb/sfml/helpers.hxx"

MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_texture_type;

static inline sf::Texture*
mrb_sfml_texture_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Texture*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_texture_type));
}

#endif
