#ifndef NW_GFX_DRAW_STATE_H
#define NW_GFX_DRAW_STATE_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#include "nw_gfx_stt.h"
namespace NW
{
	/// draw_state class
	class NW_API gfx_stt_draw : public a_gfx_stt
	{
	public:
		gfx_stt_draw(gfx_engine& graphics);
		~gfx_stt_draw();
		// --getters
		// --setters
		// --core_methods
		virtual void on_draw() override;
	private:
	};
}
#endif	// NW_GAPI
#endif	// NW_GFX_DRAW_STATE_H
