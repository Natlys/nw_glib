#ifndef NWG_VERTEX_BUFFER_H
#define NWG_VERTEX_BUFFER_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "nwg_buf.h"
namespace NW
{
	/// vertex_buffer class
	class NW_API buf_vtx : public t_cmp<buf_vtx>, public a_gfx_buf
	{
	public:
		buf_vtx(gfx_engine& graphics);
		buf_vtx(gfx_engine& graphics, size nof_bytes, cptr buffer, size stride, size offset = 0u);
		template<typename dt>
		explicit buf_vtx(gfx_engine& graphics, v1ui count, const dt* buffer, size offset = 0u) :
			buf_vtx(graphics, count * sizeof(dt), buffer, sizeof(dt), offset) { }
		template<typename dt>
		explicit buf_vtx(gfx_engine& graphics, const darray<dt>& buffer, size offset = 0u) :
			buf_vtx(graphics, buffer.size() * sizeof(dt), buffer.data(), sizeof(dt), offset) { }
		virtual ~buf_vtx();
		// --getters
		inline size get_stride_size() const { return m_stride; }
		inline size get_offset_size() const { return m_offset; }
		inline size get_data_count() const  { return (m_data_size - m_offset) / m_stride; }
		// --setters
		virtual void set_data_bytes(size nof_bytes, cptr buffer, size offset = 0u) override;
		// --core_methods
		virtual void on_draw() override;
		bit remake_bytes(size nof_bytes, cptr buffer, size stride, size offset = 0u);
		template<typename dt>
		bit remake(v1ui count, const dt* buffer = nullptr, size offset = 0u) {
			return remake_bytes(count * sizeof(dt), buffer, sizeof(dt), offset);
		}
		template<typename dt>
		bit remake(const darray<dt>& buffer, size offset = 0u) {
			return remake_bytes(buffer.size() * sizeof(dt), buffer, sizeof(dt), offset);
		}
	private:
		size m_stride;
		size m_offset;
	};
}
#endif	// NW_GAPI
#endif	// NWG_VERTEX_BUFFER_H