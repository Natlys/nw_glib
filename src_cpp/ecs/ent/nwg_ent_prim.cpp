#include <nwg_pch.hpp>
#include "nwg_ent_prim.h"
#if (defined NW_GAPI)
#include <nwg.hpp>
#include <core/nwg_data.hpp>
namespace NW
{
	gfx_ent_cube::gfx_ent_cube(gfx_engine& graphics) :
		gfx_ent_mesh(graphics) 
	{
		// input layout
		this->add_cmp(m_gfx->get_cmp<shd_layt>(0u));
		// buffers
		this->add_cmp(m_gfx->get_cmp<buf_vtx>(0u));
		this->add_cmp(m_gfx->get_cmp<buf_idx>(0u));
		// material
		this->add_cmp(m_gfx->get_cmp<gfx_mtl>(0u));
		// states
		this->add_cmp(m_gfx->get_cmp<a_gfx_stt>(0u));
	}
	gfx_ent_cube::gfx_ent_cube(gfx_engine& graphics, v1ui mtl_id) :
		gfx_ent_cube(graphics)
	{
		for (auto& icmp : m_tab) {
			if (icmp.get_ref<gfx_mtl>()->check_type<gfx_mtl>()) {
				icmp.set_ref(m_gfx->get_cmp<gfx_mtl>(mtl_id));
			}
		}
	}

	gfx_ent_cube::~gfx_ent_cube()
	{
	}
	// --==<core_methods>==--
	void gfx_ent_cube::on_draw()
	{
		gfx_ent_mesh::on_draw();
	}
	// --==</core_methods>==--
}
namespace NW
{
	gfx_ent_skybox::gfx_ent_skybox(gfx_engine& graphics) :
		gfx_ent_mesh(graphics)
	{
		{
			// vertex buffer
			this->add_cmp(m_gfx->new_cmp<buf_vtx>(vtx_cube_3f));
			// index buffer
			this->add_cmp(m_gfx->new_cmp<buf_idx>(idx_cube));
		}
		// material
		{
			mem_ref<gfx_mtl> mtl = m_gfx->new_cmp<gfx_mtl>();
			// shaders
			{
				mem_ref<buf_shd> sbuf = m_gfx->get_cmp<buf_shd>(0);
				dstr shd_code;
				// vertex shader
				mtl->add_shd(m_gfx->new_cmp<a_shd, shd_vtx>(R"(nw_gfx/src_glsl/skybox_3d_vtx.glsl)"));
				mtl->set_buf(0, sbuf, 0);
				this->add_cmp(m_gfx->new_cmp<shd_layt>(mtl->get_shd(0), darray<data_elem>{
					data_elem("vti_vtx_crd", NTP_FLOAT32, 3, 0),
				} ));
				// pixel shader
				mtl->add_shd(m_gfx->new_cmp<a_shd, shd_pxl>(R"(nw_gfx/src_glsl/skybox_3d_pxl.glsl)"));
			}
			// textures
			{
				mem_ref<a_txr> txr = m_gfx->new_cmp<a_txr, txr_cube>();
				img_bmp img;
				if (!data_sys::get().load_file(R"(data\image\sb_0.bmp)", img)) { throw init_error(__FILE__, __LINE__); return; }
				if (!txr->remake(img)) { return; }
				txr->set_smp(m_gfx->get_cmp<txr_smp>(1));
				txr->set_slot(0);
				mtl->set_txr(1, txr, 0);
			}
			if (!mtl->remake()) { throw init_error(__FILE__, __LINE__); return; }
			this->add_cmp(mtl);
		}
		// states
		{
			mem_ref<gfx_stt_ds> dpt = m_gfx->new_cmp<gfx_stt_ds>();
			dpt->set_enabled(false);
			this->add_cmp(dpt);
		}
	}
	gfx_ent_skybox::~gfx_ent_skybox()
	{
	}
	// --==<core_methods>==--
	void gfx_ent_skybox::on_draw()
	{
		gfx_ent_mesh::on_draw();
	}
	// --==</core_methods>==--
}
#endif	// NW_GAPI