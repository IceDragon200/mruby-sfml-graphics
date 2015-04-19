#include <mruby.h>
#include <mruby/class.h>
#include <SFML/Graphics.hpp>
#include "mrb_color.hxx"
#include "mrb_image.hxx"
#include "mrb_rect.hxx"
#include "mrb_shader.hxx"
#include "mrb_texture.hxx"
#include "mrb_transform.hxx"

static struct RClass *sfml_module;

extern "C" void
mrb_mruby_sfml_graphics_gem_init(mrb_state *mrb)
{
  sfml_module = mrb_define_module(mrb, "SFML");

  mrb_sfml_color_init_bind(mrb, sfml_module);
  mrb_sfml_rect_init_bind(mrb, sfml_module);
  mrb_sfml_image_init_bind(mrb, sfml_module);
  mrb_sfml_shader_init_bind(mrb, sfml_module);
  mrb_sfml_texture_init_bind(mrb, sfml_module);
  mrb_sfml_transform_init_bind(mrb, sfml_module);
}

extern "C" void
mrb_mruby_sfml_graphics_gem_final(mrb_state *mrb)
{
}
