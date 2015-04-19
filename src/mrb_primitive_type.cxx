#include <mruby.h>
#include <mruby/class.h>
#include <SFML/Graphics/PrimitiveType.hpp>
#include "mrb_primitive_type.hxx"

extern "C" void
mrb_sfml_primitive_type_init_bind(mrb_state *mrb, struct RClass *mod)
{
  struct RClass *primitive_type_module = mrb_define_module_under(mrb, mod, "PrimitiveType");

  mrb_define_const(mrb, primitive_type_module, "Points", mrb_fixnum_value(sf::PrimitiveType::Points));
  mrb_define_const(mrb, primitive_type_module, "Lines", mrb_fixnum_value(sf::PrimitiveType::Lines));
  mrb_define_const(mrb, primitive_type_module, "LinesStrip", mrb_fixnum_value(sf::PrimitiveType::LinesStrip));
  mrb_define_const(mrb, primitive_type_module, "Triangles", mrb_fixnum_value(sf::PrimitiveType::Triangles));
  mrb_define_const(mrb, primitive_type_module, "TrianglesStrip", mrb_fixnum_value(sf::PrimitiveType::TrianglesStrip));
  mrb_define_const(mrb, primitive_type_module, "TrianglesFan", mrb_fixnum_value(sf::PrimitiveType::TrianglesFan));
  mrb_define_const(mrb, primitive_type_module, "Quads", mrb_fixnum_value(sf::PrimitiveType::Quads));
}
