#include <nwg_pch.hpp>
#include "nwg_shd.h"
#if (defined NW_GAPI)
#include <core/nwg_engine.h>
#include <lib/nwg_load_buf.h>
#include <lib/nwg_load_txr.h>
#include <lib/nwg_load_shd.h>
#include <lib/nwg_load_mtl.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	a_shd::a_shd(gfx_engine& graphics) :
		t_cmp(), a_gfx_cmp(graphics), a_data_cmp(),
		m_handle(0), m_src_code("default")
	{
	}
	a_shd::~a_shd() { if (m_handle != 0) { glDeleteShader(m_handle); m_handle = 0; } }
	// --setters
	void a_shd::set_buf(buf& ref, v1ui idx) {
		if (idx >= 10) { throw run_error(__FILE__, __LINE__); }
		if (m_bufs.size() <= idx + 1) { m_bufs.resize(idx + 1); }
		m_bufs[idx] = ref;
	}
	void a_shd::set_txr(txr& ref, v1ui idx) {
		if (idx >= 10) { throw run_error(__FILE__, __LINE__); }
		if (m_txrs.size() <= idx + 1) { m_txrs.resize(idx + 1); }
		m_txrs[idx] = ref;
	}
	// --==<core_methods>==--
	bit a_shd::remake(cstr source_code)
	{
		if (m_handle != 0) { glDeleteShader(m_handle); m_handle = 0; }
		if (strlen(source_code) < NW_MAX_PATH) {
			if (data_sys::get().is_file_path(source_code)) {
				if (!data_sys::get().load_file(source_code, m_src_code)) { return false; }
			}
			else { m_src_code = source_code; }
		}
		else { m_src_code = source_code; }

		return true;
	}
	void a_shd::on_draw()
	{
		for (v1si itr = 0; itr < m_bufs.size(); itr++) {
			auto& ibuf = m_bufs[itr];
			if (ibuf.is_valid()) {
				ibuf->on_draw();
				glUniformBlockBinding(m_handle, ibuf->get_id(), ibuf->get_slot());
			}
		}
		for (v1si itr = 0; itr < m_txrs.size(); itr++) {
			auto& itxr = m_txrs[itr];
			if (itxr.is_valid()) {
				itxr->on_draw();
				glUniform1i(itr, itxr->get_slot());
			}
		}
	}
	// --==</core_methods>==--

	/// shader debugging
	bit gfx_debug_shader(v1ui shd_id) {
		if (shd_id == 0) { return false; }
		v1si32 success_code = 0;
		v1si32 log_size = 0;
		dstr log_string;
		if (glIsShader(shd_id)) {
			glGetShaderiv(shd_id, GL_COMPILE_STATUS, &success_code);
			if (success_code == 0) {
				glGetShaderiv(shd_id, GL_INFO_LOG_LENGTH, &log_size);
				log_string.resize(log_size);
				glGetShaderInfoLog(shd_id, log_size, NULL, &log_string[0]);
				throw a_error(&log_string[0], ERC_COMPILLATION, __FILE__, __LINE__);
				return success_code == 1;
			}
		}
		else {
			glGetProgramiv(m_handle, GL_LINK_STATUS, &success_code);
			if (success_code == 0) {
				glGetProgramiv(shd_id, GL_INFO_LOG_LENGTH, &log_size);
				log_string.resize(log_size);
				glGetProgramInfoLog(shd_id, log_size, NULL, &log_string[0]);
				throw a_error(&log_string[0], ERC_LINKAGE, __FILE__, __LINE__);
				return false;
			}
		}
		return success_code == 1;
	}
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	a_shd::a_shd(gfx_engine& graphics) :
		t_cmp(), a_gfx_cmp(graphics), a_data_cmp(),
		m_handle(nullptr), m_src_code("default")
	{
	}
	a_shd::~a_shd() { if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; } }
	// --setters
	void a_shd::set_buf(buf& ref, v1ui idx) {
		if (idx >= NW_MAX_SLOTS_BUF) { throw run_error(__FILE__, __LINE__); }
		if (m_bufs.size() <= idx + 1) { m_bufs.resize(idx + 1); }
		m_bufs[idx] = ref;
	}
	void a_shd::set_txr(txr& ref, v1ui idx) {
		if (idx >= NW_MAX_SLOTS_TXR) { throw run_error(__FILE__, __LINE__); }
		if (m_txrs.size() <= idx + 1) { m_txrs.resize(idx + 1); }
		m_txrs[idx] = ref;
	}
	// --==<core_methods>==--
	bit a_shd::remake(cstr source_code)
	{
		if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; }
		if (strlen(source_code) <= NW_MAX_PATH) {
			if (data_sys::get().is_file_path(source_code)) {
				if (!data_sys::get().load_file(source_code, m_src_code)) { return false; }
			}
			else { m_src_code = source_code; }
		}
		else { m_src_code = source_code; }

		return true;
	}
	void a_shd::on_draw()
	{
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI