workspace "RPGClone"
    configurations {"Debug", "Release"}
    startproject "RPGClone"    

project "RPGClone"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir("build/bin/%{cfg.system}/%{cfg.build}")
    objdir("build/intermediate/%{cfg.system}/%{cfg.build}")

    files
	{
		"src/**.h",
		"src/**.cpp"
	}

    includedirs
	{        
		"external/json/include/",
        "external/olcPack/include/",
        "external/boost/"
	}

    libdirs
    {
        "external/boost/libs"
    }

    filter "system:windows"
    systemversion "latest"

    filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		runtime "Release"
		optimize "on"