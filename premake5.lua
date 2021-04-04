--==<graphics_library_project>==--
project("nw_gfx")
	kind("staticlib")
	staticruntime("on")
	language("c++")
	cppdialect("c++17")
	targetdir(dir_out_res)
	objdir(dir_out_int)
	pchheader("nw_gfx_pch.hpp")
	pchsource("src_cpp/nw_gfx_pch.cpp")
	files{ "%{dir_cpp.own}**.c**", "%{dir_cpp.own}**.h**" }
	includedirs{ "%{dir_cpp.own}", "%{dir_cpp.ext}", "%{dir_cpp.nw_lib}" }
	libdirs{ "%{dir_lib.nw_lib}" }
	links{ "nw_lib" }
--==</graphics_library_project>==--