#ifndef NWG_MESH_ENTITY_H
#define NWG_MESH_ENTITY_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "nwg_ent_idx.h"
#include <lib/nwg_data.h>
namespace NW
{
	/// graphics_entity_mehs class
	class NW_API gfx_ent_mesh : public gfx_ent_idx, public a_data_cmp
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
#endif	// NWG_MESH_ENTITY_H