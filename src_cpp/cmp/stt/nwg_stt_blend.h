#ifndef NWG_BLEND_STATE_H
#define NWG_BLEND_STATE_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "nwg_stt.h"
namespace NW
{
	/// blend_state class
	class NW_API stt_blend : public a_gfx_stt
	{
	public:
		stt_blend(gfx_engine& graphics);
		~stt_blend();
		// --getters
		// --setters
		// --core_methods
		virtual void on_draw() override;
	};
}
#endif	// NW_GAPI
#endif	// NWG_BLEND_STATE_H