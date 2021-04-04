#include "nw_gfx_pch.hpp"
#include "nw_gfx_ent_mesh.h"
#if (defined NW_GAPI)
#include "nw_gfx.hpp"
#include "lib/nw_gfx_load_core.h"
namespace NW
{
	gfx_ent_mesh::gfx_ent_mesh(gfx_engine& graphics) :
		gfx_ent_idx(graphics), a_io_cmp(),
		m_tform(m4f::make_ident()),
		m_scl{ 1.0f, 1.0f, 1.0f }, m_rtn{ 0.0f, 0.0f, 0.0f }, m_crd{ 0.0f, 0.0f, 0.0f }
	{
	}
	gfx_ent_mesh::~gfx_ent_mesh() { }
	// --getters
	// --setters
	gfx_ent_mesh& gfx_ent_mesh::set_scl(cv3f& scl) {
		m_scl = scl;
		return *this;
	}
	gfx_ent_mesh& gfx_ent_mesh::set_rtn(cv3f& rtn) {
		m_rtn = rtn;
		return *this;
	}
	gfx_ent_mesh& gfx_ent_mesh::set_crd(cv3f& crd) {
		m_crd = crd;
		return *this;
	}
	gfx_ent_mesh& gfx_ent_mesh::set_tform(cm4f& tform) {
		m_tform = tform;
		return *this;
	}
	// --operators
	stm_out& gfx_ent_mesh::operator<<(stm_out& stm) const {
		return stm;
	}
	stm_in& gfx_ent_mesh::operator>>(stm_in& stm) {
		return stm;
	}
	// --==<core_methods>==--
	void gfx_ent_mesh::on_draw()
	{
		m_tform = m4f::make_ident()
			* m4f::make_scale(m_scl)
			* m4f::make_coord(m_crd)
			* m4f::make_rotat_xyz(m_rtn)
			;
		for (auto& icmp : m_tab) {
			icmp->on_draw();
			if (gfx_buf_idx* ibuf = icmp.get_ref<gfx_buf_idx>()->check_cast<gfx_buf_idx>()) {
				m_gfx->draw_idx(ibuf);
			}
		}
	}
	// --==</core_methods>==--
}
#endif	// NW_GAPI