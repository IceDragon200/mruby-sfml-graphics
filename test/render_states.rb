assert 'SFML::RenderStates#initialize' do
  a0 = SFML::RenderStates.new
  a1_blend_mode = SFML::RenderStates.new(SFML::BlendMode.new)
  a1_transform = SFML::RenderStates.new(SFML::Transform.new)
  a1_texture = SFML::RenderStates.new(SFML::Texture.new)
  a1_shader = SFML::RenderStates.new(SFML::Shader.new)
  a4 = SFML::RenderStates.new(SFML::BlendMode.new, SFML::Transform.new,
                              SFML::Texture.new, SFML::Shader.new)
end
