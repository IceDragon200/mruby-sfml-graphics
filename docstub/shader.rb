module SFML
  class Shader
    # Initializes a new invalid shader
    def initialize
    end

    # @overload load_from_file(vertex_filename, fragment_filename)
    #   @param [String] vertex_filename
    #   @param [String] fragment_filename
    # @overload load_from_file(filename, type)
    #   @param [String] filename
    #   @param [Shader::Type] type
    # @return [self]
    def load_from_file(a, b)
    end

    # @overload load_from_file(vertex_source, fragment_source)
    #   @param [String] vertex_source
    #   @param [String] fragment_source
    # @overload load_from_file(source, type)
    #   @param [String] source
    #   @param [Shader::Type] type
    # @return [self]
    def load_from_memory(a, b)
    end

    # @param [String] name  attribute name
    # @overload set_parameter(name, x)
    #   @param [Float] x
    # @overload set_parameter(name, color)
    #   @param [Color] color
    # @overload set_parameter(name, texture)
    #   @param [Texture] texture
    # @overload set_parameter(name, transform)
    #   @param [Transform] transform
    # @overload set_parameter(name, v2)
    #   @param [Vector2] v2
    # @overload set_parameter(name, v3)
    #   @param [Vector3] v3
    # @overload set_parameter(name, x, y)
    #   @param [Float] x
    #   @param [Float] y
    # @overload set_parameter(name, x, y, z)
    #   @param [Float] x
    #   @param [Float] y
    #   @param [Float] z
    # @overload set_parameter(name, x, y, z, w)
    #   @param [Float] x
    #   @param [Float] y
    #   @param [Float] z
    #   @param [Float] w
    # @return [self]
    def set_parameter(name, *args)
    end
  end
end
