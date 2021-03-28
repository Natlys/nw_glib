#include "nwgfx_pch.hpp"
#include "nwgfx_cmp.h"
#if (defined NW_GAPI)
namespace NWGFX
{
	a_gfx_cmp::a_gfx_cmp(gfx_engine& graphics) :
		a_gfx_rsc(graphics)
	{
	}
	a_gfx_cmp::~a_gfx_cmp() { }
	// --core_methods
	void a_gfx_cmp::on_draw()
	{
	}
}
#endif	// NW_GAPI