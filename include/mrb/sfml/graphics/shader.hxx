#ifndef MRB_SFML_SHADER_H
#define MRB_SFML_SHADER_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Graphics/Shader.hpp>

extern "C" const struct mrb_data_type mrb_sfml_shader_type;

static inline sf::Shader*
mrb_sfml_shader_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Shader*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_shader_type));
}

#endif
