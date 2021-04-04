#include "nw_gfx_pch.hpp"
#include "nw_gfx_ent_idx.h"
#if (defined NW_GAPI)
#include "core/nw_gfx_engine.h"
#include "lib/nw_gfx_load_core.h"
#include "../buf/nw_gfx_buf_idx.h"
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	gfx_ent_idx::gfx_ent_idx(gfx_engine& graphics) :
		a_gfx_ent(graphics)
	{
	}
	gfx_ent_idx::~gfx_ent_idx() { }
	// --==<core_methods>==--
	void gfx_ent_idx::on_draw()
	{
		for (auto& icmp : m_tab) {
			icmp->on_draw();
			if (gfx_buf_idx* ibuf = icmp.get_ref<gfx_buf_idx>()->check_cast<gfx_buf_idx>()) {
				m_gfx->set_prim(m_prim);
				m_gfx->draw_idx(ibuf);
			}
		}
	}
}
#endif
#if (NW_GAPI & NW_GAPI_D3D)
namespace NW
{
	gfx_ent_idx::gfx_ent_idx(gfx_engine& graphics) :
		a_gfx_ent(graphics)
	{
	}
	gfx_ent_idx::~gfx_ent_idx() { }
	// --==<core_methods>==--
	void gfx_ent_idx::on_draw()
	{
		for (auto& icmp : m_tab) {
			icmp->on_draw();
			m_gfx->get_ctxh()->IASetPrimitiveTopology(m_prim);
			if (gfx_buf_idx* ibuf = icmp.get_ref<gfx_buf_idx>()->check_cast<gfx_buf_idx>()) {
				m_gfx->get_ctxh()->IASetPrimitiveTopology(m_prim);
				m_gfx->draw_idx(ibuf);
			}
		}
	}
}
#endif
#endif	// NW_GAPI