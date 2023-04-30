
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
	target.depends "Language/C++17"
	
	target.provides "Library/Time" do
		source_root = target.package.path + 'source'
		
		library_path = build static_library: "Time", source_files: source_root.glob('Time/**/*.cpp')
		
		append linkflags library_path
		append header_search_paths source_root
	end
end

define_target "time-tests" do |target|
	target.depends "Library/UnitTest"
	target.depends "Library/Time"
	
	target.depends "Language/C++17"
	target.depends 'Build/Compile/Commands'
	
	target.provides "Test/Time" do |*arguments|
		test_root = target.package.path + 'test'
		
		run source_files: test_root.glob('Time/**/*.cpp'), arguments: arguments
		
		compile_commands destination_path: (test_root + "compile_commands.json")
	end
end

# Configurations

define_configuration "development" do |configuration|
	configuration[:source] = "https://github.com/kurocha/"
	
	# Provides all the build related infrastructure:
	configuration.require "platforms"
	configuration.require "build-files"
	
	# Provides unit testing infrastructure and generators:
	configuration.require "unit-test"
	
	# Provides some useful C++ generators:
	configuration.require "generate-project"
	configuration.require "generate-cpp-class"
	
	configuration.require "build-compile-commands"
end
