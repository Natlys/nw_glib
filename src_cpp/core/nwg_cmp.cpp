#include <nwg_pch.hpp>
#include "nwg_cmp.h"
#if (defined NW_GAPI)
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	a_gfx_cmp::a_gfx_cmp(gfx_engine& graphics) :
		m_gfx(&graphics)
	{
	}
	a_gfx_cmp::~a_gfx_cmp() { }
	// --setters
	// --core_methods
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	a_gfx_cmp::a_gfx_cmp(gfx_engine& graphics) :
		m_gfx(&graphics)
	{
	}
	a_gfx_cmp::~a_gfx_cmp() { }
	// --setters
	// --core_methods
}
#endif
#endif	// NW_GAPI