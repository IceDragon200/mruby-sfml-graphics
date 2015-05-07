#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/window/window.hxx"
#include "mrb/sfml/window/window_bind.hxx"
#include "mrb/sfml/graphics/render_target_bind.hxx"
#include "mrb/sfml/graphics/render_window.hxx"
#include "mrb/sfml/graphics/image.hxx"
#include "mrb/sfml/system/vector2.hxx"
#include "mrb_render_window.hxx"

static mrb_data_free_func render_window_free = cxx_mrb_data_free<sf::RenderWindow>;
extern "C" const struct mrb_data_type mrb_sfml_render_window_type = { "sf::RenderWindow", render_window_free };

static mrb_value
render_window_capture(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_image_value(mrb, mrb_sfml_render_window_ptr(mrb, self)->capture());
}

extern "C" void
mrb_sfml_render_window_init_bind(mrb_state *mrb, struct RClass *mod)
{
  struct RClass *render_window_cls = mrb_define_class_under(mrb, mod, "RenderWindow", mrb_class_get_under(mrb, mod, "Window"));
  MRB_SET_INSTANCE_TT(render_window_cls, MRB_TT_DATA);
  mrb_include_module(mrb, render_window_cls, mrb_module_get_under(mrb, mod, "RenderTarget"));

  mrb_sfml_window_bind_class<sf::RenderWindow>(mrb, render_window_cls);
  mrb_sfml_render_target_bind_class<sf::RenderWindow>(mrb, render_window_cls);
  mrb_define_method(mrb, render_window_cls, "capture", render_window_capture, MRB_ARGS_NONE());
}
