#ifndef MRB_SFML_RECT_H
#define MRB_SFML_RECT_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Graphics/Rect.hpp>

extern "C" const struct mrb_data_type mrb_sfml_int_rect_type;
extern "C" const struct mrb_data_type mrb_sfml_float_rect_type;
extern "C" mrb_value mrb_sfml_int_rect_value(mrb_state*, sf::IntRect);
extern "C" mrb_value mrb_sfml_float_rect_value(mrb_state*, sf::FloatRect);

template <typename T> static inline const mrb_data_type* mrb_get_sfml_rect_type();
template <> inline const mrb_data_type* mrb_get_sfml_rect_type<float>() { return &mrb_sfml_float_rect_type; };
template <> inline const mrb_data_type* mrb_get_sfml_rect_type<int>() { return &mrb_sfml_int_rect_type; };

template <typename T>
static inline sf::Rect<T>*
mrb_sfml_rect_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Rect<T>*>(mrb_data_get_ptr(mrb, self, mrb_get_sfml_rect_type<T>()));
}

#endif
