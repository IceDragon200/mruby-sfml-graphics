#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/Graphics/ConvexShape.hpp>
#include "mrb_convex_shape.hxx"
#include "mrb_shape.hxx"

static struct RClass *convex_shape_class;
static mrb_data_free_func convex_shape_free = cxx_mrb_data_free<sf::ConvexShape>;

MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_convex_shape_type = { "sf::ConvexShape", convex_shape_free };

static inline sf::ConvexShape*
get_convex_shape(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::ConvexShape*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_convex_shape_type));
}

/* @!class ConvexShape
 * @!method initialize
 *   @overload initialize
 *   @overload initialize(point_count)
 *     @param [Integer] point_count
 */
static mrb_value
convex_shape_initialize(mrb_state *mrb, mrb_value self)
{
  sf::ConvexShape *convex_shape;
  mrb_int point_count;
  mrb_int argc = mrb_get_args(mrb, "|i", &point_count);
  if (argc == 0) {
    convex_shape = new sf::ConvexShape();
  } else if (argc == 1) {
    convex_shape = new sf::ConvexShape(point_count);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected 0, or 1");
    return self;
  }
  convex_shape_free(mrb, DATA_PTR(self));
  mrb_data_init(self, convex_shape, &mrb_sfml_convex_shape_type);
  return self;
}

static mrb_value
convex_shape_set_point(mrb_state *mrb, mrb_value self)
{
  mrb_int index;
  sf::Vector2f *point;
  mrb_get_args(mrb, "id", &index, &point, &mrb_sfml_vector2f_type);
  get_convex_shape(mrb, self)->setPoint(index, *point);
  return self;
}

static mrb_value
convex_shape_get_point(mrb_state *mrb, mrb_value self)
{
  mrb_int index;
  mrb_get_args(mrb, "i", &index);
  return mrb_sfml_vector2f_value(mrb, get_convex_shape(mrb, self)->getPoint(index));
}

static mrb_value
convex_shape_set_point_count(mrb_state *mrb, mrb_value self)
{
  mrb_int points;
  mrb_get_args(mrb, "i", &points);
  get_convex_shape(mrb, self)->setPointCount(points);
  return self;
}

MRB_SFML_EXTERN void
mrb_sfml_convex_shape_init_bind(mrb_state *mrb, struct RClass *mod)
{
  convex_shape_class = mrb_define_class_under(mrb, mod, "ConvexShape", mrb_class_get_under(mrb, mod, "Shape"));
  MRB_SET_INSTANCE_TT(convex_shape_class, MRB_TT_DATA);

  mrb_define_method(mrb, convex_shape_class, "initialize", convex_shape_initialize, MRB_ARGS_ARG(0,1));
  shape_bind_class<sf::ConvexShape>(mrb, convex_shape_class);
  mrb_define_method(mrb, convex_shape_class, "set_point",      convex_shape_set_point, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, convex_shape_class, "get_point",      convex_shape_get_point, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, convex_shape_class, "set_point_count", convex_shape_set_point_count, MRB_ARGS_REQ(1));

  mrb_define_alias(mrb, convex_shape_class, "point_count=", "set_point_count");
}
