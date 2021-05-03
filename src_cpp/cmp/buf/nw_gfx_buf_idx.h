#ifndef NW_GFX_INDEX_BUFFER_H
#define NW_GFX_INDEX_BUFFER_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#	include "nw_gfx_buf.h"
namespace NW
{
	/// index_buffer class
	class NW_API gfx_buf_idx : public gfx_buf
	{
	public:
		using gibuf_t = gfx_buf_idx;
		using gibuf_tc = const gibuf_t;
	public:
		gfx_buf_idx();
		gfx_buf_idx(layt_tc& layout, size_t count);
		gfx_buf_idx(layt_tc& layout, size_t count, ptr_tc data);
		gfx_buf_idx(gibuf_tc& copy);
		gfx_buf_idx(gibuf_t&& copy);
		virtual ~gfx_buf_idx();
		// --getters
		// --setters
		inline gibuf_t& set_data() { mem_buf::set_data(); return *this; }
		inline gibuf_t& set_data(ptr_tc data) { mem_buf::set_data(data); return *this; }
		inline gibuf_t& set_data(size_t key, ptr_tc data) { mem_buf::set_data(key, data); return *this; }
		inline gibuf_t& set_data(ptr_tc data, size_t count) { mem_buf::set_data(data, count); return *this; }
		virtual buf_t& set_data(size_t key, ptr_tc data, size_t space) override;
		// --predicates
		// --operators
		inline gibuf_t& operator=(gibuf_tc& copy) { NW_CHECK(remake(copy.get_layt(), copy.get_count(), copy.get_data()), "remake error!", return *this); return *this; }
		inline gibuf_t& operator=(gibuf_t&& copy) { NW_CHECK(remake(copy.get_layt(), copy.get_count(), copy.get_data()), "remake error!", return *this); return *this; }
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
#endif	// NW_INDEX_BUFFER_H