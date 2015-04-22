module SFML
  class RenderStates
    # @!attribute blend_mode
    #   @return [BlendMode]
    attr_accessor :blend_mode
    # @!attribute transform
    #   @return [Transform]
    attr_accessor :transform
    # @!attribute texture
    #   @return [Texture]
    attr_accessor :texture
    # @!attribute shader
    #   @return [Shader]
    attr_accessor :shader

    # @overload initialize
    # @overload initialize(blend_mode)
    #   @param [BlendMode] blend_mode
    # @overload initialize(transform)
    #   @param [Transform] transform
    # @overload initialize(texture)
    #   @param [Texture] texture
    # @overload initialize(shader)
    #   @param [Shader] shader
    # @overload initialize(blend_mode, transform, texture, shader)
    #   @param [BlendMode] blend_mode
    #   @param [Transform] transform
    #   @param [Texture] texture
    #   @param [Shader] shader
    def initialize(*args)
    end
  end
end
