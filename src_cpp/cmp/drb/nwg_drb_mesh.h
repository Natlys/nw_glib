#ifndef NW_DRAWABLE_MESH_H
#define NW_DRAWABLE_MESH_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "nwg_drb_idx.h"
#include <lib/nwg_data.h>
namespace NW
{
	class NW_API drb_mesh : public drb_idx, public a_data_rsc
	{
	public:
		drb_mesh(gfx_engine& graphics);
		~drb_mesh();
		// --getters
		// --setters
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const override;
		virtual stm_in& operator>>(stm_in& stm) override;
		// --core_methods
	};
}
#endif	// NW_GAPI
#endif	// NW_DRAWABLE_MESH_H