#ifndef NWGFX_LOAD_WINDOW_API_H
#define NWGFX_LOAD_WINDOW_API_H
#include "nwgfx_core.hpp"
#if (defined NW_GAPI)
namespace NWGFX
{
	extern v1b gfx_load_wapi();
	extern v1b gfx_ext_load_wapi();
}
#if (NW_GAPI & NW_GAPI_OGL)
namespace NWGFX
{
	// context
	typedef context_handle (__stdcall* pfn_gfx_new_context)    (device_handle device);
	typedef v1s           (__stdcall* pfn_gfx_del_context)    (context_handle context);
	typedef context_handle (__stdcall* pfn_gfx_get_context)    (void);
	typedef v1s           (__stdcall* pfn_gfx_set_context)    (device_handle device, context_handle context);
	// device
	typedef device_handle  (__stdcall* pfn_gfx_get_device)     (void);
	// other
	typedef ptr            (__stdcall* pfn_gfx_get_proc)       (cstr name);
	// extensions
	typedef cstr           (__stdcall* pfn_gfx_ext_get_str)    (void);
	typedef v1s           (__stdcall* pfn_gfx_ext_get_vsync)  (void);
	typedef void           (__stdcall* pfn_gfx_ext_set_vsync)  (v1s swap_interval);
}
namespace NWGFX
{
	// context
	extern pfn_gfx_new_context gfx_new_context;
	extern pfn_gfx_del_context gfx_del_context;
	extern pfn_gfx_get_context gfx_get_context;
	extern pfn_gfx_set_context gfx_set_context;
	// device
	extern pfn_gfx_get_device  gfx_get_device;
	// other
	extern pfn_gfx_get_proc    gfx_get_proc_address;
	// extensions
	extern pfn_gfx_ext_get_str   gfx_ext_get_str;
	extern pfn_gfx_ext_get_vsync gfx_ext_get_vsync;
	extern pfn_gfx_ext_set_vsync gfx_ext_set_vsync;
}
// context
#	define wglCreateContext       gfx_new_context
#	define wglDeleteContext       gfx_del_context
#	define wglGetCurrentContext   gfx_get_context
#	define wglMakeContextCurrent  gfx_set_context
// device
#	define wglGetCurrentDC        gfx_get_device
// other
#	define wglGetProcAddress      gfx_get_proc_address
// extensions
#	define wglGetExtensionsStringEXT gfx_ext_get_str
#	define wglSwapIntervalEXT        gfx_ext_set_vsync
#	define wglGetSwapIntervalEXT     gfx_ext_get_vsync
#endif
#endif	// NW_GAPI
#endif	// NWGFX_LOAD_WINDOW_API_H