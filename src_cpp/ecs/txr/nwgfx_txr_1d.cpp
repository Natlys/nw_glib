#include "nwgfx_pch.hpp"
#include "nwgfx_txr_1d.h"
#if (defined NW_GAPI)
#include <core/nwgfx_engine.h>
#include <lib/nwgfx_load_txr.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NWGFX
{
	gfx_txr_1d::gfx_txr_1d(gfx_engine& graphics) :
		a_gfx_txr(graphics)
	{
	}
	gfx_txr_1d::~gfx_txr_1d() { }
	// --setters
	// --operators
	// --operators
	stm_out& gfx_txr_1d::operator<<(stm_out& stm) const {
		return stm;
	}
	stm_in& gfx_txr_1d::operator>>(stm_in& stm) {
		return stm;
	}
	// --==<core_methods>==--
	v1b gfx_txr_1d::remake(const a_img_cmp& img)
	{
		if (!a_gfx_txr::remake(img)) { return false; }
		if (m_size_x <= 0) { return false; }

		glGenTextures(1, &m_handle);
		glBindTexture(GL_TEXTURE_1D, m_handle);

		v4f border_color = { 0.5f, 0.5f, 0.5f, 1.0f };
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterfv(GL_TEXTURE_1D, GL_TEXTURE_BORDER_COLOR, &border_color[0]);

		glTexImage1D(GL_TEXTURE_1D, 0, m_pxl_fmt, m_size_x, 0, m_pxl_fmt, GL_UNSIGNED_BYTE, &m_pxl_data[0]);

		return true;
	}
	void gfx_txr_1d::clear(ptr value)
	{
		glClearTexImage(m_handle, 0, m_pxl_fmt, GL_UNSIGNED_BYTE, value);
	}
	void gfx_txr_1d::on_draw()
	{
		a_gfx_txr::on_draw();
		glEnable(GL_TEXTURE_1D);
		glActiveTexture(GL_TEXTURE0 + m_slot);
		glBindTexture(GL_TEXTURE_1D, m_handle);
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NWGFX
{
	gfx_txr_1d::gfx_txr_1d(gfx_engine& graphics) :
		a_gfx_txr(graphics)
	{
	}
	gfx_txr_1d::~gfx_txr_1d() { if (m_native != nullptr) { m_native->Release(); m_native = nullptr; } }
	// --setters
	// --operators
	// --operators
	stm_out& gfx_txr_1d::operator<<(stm_out& stm) const {
		return stm;
	}
	stm_in& gfx_txr_1d::operator>>(stm_in& stm) {
		return stm;
	}
	// --==<core_methods>==--
	v1b gfx_txr_1d::remake(const a_img_cmp& img)
	{
		if (m_native != nullptr) { m_native->Release(); m_native = nullptr; }

		if (!a_gfx_txr::remake(img)) { return false; }
		if (m_size_x <= 0) { return false; }
		// texture
		{
			D3D11_TEXTURE1D_DESC desc{ 0 };
			desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			desc.MiscFlags = 0u;
			desc.Format = m_pxl_fmt;
			desc.Width = m_size_x;
			desc.ArraySize = 1u;
			desc.MipLevels = 1u;
			if (get_data() == nullptr){
				desc.Usage = D3D11_USAGE_DYNAMIC;
				desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				m_gfx->get_dvch()->CreateTexture1D(&desc, nullptr, &m_native);
			}
			else {
				desc.Usage = D3D11_USAGE_DEFAULT;
				desc.CPUAccessFlags = 0u;
				D3D11_SUBRESOURCE_DATA data{ 0 };
				data.pSysMem = get_data();
				data.SysMemPitch = m_size_x * m_channels;
				data.SysMemSlicePitch = m_size_x * m_channels;
				m_gfx->get_dvch()->CreateTexture1D(&desc, &data, &m_native);
			}
			if (m_handle == nullptr) { throw init_error(__FILE__, __LINE__); return false; }
		}
		// shader_resource_view
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC desc{ };
			desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;
			desc.Format = m_pxl_fmt;
			desc.Texture1D.MipLevels = 1u;
			desc.Texture1D.MostDetailedMip = 0u;
			m_gfx->get_dvch()->CreateShaderResourceView(m_native, &desc, &m_handle);
			if (m_handle == nullptr) { throw init_error(__FILE__, __LINE__); return false; }
		}

		return true;
	}
	void gfx_txr_1d::clear(ptr value)
	{
	}
	void gfx_txr_1d::on_draw()
	{
		a_gfx_txr::on_draw();
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI