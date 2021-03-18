#include <nwg_pch.hpp>
#include "nwg_shd_rsc.h"
#if (defined NW_GAPI)
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	a_shd_rsc::a_shd_rsc(gfx_engine& graphics) :
		a_gfx_cmp(graphics)
	{
	}
	a_shd_rsc::~a_shd_rsc() { }
	// --setters
	// --==<core_methods>==--
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	a_shd_rsc::a_shd_rsc(gfx_engine& graphics) :
		a_gfx_cmp(graphics)
	{
	}
	a_shd_rsc::~a_shd_rsc() { }
	// --setters
	// --==<core_methods>==--
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI