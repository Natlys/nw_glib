#include <nwg_pch.hpp>
#include "nwg_txr_1d.h"
#if (defined NW_GAPI)
#include <core/nwg_engine.h>
#include <lib/nwg_load_txr.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	txr_1d::txr_1d(gfx_engine& graphics) :
		a_txr(graphics)
	{
	}
	txr_1d::~txr_1d() { }
	// --setters
	// --operators
	// --operators
	stm_out& txr_1d::operator<<(stm_out& stm) const {
		return stm;
	}
	stm_in& txr_1d::operator>>(stm_in& stm) {
		return stm;
	}
	// --==<core_methods>==--
	bit txr_1d::remake(const img_cmp& img)
	{
		if (!a_txr::remake(img)) { return false; }
		if (m_size_x <= 0) { return false; }

		glGenTextures(1, &m_handle);
		glBindTexture(GL_TEXTURE_1D, m_handle);

		v4f border_color = { 0.5f, 0.5f, 0.5f, 1.0f };
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterfv(GL_TEXTURE_1D, GL_TEXTURE_BORDER_COLOR, &border_color[0]);

		glTexImage1D(GL_TEXTURE_1D, 0, m_pxl_fmt, m_size_x, 0, m_img_fmt, m_data_type, &m_pxl_data[0]);

		return true;
	}
	void txr_1d::clear(ptr value)
	{
		glClearTexImage(m_handle, 0, m_pxl_fmt, m_data_type, value);
	}
	void txr_1d::on_draw()
	{
		a_txr::on_draw();
		glEnable(GL_TEXTURE_1D);
		glActiveTexture(GL_TEXTURE0 + m_slot);
		glBindTexture(GL_TEXTURE_1D, m_handle);
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	txr_1d::txr_1d(gfx_engine& graphics) :
		a_txr(graphics)
	{
	}
	txr_1d::~txr_1d() { if (m_native != nullptr) { m_native->Release(); m_native = nullptr; } }
	// --setters
	// --operators
	// --operators
	stm_out& txr_1d::operator<<(stm_out& stm) const {
		return stm;
	}
	stm_in& txr_1d::operator>>(stm_in& stm) {
		return stm;
	}
	// --==<core_methods>==--
	bit txr_1d::remake(const img_cmp& img)
	{
		if (!a_txr::remake(img)) { return false; }
		if (m_native != nullptr) { m_native->Release(); m_native = nullptr; }
		
		if (m_size_x <= 0) { return false; }

		return true;
	}
	void txr_1d::clear(ptr value)
	{
	}
	void txr_1d::on_draw()
	{
		a_txr::on_draw();
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI