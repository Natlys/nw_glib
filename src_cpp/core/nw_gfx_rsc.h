#ifndef NW_GFX_RESOURCE_H
#define NW_GFX_RESOURCE_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#include "lib/nw_gfx_const.h"
namespace NW
{
	/// abstract graphics_resource class
	class NW_API a_gfx_rsc
	{
	public:
		a_gfx_rsc(gfx_engine& graphics);
		virtual ~a_gfx_rsc();
		// --core_methods
		virtual void on_draw();
	protected:
		gfx_engine* m_gfx;
	};
}
#endif	// NW_GAPI
#endif	// NW_GFX_RESOURCE_H
