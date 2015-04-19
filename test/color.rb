assert 'SFML::Color#initialize' do
  c1 = SFML::Color.new
  c2 = SFML::Color.new(198, 178, 97)
  c3 = SFML::Color.new(198, 178, 97, 196)

  # sane default
  assert_equal 0, c1.r
  assert_equal 0, c1.g
  assert_equal 0, c1.b
  assert_equal 255, c1.a

  #
  assert_equal 198, c2.r
  assert_equal 178, c2.g
  assert_equal 97,  c2.b
  assert_equal 255, c2.a

  #
  assert_equal 198, c3.r
  assert_equal 178, c3.g
  assert_equal 97,  c3.b
  assert_equal 196, c3.a
end

assert 'SFML::Color#initialize_copy' do
  c1 = SFML::Color.new(198, 178, 97, 196)
  c2 = c1.dup

  assert_equal c1, c2
end
