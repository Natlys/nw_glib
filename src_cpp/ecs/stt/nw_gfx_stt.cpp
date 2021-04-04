#include "nw_gfx_pch.hpp"
#include "nw_gfx_stt.h"
#if (defined NW_GAPI)
#include "core/nw_gfx_engine.h"
#include "lib/nw_gfx_load_core.h"
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
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
#if (NW_GAPI & NW_GAPI_D3D)
namespace NW
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