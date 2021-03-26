#include "nwg_pch.hpp"
#include "nwg_pass.h"
#if (defined NW_GAPI)
namespace NW
{
	gfx_pass::gfx_pass(gfx_engine& graphics) :
		t_cmp(), a_gfx_cmp(graphics)
	{
		//
	}
	gfx_pass::~gfx_pass() { }
	// --setters
	// --==<core_methods>==--
	void gfx_pass::on_draw()
	{
	}
	// --==</core_methods>==--
}
#endif	// NW_GAPI