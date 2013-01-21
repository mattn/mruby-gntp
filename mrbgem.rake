MRuby::Gem::Specification.new('mruby-gntp') do |spec|
  spec.license = 'MIT'
  spec.authors = 'mattn'

  spec.cc.flags << '-DGROWL_STATIC'
  if ENV['OS'] == 'Windows_NT'
    spec.linker.libraries << 'ws2_32'
  end
end
