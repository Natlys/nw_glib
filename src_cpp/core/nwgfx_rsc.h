#ifndef NWGFX_RESOURCE_H
#define NWGFX_RESOURCE_H
#include "nwgfx_core.hpp"
#if (defined NW_GAPI)
#include <lib/nwgfx_const.h>
namespace NWGFX
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
#endif	// NWGFX_RESOURCE_H