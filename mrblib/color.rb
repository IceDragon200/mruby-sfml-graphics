module SFML
  class Color
    alias :equal_color? :==

    # Checks if the other matches this color.
    #
    # @param [Object] other
    # @return [Boolean]
    def ==(other)
      other.is_a?(Color) && equal_color?(other)
    end
  end
end
