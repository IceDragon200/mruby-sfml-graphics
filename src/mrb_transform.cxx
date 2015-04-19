#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/Graphics/Transform.hpp>
#include <mrb/sfml/graphics/transform.hxx>

static struct RClass *transform_class;

static void
transform_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    sf::Transform *transform = (sf::Transform*)ptr;
    delete transform;
  }
}

extern "C" const struct mrb_data_type mrb_sfml_transform_type = { "sf::Transform", transform_free };

static inline sf::Transform*
get_transform(mrb_state *mrb, mrb_value self)
{
  return (sf::Transform*)mrb_data_get_ptr(mrb, self, &mrb_sfml_transform_type);
}

extern "C" mrb_value
mrb_sfml_transform_value(mrb_state *mrb, sf::Transform transform)
{
  mrb_value result = mrb_obj_new(mrb, transform_class, 0, NULL);
  sf::Transform *target = get_transform(mrb, result);
  *target = transform;
  return result;
}

static mrb_value
transform_initialize(mrb_state *mrb, mrb_value self)
{
  sf::Transform *transform = new sf::Transform();
  mrb_data_init(self, transform, &mrb_sfml_transform_type);
  return self;
}

extern "C" void
mrb_sfml_transform_init_bind(mrb_state *mrb, struct RClass *mod)
{
  transform_class = mrb_define_class_under(mrb, mod, "Transform", mrb->object_class);
  MRB_SET_INSTANCE_TT(transform_class, MRB_TT_DATA);

  mrb_define_method(mrb, transform_class, "initialize", transform_initialize, MRB_ARGS_NONE());
}
