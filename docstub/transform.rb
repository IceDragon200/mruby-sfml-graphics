module SFML
  class Transform
    # @overload initialize
    # @overload initialize(a00, a01, a02, a10, a11, a12, a20, a21, a22)
    #   @param [Float] a00
    #   @param [Float] a01
    #   @param [Float] a02
    #   @param [Float] a10
    #   @param [Float] a11
    #   @param [Float] a12
    #   @param [Float] a20
    #   @param [Float] a21
    #   @param [Float] a22
    def initialize(*args)
    end

    # @return [Transform]
    def get_inverse
    end

    # @overload transform_point(point)
    #   @param [Vector2f] point
    # @overload transform_point(x, y)
    #   @param [Float] x
    #   @param [Float] y
    # @return [Vector2f]
    def transform_point(x, y = nil)
    end

    # @param [FloatRect] rect
    # @return [FloatRect]
    def transform_rect(rect)
    end

    # @param [Transform] other
    # @return [Transform]
    def combine(other)
    end

    # @overload translate(offset)
    #   @param [Vector2f] offset
    # @overload translate(x, y)
    #   @param [Float] x
    #   @param [Float] y
    # @return [Transform]
    def translate(x, y = nil)
    end

    # @overload rotate(angle)
    #   @param [Float] angle
    # @overload rotate(angle, center)
    #   @param [Float] angle
    #   @param [Vector2f] center
    # @overload rotate(angle, center_x, center_y)
    #   @param [Float] angle
    #   @param [Float] center_x
    #   @param [Float] center_y
    # @return [Transform]
    def rotate(angle, *args)
    end

    # @overload scale(factors)
    #   @param [Vector2f] factors
    # @overload scale(scale_x, scale_y)
    #   @param [Float] scale_x
    #   @param [Float] scale_y
    # @overload scale(scale_x, scale_y, center_x, center_y)
    #   @param [Float] scale_x
    #   @param [Float] scale_y
    #   @param [Float] center_x
    #   @param [Float] center_y
    # @return [Transform]
    def scale(x, y = nil)
    end

    # @overload *(vother)
    #   @param [Vector2f] vother
    #   @return [Vector2f]
    # @overload *(tother)
    #   @param [Transform] tother
    #   @return [Transform]
    def *(other)
    end

    alias :inverse :get_inverse
  end
end
