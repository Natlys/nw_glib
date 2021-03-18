#ifndef NWG_INDEXED_DRAWABLE_H
#define NWG_INDEXED_DRAWABLE_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "nwg_drb.h"
#include <cmp/buf/nwg_buf_idx.h>
namespace NW
{
	/// indexed drb class
	class NW_API drb_idx : public a_drb
	{
		using buffer = mem_ref<buf_idx>;
	public:
		drb_idx(gfx_engine& graphics);
		virtual ~drb_idx();
		// --getters
		buffer& get_buf() { return m_ibuf; }
		// --setters
		// --core_methods
		virtual void on_draw() override;
	private:
		buffer m_ibuf;
	};
}

#endif	// NW_GAPI
#endif	// NWG_INDEXED_DRAWABLE_H