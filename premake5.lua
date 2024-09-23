workspace "ZIEngine"
    configurations { "Debug", "Release" }

project "engine"
    kind "ConsoleApp"
    language "C++"
    files { "src/**.h", "**.cpp" }

    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"