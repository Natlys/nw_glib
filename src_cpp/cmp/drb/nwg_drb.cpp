#include <nwg_pch.hpp>
#include "nwg_drb.h"
#if (defined NW_GAPI)
#include <core/nwg_engine.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	a_drb::a_drb(gfx_engine& graphics) :
		t_cmp(graphics),
		m_cmps(cmps())
	{
	}
	a_drb::~a_drb() { }
	// --setters
	void a_drb::set_mtl(mtl& ref) { m_mtl = ref; }
	void a_drb::add_cmp(cmp& ref) { m_cmps.push_back(ref); }
	void a_drb::rmv_cmp(ui8 idx) { m_cmps.erase(m_cmps.begin() + idx % m_cmps.size()); }
	// --operators
	// --==<core_methods>==--
	void a_drb::on_draw()
	{
		m_mtl->on_draw();
		for (auto& icmp : m_cmps) { icmp->on_draw(); }
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	a_drb::a_drb(gfx_engine& graphics) :
		t_cmp(graphics)
	{
	}
	a_drb::~a_drb() { }
	// --setters
	void a_drb::set_mtl(mtl& ref) { m_mtl = ref; }
	void a_drb::add_rsc(rsc& ref) { m_rscs.push_back(ref); }
	void a_drb::rmv_rsc(ui8 idx) { m_rscs.erase(m_rscs.begin() + idx % m_rscs.size()); }
	// --operators
	// --==<core_methods>==--
	void a_drb::on_draw()
	{
		for (auto& irsc : m_rscs) {
			irsc->on_draw();
		}
		m_mtl->on_draw();
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI