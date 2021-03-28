#ifndef NWGFX_STATE_H
#define NWGFX_STATE_H
#include "nwgfx_core.hpp"
#if (defined NW_GAPI)
#include "../nwgfx_cmp.h"
#include <lib/nwgfx_const.h>
namespace NWGFX
{
	class NW_API a_gfx_stt : public t_cmp<a_gfx_stt>, public a_gfx_cmp
	{
	public:
		a_gfx_stt(gfx_engine& graphics);
		virtual ~a_gfx_stt();
		// --getters
		// --setters
		// --predicates
	protected:
		v1b m_is_enabled;
	};
}
#endif	// NW_GAPI
#endif	// NWGFX_STATE_H