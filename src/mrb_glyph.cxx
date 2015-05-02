#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <SFML/Graphics/Glyph.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/graphics/glyph.hxx"

struct RClass *glyph_class;
static mrb_data_free_func glyph_free = cxx_mrb_data_free<sf::Glyph>;
extern "C" const mrb_data_type mrb_sfml_glyph_type = { "sf::Glyph", glyph_free };

extern "C" mrb_value
mrb_sfml_glyph_value(mrb_state *mrb, sf::Glyph glyph)
{
  mrb_value result = mrb_obj_new(mrb, glyph_class, 0, NULL);
  sf::Glyph *target = mrb_sfml_glyph_ptr(mrb, result);
  *target = glyph;
  return result;
}

extern "C" void
mrb_sfml_glyph_init_bind(mrb_state *mrb, struct RClass *mod)
{
  glyph_class = mrb_define_class_under(mrb, mod, "Glyph", mrb->object_class);
  MRB_SET_INSTANCE_TT(glyph_class, MRB_TT_DATA);
}
