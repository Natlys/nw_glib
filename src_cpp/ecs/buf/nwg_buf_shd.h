#ifndef NWG_SHADER_BUFFER_H
#define NWG_SHADER_BUFFER_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "nwg_buf.h"
namespace NW
{
	/// shader_buffer class
	/// description:
	/// --it is used by shaders as opengl uniform buffer, or as directx constant buffer;
	class NW_API buf_shd : public t_cmp<buf_shd>, public a_gfx_buf, public data_layt
	{
		using elem = data_elem;
		using elems = darray<elem>;
	public:
		buf_shd(gfx_engine& graphics);
		buf_shd(gfx_engine& graphics, size nof_bytes, cptr buffer, size offset = 0u);
		template<typename dt>
		buf_shd(gfx_engine& graphics, const dt* buffer, size offset = 0u) :
			buf_shd(graphics, sizeof(dt), buffer, offset) { }
		template<typename dt>
		buf_shd(gfx_engine& graphics, v1ui count, const dt* buffer, size offset = 0u) :
			buf_shd(graphics, count * sizeof(dt), buffer, offset) { }
		template<typename dt>
		buf_shd(gfx_engine& graphics, const darray<dt>& buffer, size offset = 0u) :
			buf_shd(graphics, buffer.size() * sizeof(dt), buffer.data(), offset) { }
		virtual ~buf_shd();
		// --getters
		inline v1ui get_slot() const  { return m_slot; }
		// --setters
		void set_slot(v1ui bind_slot);
		void set_offset(size offset);
		virtual void set_data_bytes(size nof_bytes, cptr buffer, size offset = 0) override;
		// --core_methods
		bit remake_bytes(size nof_bytes, cptr buffer = nullptr, size offset = 0u);
		template<typename dt>
		bit remake(const dt* buffer, size offset = 0) {
			return remake_bytes(sizeof(dt), buffer, offset);
		}
		template<typename dt>
		bit remake(v1ui count, const dt* buffer, size offset = 0) {
			return remake_bytes(count * sizeof(dt), buffer, offset);
		}
		template<typename dt>
		bit remake(const darray<dt>& buffer, size offset = 0) {
			return remake_bytes(buffer.size() * sizeof(dt), buffer.data(), offset);
		}
		virtual void on_draw() override;
	private:
		v1ui m_slot;
		size m_offset;
	};
}
#endif	// NW_GAPI
#endif	// NWG_SHADER_BUFFER_H