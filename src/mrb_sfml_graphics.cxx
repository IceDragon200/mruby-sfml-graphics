#include <mruby.h>
#include <mruby/class.h>
#include <SFML/Graphics.hpp>
#include "mrb_blend_mode.hxx"
#include "mrb_circle_shape.hxx"
#include "mrb_color.hxx"
#include "mrb_convex_shape.hxx"
#include "mrb_font.hxx"
#include "mrb_glyph.hxx"
#include "mrb_image.hxx"
#include "mrb_primitive_type.hxx"
#include "mrb_rect.hxx"
#include "mrb_rectangle_shape.hxx"
#include "mrb_render_states.hxx"
#include "mrb_render_target.hxx"
#include "mrb_render_texture.hxx"
#include "mrb_render_window.hxx"
#include "mrb_shader.hxx"
#include "mrb_shape.hxx"
#include "mrb_sprite.hxx"
#include "mrb_text.hxx"
#include "mrb_texture.hxx"
#include "mrb_transform.hxx"
#include "mrb_view.hxx"
#include "mrb/sfml/helpers.hxx"

MRB_SFML_EXTERN void
mrb_mruby_sfml_graphics_gem_init(mrb_state *mrb)
{
  struct RClass* sfml_module = mrb_define_module(mrb, "SFML");
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
  mrb_sfml_render_states_init_bind(mrb, sfml_module);
  mrb_sfml_render_target_init_bind(mrb, sfml_module);
  mrb_sfml_render_texture_init_bind(mrb, sfml_module);
  mrb_sfml_render_window_init_bind(mrb, sfml_module);

  mrb_sfml_shape_init_bind(mrb, sfml_module);
  mrb_sfml_circle_shape_init_bind(mrb, sfml_module);
  mrb_sfml_convex_shape_init_bind(mrb, sfml_module);
  mrb_sfml_rectangle_shape_init_bind(mrb, sfml_module);
  mrb_sfml_sprite_init_bind(mrb, sfml_module);

  mrb_sfml_glyph_init_bind(mrb, sfml_module);
  mrb_sfml_font_init_bind(mrb, sfml_module);
  mrb_sfml_text_init_bind(mrb, sfml_module);

  mrb_sfml_view_init_bind(mrb, sfml_module);
}

MRB_SFML_EXTERN void
mrb_mruby_sfml_graphics_gem_final(mrb_state *mrb)
{
}
