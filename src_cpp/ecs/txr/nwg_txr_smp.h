#ifndef NWG_TEXTURE_SAMPLER_H
#define NWG_TEXTURE_SAMPLER_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "../nwg_cmp.h"
#include <lib/nwg_const.h>
namespace NW
{
	/// txr_smp class
	class NW_API txr_smp : public t_cmp<txr_smp>, public a_gfx_cmp
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
		txr_smp(gfx_engine& graphics);
		txr_smp(gfx_engine& graphics, texture_filters filter, texture_wraps wrap_mode, v4f border_color = v4f{ 0.5f, 0.5f, 0.5f, 1.0f } );
		~txr_smp();
		// --getters
		inline handle get_handle()                { return m_handle; }
		inline v1ui get_slot() const              { return m_slot; }
		inline texture_wraps get_wrap() const     { return convert<wrap, texture_wraps>(m_wrap); }
		inline texture_filters get_filter() const { return convert<filter, texture_filters>(m_filter); }
		// --setters
		void set_slot(v1ui txr_slot);
		// --core_methods
		bit remake(texture_filters filter, texture_wraps wrap_mode, v4f border_color = v4f{ 0.5f, 0.5f, 0.5f, 1.0f });
		virtual void on_draw() override;
	private:
		handle m_handle;
		v1ui m_slot;
		wrap m_wrap;
		filter m_filter;
		v4f m_border_color;
	};
}
#endif	// NWG_GAPI
#endif	// NWG_TEXTURE_SAMPLER_H