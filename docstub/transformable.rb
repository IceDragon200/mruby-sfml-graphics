module SFML
  # Decomposed transform defined by a position, a rotation and a scale
  module Transformable
    # @overload set_position(x, y)
    #   @param [Float] x
    #   @param [Float] y
    # @overload set_position(v2)
    #   @param [Vector2f] v2
    # @return [self]
    def set_position(*args)
    end

    # @param [Float] angle
    def set_rotation(angle)
    end

    # @overload set_scale(x, y)
    #   @param [Float] x
    #   @param [Float] y
    # @overload set_scale(v2)
    #   @param [Vector2f] v2
    # @return [self]
    def set_scale(*args)
    end

    # @overload set_origin(x, y)
    #   @param [Float] x
    #   @param [Float] y
    # @overload set_origin(v2)
    #   @param [Vector2f] v2
    # @return [self]
    def set_origin(*args)
    end

    # @return [Vector2f]
    def get_position
    end

    # @return [Float]
    def get_rotation
    end

    # @return [Vector2f]
    def get_scale
    end

    # @return [Vector2f]
    def get_origin
    end

    # @overload move(x, y)
    #   @param [Float] x
    #   @param [Float] y
    # @overload move(v2)
    #   @param [Vector2f] v2
    # @return [self]
    def move(*args)
    end

    # @param [Float] angle
    def rotate(angle)
    end

    # @overload scale(x, y)
    #   @param [Float] x
    #   @param [Float] y
    # @overload scale(v2)
    #   @param [Vector2f] v2
    # @return [self]
    def scale(*args)
    end

    # @return [Transform]
    def get_transform
    end

    # @return [Transform]
    def get_inverse_transform
    end

    alias :position :get_position
    alias :rotation :get_rotation
    alias :origin :get_origin
  end
end
