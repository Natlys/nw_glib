#ifndef NWG_IMAGE_H
#define NWG_IMAGE_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
namespace NW
{
	/// image class
	class NW_API img_cmp : public a_data_cmp
	{
	public:
		using pxl_fmt = pixel_formats;
		using data = darray<ubyte>;
	public:
		img_cmp();
		img_cmp(const img_cmp& cpy);
		img_cmp(const img_cmp& cpy, v1si offset_x, v1si offset_y, v1si width, v1si height);
		// --getters
		inline v1si get_size_x() const      { return m_size_x; }
		inline v1si get_size_y() const      { return m_size_y; }
		inline v1si get_channels() const    { return m_channels; }
		inline size get_data_size() const   { return static_cast<size>(abs(m_size_x)) * static_cast<size>(abs(m_size_y)) * static_cast<size>(abs(m_channels)); }
		inline size get_pxl_size() const    { return static_cast<size>(abs(m_size_x)) * static_cast<size>(abs(m_size_y)); }
		inline pxl_fmt get_format() const   { return m_format; }
		inline native_types get_data_type() const                   { return m_data_type; }
		inline ubyte* get_data()                                    { return &m_pxl_data[0]; }
		inline const ubyte* get_data() const                        { return &m_pxl_data[0]; }
		inline ubyte* get_data(v1ui pxl_x, v1ui pxl_y)              { return &m_pxl_data[NW_XY_TO_X(pxl_x * m_channels, pxl_y * m_channels, m_size_x) % get_data_size()]; }
		inline const ubyte* get_data(v1ui pxl_x, v1ui pxl_y) const  { return &m_pxl_data[NW_XY_TO_X(pxl_x * m_channels, pxl_y * m_channels, m_size_x) % get_data_size()]; }
		// --setters
		void set_data(const ubyte* data_ptr);
		void set_data(const img_cmp& source);
		void set_data(const img_cmp& source, v1si crd_x, v1si crd_y, v1si size_x, v1si size_y);
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const = 0;
		virtual stm_in& operator>>(stm_in& stm) = 0;
		// --core_methods
		data make_region(v1si crd_x, v1si crd_y, v1si size_x, v1si size_y) const;
	protected:
		v1si m_size_x;
		v1si m_size_y;
		v1si m_channels;
		pixel_formats m_format;
		native_types m_data_type;
		data m_pxl_data;
	};
}
namespace NW
{
	/// img_bmp class
	/// description:
	/// --used for loading of .bmp formatted files
	/// interface:
	/// ->load a bitmap as binary file->read headers "file" and "data"
	/// ->if the image is indexed - load color pallete
	/// ->read pixel data with offset which is defined in "file" header
	/// ->in the case of 24bit and not multiple-of-4 sizes, we need to consider padding
	class NW_API img_bmp : public t_cmp<img_bmp>, public img_cmp
	{
	public:
		img_bmp();
		~img_bmp();
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const override;
		virtual stm_in& operator>>(stm_in& stm) override;
	private:
		img_bmp_info m_info;
	};
}
#endif	// NW_GAPI
#endif	// NWG_IMAGE_H