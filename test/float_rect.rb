assert 'SFML::FloatRect' do
  rect = SFML::FloatRect.new(4.5, 8.3, 16.1, 32.8)
  assert_float 4.5, rect.left
  assert_float 8.3, rect.top
  assert_float 16.1, rect.width
  assert_float 32.8, rect.height
end
