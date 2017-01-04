#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/Graphics/Texture.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/graphics/texture.hxx"
#include "mrb/sfml/graphics/image.hxx"
#include "mrb/sfml/graphics/rect.hxx"
#include "mrb/sfml/window/window.hxx"
#include "mrb/sfml/system/vector2.hxx"
#include "mrb_texture.hxx"

static mrb_data_free_func texture_free = cxx_mrb_data_free<sf::Texture>;
extern "C" const struct mrb_data_type mrb_sfml_texture_type = { "sf::Texture", texture_free };

static mrb_value
texture_initialize(mrb_state *mrb, mrb_value self)
{
  sf::Texture *texture;
  sf::Texture *src = NULL;
  mrb_get_args(mrb, "|d", &src, &mrb_sfml_texture_type);
  if (src) {
    texture = new sf::Texture(*src);
  } else {
    texture = new sf::Texture();
  }
  texture_free(mrb, DATA_PTR(self));
  mrb_data_init(self, texture, &mrb_sfml_texture_type);
  return self;
}

static mrb_value
texture_create(mrb_state *mrb, mrb_value self)
{
  mrb_int width, height;
  mrb_get_args(mrb, "ii", &width, &height);
  mrb_sfml_texture_ptr(mrb, self)->create(width, height);
  return self;
}

static mrb_value
texture_load_from_file(mrb_state *mrb, mrb_value self)
{
  char *str;
  sf::IntRect *intrect = NULL;
  mrb_get_args(mrb, "z|d", &str, &intrect, &mrb_sfml_int_rect_type);
  if (intrect) {
    mrb_sfml_texture_ptr(mrb, self)->loadFromFile(std::string(str), *intrect);
  } else {
    mrb_sfml_texture_ptr(mrb, self)->loadFromFile(std::string(str));
  }
  return self;
}

static mrb_value
texture_load_from_image(mrb_state *mrb, mrb_value self)
{
  sf::Image *img;
  sf::IntRect *intrect = NULL;
  mrb_get_args(mrb, "d|d", &img, &mrb_sfml_image_type,
                           &intrect, &mrb_sfml_int_rect_type);
  if (intrect) {
    mrb_sfml_texture_ptr(mrb, self)->loadFromImage(*img, *intrect);
  } else {
    mrb_sfml_texture_ptr(mrb, self)->loadFromImage(*img);
  }
  return self;
}

static mrb_value
texture_get_size(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_vector2u_value(mrb, mrb_sfml_texture_ptr(mrb, self)->getSize());
}

static mrb_value
texture_copy_to_image(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_image_value(mrb, mrb_sfml_texture_ptr(mrb, self)->copyToImage());
}

static mrb_value
texture_update_from_image(mrb_state *mrb, mrb_value self)
{
  sf::Image *img;
  mrb_int x, y;
  mrb_int argc = mrb_get_args(mrb, "d|ii", &img, &mrb_sfml_image_type, &x, &y);
  if (argc == 1) {
    mrb_sfml_texture_ptr(mrb, self)->update(*img);
  } else if (argc == 3) {
    mrb_sfml_texture_ptr(mrb, self)->update(*img, x, y);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Expected 1 or 3");
    return mrb_nil_value();
  }
  return self;
}

static mrb_value
texture_update_from_window(mrb_state *mrb, mrb_value self)
{
  sf::Window *wnd;
  mrb_int x, y;
  mrb_int argc = mrb_get_args(mrb, "d|ii", &wnd, &mrb_sfml_window_type, &x, &y);
  if (argc == 1) {
    mrb_sfml_texture_ptr(mrb, self)->update(*wnd);
  } else if (argc == 3) {
    mrb_sfml_texture_ptr(mrb, self)->update(*wnd, x, y);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Expected 1 or 3");
    return mrb_nil_value();
  }
  return self;
}

static mrb_value
texture_set_smooth(mrb_state *mrb, mrb_value self)
{
  mrb_bool b;
  mrb_get_args(mrb, "b", &b);
  mrb_sfml_texture_ptr(mrb, self)->setSmooth(b);
  return self;
}

static mrb_value
texture_is_smooth(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value(mrb_sfml_texture_ptr(mrb, self)->isSmooth());
}

static mrb_value
texture_set_srgb(mrb_state *mrb, mrb_value self)
{
  mrb_bool b;
  mrb_get_args(mrb, "b", &b);
  mrb_sfml_texture_ptr(mrb, self)->setSrgb(b);
  return self;
}

static mrb_value
texture_is_srgb(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value(mrb_sfml_texture_ptr(mrb, self)->isSrgb());
}

static mrb_value
texture_set_repeated(mrb_state *mrb, mrb_value self)
{
  mrb_bool repeated;
  mrb_get_args(mrb, "b", &repeated);
  mrb_sfml_texture_ptr(mrb, self)->setRepeated(repeated);
  return self;
}

