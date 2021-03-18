#ifndef NWG_SHADER_RESOURCE_H
#define NWG_SHADER_RESOURCE_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include <core/nwg_cmp.h>
namespace NW
{
	class NW_API a_shd_rsc : public a_gfx_cmp
	{
	public:
		a_shd_rsc(gfx_engine& graphics);
		virtual ~a_shd_rsc();
		// --getters
		// --setters
		// --core_methods
		virtual void on_draw() = 0;
	private:
	};
}
#endif	// NW_GAPI
#endif	// NWG_SHADER_RESOURCE_H