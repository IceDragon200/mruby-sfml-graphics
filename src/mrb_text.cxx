#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/graphics/color.hxx"
#include "mrb/sfml/graphics/font.hxx"
#include "mrb/sfml/graphics/rect.hxx"
#include "mrb/sfml/system/vector2.hxx"
#include "mrb_text.hxx"
#include "mrb_drawable.hxx"
#include "mrb_transformable.hxx"

static struct RClass *text_class;
static mrb_data_free_func text_free = cxx_mrb_data_free<sf::Text>;

MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_text_type = { "sf::Text", text_free };

static inline sf::Text*
get_text(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Text*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_text_type));
}

static mrb_value
text_initialize(mrb_state *mrb, mrb_value self)
{
  sf::Text *text;
  sf::Font *font;
  char *str;
  mrb_int char_size;
  mrb_int argc = mrb_get_args(mrb, "|zdi", &str, &font, &mrb_sfml_font_type, &char_size);
  if (argc == 0) {
    text = new sf::Text();
  } else if (argc == 2) {
    text = new sf::Text(sf::String(str), *font);
  } else if (argc == 3) {
    text = new sf::Text(sf::String(str), *font, char_size);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Expected 0, 2 or 3");
    return mrb_nil_value();
  }
  mrb_data_init(self, text, &mrb_sfml_text_type);
  return self;
}

MRB_SFML_EXTERN void
mrb_sfml_text_init_bind(mrb_state *mrb, struct RClass *mod)
{
  text_class = mrb_define_class_under(mrb, mod, "Text", mrb->object_class);
  struct RClass *text_style_module = mrb_define_module_under(mrb, text_class, "Style");
  MRB_SET_INSTANCE_TT(text_class, MRB_TT_DATA);
  mrb_include_module(mrb, text_class, mrb_module_get_under(mrb, mod, "Drawable"));
  mrb_include_module(mrb, text_class, mrb_module_get_under(mrb, mod, "Transformable"));

  drawable_bind_class<sf::Text>(mrb, text_class);
  transformable_bind_class<sf::Text>(mrb, text_class);

  mrb_define_method(mrb, text_class, "initialize", text_initialize, MRB_ARGS_ARG(0,3));

  mrb_define_const(mrb, text_style_module, "Regular",       mrb_fixnum_value(sf::Text::Style::Regular));
  mrb_define_const(mrb, text_style_module, "Bold",          mrb_fixnum_value(sf::Text::Style::Bold));
  mrb_define_const(mrb, text_style_module, "Italic",        mrb_fixnum_value(sf::Text::Style::Italic));
  mrb_define_const(mrb, text_style_module, "Underlined",    mrb_fixnum_value(sf::Text::Style::Underlined));
  mrb_define_const(mrb, text_style_module, "StrikeThrough", mrb_fixnum_value(sf::Text::Style::StrikeThrough));
}
