#include "nw_gfx_pch.hpp"
#include "nw_gfx_stt_draw.h"
#if (defined NW_GAPI)
#include "core/nw_gfx_engine.h"
#include "lib/nw_gfx_load_core.h"
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	gfx_stt_draw::gfx_stt_draw(gfx_engine& graphics) :
		a_gfx_stt(graphics)
	{
	}
	gfx_stt_draw::~gfx_stt_draw() { }
	// --setters
	// --==<core_methods>==--
	void gfx_stt_draw::on_draw()
	{
		if (!m_is_enabled) { return; }
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_D3D)
namespace NW
{
	gfx_stt_draw::gfx_stt_draw(gfx_engine& graphics) :
		a_gfx_stt(graphics)
	{
	}
	gfx_stt_draw::~gfx_stt_draw() { }
	// --setters
	// --==<core_methods>==--
	void gfx_stt_draw::on_draw()
	{
		if (!m_is_enabled) { return; }
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI