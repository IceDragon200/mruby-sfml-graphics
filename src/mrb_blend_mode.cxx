#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <SFML/Graphics/BlendMode.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/graphics/blend_mode.hxx"
#include "mrb_blend_mode.hxx"

static struct RClass *blend_mode_class;
static mrb_data_free_func blend_mode_free = cxx_mrb_data_free<sf::BlendMode>;

extern "C" const mrb_data_type mrb_sfml_blend_mode_type = { "sf::BlendMode", blend_mode_free };

extern "C" mrb_value
mrb_sfml_blend_mode_value(mrb_state *mrb, sf::BlendMode blend_mode)
{
  mrb_value result = mrb_obj_new(mrb, blend_mode_class, 0, NULL);
  sf::BlendMode *target = mrb_sfml_blend_mode_ptr(mrb, result);
  *target = blend_mode;
  return result;
}

static mrb_value
blend_mode_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_int a, b, c, d, e, f;
  mrb_int argc = mrb_get_args(mrb, "|iiiiii", &a, &b, &c, &d, &e, &f);
  sf::BlendMode *blend_mode;
  if (argc == 0) {
    blend_mode = new sf::BlendMode();
  } else if (argc == 3) {
    blend_mode = new sf::BlendMode((sf::BlendMode::Factor)a, (sf::BlendMode::Factor)b, (sf::BlendMode::Equation)c);
  } else if (argc == 6) {
    blend_mode = new sf::BlendMode((sf::BlendMode::Factor)a, (sf::BlendMode::Factor)b, (sf::BlendMode::Equation)c,
                                   (sf::BlendMode::Factor)d, (sf::BlendMode::Factor)e, (sf::BlendMode::Equation)f);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected, 0, 3 or 6");
    return self;
  }
  blend_mode_free(mrb, DATA_PTR(self));
  mrb_data_init(self, blend_mode, &mrb_sfml_blend_mode_type);
  return self;
}

static mrb_value
blend_mode_get_color_src_factor(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(mrb_sfml_blend_mode_ptr(mrb, self)->colorSrcFactor);
}

static mrb_value
blend_mode_get_color_dst_factor(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(mrb_sfml_blend_mode_ptr(mrb, self)->colorDstFactor);
}

static mrb_value
blend_mode_get_color_equation(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(mrb_sfml_blend_mode_ptr(mrb, self)->colorEquation);
}

static mrb_value
blend_mode_get_alpha_src_factor(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(mrb_sfml_blend_mode_ptr(mrb, self)->alphaSrcFactor);
}

static mrb_value
blend_mode_get_alpha_dst_factor(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(mrb_sfml_blend_mode_ptr(mrb, self)->alphaDstFactor);
}

static mrb_value
blend_mode_get_alpha_equation(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(mrb_sfml_blend_mode_ptr(mrb, self)->alphaEquation);
}

static mrb_value
blend_mode_set_color_src_factor(mrb_state *mrb, mrb_value self)
{
  mrb_int value;
  mrb_get_args(mrb, "i", &value);
  mrb_sfml_blend_mode_ptr(mrb, self)->colorSrcFactor = (sf::BlendMode::Factor)value;
  return self;
}

static mrb_value
blend_mode_set_color_dst_factor(mrb_state *mrb, mrb_value self)
{
  mrb_int value;
  mrb_get_args(mrb, "i", &value);
  mrb_sfml_blend_mode_ptr(mrb, self)->colorDstFactor = (sf::BlendMode::Factor)value;
  return self;
}

static mrb_value
blend_mode_set_color_equation(mrb_state *mrb, mrb_value self)
{
  mrb_int value;
  mrb_get_args(mrb, "i", &value);
  mrb_sfml_blend_mode_ptr(mrb, self)->colorEquation = (sf::BlendMode::Equation)value;
  return self;
}

static mrb_value
blend_mode_set_alpha_src_factor(mrb_state *mrb, mrb_value self)
{
  mrb_int value;
  mrb_get_args(mrb, "i", &value);
  mrb_sfml_blend_mode_ptr(mrb, self)->alphaSrcFactor = (sf::BlendMode::Factor)value;
  return self;
}

static mrb_value
blend_mode_set_alpha_dst_factor(mrb_state *mrb, mrb_value self)
{
  mrb_int value;
  mrb_get_args(mrb, "i", &value);
  mrb_sfml_blend_mode_ptr(mrb, self)->alphaDstFactor = (sf::BlendMode::Factor)value;
  return self;
}

