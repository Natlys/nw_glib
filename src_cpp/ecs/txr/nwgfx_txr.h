#ifndef NWGFX_TEXTURE_H
#define NWGFX_TEXTURE_H
#include "nwgfx_core.hpp"
#if (defined NW_GAPI)
#include "../nwgfx_cmp.h"
#include "nwgfx_txr_smp.h"
#include "lib/nwgfx_img.h"
namespace NWGFX
{
	/// abstarct texture_component class
	/// description:
	class NW_API a_gfx_txr : public t_cmp<a_gfx_txr>, public a_img_cmp, public a_gfx_cmp
	{
	public:
		using smp = mem_ref<gfx_txr_smp>;
#if (NW_GAPI & NW_GAPI_OGL)
		using handle = GLuint;
		using gfx_txrfmt = GLenum;
		using pxl_fmt = GLenum;
#endif
#if (NW_GAPI & NW_GAPI_DX)
		using handle = ID3D11ShaderResourceView*;
		using gfx_txrfmt = DXGI_FORMAT;
		using pxl_fmt = DXGI_FORMAT;
#endif
	public:
		a_gfx_txr(gfx_engine& graphics);
		virtual ~a_gfx_txr();
		// --getters
		inline handle get_handle()                  { return m_handle; }
		inline v1u get_slot() const                 { return m_slot; }
		inline smp& get_smp()                       { return m_smp; }
		inline texture_formats get_gfx_txrfmt() const  { return convert<gfx_txrfmt, texture_formats>(m_gfx_txrfmt); }
		inline pixel_formats get_pxl_fmt() const    { return convert<pxl_fmt, pixel_formats>(m_pxl_fmt); }
		// --setters
		void set_slot(v1u gfx_txrslot);
		void set_smp(smp& ref);
		void set_gfx_txrfmt(texture_formats format);
		void set_pxl_fmt(pixel_formats format);
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const = 0;
		virtual stm_in& operator>>(stm_in& stm) = 0;
		// --core_methods
		v1b load_file(cstr file_path);
		v1b save_file(cstr file_path);
		virtual v1b remake(const a_img_cmp& img);
		virtual void clear(ptr value) = 0;
		virtual void on_draw() override;
	protected:
		handle m_handle;
		v1u m_slot;
		smp m_smp;
		gfx_txrfmt m_gfx_txrfmt;
		pxl_fmt m_pxl_fmt;
	};
}
#endif	// NW_GAPI
#endif // NWGFX_TEXTURE_H