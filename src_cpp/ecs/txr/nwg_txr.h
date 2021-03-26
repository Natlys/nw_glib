#ifndef NWG_TEXTURE_H
#define NWG_TEXTURE_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "../nwg_cmp.h"
#include "nwg_txr_smp.h"
#include <lib/nwg_img.h>
namespace NW
{
	/// abstarct texture class
	/// description:
	class NW_API a_txr : public t_cmp<a_txr>, public img_cmp, public a_gfx_cmp
	{
	public:
		using smp = mem_ref<txr_smp>;
#if (NW_GAPI & NW_GAPI_OGL)
		using handle = GLuint;
		using txr_fmt = GLenum;
		using pxl_fmt = GLenum;
#endif
#if (NW_GAPI & NW_GAPI_DX)
		using handle = ID3D11ShaderResourceView*;
		using txr_fmt = DXGI_FORMAT;
		using pxl_fmt = DXGI_FORMAT;
#endif
	public:
		a_txr(gfx_engine& graphics);
		virtual ~a_txr();
		// --getters
		inline handle get_handle()                  { return m_handle; }
		inline v1ui get_slot() const                { return m_slot; }
		inline smp& get_smp()                       { return m_smp; }
		inline pixel_formats get_pxl_fmt() const    { return convert<pxl_fmt, pixel_formats>(m_pxl_fmt); }
		inline texture_formats get_txr_fmt() const  { return convert<txr_fmt, texture_formats>(m_txr_fmt); }
		// --setters
		void set_slot(v1ui txr_slot);
		void set_smp(smp& ref);
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const = 0;
		virtual stm_in& operator>>(stm_in& stm) = 0;
		// --core_methods
		bit load_file(cstr file_path);
		bit save_file(cstr file_path);
		virtual bit remake(const img_cmp& img);
		virtual void clear(ptr value) = 0;
		virtual void on_draw() override;
	protected:
		handle m_handle;
		v1ui m_slot;
		smp m_smp;
		pxl_fmt m_pxl_fmt;
		txr_fmt m_txr_fmt;
	};
}
#endif	// NW_GAPI
#endif // NWG_TEXTURE_H