static mrb_value
blend_mode_set_alpha_equation(mrb_state *mrb, mrb_value self)
{
  mrb_int value;
  mrb_get_args(mrb, "i", &value);
  mrb_sfml_blend_mode_ptr(mrb, self)->alphaEquation = (sf::BlendMode::Equation)value;
  return self;
}


extern "C" void
mrb_sfml_blend_mode_init_bind(mrb_state *mrb, struct RClass *mod)
{
  struct RClass *blend_mode_factor_module;
  struct RClass *blend_mode_equation_module;
  blend_mode_class = mrb_define_class_under(mrb, mod, "BlendMode", mrb->object_class);
  MRB_SET_INSTANCE_TT(blend_mode_class, MRB_TT_DATA);
  blend_mode_factor_module = mrb_define_module_under(mrb, blend_mode_class, "Factor");
  blend_mode_equation_module = mrb_define_module_under(mrb, blend_mode_class, "Equation");

  mrb_define_method(mrb, blend_mode_class, "initialize", blend_mode_initialize, MRB_ARGS_ANY());

  mrb_define_method(mrb, blend_mode_class, "color_src_factor", blend_mode_get_color_src_factor, MRB_ARGS_NONE());
  mrb_define_method(mrb, blend_mode_class, "color_dst_factor", blend_mode_get_color_dst_factor, MRB_ARGS_NONE());
  mrb_define_method(mrb, blend_mode_class, "color_equation",   blend_mode_get_color_equation,   MRB_ARGS_NONE());
  mrb_define_method(mrb, blend_mode_class, "alpha_src_factor", blend_mode_get_alpha_src_factor, MRB_ARGS_NONE());
  mrb_define_method(mrb, blend_mode_class, "alpha_dst_factor", blend_mode_get_alpha_dst_factor, MRB_ARGS_NONE());
  mrb_define_method(mrb, blend_mode_class, "alpha_equation",   blend_mode_get_alpha_equation,   MRB_ARGS_NONE());

  mrb_define_method(mrb, blend_mode_class, "color_src_factor=", blend_mode_set_color_src_factor, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, blend_mode_class, "color_dst_factor=", blend_mode_set_color_dst_factor, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, blend_mode_class, "color_equation=",   blend_mode_set_color_equation,   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, blend_mode_class, "alpha_src_factor=", blend_mode_set_alpha_src_factor, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, blend_mode_class, "alpha_dst_factor=", blend_mode_set_alpha_dst_factor, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, blend_mode_class, "alpha_equation=",   blend_mode_set_alpha_equation,   MRB_ARGS_REQ(1));

  mrb_define_const(mrb, blend_mode_factor_module, "Zero",             mrb_fixnum_value(sf::BlendMode::Factor::Zero));
  mrb_define_const(mrb, blend_mode_factor_module, "One",              mrb_fixnum_value(sf::BlendMode::Factor::One));
  mrb_define_const(mrb, blend_mode_factor_module, "SrcColor",         mrb_fixnum_value(sf::BlendMode::Factor::SrcColor));
  mrb_define_const(mrb, blend_mode_factor_module, "OneMinusSrcColor", mrb_fixnum_value(sf::BlendMode::Factor::OneMinusSrcColor));
  mrb_define_const(mrb, blend_mode_factor_module, "DstColor",         mrb_fixnum_value(sf::BlendMode::Factor::DstColor));
  mrb_define_const(mrb, blend_mode_factor_module, "OneMinusDstColor", mrb_fixnum_value(sf::BlendMode::Factor::OneMinusDstColor));
  mrb_define_const(mrb, blend_mode_factor_module, "SrcAlpha",         mrb_fixnum_value(sf::BlendMode::Factor::SrcAlpha));
  mrb_define_const(mrb, blend_mode_factor_module, "OneMinusSrcAlpha", mrb_fixnum_value(sf::BlendMode::Factor::OneMinusSrcAlpha));
  mrb_define_const(mrb, blend_mode_factor_module, "DstAlpha",         mrb_fixnum_value(sf::BlendMode::Factor::DstAlpha));
  mrb_define_const(mrb, blend_mode_factor_module, "OneMinusDstAlpha", mrb_fixnum_value(sf::BlendMode::Factor::OneMinusDstAlpha));

  mrb_define_const(mrb, blend_mode_equation_module, "Add", mrb_fixnum_value(sf::BlendMode::Equation::Add));
  mrb_define_const(mrb, blend_mode_equation_module, "Subtract", mrb_fixnum_value(sf::BlendMode::Equation::Subtract));
}
