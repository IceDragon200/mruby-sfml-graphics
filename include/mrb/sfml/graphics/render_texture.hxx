#ifndef MRB_SFML_SHADER_H
#define MRB_SFML_SHADER_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Graphics/RenderTexture.hpp>
#include "mrb/sfml/graphics/render_texture.hxx"
#include "mrb/sfml/helpers.hxx"

MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_render_texture_type;

static inline sf::RenderTexture*
mrb_sfml_render_texture_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::RenderTexture*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_render_texture_type));
}

#endif
