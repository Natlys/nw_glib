#ifndef NWG_PRIMITIVE_ENTITY_H
#define NWG_PRIMITIVE_ENTITY_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "nwg_ent_mesh.h"
namespace NW
{
	/// graphics_entity_cube class
	class gfx_ent_cube : public gfx_ent_mesh
	{
	public:
		gfx_ent_cube(gfx_engine& graphics);
		gfx_ent_cube(gfx_engine& graphics, v1ui mtl_id);
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
#endif	// NWG_PRIMITIVE_ENTITY_H