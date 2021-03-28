#ifndef NWGFX_VERTEXED_ENTITY_H
#define NWGFX_VERTEXED_ENTITY_H
#include "nwgfx_core.hpp"
#if (defined NW_GAPI)
#include "../nwgfx_ent.h"
namespace NWGFX
{
	/// graphics_entity_vertexed class
	class NW_API gfx_ent_vtx : public a_gfx_ent
	{
	public:
		gfx_ent_vtx(gfx_engine& graphics);
		virtual ~gfx_ent_vtx();
		// --getters
		// --setters
		// --core_methods
		virtual void on_draw() override;
	};
}
#endif	// NW_GAPI
#endif	// NWGFX_VERTEXED_ENTITY_H