#ifndef NWG_VIEWPORT_STATE_H
#define NWG_VIEWPORT_STATE_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "nwg_stt.h"
namespace NW
{
	/// viewport_state class
	class NW_API stt_viewp : public a_gfx_stt
	{
	public:
		stt_viewp(gfx_engine& graphics);
		~stt_viewp();
		// --getters
		inline v2si get_coord() const	{ return m_crd; }
		inline v2si get_size() const	{ return m_size; }
		// --setters
		void set_coord(v2si coord);
		void set_size(v2si size);
		// --core_methods
		virtual void on_draw() override;
	private:
		v2si m_crd;
		v2si m_size;
	};
}
#endif	// NW_GAPI
#endif	// NWG_VIEWPORT_STATE_H