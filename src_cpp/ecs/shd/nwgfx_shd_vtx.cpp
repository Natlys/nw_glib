#include "nwgfx_pch.hpp"
#include "nwgfx_shd_vtx.h"
#if (defined NW_GAPI)
#include <core/nwgfx_engine.h>
#include <lib/nwgfx_load_shd.h>
#include <lib/nwgfx_load_mtl.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NWGFX
{
	shd_vtx::shd_vtx(gfx_engine& graphics) :
		a_shd(graphics)
	{
	}
	shd_vtx::shd_vtx(gfx_engine& graphics, cstr source_code) :
		shd_vtx(graphics)
	{
		if (!remake(source_code)) { throw init_error(__FILE__, __LINE__); return; }
	}
	shd_vtx::~shd_vtx() { }
	// --setters
	// --operators
	stm_out& shd_vtx::operator<<(stm_out& stm) const {
		return stm;
	}
	stm_in& shd_vtx::operator>>(stm_in& stm) {
		return stm;
	}
	// --==<core_methods>==--
	v1b shd_vtx::remake(cstr source_code)
	{
		if (!a_shd::remake(source_code)) { return false; }
		
		m_handle = glCreateShader(GL_VERTEX_SHADER);
		cstr final_code = &m_src_code[0];
		glShaderSource(m_handle, 1, &final_code, nullptr);
		glCompileShader(m_handle);

		if (!gfx_check_shader(m_handle)) { return false; }

		return true;
	}
	void shd_vtx::on_draw()
	{
		a_shd::on_draw();
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NWGFX
{
	shd_vtx::shd_vtx(gfx_engine& graphics) :
		a_shd(graphics),
		m_native(nullptr)
	{
	}
	shd_vtx::shd_vtx(gfx_engine& graphics, cstr source_code) :
		shd_vtx(graphics)
	{
		if (!remake(source_code)) { throw init_error(__FILE__, __LINE__); return; }
	}
	shd_vtx::~shd_vtx() { if (m_native != nullptr) { m_native->Release(); m_native = nullptr; } }
	// --setters
	// --operators
	stm_out& shd_vtx::operator<<(stm_out& stm) const {
		return stm;
	}
	stm_in& shd_vtx::operator>>(stm_in& stm) {
		return stm;
	}
	// --==<core_methods>==--
	v1b shd_vtx::remake(cstr source_code)
	{
		if (m_native != nullptr) { m_native->Release(); m_native = nullptr; }
		
		if (!a_shd::remake(source_code)) { return false; }

		HRESULT h_result = 0;
		if ((h_result = D3DCompile(
			&m_src_code[0],		// source code
			m_src_code.size(),	// source code length
			NULL,				// source name
			NULL,				// defines
			NULL,				// includes
			"main",				// entry point name
			"vs_4_0",			// version
			0u,					// flags1
			0u,					// flags2
			&m_handle,			// where to store the code
			NULL				// blob for error messages
		)) != S_OK) { return false; }
		if (m_handle == nullptr) { return false; }

		m_gfx->get_dvch()->CreateVertexShader(m_handle->GetBufferPointer(), m_handle->GetBufferSize(), NULL, &m_native);
		if (m_handle == nullptr) { return false; }
		m_gfx->get_ctxh()->VSSetShader(m_native, NULL, NULL);
		
		return true;
	}
	void shd_vtx::on_draw()
	{
		a_shd::on_draw();

		m_gfx->get_ctxh()->VSSetShader(m_native, NULL, NULL);

		ID3D11Buffer* buf_handles[10]{ nullptr };
		for (auto& ibuf : m_bufs) {
			if (ibuf.is_valid()) {
				buf_handles[ibuf->get_slot()] = ibuf->get_handle();
			}
		}
		m_gfx->get_ctxh()->VSSetConstantBuffers(0, 10u, &buf_handles[0]);

		ID3D11ShaderResourceView* gfx_txrhandles[10]{ nullptr };
		ID3D11SamplerState* smp_handles[10]{ nullptr };
		for (auto& itxr : m_txrs) {
			if (itxr.is_valid()) {
				gfx_txrhandles[itxr->get_slot()] = itxr->get_handle();
				auto& ismp = itxr->get_smp();
				if (ismp.is_valid()) {
					smp_handles[ismp->get_slot()] = ismp->get_handle();
				}
			}
		}
		m_gfx->get_ctxh()->VSSetShaderResources(0u, 10u, &gfx_txrhandles[0]);
		m_gfx->get_ctxh()->VSSetSamplers(0u, 10u, &smp_handles[0]);
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI