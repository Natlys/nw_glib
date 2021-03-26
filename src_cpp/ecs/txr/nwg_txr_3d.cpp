#include <nwg_pch.hpp>
#include "nwg_txr_3d.h"
#if (defined NW_GAPI)
#include <lib/nwg_load_txr.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	txr_cube::txr_cube(gfx_engine& graphics) :
		a_txr(graphics)
	{
	}
	txr_cube::~txr_cube() { }
	// --setters
	// --operators
	stm_out& txr_cube::operator<<(stm_out& stm) const {
		return stm;
	}
	stm_in& txr_cube::operator>>(stm_in& stm) {
		return stm;
	}
	// --==<core_methods>==--
	bit txr_cube::remake(const img_cmp& img)
	{
		if (!a_txr::remake(img)) { return false; }
		if (m_size_x <= 0 || m_size_y <= 0) { return false; }
		
		glGenTextures(1, &m_handle);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_handle);

		v4f border_color = { 0.5f, 0.5f, 0.5f, 1.0f };
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
		glTexParameterfv(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BORDER_COLOR, &border_color[0]);

		for (v1ui ifc = 0; ifc < 6; ifc++) {
			GLenum next = GL_TEXTURE_CUBE_MAP_POSITIVE_X + ifc;
			size size_x = m_size_x / 1;
			size size_y = m_size_y / 6;
			data face_data = make_region(m_size_x / 6 * 0, m_size_y / 6 * (5 - ifc), m_size_x / 1, m_size_y / 6);
			glTexImage2D(next, 0, m_pxl_fmt, size_x, size_y, 0, m_img_fmt, m_data_type, &face_data[0]);
		}

		return true;
	}
	void txr_cube::clear(ptr value)
	{
		glClearTexImage(m_handle, 0, m_pxl_fmt, m_data_type, value);
	}
	void txr_cube::on_draw()
	{
		a_txr::on_draw();

		glEnable(GL_TEXTURE_CUBE_MAP);
		glActiveTexture(GL_TEXTURE0 + m_slot);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_handle);
	}
	
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	txr_cube::txr_cube(gfx_engine& graphics) :
		a_txr(graphics)
	{
	}
	txr_cube::~txr_cube() { }
	// --setters
	// --operators
	stm_out& txr_cube::operator<<(stm_out& stm) const {
		return stm;
	}
	stm_in& txr_cube::operator>>(stm_in& stm) {
		return stm;
	}
	// --==<core_methods>==--
	bit txr_cube::remake(const img_cmp& img)
	{
		if (!a_txr::remake(img)) { return false; }
		if (m_size_x <= 0 || m_size_y <= 0) { return false; }

		return true;
	}
	void txr_cube::clear(ptr value)
	{
	}
	void txr_cube::on_draw()
	{
		a_txr::on_draw();
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI