module SFML
  # Utility class for manipulating 2D axis aligned rectangles
  # @abstract
  class Rect
    # @!attribute top
    #   @return [Numeric]
    attr_accessor :top
    # @!attribute left
    #   @return [Numeric]
    attr_accessor :left
    # @!attribute width
    #   @return [Numeric]
    attr_accessor :width
    # @!attribute height
    #   @return [Numeric]
    attr_accessor :height

    def initialize
    end

    # @param [Rect] other  same rect type
    def initialize_copy(other)
    end

    # @param [Rect] other
    def contains?(other)
    end

    # @param [Rect] other
    def intersects?(other)
    end
  end
end
