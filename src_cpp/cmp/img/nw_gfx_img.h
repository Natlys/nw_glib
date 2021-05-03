#ifndef NW_GFX_IMAGE_H
#define NW_GFX_IMAGE_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#	include "mem/nw_mem_buf.h"
namespace NW
{
	/// graphics_image class
	class NW_API gfx_img : public mem_buf
	{
	public:
		using img_t = gfx_img;
		using img_tc = const img_t;
	public:
		gfx_img();
		gfx_img(img_tc& copy);
		gfx_img(img_t&& copy);
		virtual ~gfx_img();
		// --getters
		inline cv1u get_size() const    { return v1u{ m_size[0] * m_size[1] * m_size[2] }; }
		inline cv1u get_size_x() const   { return v1u{ m_size[0] }; }
		inline cv1u get_size_y() const   { return v1u{ m_size[1] }; }
		inline cv1u get_size_z() const   { return v1u{ m_size[2] }; }
		inline cv2u get_size_xy() const  { return v2u{ m_size[0], m_size[1], m_size[2] }; }
		inline cv3u get_size_xyz() const { return v3u{ m_size[0], m_size[1], m_size[2] }; }
		// --setters
		gfx_img& set_size(cv1u size_x);
		gfx_img& set_size(cv1u size_x, cv1u size_y);
		gfx_img& set_size(cv2u size);
		gfx_img& set_size(cv1u size_x, cv1u size_y, cv1u size_z);
		gfx_img& set_size(cv3u size);
		inline gfx_img& set_data(cv1u key, ptr_tc data) { mem_buf::set_data(key * get_stride(), data); return *this; }
		inline gfx_img& set_data(ptr_tc data, cv1u size) { mem_buf::set_data(data, size * get_stride()); return *this; }
		inline gfx_img& set_data(ptr_tc data) { mem_buf::set_data(data); return *this; }
		inline gfx_img& set_data() { mem_buf::set_data(); return *this; }
		virtual buf_t& set_data(size_t key, ptr_tc data, size_t space) override;
		// --predicates
		inline v1bit has_size() const { return get_size() > 0u; }
		inline v1bit has_size(cv1u size) const { return get_size() >= size; }
		inline v1bit has_size_x(cv1u size_x) const { return get_size_x() >= size_x; }
		inline v1bit has_size_y(cv1u size_y) const { return get_size_y() >= size_y; }
		inline v1bit has_size_z(cv1u size_z) const { return get_size_z() >= size_z; }
		inline v1bit has_size_xy(cv1u size_x, cv1u size_y) const { return has_size_x(size_x) && has_size_y(size_y); }
		inline v1bit has_size_xy(cv2u size_xy) const { return has_size_xy(size_xy[0], size_xy[1]); }
		inline v1bit has_size_xyz(cv1u size_x, cv1u size_y, cv1u size_z) const { return has_size_x(size_x) && has_size_y(size_y) && has_size_z(size_z); }
		inline v1bit has_size_xyz(cv3u size_xyz) const { return has_size_xyz(size_xyz[0], size_xyz[1], size_xyz[2]); }
		// --operators
		inline img_t& operator=(img_tc& copy) { NW_CHECK(remake(copy.get_layt(), copy.get_size_xyz(), copy.get_data()), "remake error!", return *this); return *this; }
		inline img_t& operator=(img_t&& copy) { NW_CHECK(remake(copy.get_layt(), copy.get_size_xyz(), copy.get_data()), "remake error!", return *this); return *this; }
		virtual op_stream_t& operator<<(op_stream_t& stm) const override;
		virtual ip_stream_t& operator>>(ip_stream_t& stm) override;
		// --core_methods
		inline v1bit remake(cv2u size) { set_size(size[0], size[1], 1u); return remake(); }
		inline v1bit remake(cv3u size) { set_size(size[0], size[1], size[2]); return remake(); }
		inline v1bit remake(layt_tc& layout, cv2u size) { set_layt(layout); set_size(size); return remake(); }
		inline v1bit remake(layt_tc& layout, cv3u size) { set_layt(layout); set_size(size); return remake(); }
		inline v1bit remake(layt_tc& layout, cv2u size, ptr_tc data) { set_layt(layout); set_size(size); set_data(data); return remake(); }
		inline v1bit remake(layt_tc& layout, cv3u size, ptr_tc data) { set_layt(layout); set_size(size); set_data(data); return remake(); }
		virtual v1bit remake() override;
	protected:
		v3u m_size;
	};
}
#endif	// NW_GAPI
#endif	// NW_GFX_IMAGE_H