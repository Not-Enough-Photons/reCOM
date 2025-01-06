workspace "reCOM"
    configurations { "Debug", "Release" }
    platforms { "x86", "x86_64", "PS2" }

project "game"
    kind "ConsoleApp"
    language "C++"

    includedirs {
		"vendor",
		"src"
	}
	
    libdirs { "lib" }

    files { 
        "src/Apps/FTS/**.cpp",
		"src/Apps/FTS/**.h",
        "src/gamez/**.cpp",
		"src/gamez/**.h",
        "vendor/**.cpp",
		"vendor/**.h",
    }
	
	

    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"

    filter { "platforms:x86" }
        system "Windows"
        architecture "x86"

    filter { "platforms:x86_64" }
        system "Windows"
        architecture "x86_64"

    filter { "platforms:PS2" }
        system "bsd"
        architecture "mips"
