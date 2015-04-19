module SFML
  class Sprite
    include Drawable
    include Transformable

    def initialize
    end

    # @param [Texture] texture
    def set_texture(texture, reset_rect = false)

    end

    # @param [IntRect] rect
    def set_texture_rect(rect)
    end

    # @param [Color] color
    def set_color(color)
    end

    # @return [Texture]
    def get_texture
    end

    # @return [IntRect]
    def get_texture_rect
    end

    # @return [Color]
    def get_color
    end

    # @return [FloatRect]
    def get_local_bounds
    end

    # @return [FloatRect]
    def get_global_bounds
    end

    alias :texture= :set_texture
    alias :color= :set_color
    alias :texture_rect= :set_texture_rect

    alias :texture :get_texture
    alias :texture_rect :get_texture_rect
    alias :color :get_color
    alias :local_bounds :get_local_bounds
    alias :global_bounds :get_global_bounds
  end
end

mrb_define_class_under(mrb, mod, "Sprite", mrb_class_get_under(mrb, mod, "Shape"));
_method(mrb, sprite_class, "initialize", sprite_initialize, MRB_ARGS_NONE());
mrb_define_method(mrb, sprite_class, "set_texture", sprite_set_texture, MRB_ARGS_ARG(1, 1));
mrb_define_method(mrb, sprite_class, "set_texture_rect", sprite_set_texture_rect, MRB_ARGS_REQ(1));
mrb_define_method(mrb, sprite_class, "set_color", sprite_set_color, MRB_ARGS_REQ(1));
mrb_define_method(mrb, sprite_class, "get_texture", sprite_get_texture, MRB_ARGS_NONE());
mrb_define_method(mrb, sprite_class, "get_texture_rect", sprite_get_texture_rect, MRB_ARGS_NONE());
mrb_define_method(mrb, sprite_class, "get_color", sprite_get_color, MRB_ARGS_NONE());
mrb_define_method(mrb, sprite_class, "get_local_bounds", sprite_get_local_bounds, MRB_ARGS_NONE());
mrb_define_method(mrb, sprite_class, "get_global_bounds", sprite_get_global_bounds, MRB_ARGS_NONE());
mrb_define_alias(mrb, sprite_class, "color=", "set_color");
mrb_define_alias(mrb, sprite_class, "texture_rect=", "set_texture_rect");
mrb_define_alias(mrb, sprite_class, "texture", "get_texture");
mrb_define_alias(mrb, sprite_class, "texture_rect", "get_texture_rect");
mrb_define_alias(mrb, sprite_class, "color", "get_color");
mrb_define_alias(mrb, sprite_class, "local_bounds", "get_local_bounds");
mrb_define_alias(mrb, sprite_class, "global_bounds", "get_global_bounds");
