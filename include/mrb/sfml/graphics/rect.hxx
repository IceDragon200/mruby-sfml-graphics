#ifndef MRB_SFML_RECT_H
#define MRB_SFML_RECT_H

#include <mruby.h>
#include <mruby/data.h>

extern "C" const struct mrb_data_type mrb_sfml_int_rect_type;
extern "C" const struct mrb_data_type mrb_sfml_float_rect_type;
extern "C" mrb_value mrb_sfml_int_rect_value(mrb_state*, sf::IntRect);
extern "C" mrb_value mrb_sfml_float_rect_value(mrb_state*, sf::FloatRect);

template <typename T> static inline const mrb_data_type* mrb_get_sfml_rect_type();
template <> inline const mrb_data_type* mrb_get_sfml_rect_type<float>() { return &mrb_sfml_float_rect_type; };
template <> inline const mrb_data_type* mrb_get_sfml_rect_type<int>() { return &mrb_sfml_int_rect_type; };

#endif
