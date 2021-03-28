#ifndef NWGFX_INDEXED_ENTITY_H
#define NWGFX_INDEXED_ENTITY_H
#include "nwgfx_core.hpp"
#if (defined NW_GAPI)
#include "../nwgfx_ent.h"
namespace NWGFX
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
#endif	// NWGFX_INDEXED_ENTITY_H