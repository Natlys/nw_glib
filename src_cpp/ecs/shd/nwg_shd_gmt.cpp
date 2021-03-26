#include <nwg_pch.hpp>
#include "nwg_shd_gmt.h"
#if (defined NW_GAPI)
#include <core/nwg_engine.h>
#include <lib/nwg_load_shd.h>
#include <lib/nwg_load_mtl.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	shd_gmt::shd_gmt(gfx_engine& graphics) :
		a_shd(graphics)
	{
	}
	shd_gmt::shd_gmt(gfx_engine& graphics, cstr source_code) :
		shd_gmt(graphics)
	{
		if (!remake(source_code)) { throw init_error(__FILE__, __LINE__); return; }
	}
	shd_gmt::~shd_gmt() { }
	// --setters
	// --operators
	stm_out& shd_gmt::operator<<(stm_out& stm) const {
		return stm;
	}
	stm_in& shd_gmt::operator>>(stm_in& stm) {
		return stm;
	}
	// --==<core_methods>==--
	bit shd_gmt::remake(cstr source_code)
	{
		if (!a_shd::remake(source_code)) { return false; }

		m_handle = glCreateShader(GL_GEOMETRY_SHADER);
		cstr final_code = &m_src_code[0];
		glShaderSource(m_handle, 1, &final_code, nullptr);
		glCompileShader(m_handle);

		if (!gfx_debug_shader(m_handle)) { return false; }

		return true;
	}
	void shd_gmt::on_draw()
	{
		a_shd::on_draw();
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	shd_gmt::shd_gmt(gfx_engine& graphics) :
		a_shd(graphics),
		m_native(nullptr)
	{
	}
	shd_gmt::shd_gmt(gfx_engine& graphics, cstr source_code) :
		shd_gmt(graphics)
	{
		if (!remake(source_code)) { throw init_error(__FILE__, __LINE__); return; }
	}
	shd_gmt::~shd_gmt() { if (m_native != nullptr) { m_native->Release(); m_native = nullptr; } }
	// --setters
	// --operators
	stm_out& shd_gmt::operator<<(stm_out& stm) const {
		return stm;
	}
	stm_in& shd_gmt::operator>>(stm_in& stm) {
		return stm;
	}
	// --==<core_methods>==--
	bit shd_gmt::remake(cstr source_code)
	{
		if (m_native != nullptr) { m_native->Release(); m_native = nullptr; }
		
		if (!a_shd::remake(source_code)) { return false; }
		
		return true;
	}
	void shd_gmt::on_draw()
	{
		a_shd::on_draw();

		m_gfx->get_ctxh()->GSSetShader(m_native, NULL, NULL);

		ID3D11Buffer* buf_handles[10]{ nullptr };
		for (auto& ibuf : m_bufs) {
			if (ibuf.is_valid()) {
				buf_handles[ibuf->get_slot()] = ibuf->get_handle();
			}
		}
		m_gfx->get_ctxh()->GSSetConstantBuffers(0, 10u, &buf_handles[0]);

		ID3D11ShaderResourceView* txr_handles[10]{ nullptr };
		ID3D11SamplerState* smp_handles[10]{ nullptr };
		for (auto& itxr : m_txrs) {
			if (itxr.is_valid()) {
				txr_handles[itxr->get_slot()] = itxr->get_handle();
				auto& ismp = itxr->get_smp();
				if (ismp.is_valid()) {
					smp_handles[ismp->get_slot()] = ismp->get_handle();
				}
			}
		}
		m_gfx->get_ctxh()->GSSetShaderResources(0u, 10u, &txr_handles[0]);
		m_gfx->get_ctxh()->GSSetSamplers(0u, 10u, &smp_handles[0]);
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI