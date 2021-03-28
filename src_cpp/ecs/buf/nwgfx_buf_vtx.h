#ifndef NWGFX_VERTEX_BUFFER_H
#define NWGFX_VERTEX_BUFFER_H
#include "nwgfx_core.hpp"
#if (defined NW_GAPI)
#include "nwgfx_buf.h"
namespace NWGFX
{
	/// vertex_buffer class
	class NW_API gfx_buf_vtx : public t_cmp<gfx_buf_vtx>, public a_gfx_buf
	{
	public:
		gfx_buf_vtx(gfx_engine& graphics);
		gfx_buf_vtx(gfx_engine& graphics, size nof_bytes, cptr buffer, size stride, size offset = 0u);
		template<typename dt>
		explicit gfx_buf_vtx(gfx_engine& graphics, v1u count, const dt* buffer, size offset = 0u) :
			gfx_buf_vtx(graphics, count * sizeof(dt), buffer, sizeof(dt), offset) { }
		template<typename dt>
		explicit gfx_buf_vtx(gfx_engine& graphics, const darray<dt>& buffer, size offset = 0u) :
			gfx_buf_vtx(graphics, buffer.size() * sizeof(dt), buffer.data(), sizeof(dt), offset) { }
		virtual ~gfx_buf_vtx();
		// --setters
		virtual void set_data_bytes(size nof_bytes, cptr buffer, size offset = 0u) override;
		// --core_methods
		virtual void on_draw() override;
		v1b remake_bytes(size nof_bytes, cptr buffer, size stride, size offset = 0u);
		template<typename dt>
		v1b remake(v1u count, const dt* buffer = nullptr, size offset = 0u) {
			return remake_bytes(count * sizeof(dt), buffer, sizeof(dt), offset);
		}
		template<typename dt>
		v1b remake(const darray<dt>& buffer, size offset = 0u) {
			return remake_bytes(buffer.size() * sizeof(dt), buffer, sizeof(dt), offset);
		}
	};
}
#endif	// NW_GAPI
#endif	// NWGFX_VERTEX_BUFFER_H