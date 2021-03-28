#include "nwgfx_pch.hpp"
#include "nwgfx_ent_vtx.h"
#if (defined NW_GAPI)
#include <core/nwgfx_engine.h>
#include <lib/nwgfx_load_core.h>
#include "../buf/nwgfx_buf_vtx.h"
#if (NW_GAPI & NW_GAPI_OGL)
namespace NWGFX
{
	gfx_ent_vtx::gfx_ent_vtx(gfx_engine& graphics) :
		a_gfx_ent(graphics)
	{
	}
	gfx_ent_vtx::~gfx_ent_vtx() { }
	// --setters
	// --==<core_methods>==--
	void gfx_ent_vtx::on_draw()
	{
		v1u vtx_count = 0;
		for (auto& icmp : m_tab) {
			icmp->on_draw();
			if (icmp.get_ref<gfx_buf_vtx>()->check_type<gfx_buf_vtx>()) {
				vtx_count += icmp.get_ref<gfx_buf_vtx>()->get_count();
			}
		}
		if (vtx_count > 0) {
			m_gfx->set_prim(m_prim);
			glDrawArrays(m_prim, 0, vtx_count);
		}
	}
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NWGFX
{
	gfx_ent_vtx::gfx_ent_vtx(gfx_engine& graphics) :
		a_gfx_ent(graphics)
	{
	}
	gfx_ent_vtx::~gfx_ent_vtx() { }
	// --setters
	// --==<core_methods>==--
	void gfx_ent_vtx::on_draw()
	{
		v1u vtx_count = 0;
		for (auto& icmp : m_tab) {
			icmp->on_draw();
			if (icmp.get_ref<gfx_buf_vtx>()->check_type<gfx_buf_vtx>()) {
				vtx_count += icmp.get_ref<gfx_buf_vtx>()->get_count();
			}
		}
		if (vtx_count > 0u) {
			m_gfx->get_ctxh()->IASetPrimitiveTopology(m_prim);
			m_gfx->get_ctxh()->Draw(vtx_count, 0u);
		}
	}
}
#endif
#endif	// NW_GAPI