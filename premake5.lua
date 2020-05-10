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
IncludeDir["freetype"]  = "TypedEngine/external/freetype/include" 
IncludeDir["glad"]      = "TypedEngine/external/glad/include" 
IncludeDir["glfw"]      = "TypedEngine/external/glfw/include" 
IncludeDir["glm"]       = "TypedEngine/external/glm"
IncludeDir["lua"]       = "TypedEngine/external/lua" 
IncludeDir["stb_image"] = "TypedEngine/external/stb_image" 

group "Dependencies"
	include "TypedEngine/external/glfw"
	include "TypedEngine/external/glad"
	include "TypedEngine/external/freetype"
	include "TypedEngine/external/lua"

group ""

project "TypedEngine"
	toolset "gcc"
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
		"%{prj.location}/external/glm/glm/**.inl",
		"%{prj.location}/src/**.c",
		"%{prj.location}/src/**.cxx"
	}

	includedirs {
		"%{prj.location}/src",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.freetype}",
		"%{IncludeDir.lua}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links {
		"TELua",
		"glad",
		"freetype",
		"lua",
		"glfw",
	 	"opengl32",
		"gdi32"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		defines {
			"TE_DEBUG"
		}

	filter "configurations:Release"
		runtime "Release"
		optimize "on"



--------------------------------------------------------------- LUA UTILITY --------------------------------------------------------------

project "TELua"
	location "TypedEngine/src/Scripting"
	kind "Utility"

	prebuildcommands {
		"swig -c++ -lua core/TEcore.i"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"



--------------------------------------------------------------DLL EXPORT PROJECTS----------------------------------------------------------------------



project "TEcore"  -- TypedEngine Core Library for Lua
	toolset "gcc"
	location "TypedEngine/src/Scripting"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir("%{prj.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir("%{prj.location}/int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.location}/**.h",
		"%{prj.location}/**.c",
		"%{prj.location}/**.cxx",	
	}

	includedirs {
		"TypedEngine/src",
		"%{IncludeDir.lua}",
		"%{IncludeDir.glm}"
	}

	links {
		"TypedEngine",
		"glad",
		"freetype",
		"lua",
		"glfw",
		"opengl32",
		"gdi32"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"


-------------------------------------------------------------TYPEDEDITOR----------------------------------------------------------------------------



project "TypedEditor"
	toolset "gcc"
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
		"%{IncludeDir.glm}"
	}

	links {
		"TypedEngine",
		"glad",
		"freetype",
		"lua",
		"glfw",
		"opengl32",
		"gdi32"
	}

	postbuildcommands {
		'{COPY} "../TypedEditor/res" "%{cfg.targetdir}/res"',
		'{COPY} "../TypedEditor/gamefiles" "%{cfg.targetdir}/gamefiles"',
		'{COPY} "../TypedEngine/src/Scripting/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" "%{cfg.targetdir}/lib"',
		'@echo off && echo. && echo. && echo ">>>>>>>>>>>>>>>  SUCCESS!  <<<<<<<<<<<<<<<" && echo.'
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
