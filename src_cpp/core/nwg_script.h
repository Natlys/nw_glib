#ifndef NWG_SCRIPT_H
#define NWG_SCRIPT_H
#include <nwg_core.hpp>
#include <ecs/nwg_cmp.h>
#if (defined NW_GAPI)
namespace NW
{
	/// graphics_script class
	class gfx_script : public t_cmp<gfx_script>, public a_gfx_cmp
	{
		using step = darray<mem_ref<a_gfx_cmp>>;
	public:
		gfx_script(gfx_engine& graphics);
		~gfx_script();
		// --getters
		// --setters
		// --core_methods
		virtual void on_draw() override;
	private:
	};
}
#endif	// NW_GAPI
#endif  // NWG_SCRIPT_H