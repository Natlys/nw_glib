#ifndef GLIB_CORE_HPP
#define GLIB_CORE_HPP

// --==<linking>==--
#if defined GLIB_LINK_DYNAMIC
#ifdef GLIB_BUILD_DLL
#define GLIB_API __declspec(dllexport)
#elif defined GLIB_BUILD_EXE
#define GLIB_API __declspec(dllimport)
#endif
#else
#define GLIB_API
#endif
// --==</linking>==--

// --==<configurations>==--
// --graphics_api_choice
#define GLIB_GAPI_OGL		1 << 1
#define GLIB_GAPI GLIB_GAPI_OGL
// --==</configurations>==--

// --debug_macro
#if (defined GLIB_DEBUG)
#if (GLIB_GAPI & GLIB_GAPI_OGL)
// --opengl_debug
namespace NW
{
	extern inline void OGL_ClearErr();
	extern inline bool OGL_ErrLog(const char* funcName, const char* file, int line);
}
#define OGL_CALL(function) OGL_ClearErr();\
		function;\
		NWL_ASSERT(OGL_ErrLog(#function, NW_FNAME_APATH((std::string)__FILE__), __LINE__), "GL_ERROR: ")
#endif // NW_GRAPHICS
#else
#define GLIB_LOG(loc, what);
#define GLIB_LOG_LC(loc, what);
#define GLIB_ASSERT(expr, comment);
#define GLIB_ERR(function);

#define OGL_CALL(function);
#endif // GLIB_DEBUG
// --==</support_macroses>==--

// --==<pragmas>==--
#pragma warning(disable : 4005)
#pragma warning(disable : 4081)
#pragma warning(disable : 4099)
#pragma warning(disable : 4102)
#pragma warning(disable : 4244)
#pragma warning(disable : 4267)
#pragma warning(disable : 4552)
#pragma warning(disable : 4996)
// --==</pragmas>==--

#endif	// GLIB_CORE_HPP

#include <glib_pch.hpp>
#include <glib_def.hpp>

/*
* The project created in 16.01.2021
* Graphics library as a tool for game engines and applications
*/