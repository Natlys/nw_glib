#include <nwg_pch.hpp>
#include "nwg_load.h"
#include "nwg_load_buf.h"
#include "nwg_load_fmbuf.h"
#include "nwg_load_layt.h"
#include "nwg_load_smp.h"
#include "nwg_load_txr.h"
#include "nwg_load_shd.h"
#include "nwg_load_mtl.h"
#if (defined NW_GAPI)
namespace NW
{
	static library_handle s_gfx_lib= NULL;
}
#if (NW_GAPI & NW_GAPI_OGL)
#include <lib/nwg_load_wgl.h>
namespace NW
{
	struct ogl_version
	{
		si32 major = 0;
		si32 minor = 0;
		// --predicates
		inline bit is_supported(si32 major_ver, si32 minor_ver) {
			if (major_ver < 3) { return false; }
			if (major == minor_ver) { return minor >= minor_ver; }
			return major >= major_ver;
		}
	};

	static ogl_version s_version{ 0 };
}
namespace NW
{
	// --getters
	ptr gfx_get_proc(cstr name) {
		ptr resource = wglGetProcAddress(name);
		return resource == NULL ? ::GetProcAddress(s_gfx_lib, name) : resource;
	}
	library_handle gfx_get_lib() { return s_gfx_lib; }
	// --==<core_methods>==--
	bit gfx_init_lib() {
		if (gfx_open_lib() == FALSE) { return FALSE; }
		if (gfx_load_lib() == FALSE) { return FALSE; }
		if (gfx_close_lib() == FALSE) { return FALSE; }

		if (glGetIntegerv == NULL) { return FALSE; }
		glGetIntegerv(GL_MAJOR_VERSION, &s_version.major);
		glGetIntegerv(GL_MINOR_VERSION, &s_version.minor);
		if (s_version.major < 3) { return FALSE; }

		return TRUE;
	}
	bit gfx_open_lib()
	{
		if (s_gfx_lib != NULL) { return FALSE; }
		s_gfx_lib = ::LoadLibraryA("opengl32.dll");
		if (gfx_load_wgl() == FALSE) { return FALSE; }

		return TRUE;
	}
	bit gfx_close_lib()
	{
		if (s_gfx_lib == NULL) { return FALSE; }
		::FreeLibrary(s_gfx_lib); s_gfx_lib = NULL;
		return TRUE;
	}
	bit gfx_load_lib()
	{
		if (gfx_load_core() == FALSE) { return FALSE; }
		if (gfx_load_buf() == FALSE) { return FALSE; }
		if (gfx_load_fmbuf() == FALSE) { return FALSE; }
		if (gfx_load_layt() == FALSE) { return FALSE; }
		if (gfx_load_smp() == FALSE) { return FALSE; }
		if (gfx_load_txr() == FALSE) { return FALSE; }
		if (gfx_load_shd() == FALSE) { return FALSE; }
		if (gfx_load_mtl() == FALSE) { return FALSE; }

		return TRUE;
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	// --getters
	ptr gfx_get_proc(cstr name) {
		return ::GetProcAddress(s_gfx_lib, name);
	}
	library_handle gfx_get_lib() { return s_gfx_lib; }
	// --==<core_methods>==--
	bit gfx_init_lib() {
		if (gfx_open_lib() == FALSE) { return FALSE; }
		if (gfx_load_lib() == FALSE) { return FALSE; }
		if (gfx_close_lib() == FALSE) { return FALSE; }

		return TRUE;
	}
	bit gfx_open_lib()
	{
		if (s_gfx_lib != NULL) { return FALSE; }
		s_gfx_lib = ::LoadLibraryA("d3d11.dll");
		return TRUE;
	}
	bit gfx_close_lib()
	{
		if (s_gfx_lib == NULL) { return FALSE; }
		::FreeLibrary(s_gfx_lib); s_gfx_lib = NULL;
		return TRUE;
	}
	bit gfx_load_lib()
	{
		if (gfx_load_core() == FALSE) { return FALSE; }

		return TRUE;
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI