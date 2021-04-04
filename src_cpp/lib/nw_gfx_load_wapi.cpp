#include "nw_gfx_pch.hpp"
#include "nw_gfx_load_wapi.h"
#if (defined NW_GAPI)
#include "nw_gfx_load.h"
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	v1b gfx_load_wapi() {
		library_handle libh = gfx_get_lib();
		if (libh == NULL) { return FALSE; }
		// context
		wglCreateContext       = (pfn_gfx_new_context)(::GetProcAddress(libh, "wglCreateContext"));
		wglDeleteContext       = (pfn_gfx_del_context)(::GetProcAddress(libh, "wglDeleteContext"));
		wglGetCurrentContext   = (pfn_gfx_get_context)(::GetProcAddress(libh, "wglGetCurrentContext"));
		wglMakeContextCurrent  = (pfn_gfx_set_context)(::GetProcAddress(libh, "wglMakeCurrent"));
		// device
		wglGetCurrentDC        = (pfn_gfx_get_device)(::GetProcAddress(libh, "wglGetCurrentDC"));
		// other
		wglGetProcAddress      = (pfn_gfx_get_proc)(::GetProcAddress(libh, "wglGetProcAddress"));

		return TRUE;
	}
	
	v1b gfx_ext_has_support(cstr extension_name) { return strstr(wglGetExtensionsStringEXT(), extension_name) != NULL; }
	
	v1b gfx_ext_load_wapi()
	{
		if (gfx_get_lib() == NULL) { return FALSE; }
		
		wglGetExtensionsStringEXT = (pfn_gfx_ext_get_str)(gfx_get_proc("wglGetExtensionsStringEXT"));
		if (gfx_ext_has_support("WGL_EXT_swap_control")) {
			wglGetSwapIntervalEXT = (pfn_gfx_ext_get_vsync)(gfx_get_proc("wglGetSwapIntervalEXT"));
			wglSwapIntervalEXT = (pfn_gfx_ext_set_vsync)(gfx_get_proc("wglSwapIntervalEXT"));
		}

		return TRUE;
	}
}
namespace NW
{
	// context
	pfn_gfx_new_context  wglCreateContext = NULL;
	pfn_gfx_del_context  wglDeleteContext = NULL;
	pfn_gfx_get_context  wglGetCurrentContext = NULL;
	pfn_gfx_set_context  wglMakeContextCurrent = NULL;
	// device
	pfn_gfx_get_device   wglGetCurrentDC = NULL;
	// other
	pfn_gfx_get_proc     wglGetProcAddress = NULL;
	// extensions
	pfn_gfx_ext_get_str   wglGetExtensionsStringEXT = NULL;
	pfn_gfx_ext_get_vsync wglGetSwapIntervalEXT = NULL;
	pfn_gfx_ext_set_vsync wglSwapIntervalEXT = NULL;
}
#endif
#if (NW_GAPI & NW_GAPI_D3D)
namespace NW
{
	v1b gfx_load_wapi() {
		library_handle libh = gfx_get_lib();
		if (libh == NULL) { return FALSE; }
		
		return TRUE;
	}

	v1b gfx_ext_has_support(cstr extension_name) { return FALSE; }

	v1b gfx_ext_load_wapi()
	{
		if (gfx_get_lib() == NULL) { return FALSE; }

		return TRUE;
	}
}
#endif
#endif	// NW_GAPI