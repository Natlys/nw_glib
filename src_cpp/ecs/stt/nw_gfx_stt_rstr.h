#ifndef NW_GFX_RASTERISZER_STATE_H
#define NW_GFX_RASTERISZER_STATE_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#include "nw_gfx_stt.h"
namespace NW
{
	class NW_API gfx_stt_rstr : public a_gfx_stt
	{
#	if (NW_GAPI & NW_GAPI_OGL)
		using handle = GLuint;
#	endif
#	if (NW_GAPI & NW_GAPI_D3D)
		using handle = ID3D11RasterizerState*;
#	endif
	public:
		gfx_stt_rstr(gfx_engine& graphics);
		~gfx_stt_rstr();
		// --getters
		inline handle get_handle()            { return m_handle; }
		inline v4f get_view_rect() const      { return m_view_rect; }
		inline v4f get_scis_rect() const      { return m_scis_rect; }
		// --setters
		void set_filling(v1b is_front, v1b is_back, v1b is_solid_filling);
		void set_culling(v1b is_front, v1b is_back, v1b is_clock_culling);
		void set_multisample(v1b enable);
		// --predicates
		inline v1b is_front_filling() const { return m_is_front_filling; }
		inline v1b is_front_culling() const { return m_is_front_culling; }
		inline v1b is_back_filling() const  { return m_is_back_filling; }
		inline v1b is_back_culling() const  { return m_is_back_culling; }
		inline v1b is_solid_filling() const { return m_is_solid_filling; }
		inline v1b is_clock_culling() const { return m_is_clock_culling; }
		inline v1b is_multisample() const   { return m_is_multisample; }
		// --core_methods
		v1b remake();
		virtual void on_draw() override;
	private:
		handle m_handle;
		v1b m_is_front_filling;
		v1b m_is_front_culling;
		v1b m_is_back_filling;
		v1b m_is_back_culling;
		v1b m_is_solid_filling;
		v1b m_is_clock_culling;
		v1b m_is_multisample;
		v4f m_scis_rect;
		v4f m_view_rect;
	};
}
#endif	// NW_GAPI
#endif	// NW_GFX_RASTERISZER_STATE_H
