#include "nw_gfx_pch.hpp"
#include "nw_gfx_txr.h"
#if (defined NW_GAPI)
#include "core/nw_gfx_engine.h"
#include "lib/nw_gfx_load_txr.h"
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	a_gfx_txr::a_gfx_txr(gfx_engine& graphics) :
		t_cmp(), a_img_cmp(), a_gfx_cmp(graphics),
		m_handle(0u),
		m_slot(0u),
		m_gfx_txrfmt(convert<texture_formats, gfx_txrfmt>(TXF_RGBA)),
		m_pxl_fmt(convert<pixel_formats, pxl_fmt>(PXF_R8G8B8A8_U32))
	{
	}
	a_gfx_txr::~a_gfx_txr() { if (m_handle != 0) { glDeleteTextures(1, &m_handle); m_handle = 0; } }
	// --setters
	void a_gfx_txr::set_slot(v1u slot) {
		m_slot = slot;
		m_smp->set_slot(slot);
	}
	void a_gfx_txr::set_smp(smp& ref) {
		m_smp = ref;
	}
	void a_gfx_txr::set_gfx_txrfmt(texture_formats format) {
		m_gfx_txrfmt = convert<texture_formats, gfx_txrfmt>(format);
	}
	void a_gfx_txr::set_pxl_fmt(pixel_formats format) {
		m_pxl_fmt = convert<pixel_formats, gfx_txrfmt>(format);
	}
	// --operators
	// --==<core_methods>==--
	v1b a_gfx_txr::load_file(cstr file_path)
	{
		img_bmp img;
		if (!io_sys::get().load_file(file_path, img)) { throw init_error(__FILE__, __LINE__); return false; }
		if (!this->remake(img)) { return false; }

		return true;
	}
	v1b a_gfx_txr::remake(const a_img_cmp& img)
	{
		set_data(img);
		if (m_handle != 0) { glDeleteTextures(1, &m_handle); m_handle = 0; }
		if (m_channels <= 0) { return false; }

		return true;
	}
	void a_gfx_txr::on_draw()
	{
		m_smp->set_slot(m_slot);
		m_smp->on_draw();
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_D3D)
namespace NW
{
	a_gfx_txr::a_gfx_txr(gfx_engine& graphics) :
		t_cmp(), a_img_cmp(), a_gfx_cmp(graphics),
		m_handle(nullptr),
		m_slot(0),
		m_gfx_txrfmt(convert<texture_formats, gfx_txrfmt>(TXF_RGBA)),
		m_pxl_fmt(convert<pixel_formats, pxl_fmt>(PXF_R8G8B8A8_U32))
	{
	}
	a_gfx_txr::~a_gfx_txr()
	{
		if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; }
	}
	// --setters
	void a_gfx_txr::set_slot(v1u slot) {
		m_slot = slot;
		m_smp->set_slot(slot);
	}
	void a_gfx_txr::set_smp(smp& ref) {
		m_smp = ref;
	}
	void a_gfx_txr::set_gfx_txrfmt(texture_formats format) {
		m_gfx_txrfmt = convert<texture_formats, gfx_txrfmt>(format);
	}
	void a_gfx_txr::set_pxl_fmt(pixel_formats format) {
		m_pxl_fmt = convert<pixel_formats, gfx_txrfmt>(format);
	}
	// --operators
	// --==<core_methods>==--
	v1b a_gfx_txr::load_file(cstr file_path)
	{
		img_bmp img;
		if (!io_sys::get().load_file(file_path, img)) { throw init_error(__FILE__, __LINE__); return false; }
		if (!this->remake(img)) { return false; }

		return true;
	}
	v1b a_gfx_txr::save_file(cstr file_path)
	{
		return true;
	}
	v1b a_gfx_txr::remake(const a_img_cmp& img)
	{
		set_data(img);
		m_pxl_fmt = convert<v1s, pxl_fmt>(img.get_channels());
		m_gfx_txrfmt = convert<v1s, gfx_txrfmt>(img.get_channels());
		if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; }

		return true;
	}
	void a_gfx_txr::on_draw() {
		m_smp->set_slot(m_slot);
		m_smp->on_draw();

		m_gfx->get_ctxh()->VSSetShaderResources(m_slot, 1u, &m_handle);
		m_gfx->get_ctxh()->PSSetShaderResources(m_slot, 1u, &m_handle);
		m_gfx->get_ctxh()->GSSetShaderResources(m_slot, 1u, &m_handle);
		m_gfx->get_ctxh()->HSSetShaderResources(m_slot, 1u, &m_handle);
		m_gfx->get_ctxh()->DSSetShaderResources(m_slot, 1u, &m_handle);
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI