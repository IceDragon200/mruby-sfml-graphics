module SFML
  # Drawable representation of a texture, with its own transformations, color, etc.
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
