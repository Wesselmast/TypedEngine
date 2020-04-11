workspace "TypedEngine"
	architecture "x86_64"
	startproject "TypedEditor"

	configurations {
		"Debug",
		"Release"	
	}

	flags {
		"MultiProcessorCompile"
	}

			-- Debug / Release Operating system   x64
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["glad"]      = "TypedEngine/external/glad/include" 
IncludeDir["glfw"]      = "TypedEngine/external/glfw/include" 
IncludeDir["glm"]       = "TypedEngine/external/glm"
IncludeDir["lua"]       = "TypedEngine/external/lua/include" 
IncludeDir["stb_image"] = "TypedEngine/external/stb_image" 

group "Dependencies"
	include "TypedEngine/external/glfw"
	include "TypedEngine/external/glad"
	include "TypedEngine/external/lua"

group ""

project "TypedEngine"
	location "TypedEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.cpp",
		"%{prj.location}/external/stb_image/**.h",
		"%{prj.location}/external/stb_image/**.cpp",
		"%{prj.location}/external/glm/glm/**.hpp",
		"%{prj.location}/external/glm/glm/**.inl"
	}

	includedirs {
		"%{prj.location}/src",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.lua}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links {
		"glfw",
		"glad",
		"lua",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"



project "TypedEditor"
	location "TypedEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.cpp"
	}

	includedirs {
		"TypedEngine/src",
		"TypedEngine/external",
		"%{IncludeDir.glm}"
	}

	links {
		"TypedEngine"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"