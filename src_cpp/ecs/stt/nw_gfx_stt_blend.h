#ifndef NW_GFX_BLEND_STATE_H
#define NW_GFX_BLEND_STATE_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#include "nw_gfx_stt.h"
namespace NW
{
	/// blend_state class
	class NW_API gfx_stt_blend : public a_gfx_stt
	{
	public:
		gfx_stt_blend(gfx_engine& graphics);
		~gfx_stt_blend();
		// --getters
		// --setters
		// --core_methods
		v1b remake();
		virtual void on_draw() override;
	};
}
#endif	// NW_GAPI
#endif	// NW_GFX_BLEND_STATE_H
