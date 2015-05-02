#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/Graphics/View.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/graphics/view.hxx"
#include "mrb_view.hxx"

static mrb_data_free_func view_free = cxx_mrb_data_free<sf::View>;
extern "C" const struct mrb_data_type mrb_sfml_view_type = { "sf::View", view_free };

extern "C" void
mrb_sfml_view_init_bind(mrb_state *mrb, struct RClass *mod)
{
  struct RClass *view_class = mrb_define_class_under(mrb, mod, "View", mrb->object_class);
  MRB_SET_INSTANCE_TT(view_class, MRB_TT_DATA);
}
