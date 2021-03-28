#ifndef NWGFX_SHADER_BUFFER_H
#define NWGFX_SHADER_BUFFER_H
#include "nwgfx_core.hpp"
#if (defined NW_GAPI)
#include "nwgfx_buf.h"
namespace NWGFX
{
	/// shader_buffer class
	/// description:
	/// --it is used by shaders as opengl uniform buffer, or as directx constant buffer;
	class NW_API gfx_buf_shd : public t_cmp<gfx_buf_shd>, public a_gfx_buf, public vlayout
	{
	public:
		gfx_buf_shd(gfx_engine& graphics);
		gfx_buf_shd(gfx_engine& graphics, size nof_bytes, cptr buffer, size offset = 0u);
		template<typename dt>
		gfx_buf_shd(gfx_engine& graphics, const dt* buffer, size offset = 0u) :
			gfx_buf_shd(graphics, sizeof(dt), buffer, offset) { }
		template<typename dt>
		gfx_buf_shd(gfx_engine& graphics, v1u count, const dt* buffer, size offset = 0u) :
			gfx_buf_shd(graphics, count * sizeof(dt), buffer, offset) { }
		template<typename dt>
		gfx_buf_shd(gfx_engine& graphics, const darray<dt>& buffer, size offset = 0u) :
			gfx_buf_shd(graphics, buffer.size() * sizeof(dt), buffer.data(), offset) { }
		virtual ~gfx_buf_shd();
		// --getters
		inline v1u get_slot() const  { return m_slot; }
		// --setters
		void set_slot(v1u bind_slot);
		void set_offset(size offset);
		virtual void set_data_bytes(size nof_bytes, cptr buffer, size offset = 0) override;
		// --core_methods
		v1b remake_bytes(size nof_bytes, cptr buffer = nullptr, size offset = 0u);
		template<typename dt>
		v1b remake(const dt* buffer, size offset = 0) {
			return remake_bytes(sizeof(dt), buffer, offset);
		}
		template<typename dt>
		v1b remake(v1u count, const dt* buffer, size offset = 0) {
			return remake_bytes(count * sizeof(dt), buffer, offset);
		}
		template<typename dt>
		v1b remake(const darray<dt>& buffer, size offset = 0) {
			return remake_bytes(buffer.size() * sizeof(dt), buffer.data(), offset);
		}
		virtual void on_draw() override;
	private:
		v1u m_slot;
	};
}
#endif	// NW_GAPI
#endif	// NWGFX_SHADER_BUFFER_H