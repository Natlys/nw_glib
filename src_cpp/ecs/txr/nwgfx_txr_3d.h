#ifndef NWGFX_TEXTURE_3D_H
#define NWGFX_TEXTURE_3D_H
#include "nwgfx_core.hpp"
#if (defined NW_GAPI)
#include "nwgfx_txr.h"
namespace NWGFX
{
	/// gfx_txr_cube class
	/// description:
	class NW_API gfx_txr_cube : public a_gfx_txr
	{
	public:
		gfx_txr_cube(gfx_engine& graphics);
		~gfx_txr_cube();
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const override;
		virtual stm_in& operator>>(stm_in& stm) override;
		// --core_methods
		virtual v1b remake(const a_img_cmp& img) override;
		virtual void clear(ptr value) override;
		virtual void on_draw() override;
	private:
#if (NW_GAPI & NW_GAPI_DX)
		ID3D11Texture3D * m_native;
#endif
	};
}
#endif	// NW_GAPI
#endif	// NWGFX_TEXTURE_3D_H