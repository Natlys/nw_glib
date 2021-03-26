#include <nwg_pch.hpp>
#include "nwg_ent_idx.h"
#if (defined NW_GAPI)
#include <core/nwg_engine.h>
#include <lib/nwg_load_core.h>
#include "../buf/nwg_buf_idx.h"
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
			if (icmp.get_ref<buf_idx>()->check_type<buf_idx>()) {
				glDrawElements(m_prim, icmp.get_ref<buf_idx>()->get_data_count(),
					icmp.get_ref<buf_idx>()->get_data_type(), NULL);
			}
		}
	}
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
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
			if (icmp.get_ref<buf_idx>()->check_type<buf_idx>()) {
				m_gfx->get_ctxh()->IASetPrimitiveTopology(m_prim);
				m_gfx->get_ctxh()->DrawIndexed(icmp.get_ref<buf_idx>()->get_data_count(), 0u, 0);
			}
		}
	}
}
#endif
#endif	// NW_GAPI