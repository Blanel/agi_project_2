solution "AGI12 Project2"
	configurations { "Debug", "Release" }
	location "build"
	targetdir "bin"

	project "RenderClient"
		kind "ConsoleApp"
		language "C++"
		files { "client/source/**.h", "client/source/**.cpp" }

		if (os.is("windows")) then

			includedirs { "D:/Applications/mingw64/mingw64/include", 
						  "client/source",
						  "client/externals/mingw64/include",
						  "client/externals/mingw64/include/SDL"
						}
		end

		configuration "Debug"
			defines { "DEBUG" }
			flags {"Symbols"}

		configuration "Release"
			defines {"NDEBUG"}	
			flags {"Optimize"}

		configuration "gmake"
			links{ "glew32", "opengl32", "mingw32", "SDL2main", "SDL2", "SDL2_image" , "m", "pugixml", "boost_system-mgw47-s-1_52","boost_thread-mgw47-mt-1_52", "ws2_32" }
			libdirs{"client/externals/mingw64/lib"}
			buildoptions { "-std=c++11", "-mwindows", "-mno-ms-bitfields" }
