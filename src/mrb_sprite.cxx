#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <SFML/Graphics/Sprite.hpp>
#include "mrb/sfml/graphics/sprite.hxx"
#include "mrb/sfml/graphics/color.hxx"
#include "mrb/sfml/system/vector2.hxx"
#include "mrb/sfml/graphics/rect.hxx"
#include "mrb/sfml/graphics/texture.hxx"
#include "mrb_sprite.hxx"
#include "mrb_transformable.hxx"
#include "mrb_drawable.hxx"

static struct RClass *sprite_class;

static void
sprite_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    sf::Sprite *sprite = static_cast<sf::Sprite*>(ptr);
    delete sprite;
  }
}

extern "C" const struct mrb_data_type mrb_sfml_sprite_type = { "sf::Sprite", sprite_free };

static inline sf::Sprite*
get_sprite(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Sprite*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_sprite_type));
}

static inline sf::Texture*
get_texture(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Texture*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_texture_type));
}

static mrb_value
sprite_initialize(mrb_state *mrb, mrb_value self)
{
  sf::Sprite *sprite = new sf::Sprite();
  sprite_free(mrb, DATA_PTR(self));
  mrb_data_init(self, sprite, &mrb_sfml_sprite_type);
  return self;
}

static mrb_value
sprite_set_texture(mrb_state *mrb, mrb_value self)
{
  sf::Texture *texture;
  mrb_value texture_obj;
  mrb_bool reset_rect;
  sf::Sprite *sprite;
  mrb_int argc = mrb_get_args(mrb, "o|b", &texture_obj, &reset_rect);
  sprite = get_sprite(mrb, self);
  texture = get_texture(mrb, texture_obj);
  if (argc == 1) {
    sprite->setTexture(*texture);
  } else if (argc == 2) {
    sprite->setTexture(*texture, reset_rect);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected 1 or 2");
  }
  /* Keeps the texture alive as long as the Sprite exists */
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "__sfml_texture"), texture_obj);
  return self;
}

static mrb_value
sprite_set_texture_rect(mrb_state *mrb, mrb_value self)
{
  sf::IntRect *rect;
  mrb_get_args(mrb, "d", &rect, &mrb_sfml_int_rect_type);
  get_sprite(mrb, self)->setTextureRect(*rect);
  return self;
}

static mrb_value
sprite_set_color(mrb_state *mrb, mrb_value self)
{
  sf::Color *color;
  mrb_get_args(mrb, "d", &color, &mrb_sfml_color_type);
  get_sprite(mrb, self)->setColor(*color);
  return self;
}

static mrb_value
sprite_get_texture(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "__sfml_texture"));
}

static mrb_value
sprite_get_texture_rect(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_int_rect_value(mrb, get_sprite(mrb, self)->getTextureRect());
}

static mrb_value
sprite_get_color(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_color_value(mrb, get_sprite(mrb, self)->getColor());
}

static mrb_value
sprite_get_local_bounds(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_float_rect_value(mrb, get_sprite(mrb, self)->getLocalBounds());
}

static mrb_value
sprite_get_global_bounds(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_float_rect_value(mrb, get_sprite(mrb, self)->getGlobalBounds());
}

extern "C" void
mrb_sfml_sprite_init_bind(mrb_state *mrb, struct RClass *mod)
{
  sprite_class = mrb_define_class_under(mrb, mod, "Sprite", mrb_class_get_under(mrb, mod, "Shape"));
  MRB_SET_INSTANCE_TT(sprite_class, MRB_TT_DATA);

  mrb_define_method(mrb, sprite_class, "initialize", sprite_initialize, MRB_ARGS_NONE());
  drawable_bind_class<sf::Sprite>(mrb, sprite_class);
  transformable_bind_class<sf::Sprite>(mrb, sprite_class);
  mrb_define_method(mrb, sprite_class, "set_texture", sprite_set_texture, MRB_ARGS_ARG(1, 1));
  mrb_define_method(mrb, sprite_class, "set_texture_rect", sprite_set_texture_rect, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, sprite_class, "set_color", sprite_set_color, MRB_ARGS_REQ(1));

  mrb_define_method(mrb, sprite_class, "get_texture", sprite_get_texture, MRB_ARGS_NONE());
  mrb_define_method(mrb, sprite_class, "get_texture_rect", sprite_get_texture_rect, MRB_ARGS_NONE());
  mrb_define_method(mrb, sprite_class, "get_color", sprite_get_color, MRB_ARGS_NONE());
  mrb_define_method(mrb, sprite_class, "get_local_bounds", sprite_get_local_bounds, MRB_ARGS_NONE());
  mrb_define_method(mrb, sprite_class, "get_global_bounds", sprite_get_global_bounds, MRB_ARGS_NONE());

  mrb_define_alias(mrb, sprite_class, "texture=", "set_texture");
  mrb_define_alias(mrb, sprite_class, "color=", "set_color");
  mrb_define_alias(mrb, sprite_class, "texture_rect=", "set_texture_rect");

  mrb_define_alias(mrb, sprite_class, "texture", "get_texture");
  mrb_define_alias(mrb, sprite_class, "texture_rect", "get_texture_rect");
  mrb_define_alias(mrb, sprite_class, "color", "get_color");
  mrb_define_alias(mrb, sprite_class, "local_bounds", "get_local_bounds");
  mrb_define_alias(mrb, sprite_class, "global_bounds", "get_global_bounds");
}
