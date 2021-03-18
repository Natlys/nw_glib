#include <nwg_pch.hpp>
#include "nwg_stt_cull.h"
#if (defined NW_GAPI)
#include <core/nwg_engine.h>
#include <lib/nwg_load_core.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	stt_cull::stt_cull(gfx_engine& graphics) :
		a_gfx_stt(graphics)
	{
	}
	stt_cull::~stt_cull() { }
	// --setters
	// --==<core_methods>==--
	void stt_cull::on_draw()
	{
		if (!m_is_enabled) { return; }
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	stt_cull::stt_cull(gfx_engine& graphics) :
		a_gfx_stt(graphics)
	{
	}
	stt_cull::~stt_cull() { }
	// --setters
	// --==<core_methods>==--
	void stt_cull::on_draw()
	{
		if (!m_is_enabled) { return; }
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI