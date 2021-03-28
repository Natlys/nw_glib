#ifndef NWGFX_PRIMITIVE_ENTITY_H
#define NWGFX_PRIMITIVE_ENTITY_H
#include "nwgfx_core.hpp"
#if (defined NW_GAPI)
#include "nwgfx_ent_mesh.h"
namespace NWGFX
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
namespace NWGFX
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
#endif	// NWGFX_PRIMITIVE_ENTITY_H