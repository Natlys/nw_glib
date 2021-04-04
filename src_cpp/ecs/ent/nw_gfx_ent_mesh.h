#ifndef NW_GFX_MESH_ENTITY_H
#define NW_GFX_MESH_ENTITY_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#include "nw_gfx_ent_idx.h"
#include "lib/nw_gfx_data.h"
#include "core/nw_core_mtx.h"
namespace NW
{
	/// graphics_entity_mesh class
	class NW_API gfx_ent_mesh : public gfx_ent_idx, public a_io_cmp
	{
	public:
		gfx_ent_mesh(gfx_engine& graphics);
		virtual ~gfx_ent_mesh();
		// --getters
		inline cv3f& get_scl() const   { return m_scl; }
		inline cv3f& get_rtn() const   { return m_rtn; }
		inline cv3f& get_crd() const   { return m_crd; }
		inline cm4f& get_tform() const { return m_tform; }
		// --setters
		gfx_ent_mesh& set_scl(cv3f& scl);
		gfx_ent_mesh& set_rtn(cv3f& rtn);
		gfx_ent_mesh& set_crd(cv3f& crd);
		gfx_ent_mesh& set_tform(cm4f& tform);
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const override;
		virtual stm_in& operator>>(stm_in& stm) override;
		// --core_methods
		void on_draw() override;
	private:
		v3f m_scl;
		v3f m_rtn;
		v3f m_crd;
		m4f m_tform;
	};
}
#endif	// NW_GAPI
#endif	// NW_GFX_MESH_ENTITY_H
