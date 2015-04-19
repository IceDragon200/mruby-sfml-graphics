#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/Graphics/Sprite.hpp>
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

static mrb_value
sprite_initialize(mrb_state *mrb, mrb_value self)
{
  sf::Sprite *sprite = new sf::Sprite();
  mrb_data_init(self, sprite, &mrb_sfml_sprite_type);
  return self;
}

extern "C" void
mrb_sfml_sprite_init_bind(mrb_state *mrb, struct RClass *mod)
{
  sprite_class = mrb_define_class_under(mrb, mod, "Sprite", mrb_class_get_under(mrb, mod, "Shape"));
  MRB_SET_INSTANCE_TT(sprite_class, MRB_TT_DATA);

  mrb_define_method(mrb, sprite_class, "initialize", sprite_initialize, MRB_ARGS_NONE());
  drawable_bind_class<sf::Sprite>(mrb, sprite_class);
  transformable_bind_class<sf::Sprite>(mrb, sprite_class);
}
