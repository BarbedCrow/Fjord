workspace "Fjord"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Retail"
	}

outputdir = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"
IncludeDir = {}
IncludeDir["spdlog"] = "Engine/vendor/spdlog/include"
IncludeDir["GLFW"] = "Engine/vendor/glfw/include"

include "Engine/vendor/glfw"

project "Engine"
	location "Engine"

	language "C++"
	cppdialect "C++17"

	kind "StaticLib"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
	objdir ("bin_int/" .. outputdir .. "/%{prj.name}")

	pchheader "fjordpch.h"
	pchsource "Engine/src/fjordpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
	}

	links
	{
		"GLFW",
	}

	filter "system:windows"
		staticruntime "on"
		systemversion "latest"

		defines
		{
			"FJORD_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines 
		{
			"FJORD_ENABLE_ASSERTS",
			"FJORD_DEBUG"
		}
		
		symbols "on"

	filter "configurations:Release"
		defines "FJORD_RELEASE"
		optimize "on"

	filter "configurations:Retail"
		defines "FJORD_RETAIL"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
	objdir ("bin_int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Engine/src",
		"%{IncludeDir.spdlog}"
	}

	links
	{
		"Engine"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines 
		{
			"FJORD_ENABLE_ASSERTS",
			"FJORD_DEBUG"
		}
		symbols "on"

	filter "configurations:Release"
		defines "FJORD_RELEASE"
		optimize "on"

	filter "configurations:Retail"
		defines "FJORD_RETAIL"
		optimize "on"