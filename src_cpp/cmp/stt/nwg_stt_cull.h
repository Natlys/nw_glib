#ifndef NWG_CULL_STATE_H
#define NWG_CULL_STATE_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "nwg_stt.h"
namespace NW
{
	/// culling_state class
	class NW_API stt_cull : public a_gfx_stt
	{
	public:
		stt_cull(gfx_engine& graphics);
		~stt_cull();
		// --getters
		// --setters
		// --core_methods
		virtual void on_draw() override;
	private:
	};
}
#endif	// NW_GAPI
#endif	// NWG_CULL_STATE_H