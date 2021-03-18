#ifndef NWG_SHADER_BUFFER_H
#define NWG_SHADER_BUFFER_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "nwg_buf.h"
namespace NW
{
	/// shd_input_element struct
	struct NW_API shd_elem
	{
	public:
		schar name[128] = "default";
		data_types type = DT_DEFAULT;
		si32 count = 0;
		si32 idx = 0;
		size offset_size = 0;
	public:
		shd_elem(cstr name = "default", data_types dataType = DT_DEFAULT, si32 idx = 0, si32 count = 1);
	};
}
namespace NW
{
	/// shader_buffer class
	/// description:
	/// --it is used by shaders as opengl uniform buffer, or as directx constant buffer;
	class NW_API buf_shd : public t_cmp<buf_shd, a_gfx_buf>
	{
		using elem = shd_elem;
		using elems = darray<elem>;
	public:
		buf_shd(gfx_engine& graphics);
		virtual ~buf_shd();
		// --getters
		inline ui8 get_slot() const		{ return m_slot; }
		inline elems& get_elems()		{ return m_elems; }
		inline elem& get_elem(ui8 idx)	{ return m_elems[idx % m_elems.size()]; }
		// --setters
		void set_slot(ui8 bind_slot);
		void set_offset(size offset_size);
		virtual void set_data(size data_size, const ptr data_ptr, size offset_size = 0) override;
		void add_elem(const elem& element, si8 nof_elements = 1);
		void rmv_elem(ui8 idx);
		// --core_methods
		bit remake(size data_size, const ptr data_ptr, size offset_size);
		template<typename stype>
		bit remake(const ptr data_ptr = nullptr, size offset_size = 0);
		virtual void on_draw() override;
	private:
		ui8 m_slot;
		size m_offset_size;
		elems m_elems;
	};
	template<typename stype>
	bit buf_shd::remake(const ptr data_ptr, size offset_size) {
		return remake(sizeof(stype), data_ptr, offset_size);
	}
}
#endif	// NW_GAPI
#endif	// NWG_SHADER_BUFFER_H