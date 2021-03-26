#ifndef NWG_BUFFER_H
#define NWG_BUFFER_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "../nwg_cmp.h"
#include <lib/nwg_const.h>
namespace NW
{
	class NW_API a_gfx_buf : public a_gfx_cmp
	{
	public:
#if (NW_GAPI & NW_GAPI_OGL)
		using handle = GLuint;
		using data_type = GLenum;
#endif
#if (NW_GAPI & NW_GAPI_DX)
		using handle = ID3D11Buffer*;
		using data_type = DXGI_FORMAT;
#endif
	public:
		a_gfx_buf(gfx_engine& graphics);
		virtual ~a_gfx_buf();
		// --getters
		inline size get_data_size() const { return m_data_size; }
		inline handle get_handle()	const { return m_handle; }
		// --setters
		virtual void set_data_bytes(size nof_bytes, cptr buffer, size offset = 0) = 0;
		template<typename dt>
		void set_data(const dt* buffer, size offset = 0) {
			set_data_bytes(sizeof(dt), buffer, offset);
		}
		template<typename dt>
		void set_data(v1ui count, const dt buffer, size offset = 0) {
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
		size m_data_size;
	};
}
#endif	// NW_GAPI
#endif	// NWG_BUFFER_H