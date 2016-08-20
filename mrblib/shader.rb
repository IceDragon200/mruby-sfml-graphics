module SFML
  class Shader
    # (see #set_uniform)
    # @deprecated use #set_uniform instead
    def set_parameter(*args, &block)
      warn "set_parameter is deprecated, use #set_uniform instead"
      set_uniform(*args, &block)
    end

    # Loads a vertex shader from file
    #
    # @param [String] filename
    # @return [self]
    def load_vert_from_file(filename)
      load_from_file(filename, Type::Vertex)
    end

    # Loads a vertex shader from the given source
    #
    # @param [String] source
    # @return [self]
    def load_vert_from_memory(source)
      load_from_memory(source, Type::Vertex)
    end

    # Loads a fragment shader from file
    #
    # @param [String] filename
    # @return [self]
    def load_frag_from_file(filename)
      load_from_file(filename, Type::Fragment)
    end

    # Loads a fragment shader from the given source
    #
    # @param [String] source
    # @return [self]
    def load_frag_from_memory(source)
      load_from_memory(source, Type::Fragment)
    end
  end
end
