assert 'SFML::FloatRect' do
  rect = SFML::FloatRect.new(4.5, 8.3, 16.1, 32.8)
  # because floats are absolute BS, I'm gonna round this sh_t.
  assert_float 4.5, rect.left.round(1)
  assert_float 8.3, rect.top.round(1)
  assert_float 16.1, rect.width.round(1)
  assert_float 32.8, rect.height.round(1)
end
