#include <nwg_pch.hpp>
#include "nwg_stt_stenc.h"
#if (defined NW_GAPI)
#include <core/nwg_engine.h>
#include <lib/nwg_load_core.h>
#include <lib/nwg_load_fmbuf.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	stt_stenc::stt_stenc(gfx_engine& graphics) :
		a_gfx_stt(graphics),
		m_mask(0xff), m_func(STC_DECR), m_oper(STC_DECR)
	{
	}
	stt_stenc::~stt_stenc() { }
	// --setters
	void stt_stenc::set_mask(ui8 stencil_mask) {
		m_mask = stencil_mask;
	}
	void stt_stenc::set_func(func_type stencil_function) {
		m_func = stencil_function;
	}
	void stt_stenc::set_oper(oper_type stencil_operation) {
		m_oper = stencil_operation;
	}
	// --==<core_methods>==--
	void stt_stenc::on_draw()
	{
		if (m_is_enabled) { glEnable(GL_STENCIL_TEST); }
		else { glDisable(GL_STENCIL_TEST); return; }
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	stt_stenc::stt_stenc(gfx_engine& graphics) :
		a_gfx_stt(graphics),
		m_mask(0xff), m_func(STC_DECR), m_oper(STC_DECR)
	{
	}
	stt_stenc::~stt_stenc() { }
	// --setters
	void stt_stenc::set_mask(ui8 stencil_mask) {
		m_mask = stencil_mask;
	}
	void stt_stenc::set_func(func_type stencil_function) {
		m_func = stencil_function;
	}
	void stt_stenc::set_oper(oper_type stencil_operation) {
		m_oper = stencil_operation;
	}
	// --==<core_methods>==--
	void stt_stenc::on_draw()
	{
		if (!m_is_enabled) { return; }
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI