MRuby::Gem::Specification.new('mruby-gntp') do |spec|
  spec.license = 'MIT'
  spec.authors = 'mattn'

  spec.cxxflags = '-fpermissive'
  if ENV['OS'] == 'Windows_NT'
    spec.mruby_libs = '-lcryptopp -lboost_system-mgw47-mt-1_50 -lboost_thread-mgw47-mt-1_50 -lws2_32 -lstdc++'
  else
    spec.mruby_libs = '-lcryptopp -lboost_system -lboost_thread -lstdc++'
  end
end
