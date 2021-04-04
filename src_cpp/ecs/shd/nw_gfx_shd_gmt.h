#ifndef NW_GFX_GEOMETRY_SHADER_H
#define NW_GFX_GEOMETRY_SHADER_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#include "nw_gfx_shd.h"
namespace NW
{
	class NW_API shd_gmt : public a_shd
	{
	public:
		shd_gmt(gfx_engine& graphics);
		shd_gmt(gfx_engine& graphics, cstr source_code);
		~shd_gmt();
		// --getters
		// --setters
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const override;
		virtual stm_in& operator>>(stm_in& stm) override;
		// --core_methods
		virtual v1b remake(cstr source_code) override;
		virtual void on_draw() override;
	private:
#if(NW_GAPI & NW_GAPI_D3D)
		ID3D11GeometryShader* m_native;
#endif
	};
}
#endif	// NW_GAPI
#endif // NW_GFX_GEOMETRY_SHADER_H
