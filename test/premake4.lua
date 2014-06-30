project "test"
	kind "ConsoleApp"
	language "C++"
	files { "src/**" }
	links { "teabag", "sfml-system", "sfml-window", "sfml-graphics" }
	libdirs { ".." }
	includedirs { "." }
	objdir "build/test/obj"
	buildoptions { "-std=c++1y" }

	configuration "debug"
		flags { "Symbols", "ExtraWarnings" }

	configuration "release"
		flags { "Optimize" }

