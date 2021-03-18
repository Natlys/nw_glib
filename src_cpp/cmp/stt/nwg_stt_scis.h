#ifndef NWG_SCISSOR_STATE_H
#define NWG_SCISSOR_STATE_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "nwg_stt.h"
namespace NW
{
	/// scissor_state class
	class NW_API stt_scis : public a_gfx_stt
	{
	public:
		stt_scis(gfx_engine& graphics);
		~stt_scis();
		// --getters
		// --setters
		// --core_methods
		virtual void on_draw() override;
	private:
		v2si  m_crd;
		v2si m_size;
	};
}
#endif	// NW_GAPI
#endif	// NWG_STENCIL_STATE_H