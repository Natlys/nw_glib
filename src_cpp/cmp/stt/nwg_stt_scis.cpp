#include <nwg_pch.hpp>
#include "nwg_stt_scis.h"
#if (defined NW_GAPI)
#include <core/nwg_engine.h>
#include <lib/nwg_load_core.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	stt_scis::stt_scis(gfx_engine& graphics) :
		a_gfx_stt(graphics),
		m_crd{ 0, 0 }, m_size{ 800, 600}
	{
	}
	stt_scis::~stt_scis() { }
	// --==<core_methods>==--
	void stt_scis::on_draw()
	{
		if (!m_is_enabled) { glDisable(GL_SCISSOR_TEST); return; }
		glEnable(GL_SCISSOR_TEST);
		glScissor(m_crd[0], m_crd[0], m_size[0], m_size[1]);
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	stt_scis::stt_scis(gfx_engine& graphics) :
		a_gfx_stt(graphics),
		m_crd{ 0, 0 }, m_size{ 800, 600 }
	{
	}
	stt_scis::~stt_scis() { }
	// --==<core_methods>==--
	void stt_scis::on_draw()
	{
		if (!m_is_enabled) { return; }
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI