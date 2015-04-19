module SFML
  class Color
    # @!attribute r
    #   @return [Integer]
    attr_accessor :r
    # @!attribute g
    #   @return [Integer]
    attr_accessor :g
    # @!attribute b
    #   @return [Integer]
    attr_accessor :b
    # @!attribute a
    #   @return [Integer]
    attr_accessor :a

    # @param [Integer] r
    # @param [Integer] g
    # @param [Integer] b
    # @param [Integer] a
    def initialize(r = 0, g = 0, b = 0, a = 255)
    end

    # @param [Color] other
    # @return [Color]
    def +(other)
    end

    # @param [Color] other
    # @return [Color]
    def -(other)
    end

    # @param [Color] other
    # @return [Color]
    def *(other)
    end
  end
end
