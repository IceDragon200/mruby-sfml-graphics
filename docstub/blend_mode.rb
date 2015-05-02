module SFML
  class BlendMode
    module Factor
      # @return [Integer]
      Zero = 0
      # @return [Integer]
      One = 1
      # @return [Integer]
      SrcColor = 2
      # @return [Integer]
      OneMinusSrcColor = 3
      # @return [Integer]
      DstColor = 4
      # @return [Integer]
      OneMinusDstColor = 5
      # @return [Integer]
      SrcAlpha = 6
      # @return [Integer]
      OneMinusSrcAlpha = 7
      # @return [Integer]
      DstAlpha = 8
      # @return [Integer]
      OneMinusDstAlpha = 9
    end

    module Equation
      # @return [Integer]
      Add = 0
      # @return [Integer]
      Subtract = 1
    end

    # @!attribute color_src_factor
    #   @return [Factor]
    attr_accessor :color_src_factor
    # @!attribute color_dst_factor
    #   @return [Factor]
    attr_accessor :color_dst_factor
    # @!attribute color_equation
    #   @return [Equation]
    attr_accessor :color_equation
    # @!attribute alpha_src_factor
    #   @return [Factor]
    attr_accessor :alpha_src_factor
    # @!attribute alpha_dst_factor
    #   @return [Factor]
    attr_accessor :alpha_dst_factor
    # @!attribute alpha_equation
    #   @return [Equation]
    attr_accessor :alpha_equation

    # @overload initialize
    # @overload initialize(source_factor, destination_factor, blend_equation)
    #   @param [Factor] source_factor
    #   @param [Factor] destination_factor
    #   @param [Equation] blend_equation
    # @overload initialize(color_source_factor, color_destination_factor, color_blend_equation,
    #                      alpha_source_factor, alpha_destination_factor, alpha_blend_equation)
    #   @param [Factor] color_source_factor
    #   @param [Factor] color_destination_factor
    #   @param [Equation] color_blend_equation
    #   @param [Factor] alpha_source_factor
    #   @param [Factor] alpha_destination_factor
    #   @param [Equation] alpha_blend_equation
    def initialize(*args)
    end

    # @param [BlendMode] other
    # @return [Boolean]
    def ==(other)
    end
  end
end
