#ifndef NW_GFX_BUFFER_H
#define NW_GFX_BUFFER_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#	include "../nw_gfx_cmp.h"
#	include "mem/nw_mem_buf.h"
namespace NW
{
	/// graphics_buffer class
	class NW_API gfx_buf : public t_cmp<gfx_buf>, public a_gfx_cmp, public mem_buf
	{
	public:
		using gbuf_t = gfx_buf;
		using gbuf_tc = const gbuf_t;
#	if (NW_GAPI & NW_GAPI_OGL)
		using handle_t = GLuint;
#	endif
#	if (NW_GAPI & NW_GAPI_D3D)
		using handle_t = ID3D11Buffer*;
#	endif
		using handle_tc = const handle_t;
	public:
		gfx_buf();
		gfx_buf(layt_tc& layout, size_t count);
		gfx_buf(layt_tc& layout, size_t count, ptr_tc data);
		gfx_buf(gbuf_tc& copy);
		gfx_buf(gbuf_t&& copy);
		virtual ~gfx_buf();
		// --getters
		inline handle_t get_handle()        { return m_handle; }
		inline handle_tc get_handle() const { return m_handle; }
		// --setters
		inline gbuf_t& set_data() { mem_buf::set_data(); return *this; }
		inline gbuf_t& set_data(ptr_tc data) { mem_buf::set_data(data); return *this; }
		inline gbuf_t& set_data(size_t key, ptr_tc data) { mem_buf::set_data(key, data); return *this; }
		inline gbuf_t& set_data(ptr_tc data, size_t count) { mem_buf::set_data(data, count); return *this; }
		virtual buf_t& set_data(size_t key, ptr_tc data, size_t count) override;
		// --operators
		inline gbuf_t& operator=(gbuf_tc& copy) { NW_CHECK(remake(copy.get_layt(), copy.get_count(), copy.get_data()), "remake error!", return *this); return *this; }
		inline gbuf_t& operator=(gbuf_t&& copy) { NW_CHECK(remake(copy.get_layt(), copy.get_count(), copy.get_data()), "remake error!", return *this); return *this; }
		virtual op_stream_t& operator<<(op_stream_t& stm) const override;
		virtual ip_stream_t& operator>>(ip_stream_t& stm) override;
		// --core_methods
		inline v1bit remake(layt_tc& layout, size_t count) { return mem_buf::remake(layout, count); }
		inline v1bit remake(layt_tc& layout, size_t count, ptr_tc data) { return mem_buf::remake(layout, count, data); }
		virtual v1bit remake() override;
		virtual v1nil on_draw() override;
	protected:
		handle_t m_handle;
	};
}
#endif	// NW_GAPI
#endif	// NW_GFX_BUFFER_H
