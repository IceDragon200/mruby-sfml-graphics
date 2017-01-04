MRuby::Gem::Specification.new('mruby-sfml-graphics') do |spec|
  spec.license = 'MIT'
  spec.authors = ['Corey Powell']
  spec.version = '2.4.1.0'
  spec.summary = 'SFML Graphics binding'
  spec.description = 'SFML Graphics binding'
  spec.homepage = 'https://github.com/IceDragon200/mruby-sfml-graphics'

  spec.add_dependency 'mruby-sfml-system', github: 'IceDragon200/mruby-sfml-system'
  spec.add_dependency 'mruby-sfml-window', github: 'IceDragon200/mruby-sfml-window'
end
