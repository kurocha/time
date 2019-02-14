
#
#  This file is part of the "Teapot" project, and is released under the MIT license.
#

teapot_version "3.0"

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
	target.depends 'Build/Files'
	target.depends 'Build/Clang'
	
	target.depends :platform
	target.depends "Language/C++11", private: true
	
	target.provides "Library/Time" do
		source_root = target.package.path + 'source'
		
		library_path = build prefix: environment.checksum, static_library: "Time", source_files: source_root.glob('Time/**/*.cpp')
		
		append linkflags library_path
		append header_search_paths source_root
	end
end

define_target "time-tests" do |target|
	target.depends "Library/Time"
	
	target.depends "Language/C++14", private: true
	target.depends "Library/UnitTest"
	
	target.provides "Test/Time" do |arguments|
		test_root = target.package.path + 'test'
		
		run prefix: environment.checksum, source_files: test_root.glob('Time/**/*.cpp'), arguments: arguments
	end
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
