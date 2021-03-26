#ifndef NWG_INDEX_BUFFER_H
#define NWG_INDEX_BUFFER_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "nwg_buf.h"
namespace NW
{
	/// index_buffer class
	class NW_API buf_idx : public t_cmp<buf_idx>, public a_gfx_buf
	{
	public:
		buf_idx(gfx_engine& graphics);
		buf_idx(gfx_engine& graphics, size nof_bytes, cptr buffer, native_types type);
		template<typename dt>
		buf_idx(gfx_engine& graphics, v1ui count, const dt* buffer) :
			buf_idx(graphics, count * sizeof(dt), buffer, t_ntp_info<dt>::enum_type) { }
		template<typename dt>
		buf_idx(gfx_engine& graphics, const darray<dt>& buffer) :
			buf_idx(graphics, buffer.size() * sizeof(dt), buffer.data(), t_ntp_info<dt>::enum_type) { }
		virtual ~buf_idx();
		// --getters
		inline data_type get_data_type() const { return m_data_type; }
		inline size get_data_count() const     { return m_data_size / convert<data_type, size>(m_data_type); }
		// --setters
		virtual void set_data_bytes(size nof_bytes, cptr buffer, size offset = 0u) override;
		// --core_methods
		bit remake_bytes(size nof_bytes, cptr buffer, native_types type);
		template<typename dt>
		bit remake(v1ui count, const dt* buffer = nullptr) {
			return remake_bytes(count * sizeof(dt), buffer, t_ntp_info<dt>::enum_type);
		}
		template<typename dt>
		bit remake(const darray<dt>& buffer) {
			return remake_bytes(buffer.size() * sizeof(dt), buffer.data(), t_ntp_info<dt>::enum_type);
		}
		virtual void on_draw() override;
	private:
		data_type m_data_type;
	};
}
#endif	// NW_GAPI
#endif	// NW_INDEX_BUFFER_H