
#
#  This file is part of the "Teapot" project, and is released under the MIT license.
#

teapot_version "2.3"

# Project Metadata

define_project "time" do |project|
	project.title = 'Time'
	project.summary = 'Provides time related abstractions.'
	
	project.license = "MIT License"
	project.add_author 'Samuel Williams', email: 'samuel.williams@oriontransfer.co.nz'
	
	project.version = "1.0.0"
end

# Build Targets

define_target 'time-library' do |target|
	source_root = target.package.path + 'source'
	
	target.build do
		build prefix: target.name, static_library: "Time", source_files: source_root.glob('Time/**/*.cpp')
	end
	
	target.depends 'Build/Files'
	target.depends 'Build/Clang'
	
	target.depends :platform
	target.depends "Language/C++11", private: true
	
	target.depends "Build/Files"
	target.depends "Build/Clang"
	
	target.provides "Library/Time" do
		append linkflags [
			->{build_prefix + target.name + 'Time.a'}
		]
		
		append header_search_paths [
			source_root
		]
	end
end

define_target "time-tests" do |target|
	target.build do |*arguments|
		test_root = target.package.path + 'test'
		
		run prefix: target.name, source_files: test_root.glob('Time/**/*.cpp'), arguments: arguments
	end
	
	target.depends "Language/C++14", private: true
	
	target.depends "Library/UnitTest"
	target.depends "Library/Time"
	
	target.provides "Test/Time"
end

# Configurations

define_configuration "test" do |configuration|
	configuration[:source] = "http://github.com/kurocha/"
	
	# Provides all the build related infrastructure:
	configuration.require "platforms"
	configuration.require "build-files"
	
	# Provides unit testing infrastructure and generators:
	configuration.require "unit-test"
	
	# Provides some useful C++ generators:
	configuration.require "generate-project"
	configuration.require "generate-travis"
	configuration.require "generate-cpp-class"
end
