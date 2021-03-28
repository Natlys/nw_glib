#include "nwgfx_pch.hpp"
#include "nwgfx_rsc.h"
#if (defined NW_GAPI)
namespace NWGFX
{
	a_gfx_rsc::a_gfx_rsc(gfx_engine& graphics) :
		m_gfx(&graphics)
	{
	}
	a_gfx_rsc::~a_gfx_rsc() { }
	// --core_methods
	void a_gfx_rsc::on_draw()
	{
	}
}
#endif	// NW_GAPI