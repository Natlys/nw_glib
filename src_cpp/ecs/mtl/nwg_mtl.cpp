#include <nwg_pch.hpp>
#include "nwg_mtl.h"
#if (defined NW_GAPI)
#include <core/nwg_engine.h>
#include <lib/nwg_load_txr.h>
#include <lib/nwg_load_mtl.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	gfx_mtl::gfx_mtl(gfx_engine& graphics) :
		t_cmp(), a_gfx_cmp(graphics), a_data_cmp(),
		m_handle(0)
	{
	}
	gfx_mtl::~gfx_mtl() { if (m_handle != 0) { glDeleteProgram(m_handle); m_handle = 0; } }
	// --setters
	void gfx_mtl::set_buf(v1ui shd_idx, buf& ref, v1ui buf_idx) {
		get_shd(shd_idx)->set_buf(ref, buf_idx);
	}
	void gfx_mtl::set_txr(v1ui shd_idx, txr& ref, v1ui txr_idx) {
		get_shd(shd_idx)->set_txr(ref, txr_idx);
	}
	void gfx_mtl::add_shd(shd& ref) {
		m_shds.push_back(ref);
	}
	void gfx_mtl::rmv_shd(v1ui idx) {
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
		if (!gfx_debug_shader(m_handle)) { return false; }

		return true;
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW {
	gfx_mtl::gfx_mtl(gfx_engine& graphics) :
		t_cmp(), a_gfx_cmp(graphics), a_data_cmp()
	{
	}
	gfx_mtl::~gfx_mtl() { }
	// --setters
	void gfx_mtl::set_buf(v1ui shd_idx, buf& ref, v1ui buf_idx) {
		get_shd(shd_idx)->set_buf(ref, buf_idx);
	}
	void gfx_mtl::set_txr(v1ui shd_idx, txr& ref, v1ui txr_idx) {
		get_shd(shd_idx)->set_txr(ref, txr_idx);
	}
	void gfx_mtl::add_shd(shd& ref) {
		m_shds.push_back(ref);
	}
	void gfx_mtl::rmv_shd(v1ui idx) {
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
	bit gfx_mtl::remake()
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