assert 'SFML::Image#initialize' do
  img = SFML::Image.new
end

assert 'SFML::Image#create' do
  img = SFML::Image.new
  img.create 32, 32
  img.size
end
