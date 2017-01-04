#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <SFML/Graphics/Font.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/graphics/font.hxx"

struct RClass *font_class;
static mrb_data_free_func font_free = cxx_mrb_data_free<sf::Font>;

MRB_SFML_EXTERN const mrb_data_type mrb_sfml_font_type = { "sf::Font", font_free };

MRB_SFML_EXTERN void
mrb_sfml_font_init_bind(mrb_state *mrb, struct RClass *mod)
{
  font_class = mrb_define_class_under(mrb, mod, "Font", mrb->object_class);
  MRB_SET_INSTANCE_TT(font_class, MRB_TT_DATA);
}
