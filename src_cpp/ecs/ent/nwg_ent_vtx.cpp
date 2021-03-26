#include <nwg_pch.hpp>
#include "nwg_ent_vtx.h"
#if (defined NW_GAPI)
#include <core/nwg_engine.h>
#include <lib/nwg_load_core.h>
#include "../buf/nwg_buf_vtx.h"
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
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
		v1ui vtx_count = 0;
		for (auto& icmp : m_tab) {
			icmp->on_draw();
			if (icmp.get_ref<buf_vtx>()->check_type<buf_vtx>()) {
				vtx_count += icmp.get_ref<buf_vtx>()->get_data_count();
			}
		}
		if (vtx_count > 0) {
			glDrawArrays(convert<gfx_primitives, GLenum>(m_prim), 0, vtx_count);
		}
	}
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
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
		v1ui vtx_count = 0;
		for (auto& icmp : m_tab) {
			icmp->on_draw();
			if (icmp.get_ref<buf_vtx>()->check_type<buf_vtx>()) {
				vtx_count += icmp.get_ref<buf_vtx>()->get_data_count();
			}
		}
		m_gfx->get_ctxh()->Draw(vtx_count, 0);
	}
}
#endif
#endif	// NW_GAPI