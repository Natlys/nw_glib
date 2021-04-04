#include "nw_gfx_pch.hpp"
#include "nw_gfx_txr_smp.h"
#if (defined NW_GAPI)
#include "core/nw_gfx_engine.h"
#include "lib/nw_gfx_load_smp.h"
#include "lib/nw_gfx_load_txr.h"
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	gfx_txr_smp::gfx_txr_smp(gfx_engine& graphics) :
		t_cmp(), a_gfx_cmp(graphics),
		m_handle(0u),
		m_slot(0u),
		m_filter(convert<texture_filters, filter>(TXFL_NEAREST)),
		m_wrap(convert<texture_wraps, wrap>(TXW_REPEAT)),
		m_border_color(v4f{ 0.5f, 0.5f, 0.5f, 1.0f })
	{
	}
	gfx_txr_smp::gfx_txr_smp(gfx_engine& graphics, texture_filters filter, texture_wraps wrap_mode, v4f border_color) :
		gfx_txr_smp(graphics)
	{
		if (!remake(filter, wrap_mode, border_color)) { throw init_error(__FILE__, __LINE__); return; }
	}
	gfx_txr_smp::~gfx_txr_smp() { if (m_handle != 0) { glDeleteSamplers(1, &m_handle); m_handle = 0; } }
	// --setters
	void gfx_txr_smp::set_slot(v1u slot) {
		m_slot = slot;
	}
	// --==<core_methods>==--
	v1b gfx_txr_smp::remake(texture_filters filter_mode, texture_wraps wrap_mode, v4f border_color)
	{
		if (filter_mode != TXFL_DEFAULT) { m_filter = convert<texture_filters, filter>(filter_mode); }
		if (wrap_mode != TXW_DEFAULT) { m_wrap = convert<texture_wraps, wrap>(wrap_mode); }
		if (wrap_mode == TXW_BORDER) { m_border_color = border_color; }
		if (m_handle != 0) { glDeleteSamplers(1, &m_handle); m_handle = 0; }

		glGenSamplers(1, &m_handle);
		glSamplerParameteri(m_handle, GL_TEXTURE_MIN_FILTER, m_filter);
		glSamplerParameteri(m_handle, GL_TEXTURE_MAG_FILTER, m_filter);
		glSamplerParameteri(m_handle, GL_TEXTURE_WRAP_S, m_wrap);
		glSamplerParameteri(m_handle, GL_TEXTURE_WRAP_T, m_wrap);
		glSamplerParameteri(m_handle, GL_TEXTURE_WRAP_R, m_wrap);
		glSamplerParameterfv(m_handle, GL_TEXTURE_BORDER_COLOR, &m_border_color[0]);

		return true;
	}
	void gfx_txr_smp::on_draw()
	{
		glBindSampler(m_slot, m_handle);
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_D3D)
namespace NW
{
	gfx_txr_smp::gfx_txr_smp(gfx_engine& graphics) :
		t_cmp(), a_gfx_cmp(graphics),
		m_handle(nullptr),
		m_slot(0),
		m_filter(convert<texture_filters, filter>(TXFL_NEAREST)),
		m_wrap(convert<texture_wraps, wrap>(TXW_REPEAT)),
		m_border_color(v4f{ 0.5f, 0.5f, 0.5f, 1.0f })
	{
	}
	gfx_txr_smp::gfx_txr_smp(gfx_engine& graphics, texture_filters filter, texture_wraps wrap_mode, v4f border_color) :
		gfx_txr_smp(graphics)
	{
		if (!remake(filter, wrap_mode, border_color)) { throw init_error(__FILE__, __LINE__); return; }
	}
	gfx_txr_smp::~gfx_txr_smp() { if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; } }
	// --setters
	void gfx_txr_smp::set_slot(v1u slot) {
		m_slot = slot;
	}
	// --==<core_methods>==--
	v1b gfx_txr_smp::remake(texture_filters filter_mode, texture_wraps wrap_mode, v4f border_color)
	{
		if (filter_mode != TXFL_DEFAULT) { m_filter = convert<texture_filters, filter>(filter_mode); }
		if (wrap_mode != TXW_DEFAULT) { m_wrap = convert<texture_wraps, wrap>(wrap_mode); }
		if (wrap_mode == TXW_BORDER) { m_border_color = border_color; }
		if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; }
		
		D3D11_SAMPLER_DESC smp_desc{ };
		smp_desc.AddressU = m_wrap;
		smp_desc.AddressV = m_wrap;
		smp_desc.AddressW = m_wrap;
		smp_desc.Filter = m_filter;
		smp_desc.BorderColor[0] = m_border_color[0];
		smp_desc.BorderColor[1] = m_border_color[1];
		smp_desc.BorderColor[2] = m_border_color[2];
		smp_desc.BorderColor[3] = m_border_color[3];
		smp_desc.ComparisonFunc;	//
		smp_desc.MaxAnisotropy;		// for the filter "anostropy"
		smp_desc.MinLOD;			// minimal level of details
		smp_desc.MaxLOD;			// maximal level of details
		smp_desc.MipLODBias;		// level of details for mipmapping
		m_gfx->get_dvch()->CreateSamplerState(&smp_desc, &m_handle);
		if (m_handle == nullptr) { throw init_error(__FILE__, __LINE__); return false; }

		return true;
	}
	void gfx_txr_smp::on_draw()
	{
		m_gfx->get_ctxh()->VSSetSamplers(m_slot, 1u, &m_handle);
		m_gfx->get_ctxh()->PSSetSamplers(m_slot, 1u, &m_handle);
		m_gfx->get_ctxh()->GSSetSamplers(m_slot, 1u, &m_handle);
		m_gfx->get_ctxh()->HSSetSamplers(m_slot, 1u, &m_handle);
		m_gfx->get_ctxh()->DSSetSamplers(m_slot, 1u, &m_handle);
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI