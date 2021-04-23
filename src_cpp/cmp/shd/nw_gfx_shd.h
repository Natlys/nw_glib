#ifndef NW_GFX_SHADER_H
#define NW_GFX_SHADER_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#	include "../nw_gfx_cmp.h"
#	include "..//txr/nw_gfx_txr.h"
#	include "../buf/nw_gfx_buf_shd.h"
namespace NW
{
	class NW_API a_gfx_shd : public t_cmp<a_gfx_shd>, public a_gfx_cmp, public a_iop_cmp
	{
	public:
		using source_t = dstr_t;
		using source_tc = const source_t;
		using txr_t = mem_ref<a_gfx_txr>;
		using txr_tc = const txr_t;
		using buf_t = mem_ref<gfx_buf_shd>;
		using buf_tc = const buf_t;
		using txrs_t = t_darray<txr_t>;
		using txrs_tc = const txrs_t;
		using bufs_t = t_darray<buf_t>;
		using bufs_tc = const bufs_t;
#	if (NW_GAPI & NW_GAPI_OGL)
		using handle_t = GLuint;
#	endif
#	if (NW_GAPI & NW_GAPI_D3D)
		using handle_t = ID3DBlob*;
#	endif
		using handle_tc = const handle_t;
	public:
		a_gfx_shd();
		a_gfx_shd(source_tc& source);
		virtual ~a_gfx_shd();
		// --getters
		inline handle_t get_handle()        { return m_handle; }
		inline handle_tc get_handle() const { return m_handle; }
		inline source_t& get_source()        { return m_source; }
		inline source_tc& get_source() const { return m_source; }
		inline bufs_t& get_bufs(cv1u key)        { return m_bufs; }
		inline bufs_tc& get_bufs(cv1u key) const { return m_bufs; }
		inline buf_t& get_buf(cv1u key)        { return m_bufs[key]; }
		inline buf_tc& get_buf(cv1u key) const { return m_bufs[key]; }
		// --setters
		v1nil set_source(source_tc& source);
		v1nil set_buf(buf_t& ref, cv1u key = NW_NULL);
		v1nil set_txr(txr_t& ref, cv1u key = NW_NULL);
		// --predicates
		inline v1bit has_buf(cv1u key = NW_NULL) const { return m_bufs.size() > key; }
		inline v1bit has_txr(cv1u key = NW_NULL) const { return m_txrs.size() > key; }
		// --operators
		virtual op_stream_t& operator<<(op_stream_t& stm) const = 0;
		virtual ip_stream_t& operator>>(ip_stream_t& stm) = 0;
		// --core_methods
		virtual v1bit remake();
		inline v1bit remake(source_tc& source) { set_source(source); return remake(); }
		virtual v1nil on_draw() override;
	protected:
		handle_t m_handle;
		source_t m_source;
		bufs_t m_bufs;
		txrs_t m_txrs;
	};
}
#endif	// NW_GAPI
#endif // NW_GFX_SHADER_H
