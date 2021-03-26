#include <nwg_pch.hpp>
#include "nwg_stt_blend.h"
#if (defined NW_GAPI)
#include <core/nwg_engine.h>
#include <lib/nwg_load_core.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	gfx_stt_blend::gfx_stt_blend(gfx_engine& graphics) :
		a_gfx_stt(graphics)
	{
	}
	gfx_stt_blend::~gfx_stt_blend() { }
	// --==<core_methods>==--
	bit gfx_stt_blend::remake()
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
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	gfx_stt_blend::gfx_stt_blend(gfx_engine& graphics) :
		a_gfx_stt(graphics)
	{
	}
	gfx_stt_blend::~gfx_stt_blend() { }
	// --==<core_methods>==--
	bit gfx_stt_blend::remake()
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