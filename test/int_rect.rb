assert 'SFML::IntRect' do
  rect = SFML::IntRect.new(4, 8, 16, 32)
  assert_equal 4, rect.left
  assert_equal 8, rect.top
  assert_equal 16, rect.width
  assert_equal 32, rect.height
end
