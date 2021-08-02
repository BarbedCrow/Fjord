workspace "Fjord"
	architecture "x64"
	startproject "Editor"

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
IncludeDir["glad"] = "Engine/vendor/glad/include"
IncludeDir["imgui"] = "Engine/vendor/imgui"
IncludeDir["glm"] = "Engine/vendor/glm"
IncludeDir["stb"] = "Engine/vendor/stb"
IncludeDir["entt"] = "Engine/vendor/entt/include"

include "Engine/vendor/glfw"
include "Engine/vendor/glad"
include "Engine/vendor/imgui"

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
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/stb/**.h",
		"%{prj.name}/vendor/stb/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.entt}",
	}

	links
	{
		"GLFW",
		"glad",
		"imgui",
		"opengl32.lib"
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
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/assets/**.glsl",
		"%{prj.name}/assets/**.png",
	}

	includedirs
	{
		"Engine/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
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

project "Editor"
	location "Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
	objdir ("bin_int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/assets/**.glsl",
		"%{prj.name}/assets/**.png",
	}

	includedirs
	{
		"Engine/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.imgui}",
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