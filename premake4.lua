solution "Teabag Engine"
	configurations { "debug", "release" }

project "teabag"
	kind "SharedLib"
	language "C++"
	files { "src/**" }
	links { "sfml-system", "sfml-window", "sfml-graphics" }
	objdir "build/obj"
	buildoptions { "-std=c++11" }

	configuration "debug"
		flags { "Symbols", "ExtraWarnings" }

	configuration "release"
		flags { "Optimize" }

project "test"
	kind "ConsoleApp"
	language "C++"
	files { "test/src/**" }
	links { "teabag", "sfml-system", "sfml-window", "sfml-graphics" }
	objdir "build/test/obj"
	buildoptions { "-std=c++11" }
	targetdir "test"

	configuration "debug"
		flags { "Symbols", "ExtraWarnings" }

	configuration "release"
		flags { "Optimize" }
