#ifndef NW_GFX_STATE_H
#define NW_GFX_STATE_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#include "../nw_gfx_cmp.h"
#include "lib/nw_gfx_const.h"
namespace NW
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
#endif	// NW_GFX_STATE_H
