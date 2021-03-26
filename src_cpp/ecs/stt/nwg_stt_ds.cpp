#include <nwg_pch.hpp>
#include "nwg_stt_ds.h"
#if (defined NW_GAPI)
#include <core/nwg_engine.h>
#include <lib/nwg_load_core.h>
#include <lib/nwg_load_fmbuf.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	gfx_stt_ds::gfx_stt_ds(gfx_engine& graphics) :
		a_gfx_stt(graphics),
		m_handle(nullptr),
		m_is_enabled_depth(false),
		m_is_enabled_stencil(false),
		m_mask_depth(0xff),
		m_mask_stencil(0xff),
		m_func_depth(convert<logic_opers, func_depth>(LOGIC_LESSER)),
		m_func_stencil(convert<logic_opers, func_stencil>(LOGIC_ALWAYS)),
		m_oper_stencil(convert<stencil_opers, oper_stencil>(STENC_KEEP))
	{
	}
	gfx_stt_ds::~gfx_stt_ds() { }
	// --setters
	void gfx_stt_ds::set_mask_depth(v1ui8 mask) {
		if (mask == 0x00) { m_is_enabled_depth = false; return; }
		m_mask_depth = mask;
	}
	void gfx_stt_ds::set_mask_stencil(v1ui8 mask) {
		if (mask == 0x00) { m_is_enabled_stencil = false; return; }
		m_mask_stencil = mask;
	}
	void gfx_stt_ds::set_func_depth(logic_opers function) {
		if (function == LOGIC_DEFAULT) { m_is_enabled_depth = false; return; }
		m_func_depth = convert<logic_opers, func_depth>(function);
	}
	void gfx_stt_ds::set_func_stencil(logic_opers function) {
		if (function == LOGIC_DEFAULT) { m_is_enabled_stencil = false; return; }
		m_func_stencil = convert<logic_opers, func_stencil>(function);
	}
	void gfx_stt_ds::set_oper_stencil(stencil_opers operation) {
		if (operation == STENC_DEFAULT) { m_is_enabled_stencil = false; return; }
		m_oper_stencil = convert<stencil_opers, oper_stencil>(operation);
	}
	void gfx_stt_ds::set_enabled_depth(bit enable) {
		m_is_enabled_depth = enable;
	}
	void gfx_stt_ds::set_enabled_stencil(bit enable) {
		m_is_enabled_stencil = enable;
	}
	// --==<core_methods>==--
	bit gfx_stt_ds::remake()
	{
		return true;
	}
	void gfx_stt_ds::on_draw()
	{
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	gfx_stt_ds::gfx_stt_ds(gfx_engine& graphics) :
		a_gfx_stt(graphics),
		m_handle(nullptr),
		m_is_enabled_depth(false),
		m_is_enabled_stencil(false),
		m_mask_depth(0xff),
		m_mask_stencil(0xff),
		m_func_depth(convert<logic_opers, func_depth>(LOGIC_LESSER)),
		m_func_stencil(convert<logic_opers, func_stencil>(LOGIC_ALWAYS)),
		m_oper_stencil(convert<stencil_opers, oper_stencil>(STENC_KEEP))
	{
	}
	gfx_stt_ds::~gfx_stt_ds() { }
	// --setters
	void gfx_stt_ds::set_mask_depth(v1ui8 mask) {
		if (mask == 0x00) { m_is_enabled_depth = false; return; }
		m_mask_depth = mask;
	}
	void gfx_stt_ds::set_mask_stencil(v1ui8 mask) {
		if (mask == 0x00) { m_is_enabled_stencil = false; return; }
		m_mask_stencil = mask;
	}
	void gfx_stt_ds::set_func_depth(logic_opers function) {
		if (function == LOGIC_DEFAULT) { m_is_enabled_depth = false; return; }
		m_func_depth = convert<logic_opers, func_depth>(function);
	}
	void gfx_stt_ds::set_func_stencil(logic_opers function) {
		if (function == LOGIC_DEFAULT) { m_is_enabled_stencil = false; return; }
		m_func_stencil = convert<logic_opers, func_stencil>(function);
	}
	void gfx_stt_ds::set_oper_stencil(stencil_opers operation) {
		if (operation == STENC_DEFAULT) { m_is_enabled_stencil = false; return; }
		m_oper_stencil = convert<stencil_opers, oper_stencil>(operation);
	}
	void gfx_stt_ds::set_enabled_depth(bit enable) {
		m_is_enabled_depth = enable;
	}
	void gfx_stt_ds::set_enabled_stencil(bit enable) {
		m_is_enabled_stencil = enable;
	}
	// --==<core_methods>==--
	bit gfx_stt_ds::remake() {
		if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; }
		
		D3D11_DEPTH_STENCIL_DESC desc;
		desc.DepthEnable = is_enabled_depth();
		desc.StencilEnable = is_enabled_stencil();
		desc.DepthWriteMask = m_mask_depth ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
		desc.StencilReadMask = m_mask_stencil;
		desc.StencilWriteMask = m_mask_stencil;
		desc.BackFace.StencilFailOp = m_oper_stencil;
		desc.BackFace.StencilPassOp = m_oper_stencil;
		desc.BackFace.StencilDepthFailOp = m_oper_stencil;
		desc.BackFace.StencilFunc = m_func_depth;
		desc.FrontFace.StencilFailOp = m_oper_stencil;
		desc.FrontFace.StencilPassOp = m_oper_stencil;
		desc.FrontFace.StencilDepthFailOp = m_oper_stencil;
		desc.FrontFace.StencilFunc = m_func_depth;

		m_gfx->get_dvch()->CreateDepthStencilState(&desc, &m_handle);
		if (m_handle == nullptr) { return false; }

		return true;
	}
	void gfx_stt_ds::on_draw()
	{
		if (!m_is_enabled) { return; }
		m_gfx->get_ctxh()->OMSetDepthStencilState(m_handle, 0xff);
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI