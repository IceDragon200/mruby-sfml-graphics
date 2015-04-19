#ifndef MRB_SFML_COLOR_H
#define MRB_SFML_COLOR_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Graphics/Color.hpp>

extern "C" const struct mrb_data_type mrb_sfml_color_type;
extern "C" mrb_value mrb_sfml_color_value(mrb_state*, sf::Color);

#endif
