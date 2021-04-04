#include "nw_gfx_pch.hpp"
#include "nw_gfx_stt_blend.h"
#if (defined NW_GAPI)
#include "core/nw_gfx_engine.h"
#include "lib/nw_gfx_load_core.h"
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	gfx_stt_blend::gfx_stt_blend(gfx_engine& graphics) :
		a_gfx_stt(graphics)
	{
	}
	gfx_stt_blend::~gfx_stt_blend() { }
	// --==<core_methods>==--
	v1b gfx_stt_blend::remake()
	{
		return true;
	}
	void gfx_stt_blend::on_draw()
	{
		if (!m_is_enabled) { glDisable(GL_BLEND); return; }
		glEnable(GL_BLEND);
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_D3D)
namespace NW
{
	gfx_stt_blend::gfx_stt_blend(gfx_engine& graphics) :
		a_gfx_stt(graphics)
	{
	}
	gfx_stt_blend::~gfx_stt_blend() { }
	// --==<core_methods>==--
	v1b gfx_stt_blend::remake()
	{
		return true;
	}
	void gfx_stt_blend::on_draw()
	{
		if (!m_is_enabled) { return; }
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI