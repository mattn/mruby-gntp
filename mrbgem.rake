MRuby::Gem::Specification.new('mruby-gntp') do |spec|
  spec.license = 'MIT'
  spec.authors = 'mattn'

  spec.cflags = '-DGROWL_STATIC'
  if ENV['OS'] == 'Windows_NT'
    spec.mruby_libs = '-lws2_32'
  end
end
