#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/Graphics/Texture.hpp>

static struct RClass *texture_class;

static void
texture_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    sf::Texture *texture = (sf::Texture*)ptr;
    delete texture;
  }
}

extern "C" const struct mrb_data_type mrb_sfml_texture_type = { "sf::Texture", texture_free };

static inline sf::Texture*
get_texture(mrb_state *mrb, mrb_value self)
{
  return (sf::Texture*)mrb_data_get_ptr(mrb, self, &mrb_sfml_texture_type);
}

static mrb_value
texture_initialize(mrb_state *mrb, mrb_value self)
{
  sf::Texture *texture = new sf::Texture();
  mrb_data_init(self, texture, &mrb_sfml_texture_type);
  return self;
}

extern "C" void
mrb_sfml_texture_init_bind(mrb_state *mrb, struct RClass *mod)
{
  texture_class = mrb_define_class_under(mrb, mod, "Texture", mrb->object_class);
  MRB_SET_INSTANCE_TT(texture_class, MRB_TT_DATA);

  mrb_define_method(mrb, texture_class, "initialize", texture_initialize, MRB_ARGS_NONE());
}
