#ifndef NW_TEXTURE_1D_H
#define NW_TEXTURE_1D_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "nwg_txr.h"
namespace NW
{
	/// texture_1d class
	/// description:
	class NW_API txr_1d : public a_txr
	{
	public:
		txr_1d(gfx_engine& graphics, cstr name);
		~txr_1d();
		// --getters
		// --setters
		// --core_methods
		virtual bit remake(const a_img& img);
		virtual void clear(ptr value) override;
		virtual void on_draw() override;
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const override;
		virtual stm_in& operator>>(stm_in& stm) override;
	private:
	};
}
#endif	// NW_GAPI
#endif	// NW_TEXTURE_3D_H