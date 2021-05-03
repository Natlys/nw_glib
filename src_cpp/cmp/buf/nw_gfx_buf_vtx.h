#ifndef NW_GFX_VERTEX_BUFFER_H
#define NW_GFX_VERTEX_BUFFER_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#	include "nw_gfx_buf.h"
#	include "mem/nw_mem_buf.h"
namespace NW
{
	/// vertex_buffer class
	class NW_API gfx_buf_vtx : public gfx_buf
	{
	public:
		using gvbuf_t = gfx_buf_vtx;
		using gvbuf_tc = const gvbuf_t;
	public:
		gfx_buf_vtx();
		gfx_buf_vtx(gvbuf_tc& copy);
		gfx_buf_vtx(gvbuf_t&& copy);
		gfx_buf_vtx(layt_tc& layout, size_t count);
		gfx_buf_vtx(layt_tc& layout, size_t count, ptr_tc data);
		virtual ~gfx_buf_vtx();
		// --getters
		// --setters
		inline gvbuf_t& set_data() { mem_buf::set_data(); return *this; }
		inline gvbuf_t& set_data(ptr_tc data) { mem_buf::set_data(data); return *this; }
		inline gvbuf_t& set_data(size_t key, ptr_tc data) { mem_buf::set_data(key, data); return *this; }
		inline gvbuf_t& set_data(ptr_tc data, size_t count) { mem_buf::set_data(data, count); return *this; }
		virtual buf_t& set_data(size_t key, ptr_tc data, size_t count) override;
		// --predicates
		// --operators
		inline gvbuf_t& operator=(gvbuf_tc& copy) { NW_CHECK(remake(copy.get_layt(), copy.get_count(), copy.get_data()), "remake error!", return *this); return *this; }
		inline gvbuf_t& operator=(gvbuf_t&& copy) { NW_CHECK(remake(copy.get_layt(), copy.get_count(), copy.get_data()), "remake error!", return *this); return *this; }
		virtual op_stream_t& operator<<(op_stream_t& stm) const override;
		virtual ip_stream_t& operator>>(ip_stream_t& stm) override;
		// --core_methods
		inline v1bit remake(layt_tc& layout, size_t count) { return gfx_buf::remake(layout, count); }
		inline v1bit remake(layt_tc& layout, size_t count, ptr_tc data) { return gfx_buf::remake(layout, count, data); }
		virtual v1bit remake() override;
		virtual v1nil on_draw() override;
	};
}
#endif	// NW_GAPI
#endif	// NW_GFX_VERTEX_BUFFER_H
