#ifndef NW_GFX_VERTEXED_ENTITY_H
#define NW_GFX_VERTEXED_ENTITY_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#include "../nw_gfx_ent.h"
namespace NW
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
#endif	// NW_GFX_VERTEXED_ENTITY_H
