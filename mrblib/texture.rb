module SFML
  class Texture
    # @overload update(window)
    #   @param [Window] window
    # @overload update(window, x, y)
    #   @param [Window] window
    #   @param [Integer] x
    #   @param [Integer] y
    # @overload update(image)
    #   @param [Image] image
    # @overload update(image, x, y)
    #   @param [Image] image
    #   @param [Integer] x
    #   @param [Integer] y
    def update(obj, *a)
      if obj.is_a?(Window)
        update_from_window(obj, *a)
      elsif obj.is_a?(Image)
        update_from_image(obj, *a)
      else
        raise TypeError, 'expected SFML::Window or SFML::Image'
      end
    end
  end
end
