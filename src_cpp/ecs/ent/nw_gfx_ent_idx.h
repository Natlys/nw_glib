#ifndef NW_GFX_INDEXED_ENTITY_H
#define NW_GFX_INDEXED_ENTITY_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#include "../nw_gfx_ent.h"
namespace NW
{
	/// graphics_entity_indexed class
	class NW_API gfx_ent_idx : public a_gfx_ent
	{
	public:
		gfx_ent_idx(gfx_engine& graphics);
		virtual ~gfx_ent_idx();
		// --getters
		// --setters
		// --core_methods
		virtual void on_draw() override;
	};
}

#endif	// NW_GAPI
#endif	// NW_GFX_INDEXED_ENTITY_H
