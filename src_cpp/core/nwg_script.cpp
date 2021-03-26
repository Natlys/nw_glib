#include "nwg_pch.hpp"
#include "nwg_script.h"
#if (defined NW_GAPI)
namespace NW
{
	gfx_script::gfx_script(gfx_engine& graphics) :
		t_cmp(), a_gfx_cmp(graphics)
	{
		//
	}
	gfx_script::~gfx_script() {}
	// --setters
	// --==<core_methods>==--
	void gfx_script::on_draw()
	{
	}
	// --==</core_methods>==--
}
#endif	// NW_GAPI