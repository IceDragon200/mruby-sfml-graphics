#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/string.h>
#include <SFML/Graphics/Shader.hpp>
#include <string>
#include "mrb/sfml/graphics/shader.hxx"
#include "mrb/sfml/graphics/color.hxx"
#include "mrb/sfml/graphics/transform.hxx"
#include "mrb/sfml/graphics/texture.hxx"
#include "mrb/sfml/system/vector2.hxx"
#include "mrb/sfml/system/vector3.hxx"
#include "mrb_shader.hxx"

static struct RClass *shader_class;
static struct RClass *shader_type_module;

static void
shader_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    sf::Shader *shader = (sf::Shader*)ptr;
    delete shader;
  }
}

extern "C" const struct mrb_data_type mrb_sfml_shader_type = { "sf::Shader", shader_free };

static inline sf::Shader*
get_shader(mrb_state *mrb, mrb_value self)
{
  return (sf::Shader*)mrb_data_get_ptr(mrb, self, &mrb_sfml_shader_type);
}

static mrb_value
shader_initialize(mrb_state *mrb, mrb_value self)
{
  sf::Shader *shader = new sf::Shader();
  mrb_data_init(self, shader, &mrb_sfml_shader_type);
  return self;
}

static mrb_value
shader_load_from_file(mrb_state *mrb, mrb_value self)
{
  char *name;
  mrb_value other;
  mrb_get_args(mrb, "zo", &name, &other);
  sf::Shader *shader = get_shader(mrb, self);
  if (mrb_type(other) == MRB_TT_FIXNUM) {
    mrb_bool_value(shader->loadFromFile(std::string(name), (sf::Shader::Type)mrb_int(mrb, other)));
  } else if (mrb_type(other) == MRB_TT_STRING) {
    mrb_bool_value(shader->loadFromFile(std::string(name), std::string(mrb_str_to_cstr(mrb, other))));
  } else {
    mrb_raise(mrb, E_TYPE_ERROR, "expected Integer or String");
  }
  return mrb_bool_value(false);
}

static mrb_value
shader_load_from_memory(mrb_state *mrb, mrb_value self)
{
  char *name;
  mrb_value other;
  mrb_get_args(mrb, "zo", &name, &other);
  sf::Shader *shader = get_shader(mrb, self);
  if (mrb_type(other) == MRB_TT_FIXNUM) {
    mrb_bool_value(shader->loadFromMemory(std::string(name), (sf::Shader::Type)mrb_int(mrb, other)));
  } else if (mrb_type(other) == MRB_TT_STRING) {
    mrb_bool_value(shader->loadFromMemory(std::string(name), std::string(mrb_str_to_cstr(mrb, other))));
  } else {
    mrb_raise(mrb, E_TYPE_ERROR, "expected Integer or String");
  }
  return mrb_bool_value(false);
}

static void
shader_set_parameter_data(mrb_state *mrb, sf::Shader *shader, std::string &name, mrb_value x)
{
  void *dptr = DATA_PTR(x);
  const struct mrb_data_type *dt = DATA_TYPE(x);
  if (&mrb_sfml_color_type == dt) {
    shader->setParameter(name, *((sf::Color*)dptr));
  } else if (&mrb_sfml_texture_type == dt) {
    shader->setParameter(name, *((sf::Texture*)dptr));
  } else if (&mrb_sfml_transform_type == dt) {
    shader->setParameter(name, *((sf::Transform*)dptr));
  } else if (&mrb_sfml_vector2f_type == dt) {
    shader->setParameter(name, *((sf::Vector2f*)dptr));
  } else if (&mrb_sfml_vector3f_type == dt) {
    shader->setParameter(name, *((sf::Vector3f*)dptr));
  } else {
    mrb_raise(mrb, E_TYPE_ERROR, "expected SFML::Color, SFML::Texture, SFML::Transform, SFML::Vector2, or SFML::Vector3");
  }
}

static mrb_value
shader_set_parameter(mrb_state *mrb, mrb_value self)
{
  char *name;
  sf::Shader *shader;
  mrb_value x;
  mrb_float y, z, w;
  mrb_int argc = mrb_get_args(mrb, "zo|fff", &name, &x, &y, &z, &w);
  shader = get_shader(mrb, self);
  std::string sname(name);
  if (argc == 2) {
    switch (mrb_type(x)) {
      case MRB_TT_FIXNUM:
      case MRB_TT_FLOAT: {
        shader->setParameter(sname, (float)mrb_to_flo(mrb, x));
      } break;
      case MRB_TT_DATA: {
        shader_set_parameter_data(mrb, shader, sname, x);
      } break;
      default: {
        mrb_raise(mrb, E_TYPE_ERROR, "expected Numeric, or DATA");
      }
    }
  } else if (argc == 3) {
    shader->setParameter(sname, (float)mrb_to_flo(mrb, x), (float)y);
  } else if (argc == 4) {
    shader->setParameter(sname, (float)mrb_to_flo(mrb, x), (float)y, (float)z);
  } else if (argc == 5) {
    shader->setParameter(sname, (float)mrb_to_flo(mrb, x), (float)y, (float)z, (float)w);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected 2, 3, 4, or 5 arguments");
  }
  return self;
}

//static mrb_value
//shader_get_native_handle(mrb_state *mrb, mrb_value self)
//{
//  return mrb_fixnum_value(get_shader(mrb, self)->getNativeHandle());
//}

static mrb_value
shader_s_bind(mrb_state *mrb, mrb_value klass)
{
  sf::Shader *shader;
  mrb_get_args(mrb, "d", &shader, &mrb_sfml_shader_type);
  sf::Shader::bind(shader);
  return klass;
}

static mrb_value
shader_s_available(mrb_state *mrb, mrb_value klass)
{
  return mrb_bool_value(sf::Shader::isAvailable());
}

extern "C" void
mrb_sfml_shader_init_bind(mrb_state *mrb, struct RClass *mod)
{
  shader_class = mrb_define_class_under(mrb, mod, "Shader", mrb->object_class);
  shader_type_module = mrb_define_module_under(mrb, shader_class, "Type");
  MRB_SET_INSTANCE_TT(shader_class, MRB_TT_DATA);

  mrb_define_method(mrb, shader_class, "initialize",       shader_initialize,       MRB_ARGS_NONE());
  mrb_define_method(mrb, shader_class, "load_from_file",   shader_load_from_file,   MRB_ARGS_REQ(2));
  mrb_define_method(mrb, shader_class, "load_from_memory", shader_load_from_memory, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, shader_class, "set_parameter",    shader_set_parameter,    MRB_ARGS_ANY());
  //mrb_define_method(mrb, shader_class, "native_handle",   shader_get_native_handle, MRB_ARGS_NONE());

  mrb_define_class_method(mrb, shader_class, "bind",       shader_s_bind,      MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, shader_class, "available?", shader_s_available, MRB_ARGS_NONE());

  mrb_define_const(mrb, shader_type_module, "Vertex",   mrb_fixnum_value(sf::Shader::Type::Vertex));
  mrb_define_const(mrb, shader_type_module, "Fragment", mrb_fixnum_value(sf::Shader::Type::Fragment));
}
