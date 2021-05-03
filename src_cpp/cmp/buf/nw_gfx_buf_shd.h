#ifndef NW_GFX_SHADER_BUFFER_H
#define NW_GFX_SHADER_BUFFER_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#	include "nw_gfx_buf.h"
#	include "mem/nw_mem_buf.h"
namespace NW
{
	/// shader_buffer class
	/// description:
	/// --it is used by shaders as opengl uniform buffer, or as directx constant buffer;
	class NW_API gfx_buf_shd : public gfx_buf
	{
	public:
		using gsbuf_t = gfx_buf_shd;
		using gsbuf_tc = const gsbuf_t;
	public:
		gfx_buf_shd();
		gfx_buf_shd(gsbuf_tc& copy);
		gfx_buf_shd(gsbuf_t&& copy);
		gfx_buf_shd(layt_tc& layout, size_t count);
		gfx_buf_shd(layt_tc& layout, size_t count, ptr_tc data);
		virtual ~gfx_buf_shd();
		// --getters
		inline cv1u get_slot() const { return m_slot; }
		// --setters
		gsbuf_t& set_slot(cv1u slot);
		inline gsbuf_t& set_data() { mem_buf::set_data(); return *this; }
		inline gsbuf_t& set_data(ptr_tc data) { mem_buf::set_data(data); return *this; }
		inline gsbuf_t& set_data(size_t key, ptr_tc data) { mem_buf::set_data(key, data); return *this; }
		inline gsbuf_t& set_data(ptr_tc data, size_t count) { mem_buf::set_data(data, count); return *this; }
		virtual buf_t& set_data(size_t key, ptr_tc data, size_t count) override;
		// --predicates
		// --operators
		inline gsbuf_t& operator=(gsbuf_tc& copy) { NW_CHECK(remake(copy.get_layt(), copy.get_count(), copy.get_data()), "remake error!", return *this); return set_slot(copy.get_slot()); }
		inline gsbuf_t& operator=(gsbuf_t&& copy) { NW_CHECK(remake(copy.get_layt(), copy.get_count(), copy.get_data()), "remake error!", return *this); return set_slot(copy.get_slot()); }
		virtual op_stream_t& operator<<(op_stream_t& stm) const override;
		virtual ip_stream_t& operator>>(ip_stream_t& stm) override;
		// --core_methods
		inline v1bit remake(layt_tc& layout, size_t count) { return gfx_buf::remake(layout, count); }
		inline v1bit remake(layt_tc& layout, size_t count, ptr_tc data) { return gfx_buf::remake(layout, count, data); }
		virtual v1bit remake() override;
		virtual v1nil on_draw() override;
	private:
		v1u m_slot;
	};
}
#endif	// NW_GAPI
#endif	// NW_GFX_SHADER_BUFFER_H
