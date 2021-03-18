#ifndef NWG_DRAW_STATE_H
#define NWG_DRAW_STATE_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "nwg_stt.h"
namespace NW
{
	/// draw_state class
	class NW_API stt_draw : public a_gfx_stt
	{
	public:
#if (NW_GAPI & NW_GAPI_OGL)
		using primitive = gfx_primitives;
#endif
#if (NW_GAPI & NW_GAPI_DX)
		using primitive = gfx_primitives;
#endif
	public:
		stt_draw(gfx_engine& graphics);
		~stt_draw();
		// --getters
		inline primitive get_primitive() const	{ return m_prim; }
		// --setters
		void set_primitive(gfx_primitives primitive_topology);
		// --core_methods
		virtual void on_draw() override;
	private:
		primitive m_prim;
	};
}
#endif	// NW_GAPI
#endif	// NWG_DRAW_STATE_H