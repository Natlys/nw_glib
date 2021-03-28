#ifndef NWGFX_SHADER_H
#define NWGFX_SHADER_H
#include "nwgfx_core.hpp"
#if (defined NW_GAPI)
#include "../nwgfx_cmp.h"
#include "../txr/nwgfx_txr.h"
#include "../buf/nwgfx_buf_shd.h"
#include "nwgfx_shd_layt.h"
namespace NWGFX
{
	class NW_API a_shd : public t_cmp<a_shd>, public a_gfx_cmp, public a_io_cmp
	{
	public:
		using txr = mem_ref<a_gfx_txr>;
		using buf = mem_ref<gfx_buf_shd>;
		using txrs = darray<txr>;
		using bufs = darray<buf>;
#if (NW_GAPI & NW_GAPI_OGL)
		using handle = GLuint;
#endif
#if (NW_GAPI & NW_GAPI_DX)
		using handle = ID3DBlob*;
#endif
	public:
		a_shd(gfx_engine& graphics);
		virtual ~a_shd();
		// --getters
		inline cstr get_src_code() const { return &m_src_code[0]; }
		inline bufs& get_bufs(v1u idx)  { return m_bufs; }
		inline buf& get_buf(v1u idx)    { return m_bufs[idx % m_bufs.size()]; }
		inline handle get_handle()       { return m_handle; }
		// --setters
		void set_buf(buf& ref, v1u idx = 0);
		void set_txr(txr& ref, v1u idx = 0);
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const = 0;
		virtual stm_in& operator>>(stm_in& stm) = 0;
		// --core_methods
		virtual v1b remake(cstr source_code);
		virtual void on_draw() override;
	protected:
		handle m_handle;
		dstr m_src_code;
		bufs m_bufs;
		txrs m_txrs;
	};
}
#endif	// NW_GAPI
#endif // NWGFX_SHADER_H