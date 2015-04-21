assert 'SFML::RectangleShape#initialize' do
  rs = SFML::RectangleShape.new
  rs.set_size(SFML::Vector2f.new(32, 64))
  rs2 = SFML::RectangleShape.new(SFML::Vector2f.new(32, 64))

  assert_equal SFML::Vector2f.new(32, 64), rs.get_size
  assert_equal SFML::Vector2f.new(32, 64), rs2.get_size
end
