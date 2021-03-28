#ifndef NWGFX_COMPONENT_H
#define NWGFX_COMPONENT_H
#include "nwgfx_core.hpp"
#if (defined NW_GAPI)
#include "../core/nwgfx_rsc.h"
namespace NWGFX
{
	/// abstract graphics_component class
	class NW_API a_gfx_cmp : public a_gfx_rsc
	{
	protected:
		a_gfx_cmp(gfx_engine& graphics);
	public:
		virtual ~a_gfx_cmp();
		// --core_methods
		virtual void on_draw();
	};
}
#endif	// NW_GAPI
#endif	// NWGFX_COMPONENT_H