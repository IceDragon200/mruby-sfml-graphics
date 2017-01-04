#ifndef MRB_SFML_VIEW_H
#define MRB_SFML_VIEW_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <SFML/Graphics/View.hpp>
#include "mrb/sfml/helpers.hxx"

MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_view_type;

static inline sf::View*
mrb_sfml_view_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::View*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_view_type));
}

#endif
