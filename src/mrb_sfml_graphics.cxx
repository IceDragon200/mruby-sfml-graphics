#include <mruby.h>
#include <mruby/class.h>
#include <SFML/Graphics.hpp>
#include "mrb_blend_mode.hxx"
#include "mrb_color.hxx"
#include "mrb_image.hxx"
#include "mrb_rect.hxx"
#include "mrb_shader.hxx"
#include "mrb_texture.hxx"
#include "mrb_transform.hxx"
#include "mrb_primitive_type.hxx"
#include "mrb_shape.hxx"
#include "mrb_circle_shape.hxx"
#include "mrb_convex_shape.hxx"
#include "mrb_rectangle_shape.hxx"
#include "mrb_sprite.hxx"

static struct RClass *sfml_module;

extern "C" void
mrb_mruby_sfml_graphics_gem_init(mrb_state *mrb)
{
  sfml_module = mrb_define_module(mrb, "SFML");
  mrb_define_module_under(mrb, sfml_module, "Drawable");
  mrb_define_module_under(mrb, sfml_module, "Transformable");

  mrb_sfml_blend_mode_init_bind(mrb, sfml_module);
  mrb_sfml_color_init_bind(mrb, sfml_module);
  mrb_sfml_rect_init_bind(mrb, sfml_module);
  mrb_sfml_transform_init_bind(mrb, sfml_module);
  mrb_sfml_primitive_type_init_bind(mrb, sfml_module);
  mrb_sfml_image_init_bind(mrb, sfml_module);
  mrb_sfml_texture_init_bind(mrb, sfml_module);
  mrb_sfml_shader_init_bind(mrb, sfml_module);

  mrb_sfml_shape_init_bind(mrb, sfml_module);
  mrb_sfml_circle_shape_init_bind(mrb, sfml_module);
  mrb_sfml_convex_shape_init_bind(mrb, sfml_module);
  mrb_sfml_rectangle_shape_init_bind(mrb, sfml_module);
  mrb_sfml_sprite_init_bind(mrb, sfml_module);
}

extern "C" void
mrb_mruby_sfml_graphics_gem_final(mrb_state *mrb)
{
}
