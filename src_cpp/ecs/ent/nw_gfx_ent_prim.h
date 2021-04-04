#ifndef NW_GFX_PRIMITIVE_ENTITY_H
#define NW_GFX_PRIMITIVE_ENTITY_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#include "nw_gfx_ent_mesh.h"
namespace NW
{
	/// graphics_entity_cube class
	class gfx_ent_cube : public gfx_ent_mesh
	{
	public:
		gfx_ent_cube(gfx_engine& graphics);
		gfx_ent_cube(gfx_engine& graphics, v1u mtl_id);
		~gfx_ent_cube();
		// --getters
		// --setters
		// --core_methods
		virtual void on_draw() override;
	private:
	};
}
namespace NW
{
	/// graphics_entity_skybox class
	class gfx_ent_skybox : public gfx_ent_mesh
	{
	public:
		gfx_ent_skybox(gfx_engine& graphics);
		~gfx_ent_skybox();
		// --getters
		// --setters
		// --core_methods
		virtual void on_draw() override;
	private:
	};
}
#endif	// NW_GAPI
#endif	// NW_GFX_PRIMITIVE_ENTITY_H
