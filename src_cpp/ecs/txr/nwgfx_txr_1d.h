#ifndef NW_TEXTURE_1D_H
#define NW_TEXTURE_1D_H
#include "nwgfx_core.hpp"
#if (defined NW_GAPI)
#include "nwgfx_txr.h"
namespace NWGFX
{
	/// texture_1d class
	/// description:
	class NW_API gfx_txr_1d : public a_gfx_txr
	{
	public:
		gfx_txr_1d(gfx_engine& graphics);
		~gfx_txr_1d();
		// --getters
		// --setters
		// --core_methods
		virtual v1b remake(const a_img_cmp& img);
		virtual void clear(ptr value) override;
		virtual void on_draw() override;
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const override;
		virtual stm_in& operator>>(stm_in& stm) override;
	private:
#if (NW_GAPI & NW_GAPI_DX)
		ID3D11Texture1D* m_native;
#endif
	};
}
#endif	// NW_GAPI
#endif	// NW_TEXTURE_3D_H