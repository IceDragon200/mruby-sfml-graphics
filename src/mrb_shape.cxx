#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/Graphics/Shape.hpp>
#include "mrb_shape.hxx"

static struct RClass *shape_class;

extern "C" void
mrb_sfml_shape_init_bind(mrb_state *mrb, struct RClass *mod)
{
  shape_class = mrb_define_class_under(mrb, mod, "Shape", mrb->object_class);
  mrb_include_module(mrb, shape_class, mrb_module_get_under(mrb, mod, "Drawable"));
  mrb_include_module(mrb, shape_class, mrb_module_get_under(mrb, mod, "Transformable"));
}
