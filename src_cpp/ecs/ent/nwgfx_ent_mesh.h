#ifndef NWGFX_MESH_ENTITY_H
#define NWGFX_MESH_ENTITY_H
#include "nwgfx_core.hpp"
#if (defined NW_GAPI)
#include "nwgfx_ent_idx.h"
#include "lib/nwgfx_data.h"
namespace NWGFX
{
	/// graphics_entity_mesh class
	class NW_API gfx_ent_mesh : public gfx_ent_idx, public a_io_cmp
	{
	public:
		gfx_ent_mesh(gfx_engine& graphics);
		virtual ~gfx_ent_mesh();
		// --getters
		inline const v3f& get_scl() const	{ return m_scl; }
		inline const v3f& get_rtn() const	{ return m_rtn; }
		inline const v3f& get_crd() const	{ return m_crd; }
		inline const m4f& get_tform() const { return m_tform; }
		// --setters
		void set_scl(const v3f& scl);
		void set_rtn(const v3f& rtn);
		void set_crd(const v3f& crd);
		void set_tform(const m4f& tform);
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
#endif	// NWGFX_MESH_ENTITY_H