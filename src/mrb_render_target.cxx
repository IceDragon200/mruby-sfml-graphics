#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/graphics/render_target_bind.hxx"

MRB_SFML_EXTERN void
mrb_sfml_render_target_init_bind(mrb_state *mrb, struct RClass *mod)
{
  struct RClass *render_target_mod = mrb_define_module_under(mrb, mod, "RenderTarget");
}