static mrb_value
texture_is_repeated(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value(mrb_sfml_texture_ptr(mrb, self)->isRepeated());
}

static mrb_value
texture_generate_mipmap(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value(mrb_sfml_texture_ptr(mrb, self)->generateMipmap());
}

static mrb_value
texture_get_native_handle(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(mrb_sfml_texture_ptr(mrb, self)->getNativeHandle());
}

static mrb_value
texture_s_bind(mrb_state *mrb, mrb_value self)
{
  sf::Texture *texture;
  mrb_int coord_type = (mrb_int)sf::Texture::CoordinateType::Normalized;
  mrb_get_args(mrb, "d|i", &texture, &mrb_sfml_texture_type, &coord_type);
  sf::Texture::bind(texture, (sf::Texture::CoordinateType)coord_type);
  return self;
}

static mrb_value
texture_s_get_maximum_size(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(sf::Texture::getMaximumSize());
}

extern "C" void
mrb_sfml_texture_init_bind(mrb_state *mrb, struct RClass *mod)
{
  struct RClass *texture_class = mrb_define_class_under(mrb, mod, "Texture", mrb->object_class);
  struct RClass *coordinate_type_mod = mrb_define_module_under(mrb, texture_class, "CoordinateType");
  mrb_define_const(mrb, coordinate_type_mod, "Normalized", mrb_fixnum_value(sf::Texture::CoordinateType::Normalized));
  mrb_define_const(mrb, coordinate_type_mod, "Pixels", mrb_fixnum_value(sf::Texture::CoordinateType::Pixels));

  MRB_SET_INSTANCE_TT(texture_class, MRB_TT_DATA);

  mrb_define_method(mrb, texture_class, "initialize",         texture_initialize,         MRB_ARGS_ARG(0,1));
  mrb_define_method(mrb, texture_class, "create",             texture_create,             MRB_ARGS_REQ(2));
  mrb_define_method(mrb, texture_class, "load_from_file",     texture_load_from_file,     MRB_ARGS_ARG(1,1));
  mrb_define_method(mrb, texture_class, "load_from_image",    texture_load_from_image,    MRB_ARGS_ARG(1,1));

  mrb_define_method(mrb, texture_class, "get_size",           texture_get_size,           MRB_ARGS_NONE());
  mrb_define_alias(mrb, texture_class, "size", "get_size");

  mrb_define_method(mrb, texture_class, "copy_to_image",      texture_copy_to_image,      MRB_ARGS_NONE());
  mrb_define_alias(mrb, texture_class, "to_image", "copy_to_image");

  mrb_define_method(mrb, texture_class, "update_from_image",  texture_update_from_image,  MRB_ARGS_ARG(1,2));
  mrb_define_method(mrb, texture_class, "update_from_window", texture_update_from_window, MRB_ARGS_ARG(1,2));
  mrb_define_method(mrb, texture_class, "set_smooth",         texture_set_smooth,         MRB_ARGS_REQ(1));
  mrb_define_method(mrb, texture_class, "is_smooth",          texture_is_smooth,          MRB_ARGS_NONE());
  mrb_define_alias(mrb, texture_class, "smooth=", "set_smooth");
  mrb_define_alias(mrb, texture_class, "smooth", "is_smooth");
  mrb_define_alias(mrb, texture_class, "smooth?", "is_smooth");

  mrb_define_method(mrb, texture_class, "set_srgb",           texture_set_srgb,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, texture_class, "is_srgb",            texture_is_srgb,            MRB_ARGS_NONE());
  mrb_define_alias(mrb, texture_class, "srgb=", "set_srgb");
  mrb_define_alias(mrb, texture_class, "srgb", "is_srgb");
  mrb_define_alias(mrb, texture_class, "srgb?", "is_srgb");

  mrb_define_method(mrb, texture_class, "set_repeated",       texture_set_repeated,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, texture_class, "is_repeated",        texture_is_repeated,        MRB_ARGS_NONE());
  mrb_define_alias(mrb, texture_class, "repeated=", "set_repeated");
  mrb_define_alias(mrb, texture_class, "repeated", "is_repeated?");
  mrb_define_alias(mrb, texture_class, "repeated?", "is_repeated?");

  mrb_define_method(mrb, texture_class, "generate_mipmap", texture_generate_mipmap, MRB_ARGS_NONE());

  mrb_define_method(mrb, texture_class, "get_native_handle",  texture_get_native_handle,  MRB_ARGS_NONE());
  mrb_define_alias(mrb, texture_class, "native_handle", "get_native_handle");

  mrb_define_class_method(mrb, texture_class, "bind",             texture_s_bind,             MRB_ARGS_ARG(1,1));
  mrb_define_class_method(mrb, texture_class, "get_maximum_size", texture_s_get_maximum_size, MRB_ARGS_NONE());
}
