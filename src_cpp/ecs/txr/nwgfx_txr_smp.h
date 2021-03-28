#ifndef NWGFX_TEXTURE_SAMPLER_H
#define NWGFX_TEXTURE_SAMPLER_H
#include "nwgfx_core.hpp"
#if (defined NW_GAPI)
#include "../nwgfx_cmp.h"
#include <lib/nwgfx_const.h>
namespace NWGFX
{
	/// gfx_txr_smp class
	class NW_API gfx_txr_smp : public t_cmp<gfx_txr_smp>, public a_gfx_cmp
	{
	public:
#if (NW_GAPI & NW_GAPI_OGL)
		using handle = GLuint;
		using wrap = GLenum;
		using filter = GLenum;
#endif
#if (NW_GAPI & NW_GAPI_DX)
		using handle = ID3D11SamplerState*;
		using wrap = D3D11_TEXTURE_ADDRESS_MODE;
		using filter = D3D11_FILTER;
#endif
	public:
		gfx_txr_smp(gfx_engine& graphics);
		gfx_txr_smp(gfx_engine& graphics, texture_filters filter, texture_wraps wrap_mode, v4f border_color = v4f{ 0.5f, 0.5f, 0.5f, 1.0f } );
		~gfx_txr_smp();
		// --getters
		inline handle get_handle()                { return m_handle; }
		inline v1u get_slot() const               { return m_slot; }
		inline texture_wraps get_wrap() const     { return convert<wrap, texture_wraps>(m_wrap); }
		inline texture_filters get_filter() const { return convert<filter, texture_filters>(m_filter); }
		// --setters
		void set_slot(v1u gfx_txrslot);
		// --core_methods
		v1b remake(texture_filters filter, texture_wraps wrap_mode, v4f border_color = v4f{ 0.5f, 0.5f, 0.5f, 1.0f });
		virtual void on_draw() override;
	private:
		handle m_handle;
		v1u m_slot;
		wrap m_wrap;
		filter m_filter;
		v4f m_border_color;
	};
}
#endif	// NWGFX_GAPI
#endif	// NWGFX_TEXTURE_SAMPLER_H