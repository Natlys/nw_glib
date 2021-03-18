#include <nwg_pch.hpp>
#include "nwg_shd.h"
#if (defined NW_GAPI)
#include <core/nwg_engine.h>
#include <lib/nwg_load_shd.h>
#include <lib/nwg_load_mtl.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	a_shd::a_shd(gfx_engine& graphics, cstr name) :
		t_cmp(graphics), a_data_rsc(name),
		m_handle(0), m_src_code("default"), m_rscs(rscs())
	{
	}
	a_shd::~a_shd() { if (m_handle != 0) { glDeleteShader(m_handle); m_handle = 0; } }
	// --setters
	void a_shd::add_rsc(rsc& ref) {
		m_rscs.push_back(ref);
	}
	void a_shd::rmv_rsc(ui8 idx) {
		m_rscs.erase(m_rscs.begin() + idx % m_rscs.size());
	}
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	a_shd::a_shd(gfx_engine& graphics, cstr name) :
		t_cmp(graphics), a_data_rsc(name),
		m_handle(nullptr), m_src_code("default"), m_rscs(rscs())
	{
	}
	a_shd::~a_shd() { if (m_hadle != nullptr) { m_hadle->Release(); m_hadle = nullptr; } }
	// --setters
	void a_shd::add_rsc(rsc& ref) {
		m_rscs.push_back(ref);
	}
	void a_shd::rmv_rsc(ui8 idx) {
		m_rscs.erase(m_rscs.begin() + idx % m_rscs.size());
	}
}
#endif
#endif	// NW_GAPI