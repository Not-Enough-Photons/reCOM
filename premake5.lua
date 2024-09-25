workspace "ZIEngine"
    configurations { "Debug", "Release" }

project "engine"
    kind "ConsoleApp"
    language "C++"
    files { 
        "src/*.cpp",
        "src/*.h",
		"src/ai/**.cpp",
		"src/ai/**.h",
		"src/audio/**.cpp",
		"src/audio/**.h",
		"src/editor/**.cpp",
		"src/editor/**.h",
		"src/entity/**.cpp",
		"src/entity/**.h",
		"src/math/**.cpp",
		"src/math/**.h",
		"src/node/**.cpp",
		"src/node/**.h",
		"src/reader/**.cpp",
		"src/reader/**.h",
		"src/system/**.cpp",
		"src/system/**.h",
		"src/ui/**.cpp",
		"src/ui/**.h",
		"src/zar/**.cpp",
		"src/zar/**.h"
    }

    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"