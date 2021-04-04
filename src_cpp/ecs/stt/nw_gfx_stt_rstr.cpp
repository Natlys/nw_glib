#include "nw_gfx_pch.hpp"
#include "nw_gfx_stt_rstr.h"
#if (defined NW_GAPI)
#include "core/nw_gfx_engine.h"
#include "lib/nw_gfx_load_core.h"
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	gfx_stt_rstr::gfx_stt_rstr(gfx_engine& graphics) :
		a_gfx_stt(graphics),
		m_handle(0u),
		m_is_front_culling(false), m_is_front_filling(false),
		m_is_back_culling(false), m_is_back_filling(false),
		m_is_clock_culling(false), m_is_solid_filling(false),
		m_is_multisample(false),
		m_scis_rect{ 0, 0, 800, 600 }
	{
	}
	gfx_stt_rstr::~gfx_stt_rstr() {}
	// --setters
	void gfx_stt_rstr::set_filling(v1b is_front, v1b is_back, v1b is_solid_filling) {
		m_is_front_filling = is_front;
		m_is_back_filling = is_back;
		m_is_solid_filling = is_solid_filling;
	}
	void gfx_stt_rstr::set_culling(v1b is_front, v1b is_back, v1b is_clock_culling) {
		m_is_front_culling = is_front;
		m_is_back_culling = is_back;
		m_is_clock_culling = is_clock_culling;
	}
	void gfx_stt_rstr::set_multisample(v1b enable) {
		m_is_multisample = enable;
	}
	// --==<core_methods>==--
	v1b gfx_stt_rstr::remake()
	{
		return true;
	}
	void gfx_stt_rstr::on_draw()
	{
	}
}
#endif
#if (NW_GAPI & NW_GAPI_D3D)
namespace NW
{
	gfx_stt_rstr::gfx_stt_rstr(gfx_engine& graphics) :
		a_gfx_stt(graphics),
		m_handle(nullptr),
		m_is_front_culling(false), m_is_front_filling(false),
		m_is_back_culling(false), m_is_back_filling(false),
		m_is_clock_culling(false), m_is_solid_filling(false),
		m_is_multisample(false),
		m_scis_rect{ 0, 0, 800, 600 }
	{
	}
	gfx_stt_rstr::~gfx_stt_rstr()
	{
		if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; }
	}
	// --setters
	void gfx_stt_rstr::set_filling(v1b is_front, v1b is_back, v1b is_solid_filling) {
		m_is_front_filling = is_front;
		m_is_back_filling = is_back;
		m_is_solid_filling = is_solid_filling;
	}
	void gfx_stt_rstr::set_culling(v1b is_front, v1b is_back, v1b is_clock_culling) {
		m_is_front_culling = is_front;
		m_is_back_culling = is_back;
		m_is_clock_culling = is_clock_culling;
	}
	void gfx_stt_rstr::set_multisample(v1b enable) {
		m_is_multisample = enable;
	}
	// --==<core_methods>==--
	v1b gfx_stt_rstr::remake()
	{
		if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; }
		
		D3D11_RASTERIZER_DESC desc{ };
		desc.CullMode = is_front_culling() ? D3D11_CULL_FRONT : is_back_culling() ? D3D11_CULL_BACK : D3D11_CULL_NONE;
		desc.FillMode = is_solid_filling() ? D3D11_FILL_SOLID : D3D11_FILL_WIREFRAME;
		desc.FrontCounterClockwise = !is_clock_culling();
		desc.MultisampleEnable = is_multisample();
		desc.AntialiasedLineEnable = FALSE;
		desc.ScissorEnable = m_scis_rect[3] > m_scis_rect[1] && m_scis_rect[2] > m_scis_rect[0];
		desc.DepthBias = 0;
		desc.DepthBiasClamp = 0.0f;
		desc.DepthClipEnable = FALSE;
		m_gfx->get_dvch()->CreateRasterizerState(&desc, &m_handle);
		if (m_handle == nullptr) { return false; }

		return true;
	}
	void gfx_stt_rstr::on_draw()
	{
		m_gfx->get_ctxh()->RSSetState(m_handle);
	}
}
#endif
#endif	// NW_GAPI