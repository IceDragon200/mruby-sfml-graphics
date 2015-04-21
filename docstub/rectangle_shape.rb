module SFML
  class RectangleShape < Shape
    # @overload initialize
    # @overload initialize(size)
    #   @param [Vector2f] size
    def initialize(*args)
    end

    # @param [Vector2f] size
    def set_size(size)
    end

    # @return [Vector2f]
    def get_size
    end

    alias :size= :set_size
    alias :size :get_size
  end
end
