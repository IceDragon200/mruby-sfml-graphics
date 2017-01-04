#ifndef MRB_SFML_IMAGE_H
#define MRB_SFML_IMAGE_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Graphics/Image.hpp>
#include "mrb/sfml/helpers.hxx"

MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_image_type;
MRB_SFML_EXTERN mrb_value mrb_sfml_image_value(mrb_state*, sf::Image);

static inline sf::Image*
mrb_sfml_image_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Image*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_image_type));
}

#endif
