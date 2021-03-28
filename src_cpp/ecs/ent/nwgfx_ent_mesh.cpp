#include "nwgfx_pch.hpp"
#include "nwgfx_ent_mesh.h"
#if (defined NW_GAPI)
#include "nwgfx.hpp"
#include "lib/nwgfx_load_core.h"
namespace NWGFX
{
	gfx_ent_mesh::gfx_ent_mesh(gfx_engine& graphics) :
		gfx_ent_idx(graphics), a_io_cmp(),
		m_tform(1.0f),
		m_scl{ 1.0f, 1.0f, 1.0f }, m_rtn{ 0.0f, 0.0f, 0.0f }, m_crd{ 0.0f, 0.0f, 0.0f }
	{
	}
	gfx_ent_mesh::~gfx_ent_mesh() { }
	// --getters
	// --setters
	void gfx_ent_mesh::set_scl(const v3f& scl) {
		m_scl = scl;
	}
	void gfx_ent_mesh::set_rtn(const v3f& rtn) {
		m_rtn = rtn;
	}
	void gfx_ent_mesh::set_crd(const v3f& crd) {
		m_crd = crd;
	}
	void gfx_ent_mesh::set_tform(const m4f& tform) {
		m_tform = tform;
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
		m_tform = m4f(1.0f)
			* mat_scale(m4f(1.0f), m_scl)
			* mat_move(m4f(1.0f), m_crd)
			* mat_rotate(m4f(1.0f), deg_to_rad(m_rtn.y), v3f(0.0f, 1.0f, 0.0f))
			* mat_rotate(m4f(1.0f), deg_to_rad(m_rtn.x), v3f(1.0f, 0.0f, 0.0f))
			* mat_rotate(m4f(1.0f), deg_to_rad(m_rtn.z), v3f(0.0f, 0.0f, 1.0f))
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