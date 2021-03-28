#ifndef NWGFX_BLEND_STATE_H
#define NWGFX_BLEND_STATE_H
#include "nwgfx_core.hpp"
#if (defined NW_GAPI)
#include "nwgfx_stt.h"
namespace NWGFX
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
#endif	// NWGFX_BLEND_STATE_H