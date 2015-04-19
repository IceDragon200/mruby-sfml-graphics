module SFML
  class Shape
    include Drawable
    include Transformable

    # @param [Texture] texture
    # @param [Boolean] reset_rect
    # @return [self]
    def set_texture(texture, reset_rect = false)
    end

    # @param [IntRect] rect
    # @return [self]
    def set_texture_rect(rect)
    end

    # @param [Color] color
    # @return [self]
    def set_fill_color(color)
    end

    # @param [Color] color
    # @return [self]
    def set_outline_color(color)
    end

    # @param [Float] thickness
    # @return [self]
    def set_outline_thickness(thickness)
    end

    # @return [Texture]
    def get_texture
    end

    # @return [IntRect]
    def get_texture_rect
    end

    # @return [Color]
    def get_fill_color
    end

    # @return [Color]
    def get_outline_color
    end

    # @return [Integer]
    def get_point_count
    end

    # @param [Integer] index
    # @return [Vector2f]
    def get_point(index)
    end

    # @return [FloatRect]
    def get_local_bounds
    end

    # @return [FloatRect]
    def get_global_bounds
    end

    alias :texture= :set_texture
    alias :texture_rect= :set_texture_rect
    alias :fill_color= :set_fill_color
    alias :outline_color= :set_outline_color
    alias :outline_thickness= :set_outline_thickness

    alias :texture :get_texture
    alias :texture_rect :get_texture_rect
    alias :fill_color :get_fill_color
    alias :outline_color :get_outline_color
    alias :outline_thickness :get_outline_thickness
    alias :point_count :get_point_count
    alias :point_at :get_point
    alias :local_bounds :get_local_bounds
    alias :global_bounds :get_global_bounds
  end
end
