module SFML
  # Specialized shape representing a circle
  class CircleShape < Shape
    def initialize
    end

    # @param [Float] rad
    def set_radius(rad)
    end

    # @param [Integer] count
    def set_point_count(count)
    end

    alias :radius= :set_radius
    alias :radius :get_radius
    alias :point_count= :set_point_count
  end
end
