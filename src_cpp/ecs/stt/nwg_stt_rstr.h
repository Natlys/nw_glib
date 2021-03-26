#ifndef NWG_RASTERISZER_STATE_H
#define NWG_RASTERISZER_STATE_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "nwg_stt.h"
namespace NW
{
	class NW_API gfx_stt_rstr : public a_gfx_stt
	{
#	if (NW_GAPI & NW_GAPI_OGL)
		using handle = GLuint;
		using filling = GLenum;
		using culling = GLenum;
		using view_rect = v4f;
		using scis_rect = v4f;
#	endif
#	if (NW_GAPI & NW_GAPI_DX)
		using handle = ID3D11RasterizerState*;
		using filling = D3D11_FILL_MODE;
		using culling = D3D11_CULL_MODE;
		using view_rect = D3D11_VIEWPORT;
		using scis_rect = D3D11_RECT;
#	endif
	public:
		gfx_stt_rstr(gfx_engine& graphics);
		~gfx_stt_rstr();
		// --getters
		inline handle get_handle()            { return m_handle; }
		inline fill_modes get_filling()	const { return convert<filling, fill_modes>(m_filling); }
		inline cull_modes get_culling() const { return convert<culling, cull_modes>(m_culling); }
		inline v4f get_view_rect() const      { return v4f{ m_view_rect.TopLeftY, m_view_rect.TopLeftY, m_view_rect.Width, m_view_rect.Height }; }
		inline v4f get_scis_rect() const      { return v4f{ m_scis_rect.left, m_scis_rect.top, m_scis_rect.right, m_scis_rect.bottom }; }
		// --setters
		void set_filling(fill_modes mode);
		void set_culling(cull_modes mode);
		// --core_methods
		bit remake();
		virtual void on_draw() override;
	private:
		handle m_handle;
		filling m_filling;
		culling m_culling;
		scis_rect m_scis_rect;
		view_rect m_view_rect;
	};
}
#endif	// NW_GAPI
#endif	// NWG_RASTERISZER_STATE_H