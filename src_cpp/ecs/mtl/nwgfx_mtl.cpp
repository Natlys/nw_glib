#include "nwgfx_pch.hpp"
#include "nwgfx_mtl.h"
#if (defined NW_GAPI)
#include <core/nwgfx_engine.h>
#include <lib/nwgfx_load_txr.h>
#include <lib/nwgfx_load_mtl.h>
#include <lib/nwgfx_load_shd.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NWGFX
{
	gfx_mtl::gfx_mtl(gfx_engine& graphics) :
		t_cmp(), a_gfx_cmp(graphics), a_io_cmp(),
		m_handle(0)
	{
	}
	gfx_mtl::~gfx_mtl() { if (m_handle != 0) { glDeleteProgram(m_handle); m_handle = 0; } }
	// --setters
	void gfx_mtl::set_buf(v1u shd_idx, buf& ref, v1u gfx_buf_idx) {
		get_shd(shd_idx)->set_buf(ref, gfx_buf_idx);
	}
	void gfx_mtl::set_txr(v1u shd_idx, txr& ref, v1u gfx_txridx) {
		get_shd(shd_idx)->set_txr(ref, gfx_txridx);
	}
	void gfx_mtl::add_shd(shd& ref) {
		m_shds.push_back(ref);
	}
	void gfx_mtl::rmv_shd(v1u idx) {
		m_shds.erase(m_shds.begin() + idx % m_shds.size());
	}
	// --operators
	stm_out& gfx_mtl::operator<<(stm_out& stm) const {
		return stm;
	}
	stm_in& gfx_mtl::operator>>(stm_in& stm) {
		return stm;
	}
	// --==<core_methods>==--
	void gfx_mtl::on_draw() {
		glUseProgram(m_handle);
		for (auto& ishd : m_shds) {
			ishd->on_draw();
		}
	}
	bool gfx_mtl::remake()
	{
		if (m_handle != 0) { glDeleteProgram(m_handle); m_handle = 0; }
		m_handle = glCreateProgram();
		if (m_shds.size() == 0) { return false; }

		for (auto& ishd : m_shds) {
			glAttachShader(m_handle, ishd->get_handle());
		}

		glLinkProgram(m_handle);
		if (!gfx_check_shader(m_handle)) { return false; }

		return true;
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NWGFX
{
	gfx_mtl::gfx_mtl(gfx_engine& graphics) :
		t_cmp(), a_gfx_cmp(graphics), a_io_cmp()
	{
	}
	gfx_mtl::~gfx_mtl() { }
	// --setters
	void gfx_mtl::set_buf(v1u shd_idx, buf& ref, v1u gfx_buf_idx) {
		get_shd(shd_idx)->set_buf(ref, gfx_buf_idx);
	}
	void gfx_mtl::set_txr(v1u shd_idx, txr& ref, v1u gfx_txridx) {
		get_shd(shd_idx)->set_txr(ref, gfx_txridx);
	}
	void gfx_mtl::add_shd(shd& ref) {
		m_shds.push_back(ref);
	}
	void gfx_mtl::rmv_shd(v1u idx) {
		m_shds.erase(m_shds.begin() + idx % m_shds.size());
	}
	// --operators
	stm_out& gfx_mtl::operator<<(stm_out& stm) const {
		return stm;
	}
	stm_in& gfx_mtl::operator>>(stm_in& stm) {
		return stm;
	}
	// --==<core_methods>==--
	v1b gfx_mtl::remake()
	{
		//
		return true;
	}
	void gfx_mtl::on_draw() {
		for (auto& ishd : m_shds) {
			ishd->on_draw();
		}
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI