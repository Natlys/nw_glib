#ifndef NWG_PASS_H
#define NWG_PASS_H
#include <nwg_core.hpp>
#include <ecs/nwg_cmp.h>
#if (defined NW_GAPI)
namespace NW
{
	/// graphics_script class
	class gfx_pass : public t_cmp<gfx_pass>, public a_gfx_cmp
	{
	public:
		gfx_pass(gfx_engine& graphics);
		~gfx_pass();
		// --getters
		// --setters
		// --core_methods
		virtual void on_draw() override;
	private:
	};
}
#endif	// NW_GAPI
#endif  // NWG_PASS_H