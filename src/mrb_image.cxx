#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/Graphics/Image.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/graphics/image.hxx"
#include "mrb/sfml/graphics/color.hxx"
#include "mrb/sfml/graphics/rect.hxx"
#include "mrb/sfml/system/vector2.hxx"
#include "mrb_image.hxx"

static struct RClass *image_class;
static mrb_data_free_func image_free = cxx_mrb_data_free<sf::Image>;
extern "C" const struct mrb_data_type mrb_sfml_image_type = { "sf::Image", image_free };

extern "C" mrb_value
mrb_sfml_image_value(mrb_state *mrb, sf::Image img)
{
  mrb_value result = mrb_obj_new(mrb, image_class, 0, NULL);
  sf::Image *target = mrb_sfml_image_ptr(mrb, result);
  *target = img;
  return result;
}

static mrb_value
image_initialize(mrb_state *mrb, mrb_value self)
{
  sf::Image *image = new sf::Image();
  image_free(mrb, DATA_PTR(self));
  mrb_data_init(self, image, &mrb_sfml_image_type);
  return self;
}

static mrb_value
image_create(mrb_state *mrb, mrb_value self)
{
  mrb_int w;
  mrb_int h;
  sf::Color *color = NULL;
  mrb_get_args(mrb, "ii|d", &w, &h, &color, &mrb_sfml_color_type);
  if (color) {
    mrb_sfml_image_ptr(mrb, self)->create(w, h, *color);
  } else {
    mrb_sfml_image_ptr(mrb, self)->create(w, h);
  }
  return self;
}

static mrb_value
image_load_from_file(mrb_state *mrb, mrb_value self)
{
  char *name;
  mrb_get_args(mrb, "z", &name);
  return mrb_bool_value(mrb_sfml_image_ptr(mrb, self)->loadFromFile(std::string(name)));
}

static mrb_value
image_save_to_file(mrb_state *mrb, mrb_value self)
{
  char *name;
  mrb_get_args(mrb, "z", &name);
  return mrb_bool_value(mrb_sfml_image_ptr(mrb, self)->saveToFile(std::string(name)));
}

static mrb_value
image_get_size(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_vector2u_value(mrb, mrb_sfml_image_ptr(mrb, self)->getSize());
}

static mrb_value
image_create_mask_from_color(mrb_state *mrb, mrb_value self)
{
  sf::Color *color;
  mrb_int alpha;
  mrb_get_args(mrb, "d|i", &color, &mrb_sfml_color_type, &alpha);
  mrb_sfml_image_ptr(mrb, self)->createMaskFromColor(*color, alpha);
  return self;
}

static mrb_value
image_copy(mrb_state *mrb, mrb_value self)
{
  sf::Image *source;
  mrb_int x, y;
  sf::IntRect *src_rect;
  mrb_bool apply_alpha;
  mrb_int argc = mrb_get_args(mrb, "dii|db", &source, &mrb_sfml_image_type,
                              &x, &y,
                              &src_rect, &mrb_sfml_int_rect_type,
                              &apply_alpha);
  if (argc == 3) {
    mrb_sfml_image_ptr(mrb, self)->copy(*source, x, y);
  } else if (argc == 4) {
    mrb_sfml_image_ptr(mrb, self)->copy(*source, x, y, *src_rect);
  } else if (argc == 5) {
    mrb_sfml_image_ptr(mrb, self)->copy(*source, x, y, *src_rect, apply_alpha);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected 3, 4, or 5");
  }
  return self;
}

static mrb_value
image_set_pixel(mrb_state *mrb, mrb_value self)
{
  mrb_int x, y;
  sf::Color *color;
  mrb_get_args(mrb, "iid", &x, &y, &color, &mrb_sfml_color_type);
  mrb_sfml_image_ptr(mrb, self)->setPixel(x, y, *color);
  return self;
}

static mrb_value
image_get_pixel(mrb_state *mrb, mrb_value self)
{
  mrb_int x, y;
  mrb_get_args(mrb, "ii", &x, &y);
  return mrb_sfml_color_value(mrb, mrb_sfml_image_ptr(mrb, self)->getPixel(x, y));
}

static mrb_value
image_flip_horizontally(mrb_state *mrb, mrb_value self)
{
  mrb_sfml_image_ptr(mrb, self)->flipHorizontally();
  return self;
}

static mrb_value
image_flip_vertically(mrb_state *mrb, mrb_value self)
{
  mrb_sfml_image_ptr(mrb, self)->flipVertically();
  return self;
}

extern "C" void
mrb_sfml_image_init_bind(mrb_state *mrb, struct RClass *mod)
{
  image_class = mrb_define_class_under(mrb, mod, "Image", mrb->object_class);
  MRB_SET_INSTANCE_TT(image_class, MRB_TT_DATA);

  mrb_define_method(mrb, image_class, "initialize",             image_initialize,             MRB_ARGS_NONE());
  mrb_define_method(mrb, image_class, "create",                 image_create,                 MRB_ARGS_ARG(2,1));
  mrb_define_method(mrb, image_class, "load_from_file",         image_load_from_file,         MRB_ARGS_REQ(1));
  mrb_define_method(mrb, image_class, "save_to_file",           image_save_to_file,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, image_class, "size",                   image_get_size,               MRB_ARGS_NONE());
  mrb_define_method(mrb, image_class, "create_mask_from_color", image_create_mask_from_color, MRB_ARGS_ARG(1,1));
  mrb_define_method(mrb, image_class, "copy",                   image_copy,                   MRB_ARGS_ARG(3, 2));
  mrb_define_method(mrb, image_class, "set_pixel",              image_set_pixel,              MRB_ARGS_REQ(3));
  mrb_define_method(mrb, image_class, "get_pixel",              image_get_pixel,              MRB_ARGS_REQ(2));
  mrb_define_method(mrb, image_class, "flip_horizontally",      image_flip_horizontally,      MRB_ARGS_NONE());
  mrb_define_method(mrb, image_class, "flip_vertically",        image_flip_vertically,        MRB_ARGS_NONE());
}
