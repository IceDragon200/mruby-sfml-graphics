#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/Graphics/RenderTexture.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/graphics/render_target_bind.hxx"
#include "mrb/sfml/graphics/render_texture.hxx"
#include "mrb/sfml/graphics/image.hxx"
#include "mrb/sfml/system/vector2.hxx"
#include "mrb_render_texture.hxx"

static mrb_data_free_func render_texture_free = cxx_mrb_data_free<sf::RenderTexture>;
MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_render_texture_type = { "sf::RenderTexture", render_texture_free };

static mrb_value
render_texture_create(mrb_state *mrb, mrb_value self)
{
  mrb_int width, height;
  mrb_bool depth_buffer = false;
  mrb_get_args(mrb, "ii|b", &width, &height, &depth_buffer);
  mrb_sfml_render_texture_ptr(mrb, self)->create(width, height, depth_buffer);
  return self;
}

static mrb_value
render_texture_set_smooth(mrb_state *mrb, mrb_value self)
{
  mrb_bool smooth;
  mrb_get_args(mrb, "b", &smooth);
  mrb_sfml_render_texture_ptr(mrb, self)->setSmooth(smooth);
  return self;
}

static mrb_value
render_texture_is_smooth(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value(mrb_sfml_render_texture_ptr(mrb, self)->isSmooth());
}

static mrb_value
render_texture_set_repeated(mrb_state *mrb, mrb_value self)
{
  mrb_bool repeated;
  mrb_get_args(mrb, "b", &repeated);
  mrb_sfml_render_texture_ptr(mrb, self)->setRepeated(repeated);
  return self;
}

static mrb_value
render_texture_is_repeated(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value(mrb_sfml_render_texture_ptr(mrb, self)->isRepeated());
}

static mrb_value
render_texture_generate_mipmap(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value(mrb_sfml_render_texture_ptr(mrb, self)->generateMipmap());
}

static mrb_value
render_texture_set_active(mrb_state *mrb, mrb_value self)
{
  mrb_bool active = true;
  mrb_get_args(mrb, "|b", &active);
  mrb_sfml_render_texture_ptr(mrb, self)->setActive(active);
  return self;
}

static mrb_value
render_texture_display(mrb_state *mrb, mrb_value self)
{
  mrb_sfml_render_texture_ptr(mrb, self)->display();
  return self;
}

static mrb_value
render_texture_get_texture(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "texture"));
}

MRB_SFML_EXTERN void
mrb_sfml_render_texture_init_bind(mrb_state *mrb, struct RClass *mod)
{
  struct RClass *render_texture_cls = mrb_define_class_under(mrb, mod, "RenderTexture", mrb_class_get_under(mrb, mod, "Texture"));
  MRB_SET_INSTANCE_TT(render_texture_cls, MRB_TT_DATA);
  mrb_include_module(mrb, render_texture_cls, mrb_module_get_under(mrb, mod, "RenderTarget"));

  mrb_sfml_render_target_bind_class<sf::RenderTexture>(mrb, render_texture_cls);

  mrb_define_method(mrb, render_texture_cls, "create", render_texture_create, MRB_ARGS_ARG(2,1));

  mrb_define_method(mrb, render_texture_cls, "set_smooth", render_texture_set_smooth, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, render_texture_cls, "is_smooth?", render_texture_is_smooth, MRB_ARGS_NONE());
  mrb_define_alias(mrb, render_texture_cls, "smooth=", "set_smooth");
  mrb_define_alias(mrb, render_texture_cls, "smooth", "is_smooth?");
  mrb_define_alias(mrb, render_texture_cls, "smooth?", "is_smooth?");

  mrb_define_method(mrb, render_texture_cls, "set_repeated", render_texture_set_repeated, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, render_texture_cls, "is_repeated?", render_texture_is_repeated, MRB_ARGS_NONE());
  mrb_define_alias(mrb, render_texture_cls, "repeated=", "set_repeated");
  mrb_define_alias(mrb, render_texture_cls, "repeated", "is_repeated?");
  mrb_define_alias(mrb, render_texture_cls, "repeated?", "is_repeated?");

  mrb_define_method(mrb, render_texture_cls, "generate_mipmap", render_texture_generate_mipmap, MRB_ARGS_NONE());
  mrb_define_method(mrb, render_texture_cls, "set_active", render_texture_set_active, MRB_ARGS_ARG(0,1));

  mrb_define_method(mrb, render_texture_cls, "display", render_texture_display, MRB_ARGS_NONE());

  mrb_define_method(mrb, render_texture_cls, "get_texture", render_texture_get_texture, MRB_ARGS_NONE());
  mrb_define_alias(mrb, render_texture_cls, "texture", "get_texture");
}
