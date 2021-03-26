#include <nwg_pch.hpp>
#include "nwg_txr.h"
#if (defined NW_GAPI)
#include <core/nwg_engine.h>
#include <lib/nwg_load_txr.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	a_txr::a_txr(gfx_engine& graphics) :
		t_cmp(), img_cmp(), a_gfx_cmp(graphics),
		m_handle(0u),
		m_slot(0u),
		m_txr_fmt(TXF_RGBA),
		m_smp(smp())
	{
	}
	a_txr::~a_txr() { if (m_handle != 0) { glDeleteTextures(1, &m_handle); m_handle = 0; } }
	// --setters
	void a_txr::set_slot(v1ui slot) {
		m_slot = slot;
		m_smp->set_slot(slot);
	}
	void a_txr::set_smp(smp& ref) {
		m_smp = ref;
	}
	// --operators
	// --==<core_methods>==--
	bit a_txr::remake(const img_cmp& img)
	{
		set_data(img);
		if (m_handle != 0) { glDeleteTextures(1, &m_handle); m_handle = 0; }
		if (m_channels <= 0) { return false; }

		return true;
	}
	void a_txr::on_draw()
	{
		m_smp->set_slot(m_slot);
		m_smp->on_draw();
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	a_txr::a_txr(gfx_engine& graphics) :
		t_cmp(), img_cmp(), a_gfx_cmp(graphics),
		m_handle(nullptr),
		m_slot(0),
		m_txr_fmt(convert<texture_formats, txr_fmt>(TXF_RGBA)),
		m_pxl_fmt(convert<pixel_formats, pxl_fmt>(PXF_R8G8B8A8_UINT32)),
		m_smp(smp())
	{
	}
	a_txr::~a_txr()
	{
		if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; }
	}
	// --setters
	void a_txr::set_slot(v1ui slot) {
		m_slot = slot;
		m_smp->set_slot(slot);
	}
	void a_txr::set_smp(smp& ref) {
		m_smp = ref;
	}
	// --operators
	bit a_txr::load_file(cstr file_path)
	{
		img_bmp img;
		if (!data_sys::get().load_file(file_path, img)) { throw init_error(__FILE__, __LINE__); return false; }
		if (!this->remake(img)) { return false; }

		return true;
	}
	bit a_txr::save_file(cstr file_path)
	{
		return true;
	}
	// --==<core_methods>==--
	bit a_txr::remake(const img_cmp& img)
	{
		set_data(img);
		m_pxl_fmt = convert<pixel_formats, pxl_fmt>(img.get_format());
		m_txr_fmt = convert<pixel_formats, txr_fmt>(img.get_format());
		if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; }

		return true;
	}
	void a_txr::on_draw() {
		m_smp->set_slot(m_slot);
		m_smp->on_draw();

		m_gfx->get_ctxh()->VSSetShaderResources(0u, 1u, &m_handle);
		m_gfx->get_ctxh()->PSSetShaderResources(0u, 1u, &m_handle);
		m_gfx->get_ctxh()->GSSetShaderResources(0u, 1u, &m_handle);
		m_gfx->get_ctxh()->HSSetShaderResources(0u, 1u, &m_handle);
		m_gfx->get_ctxh()->DSSetShaderResources(0u, 1u, &m_handle);
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI