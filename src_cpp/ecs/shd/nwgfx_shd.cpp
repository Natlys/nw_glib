#include "nwgfx_pch.hpp"
#include "nwgfx_shd.h"
#if (defined NW_GAPI)
#include <core/nwgfx_engine.h>
#include <lib/nwgfx_load_buf.h>
#include <lib/nwgfx_load_txr.h>
#include <lib/nwgfx_load_shd.h>
#include <lib/nwgfx_load_mtl.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NWGFX
{
	a_shd::a_shd(gfx_engine& graphics) :
		t_cmp(), a_gfx_cmp(graphics), a_io_cmp(),
		m_handle(0), m_src_code("default")
	{
	}
	a_shd::~a_shd() { if (m_handle != 0) { glDeleteShader(m_handle); m_handle = 0; } }
	// --setters
	void a_shd::set_buf(buf& ref, v1u idx) {
		if (idx >= 10) { throw run_error(__FILE__, __LINE__); }
		if (m_bufs.size() <= idx + 1) { m_bufs.resize(idx + 1); }
		m_bufs[idx] = ref;
	}
	void a_shd::set_txr(txr& ref, v1u idx) {
		if (idx >= 10) { throw run_error(__FILE__, __LINE__); }
		if (m_txrs.size() <= idx + 1) { m_txrs.resize(idx + 1); }
		m_txrs[idx] = ref;
	}
	// --==<core_methods>==--
	v1b a_shd::remake(cstr source_code)
	{
		if (m_handle != 0) { glDeleteShader(m_handle); m_handle = 0; }
		if (strlen(source_code) < NW_MAX_PATH) {
			if (io_sys::get().is_file_path(source_code)) {
				if (!io_sys::get().load_file(source_code, m_src_code)) { return false; }
			}
			else { m_src_code = source_code; }
		}
		else { m_src_code = source_code; }

		return true;
	}
	void a_shd::on_draw()
	{
		for (v1s itr = 0; itr < m_bufs.size(); itr++) {
			auto& ibuf = m_bufs[itr];
			if (ibuf.is_valid()) {
				ibuf->on_draw();
				glUniformBlockBinding(m_handle, ibuf->get_id(), ibuf->get_slot());
			}
		}
		for (v1s itr = 0; itr < m_txrs.size(); itr++) {
			auto& itxr = m_txrs[itr];
			if (itxr.is_valid()) {
				itxr->on_draw();
				glUniform1i(itr, itxr->get_slot());
			}
		}
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NWGFX
{
	a_shd::a_shd(gfx_engine& graphics) :
		t_cmp(), a_gfx_cmp(graphics), a_io_cmp(),
		m_handle(nullptr), m_src_code("default")
	{
	}
	a_shd::~a_shd() { if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; } }
	// --setters
	void a_shd::set_buf(buf& ref, v1u idx) {
		if (idx >= NW_MAX_SLOTS_BUF) { throw run_error(__FILE__, __LINE__); }
		if (m_bufs.size() <= idx + 1) { m_bufs.resize(idx + 1); }
		m_bufs[idx] = ref;
	}
	void a_shd::set_txr(txr& ref, v1u idx) {
		if (idx >= NW_MAX_SLOTS_TXR) { throw run_error(__FILE__, __LINE__); }
		if (m_txrs.size() <= idx + 1) { m_txrs.resize(idx + 1); }
		m_txrs[idx] = ref;
	}
	// --==<core_methods>==--
	v1b a_shd::remake(cstr source_code)
	{
		if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; }
		if (strlen(source_code) <= NW_MAX_PATH) {
			if (io_sys::get().is_file_path(source_code)) {
				if (!io_sys::get().load_file(source_code, m_src_code)) { return false; }
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