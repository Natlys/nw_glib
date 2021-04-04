#ifndef NW_GFX_BUFFER_H
#define NW_GFX_BUFFER_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#include "../nw_gfx_cmp.h"
#include "lib/nw_gfx_const.h"
namespace NW
{
	class NW_API a_gfx_buf : public a_gfx_cmp
	{
	public:
#if (NW_GAPI & NW_GAPI_OGL)
		using handle = GLuint;
		using data_type = GLenum;
#endif
#if (NW_GAPI & NW_GAPI_D3D)
		using handle = ID3D11Buffer*;
		using data_type = DXGI_FORMAT;
#endif
	public:
		a_gfx_buf(gfx_engine& graphics);
		virtual ~a_gfx_buf();
		// --getters
		inline handle get_handle()	   { return m_handle; }
		inline size get_size() const   { return m_size; }
		inline size get_stride() const { return m_stride; }
		inline size get_count() const  { return m_size / m_stride; }
		inline size get_offset() const { return m_offset; }
		// --setters
		virtual void set_data_bytes(size nof_bytes, cptr buffer, size offset = 0) = 0;
		template<typename dt>
		void set_data(const dt* buffer, size offset = 0) {
			set_data_bytes(sizeof(dt), buffer, offset);
		}
		template<typename dt>
		void set_data(v1u count, const dt buffer, size offset = 0) {
			set_data_bytes(count * sizeof(dt), buffer, offset);
		}
		template<typename dt>
		void set_data(const darray<dt>& buffer, size offset = 0) {
			set_data_bytes(buffer.size() * sizeof(dt), buffer.data(), offset);
		}
		// --core_methods
		virtual void on_draw() = 0;
	protected:
		handle m_handle;
		size m_size;
		size m_stride;
		size m_offset;
	};
}
#endif	// NW_GAPI
#endif	// NW_GFX_BUFFER_H
