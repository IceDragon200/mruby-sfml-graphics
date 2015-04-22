#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <SFML/Graphics/BlendMode.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "mrb/sfml/graphics/blend_mode.hxx"
#include "mrb/sfml/graphics/transform.hxx"
#include "mrb/sfml/graphics/texture.hxx"
#include "mrb/sfml/graphics/shader.hxx"
#include "mrb/sfml/graphics/render_states.hxx"
#include "mrb/cxx/helpers.hxx"
#include "mrb_render_states.hxx"

static struct RClass *render_states_class;

static void
render_states_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    sf::RenderStates *render_states = static_cast<sf::RenderStates*>(ptr);
    delete render_states;
  }
}

extern "C" const struct mrb_data_type mrb_sfml_render_states_type = { "sf::RenderStates", render_states_free };

static inline sf::BlendMode*
get_blend_mode(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::BlendMode*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_blend_mode_type));
}

static inline sf::Transform*
get_transform(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Transform*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_transform_type));
}

static inline sf::Texture*
get_texture(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Texture*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_texture_type));
}

static inline sf::Shader*
get_shader(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Shader*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_shader_type));
}

static inline sf::RenderStates*
get_render_states(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::RenderStates*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_render_states_type));
}

static mrb_value
render_states_initialize(mrb_state *mrb, mrb_value self)
{
  sf::RenderStates *render_states;
  mrb_value obj = mrb_nil_value();
  sf::Transform *transform;
  mrb_value obj_texture = mrb_nil_value();
  mrb_value obj_shader = mrb_nil_value();
  /* The first argument is fuzzy, while the others are only used for the 4
     parameter initialize, I can save quite a bit of work by just throwing all
     of it here. However, a reference to the texture and shader must be stored.
   */
  mrb_int argc = mrb_get_args(mrb, "|odoo", &obj,
                                   &transform, &mrb_sfml_transform_type,
                                   &obj_texture,
                                   &obj_shader);
  if (argc == 0) {
    render_states = new sf::RenderStates();
  } else if (argc == 1) {
    cxx_mrb_ensure_type_data(mrb, obj);
    if (DATA_TYPE(obj) == &mrb_sfml_blend_mode_type) {
      render_states = new sf::RenderStates(*get_blend_mode(mrb, obj));
    } else if (DATA_TYPE(obj) == &mrb_sfml_transform_type) {
      render_states = new sf::RenderStates(*get_transform(mrb, obj));
    } else if (DATA_TYPE(obj) == &mrb_sfml_texture_type) {
      render_states = new sf::RenderStates(get_texture(mrb, obj));
    } else if (DATA_TYPE(obj) == &mrb_sfml_shader_type) {
      render_states = new sf::RenderStates(get_shader(mrb, obj));
    } else {
      mrb_raise(mrb, E_TYPE_ERROR, "Expected SFML::BlendMode, SFML::Transform, SFML::Texture or SFML::Shader");
      return mrb_nil_value();
    }
  } else if (argc == 4) {
    render_states = new sf::RenderStates(*get_blend_mode(mrb, obj),
                                         *transform,
                                          get_texture(mrb, obj_texture),
                                          get_shader(mrb, obj_shader));
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Expected 0, 1 or 4");
    return mrb_nil_value();
  }
  mrb_data_init(self, render_states, &mrb_sfml_render_states_type);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "__sfml_texture"), obj_texture);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "__sfml_shader"), obj_shader);
  return self;
}

static mrb_value
render_states_set_blend_mode(mrb_state *mrb, mrb_value self)
{
  sf::BlendMode *blend_mode;
  mrb_get_args(mrb, "d", &blend_mode, &mrb_sfml_blend_mode_type);
  get_render_states(mrb, self)->blendMode = *blend_mode;
  return self;
}

static mrb_value
render_states_set_transform(mrb_state *mrb, mrb_value self)
{
  sf::Transform *transform;
  mrb_get_args(mrb, "d", &transform, &mrb_sfml_transform_type);
  get_render_states(mrb, self)->transform = *transform;
  return self;
}

static mrb_value
render_states_set_texture(mrb_state *mrb, mrb_value self)
{
  sf::RenderStates *render_states;
  sf::Texture *texture;
  mrb_value obj;
  mrb_get_args(mrb, "o", &obj);
  render_states = get_render_states(mrb, self);
  texture = get_texture(mrb, obj);
  render_states->texture = texture;
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "__sfml_texture"), obj);
  return self;
}

static mrb_value
render_states_set_shader(mrb_state *mrb, mrb_value self)
{
  sf::RenderStates *render_states;
  sf::Shader *shader;
  mrb_value obj;
  mrb_get_args(mrb, "o", &obj);
  render_states = get_render_states(mrb, self);
  shader = get_shader(mrb, obj);
  render_states->shader = shader;
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "__sfml_shader"), obj);
  return self;
}

static mrb_value
render_states_get_blend_mode(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_blend_mode_value(mrb, get_render_states(mrb, self)->blendMode);
}

static mrb_value
render_states_get_transform(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_transform_value(mrb, get_render_states(mrb, self)->transform);
}

static mrb_value
render_states_get_texture(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "__sfml_texture"));
}

static mrb_value
render_states_get_shader(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "__sfml_shader"));
}

extern "C" void
mrb_sfml_render_states_init_bind(mrb_state *mrb, struct RClass *mod)
{
  render_states_class = mrb_define_class_under(mrb, mod, "RenderStates", mrb->object_class);
  MRB_SET_INSTANCE_TT(render_states_class, MRB_TT_DATA);

  mrb_define_method(mrb, render_states_class, "initialize", render_states_initialize, MRB_ARGS_ARG(0,4));

  mrb_define_method(mrb, render_states_class, "blend_mode", render_states_get_blend_mode, MRB_ARGS_NONE());
  mrb_define_method(mrb, render_states_class, "transform",  render_states_get_transform,  MRB_ARGS_NONE());
  mrb_define_method(mrb, render_states_class, "texture",    render_states_get_texture,    MRB_ARGS_NONE());
  mrb_define_method(mrb, render_states_class, "shader",     render_states_get_shader,     MRB_ARGS_NONE());

  mrb_define_method(mrb, render_states_class, "blend_mode=", render_states_set_blend_mode, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, render_states_class, "transform=",  render_states_set_transform,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, render_states_class, "texture=",    render_states_set_texture,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, render_states_class, "shader=",     render_states_set_shader,     MRB_ARGS_REQ(1));
}
