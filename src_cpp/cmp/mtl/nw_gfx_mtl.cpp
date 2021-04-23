#include "nw_gfx_pch.hpp"
#include "nw_gfx_mtl.h"
#if (defined NW_GAPI)
#include "core/nw_gfx_engine.h"
#	include "lib/nw_gfx_lib_txr.h"
#	include "lib/nw_gfx_lib_mtl.h"
#	include "lib/nw_gfx_lib_shd.h"
#	include "lib/nw_gfx_lib_debug.h"
#	if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	gfx_mtl::gfx_mtl() :
		t_cmp(), a_gfx_cmp(), a_iop_cmp(),
		m_handle(NW_NULL)
	{
	}
	gfx_mtl::~gfx_mtl() { if (m_handle != NW_NULL) { glDeleteProgram(m_handle); m_handle = NW_NULL; } }
	// --setters
	v1nil gfx_mtl::set_buf(cv1u shd_key, buf_t& ref, cv1u buf_key) {
		get_shd(shd_key)->set_buf(ref, buf_key);
	}
	v1nil gfx_mtl::set_txr(cv1u shd_key, txr_t& ref, cv1u txr_idx) {
		get_shd(shd_key)->set_txr(ref, txr_idx);
	}
	v1nil gfx_mtl::add_shd(shd_t& ref) {
		m_shds.push_back(ref);
	}
	v1nil gfx_mtl::rmv_shd(cv1u key) {
		m_shds.erase(m_shds.begin() + key % m_shds.size());
	}
	// --operators
	op_stream_t& gfx_mtl::operator<<(op_stream_t& stm) const {
		return stm;
	}
	ip_stream_t& gfx_mtl::operator>>(ip_stream_t& stm) {
		return stm;
	}
	// --==<core_methods>==--
	v1nil gfx_mtl::on_draw() {
		glUseProgram(m_handle);
		for (auto& ishd : m_shds) {
			ishd->on_draw();
		}
	}
	v1bit gfx_mtl::remake()
	{
		if (m_handle != NW_NULL) { glDeleteProgram(m_handle); m_handle = NW_NULL; }
		m_handle = glCreateProgram();
		if (m_shds.size()) { return NW_FALSE; }

		for (auto& ishd : m_shds) { glAttachShader(get_handle(), ishd->get_handle()); }
		glLinkProgram(get_handle());
		NW_CHECK(gfx_check_shader(get_handle()), "failed remake!", return NW_FALSE);

		return NW_TRUE;
	}
	// --==</core_methods>==--
}
#	endif	// GAPI_OGL
#	if (NW_GAPI & NW_GAPI_D3D)
namespace NW
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
	void gfx_mtl::set_txr(v1u shd_idx, txr& ref, v1u txr_idx) {
		get_shd(shd_idx)->set_txr(ref, txr_idx);
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
	v1bit gfx_mtl::remake()
	{
		//
		return NW_TRUE;
	}
	void gfx_mtl::on_draw() {
		for (auto& ishd : m_shds) {
			ishd->on_draw();
		}
	}
	// --==</core_methods>==--
}
#	endif	// GAPI_D3D
#endif	// NW_GAPI