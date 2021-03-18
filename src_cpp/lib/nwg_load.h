#ifndef NWG_LOAD_H
#define NWG_LOAD_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
namespace NW
{
	// --getters
	extern ptr gfx_get_proc(cstr proc_name);
	extern library_handle gfx_get_lib();
	// --predicates
	// --==<core_methods>==--
	extern bit gfx_init_lib();
	extern bit gfx_open_lib();
	extern bit gfx_close_lib();
	extern bit gfx_load_lib();
	// --==</core_methods>==--
}
#endif	// NW_GAPI
#endif	// NWG_LOAD_H