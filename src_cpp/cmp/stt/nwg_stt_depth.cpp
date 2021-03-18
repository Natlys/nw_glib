#include <nwg_pch.hpp>
#include "nwg_stt_depth.h"
#if (defined NW_GAPI)
#include <lib/nwg_load_core.h>
#include <lib/nwg_load_fmbuf.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	stt_depth::stt_depth(gfx_engine& graphics) :
		a_gfx_stt(graphics),
		m_mask(true), m_function(DTC_LESS)
	{
	}
	stt_depth::~stt_depth() { }
	// --setters
	void stt_depth::set_mask(bit enable) {
		m_mask = enable;
	}
	void stt_depth::set_func(fn_type function) {
		m_function = function;
	}
	// --==<core_methods>==--
	void stt_depth::on_draw()
	{
		if (m_is_enabled) { glEnable(GL_DEPTH_TEST); }
		else { glDisable(GL_DEPTH_TEST); return; }
		glDepthMask(m_mask ? GL_TRUE : GL_FALSE);
		glDepthFunc(convert_enum<fn_type, GLenum>(m_function));
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	stt_depth::stt_depth(gfx_engine& graphics) :
		a_gfx_stt(graphics),
		m_mask(true), m_function(DTC_LESS)
	{
	}
	stt_depth::~stt_depth() { }
	// --setters
	void stt_depth::set_mask(bit enable) {
		m_mask = enable;
	}
	void stt_depth::set_func(fn_type function) {
		m_function = function;
	}
	// --==<core_methods>==--
	void stt_depth::on_draw()
	{
		if (!m_is_enabled) { return; }
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI