#include <nwg_pch.hpp>
#include "nwg_stt_rstr.h"
#if (defined NW_GAPI)
#include <core/nwg_engine.h>
#include <lib/nwg_load_core.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	gfx_stt_rstr::gfx_stt_rstr(gfx_engine& graphics) :
		a_gfx_stt(graphics)
	{
	}
	gfx_stt_rstr::~gfx_stt_rstr() {}
	// --setters
	void gfx_stt_rstr::set_filling(fill_modes mode) {
		//
	}
	void gfx_stt_rstr::set_culling(cull_modes mode) {
		//
	}
	// --==<core_methods>==--
	bit gfx_stt_rstr::remake()
	{
		//
	}
	void gfx_stt_rstr::on_draw()
	{
	}
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	gfx_stt_rstr::gfx_stt_rstr(gfx_engine& graphics) :
		a_gfx_stt(graphics)
	{
	}
	gfx_stt_rstr::~gfx_stt_rstr()
	{
		if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; }
	}
	// --setters
	void gfx_stt_rstr::set_filling(fill_modes mode) {
		//
	}
	void gfx_stt_rstr::set_culling(cull_modes mode) {
		//
	}
	// --==<core_methods>==--
	bit gfx_stt_rstr::remake()
	{
		if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; }
		
		D3D11_RASTERIZER_DESC desc;
		desc.CullMode = m_culling;
		desc.FillMode = m_filling;
		m_gfx->get_dvch()->CreateRasterizerState(&desc, &m_handle);
		if (m_handle == nullptr) { return false; }

		return true;
	}
	void gfx_stt_rstr::on_draw()
	{
	}
}
#endif
#endif	// NW_GAPI