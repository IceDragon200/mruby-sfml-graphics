module SFML
  # Class for loading, manipulating and saving images
  class Image
    def initialize
    end

    # @param [Integer] width
    # @param [Integer] height
    # @return [self]
    def create(width, height, color = Color.new(0, 0, 0))
    end

    # @param [String] filename
    # @return [self]
    def load_from_file(filename)
    end

    # @param [String] filename
    # @return [self]
    def save_to_file(filename)
    end

    # @return [Vector2u]
    def size
    end

    # @param [Color] color
    # @param [Integer] alpha
    # @return [self]
    def create_mask_from_color(color, alpha = 0)
    end

    # @param [Image] source
    # @param [Integer] x
    # @param [Integer] y
    # @param [IntRect] src_rect
    # @param [Boolean] apply_alpha
    # @return [self]
    def copy(source, x, y, src_rect = IntRect.new(0, 0, 0, 0), apply_alpha = false)
    end

    # @param [Integer] x
    # @param [Integer] y
    # @param [Color] color
    # @return [self]
    def set_pixel(x, y, color)
    end

    # @param [Integer] x
    # @param [Integer] y
    # @return [Color]
    def get_pixel(x, y)
    end

    # @return [self]
    def flip_horizontally
    end

    # @return [self]
    def flip_vertically
    end
  end
end
