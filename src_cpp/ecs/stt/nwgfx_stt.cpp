#include "nwgfx_pch.hpp"
#include "nwgfx_stt.h"
#if (defined NW_GAPI)
#include <core/nwgfx_engine.h>
#include <lib/nwgfx_load_core.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NWGFX
{
	a_gfx_stt::a_gfx_stt(gfx_engine& graphics) :
		t_cmp(), a_gfx_cmp(graphics),
		m_is_enabled(true)
	{
	}
	a_gfx_stt::~a_gfx_stt() { }
	// --setters
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NWGFX
{
	a_gfx_stt::a_gfx_stt(gfx_engine& graphics) :
		t_cmp(), a_gfx_cmp(graphics),
		m_is_enabled(true)
	{
	}
	a_gfx_stt::~a_gfx_stt() { }
	// --setters
}
#endif
#endif	// NW_GAPI