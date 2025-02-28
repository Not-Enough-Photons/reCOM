workspace "reCOM"
    configurations { "Debug", "Release" }
    platforms { "x86", "x86_64", "PS2" }
	defaultplatform "x86"

project "fts"
    kind "ConsoleApp"
    language "C++"

	flags { "MultiProcessorCompile" }

    includedirs {
		"src",
		"vendor"
	}
	
    libdirs { "lib" }
	
	links { "opengl32.lib", "SDL3.lib", "SDL3_image.lib", "SDL3_ttf.lib", "glew32.lib" }

    files {
        "src/Apps/FTS/**.cpp",
		"src/Apps/FTS/**.h",
        "src/gamez/**.cpp",
		"src/gamez/**.h",
        "vendor/**.cpp",
		"vendor/**.h",
        "data/**.rdr",
        "data/**.zrdr"
    }

	removefiles {
		"vendor/glm/glm.cppm"
	}

    filter { "configurations:Debug" }
        defines { "DEBUG", "NOGAME" }
        symbols "On"
		targetdir "output/debug"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"
		targetdir "output/release"

    filter { "platforms:x86" }
        system "Windows"
        architecture "x86"
		targetname ("fts32")

    filter { "platforms:x86_64" }
        system "Windows"
        architecture "x86_64"
		targetname ("fts64")

    filter { "platforms:PS2" }
        system "bsd"
        architecture "mips"
		targetname ("SCUS-972")
		targetextension (".05")
