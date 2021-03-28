#include "nwgfx_pch.hpp"
#include "nwgfx_txr_2d.h"
#if (defined NW_GAPI)
#include <core/nwgfx_engine.h>
#include <core/nwgfx_data.hpp>
#include <lib/nwgfx_load_txr.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NWGFX
{
	gfx_txr_2d::gfx_txr_2d(gfx_engine& graphics) :
		a_gfx_txr(graphics)
	{
	}
	gfx_txr_2d::~gfx_txr_2d() { }
	// --setters
	// --operators
	stm_out& gfx_txr_2d::operator<<(stm_out& stm) const {
		return stm;
	}
	stm_in& gfx_txr_2d::operator>>(stm_in& stm) {
		return stm;
	}
	// --==<core_methods>==--
	v1b gfx_txr_2d::remake(const a_img_cmp& img)
	{
		if (!a_gfx_txr::remake(img)) { return false; }
		if (m_size_x <= 0 || m_size_y <= 0) { return false; }
		
		glGenTextures(1, &m_handle);
		glBindTexture(GL_TEXTURE_2D, m_handle);

		v4f border_color = { 0.5f, 0.5f, 0.5f, 1.0f };
		glBindTexture(GL_TEXTURE_2D, m_handle);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &border_color[0]);

		glTexImage2D(GL_TEXTURE_2D, 0, m_pxl_fmt, m_size_x, m_size_y, 0, m_pxl_fmt, GL_UNSIGNED_BYTE, &m_pxl_data[0]);
		glGenerateMipmap(GL_TEXTURE_2D);

		return true;
	}
	void gfx_txr_2d::clear(ptr value)
	{
		glClearTexImage(m_handle, 0, m_pxl_fmt, m_pxl_fmt, value);
	}
	void gfx_txr_2d::on_draw()
	{
		a_gfx_txr::on_draw();

		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0 + m_slot);
		glBindTexture(GL_TEXTURE_2D, m_handle);
	}
	// --==</core_methods>==--
}
namespace NWGFX
{
	gfx_txr_2d_mulsmp::gfx_txr_2d_mulsmp(gfx_engine& graphics) :
		gfx_txr_2d(graphics),
		m_samples(0)
	{
	}
	gfx_txr_2d_mulsmp::~gfx_txr_2d_mulsmp() { }
	// --setters
	void gfx_txr_2d_mulsmp::set_samples(v1u samples) {
		m_samples = samples;
	}
	// --operators
	stm_out& gfx_txr_2d_mulsmp::operator<<(stm_out& stm) const {
		return stm;
	}
	stm_in& gfx_txr_2d_mulsmp::operator>>(stm_in& stm) {
		return stm;
	}
	// --==<core_methods>==--
	v1b gfx_txr_2d_mulsmp::remake(const a_img_cmp& img)
	{
		if (!a_gfx_txr::remake(img)) { return false; }
		if (m_size_x <= 0 || m_size_y <= 0) { return false; }
		
		glGenTextures(1, &m_handle);
		glBindTexture(GL_TEXTURE_2D, m_handle);

		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_samples, m_pxl_fmt, m_size_x, m_size_y, GL_FALSE);

		return true;
	}
	void gfx_txr_2d_mulsmp::on_draw()
	{
		a_gfx_txr::on_draw();

		glEnable(GL_MULTISAMPLE);
		glActiveTexture(GL_TEXTURE0 + m_slot);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_handle);
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NWGFX
{
	gfx_txr_2d::gfx_txr_2d(gfx_engine& graphics) :
		a_gfx_txr(graphics),
		m_native(nullptr)
	{
	}
	gfx_txr_2d::~gfx_txr_2d() { if (m_native != nullptr) { m_native->Release(); m_native = nullptr; } }
	// --setters
	// --operators
	stm_out& gfx_txr_2d::operator<<(stm_out& stm) const {
		return stm;
	}
	stm_in& gfx_txr_2d::operator>>(stm_in& stm) {
		return stm;
	}
	// --==<core_methods>==--
	v1b gfx_txr_2d::remake(const a_img_cmp& source)
	{
		if (m_native != nullptr) { m_native->Release(); m_native = nullptr; }

		if (!a_gfx_txr::remake(source)) { return false; }
		if (m_size_x <= 0 || m_size_y <= 0) { return false; }
		// texture
		{
			D3D11_TEXTURE2D_DESC desc{ 0 };
			desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			desc.Format = m_pxl_fmt;
			desc.Width = m_size_x;
			desc.Height = m_size_y;
			desc.MipLevels = 1u;
			desc.ArraySize = 1u;
			desc.SampleDesc.Count = 1u;
			desc.SampleDesc.Quality = 0u;
			desc.MiscFlags = 0u;

			if (get_data() == nullptr) {
				desc.Usage = D3D11_USAGE_DYNAMIC;
				desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				m_gfx->get_dvch()->CreateTexture2D(&desc, nullptr, &m_native);
			}
			else {
				desc.Usage = D3D11_USAGE_DEFAULT;
				desc.CPUAccessFlags = 0u;
				D3D11_SUBRESOURCE_DATA data{ 0 };
				data.pSysMem = get_data();
				data.SysMemPitch = m_size_x * m_channels;
				data.SysMemSlicePitch = m_size_x * m_size_y * m_channels;
				m_gfx->get_dvch()->CreateTexture2D(&desc, &data, &m_native);
			}
			if (m_native == nullptr) { throw init_error(__FILE__, __LINE__); return false; }
		}
		// shader_resource_view
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC desc{ };
			desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			desc.Format = m_pxl_fmt;
			desc.Texture2D.MostDetailedMip = 0u;
			desc.Texture2D.MipLevels = 1u;
			m_gfx->get_dvch()->CreateShaderResourceView(m_native, &desc, &m_handle);
			if (m_handle == nullptr) { throw init_error(__FILE__, __LINE__); return false; }
		}

		return true;
	}
	void gfx_txr_2d::clear(ptr value)
	{
	}
	void gfx_txr_2d::on_draw()
	{
		a_gfx_txr::on_draw();
	}
	// --==</core_methods>==--
}
namespace NWGFX
{
	gfx_txr_2d_mulsmp::gfx_txr_2d_mulsmp(gfx_engine& graphics) :
		gfx_txr_2d(graphics),
		m_samples(0)
	{
	}
	gfx_txr_2d_mulsmp::~gfx_txr_2d_mulsmp() { if (m_native != nullptr) { m_native->Release(); m_native = nullptr; } }
	// --setters
	void gfx_txr_2d_mulsmp::set_samples(v1u samples) {
		m_samples = samples;
	}
	// --operators
	stm_out& gfx_txr_2d_mulsmp::operator<<(stm_out& stm) const {
		return stm;
	}
	stm_in& gfx_txr_2d_mulsmp::operator>>(stm_in& stm) {
		return stm;
	}
	// --==<core_methods>==--
	v1b gfx_txr_2d_mulsmp::remake(const a_img_cmp& img)
	{
		if (m_native != nullptr) { m_native->Release(); m_native = nullptr; }
		
		if (!a_gfx_txr::remake(img)) { return false; }
		if (m_size_x <= 0 || m_size_y <= 0) { return false; }
		
		return true;
	}
	void gfx_txr_2d_mulsmp::on_draw()
	{
		a_gfx_txr::on_draw();
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI