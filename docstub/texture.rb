module SFML
  # Image living on the graphics card that can be used for drawing
  class Texture
    def initialize
    end

    # @param [Integer] width
    # @param [Integer] height
    # @return [self]
    def create(width, height)
    end

    # @param [String] filename
    # @param [IntRect] rect
    # @return [self]
    def load_from_file(filename, rect = IntRect.new)
    end
  end
end
