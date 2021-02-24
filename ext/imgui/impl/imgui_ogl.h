#ifndef IMGUI_OGL_H
#define IMGUI_OGL_H

// About Desktop OpenGL function loaders:
//  Modern Desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.

// About GLSL version:
//  The 'glsl_version' initialization parameter should be NULL (default) or a "#version XXX" string.
//  On computer platform the GLSL version default to "#version 130". On OpenGL ES 3 platform it defaults to "#version 300 es"
//  Only override if your GL version doesn't handle this GLSL version. See GLSL version table at the top of imgui_impl_opengl3.cpp.

#include "../imgui_core.hpp"      // IMGUI_IMPL_API

namespace GUI
{
	// backend api
	IMGUI_IMPL_API bool     OGLInit(const char* glsl_version = NULL);
	IMGUI_IMPL_API void     OGLShutdown();
	IMGUI_IMPL_API void     OGLNewFrame();
	IMGUI_IMPL_API void     OGLRenderDrawData(ImDrawData* draw_data);
}

#endif IMGUI_OGL_H