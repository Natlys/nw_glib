#ifndef NW_GFX_INDEX_BUFFER_H
#define NW_GFX_INDEX_BUFFER_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#include "nw_gfx_buf.h"
namespace NW
{
	/// index_buffer class
	class NW_API gfx_buf_idx : public t_cmp<gfx_buf_idx>, public a_gfx_buf
	{
	public:
		gfx_buf_idx(gfx_engine& graphics);
		gfx_buf_idx(gfx_engine& graphics, size nof_bytes, cptr buffer, value_types type);
		template<typename dt>
		gfx_buf_idx(gfx_engine& graphics, v1u count, const dt* buffer) :
			gfx_buf_idx(graphics, count * sizeof(dt), buffer, NW_GET_VTYPE_ENUM_S(dt)) { }
		template<typename dt>
		gfx_buf_idx(gfx_engine& graphics, const darray<dt>& buffer) :
			gfx_buf_idx(graphics, buffer.size() * sizeof(dt), buffer.data(), NW_GET_VTYPE_ENUM_S(dt)) { }
		virtual ~gfx_buf_idx();
		// --getters
		inline data_type get_data_type() const { return m_data_type; }
		// --setters
		virtual void set_data_bytes(size nof_bytes, cptr buffer, size offset = 0u) override;
		// --core_methods
		v1b remake_bytes(size nof_bytes, cptr buffer, value_types type);
		template<typename dt>
		v1b remake(v1u count, const dt* buffer = nullptr) {
			return remake_bytes(count * sizeof(dt), buffer, t_ntp_info<dt>::enum_type);
		}
		template<typename dt>
		v1b remake(const darray<dt>& buffer) {
			return remake_bytes(buffer.size() * sizeof(dt), buffer.data(), NW_GET_VTYPE_ENUM_S(dt));
		}
		virtual void on_draw() override;
	private:
		data_type m_data_type;
	};
}
#endif	// NW_GAPI
#endif	// NW_INDEX_BUFFER_H