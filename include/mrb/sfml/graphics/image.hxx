#ifndef MRB_SFML_IMAGE_H
#define MRB_SFML_IMAGE_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Graphics/Image.hpp>

extern "C" const struct mrb_data_type mrb_sfml_image_type;
extern "C" mrb_value mrb_sfml_image_value(mrb_state*, sf::Image);

static inline sf::Image*
mrb_sfml_image_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Image*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_image_type));
}

#endif
