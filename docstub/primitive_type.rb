module SFML
  # Types of primitives that a sf::VertexArray can render
  #
  # Points and lines have no area, therefore their thickness
  # will always be 1 pixel, regardless the current transform
  # and view.
  module PrimitiveType
    # @return [Integer]
    Points = 0
    # @return [Integer]
    Lines = 1
    # @return [Integer]
    LinesStrip = 2
    # @return [Integer]
    Triangles = 3
    # @return [Integer]
    TrianglesStrip = 4
    # @return [Integer]
    TrianglesFan = 5
    # @return [Integer]
    Quads = 6
  end
end
