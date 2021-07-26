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

project "Engine"
	location "Engine"

	language "C++"
	cppdialect "C++17"

	kind "StaticLib"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
	objdir ("bin_int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
	}

	filter "system:windows"
		staticruntime "on"
		systemversion "latest"

		defines
		{
			"FJORD_PLATFORM_WINDOWS",
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
		"Engine/src"
	}

	links
	{
		"Engine"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"FJORD_PLATFORM_WINDOWS"
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