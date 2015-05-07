module SFML
  # Window that can serve as a target for 2D drawing
  class RenderWindow < Window
    include RenderTarget
  end
end
