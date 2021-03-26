#ifndef NWG_SHADER_H
#define NWG_SHADER_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "../nwg_cmp.h"
#include "../txr/nwg_txr.h"
#include "../buf/nwg_buf_shd.h"
#include "nwg_shd_layt.h"
namespace NW
{
	class NW_API a_shd : public t_cmp<a_shd>, public a_gfx_cmp, public a_data_cmp
	{
	public:
		using txr = mem_ref<a_txr>;
		using buf = mem_ref<buf_shd>;
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
		inline bufs& get_bufs(v1ui idx)  { return m_bufs; }
		inline buf& get_buf(v1ui idx)    { return m_bufs[idx % m_bufs.size()]; }
		inline handle get_handle()       { return m_handle; }
		// --setters
		void set_buf(buf& ref, v1ui idx = 0);
		void set_txr(txr& ref, v1ui idx = 0);
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const = 0;
		virtual stm_in& operator>>(stm_in& stm) = 0;
		// --core_methods
		virtual bit remake(cstr source_code);
		virtual void on_draw() override;
	protected:
		handle m_handle;
		dstr m_src_code;
		bufs m_bufs;
		txrs m_txrs;
	};
	extern NW_API bit gfx_debug_shader(v1ui shd_id);
}
#endif	// NW_GAPI
#endif // NWG_SHADER_H