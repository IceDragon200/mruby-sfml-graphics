#ifndef MRB_SFML_PRIMITIVE_PRIV_H
#define MRB_SFML_PRIMITIVE_PRIV_H

#include <mruby.h>
#include <mruby/class.h>
#include "mrb/sfml/helpers.hxx"

MRB_SFML_EXTERN void mrb_sfml_primitive_type_init_bind(mrb_state *mrb, struct RClass *mod);

#endif
