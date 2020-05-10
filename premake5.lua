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
	location "TypedEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("int/" .. outputdir .. "/%{prj.name}")

	buildoptions {
		"-Winvalid-pch"
	}

	pchheader "PCH.h"
	pchsource "TypedEngine/src/PCH.cpp"

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



----------------------------------------------------------------LUA STATIC LIBRARY--------------------------------------------------------------

project "TELua"
	location "TypedEngine/src/Scripting"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("%{prj.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir("%{prj.location}/int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.location}/**.h",
		"%{prj.location}/**.c"
	}

	includedirs {
		"%{IncludeDir.lua}",
		"%{IncludeDir.glm}"
	}

	links {
		"lua"
	}

	prebuildcommands {
		"swig -c++ -lua core/TEcore.i"         --  SWIG SHOULD RECOMPILE ONLY WHEN FILE DIRTY AND ONLY ONCE:  --
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
	location "TypedEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("int/" .. outputdir .. "/%{prj.name}")

	pchheader "PCH.h"
	pchsource "TypedEngine/src/PCH.cpp"

	files {
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.cpp",
		"TypedEngine/src/Scripting/core/TEcore_wrap.cxx"        -- Ugliest thing I've ever seen. Should be fixed!!!!!
	}

	includedirs {
		"TypedEngine/src",
		"%{IncludeDir.lua}",	
		"%{IncludeDir.glm}"
	}

	links {
		"TypedEngine",
		"TELua",
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
