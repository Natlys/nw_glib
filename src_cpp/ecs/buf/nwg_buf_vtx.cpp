#include <nwg_pch.hpp>
#include "nwg_buf_vtx.h"
#if (defined NW_GAPI)
#include <core/nwg_engine.h>
#include <lib/nwg_load_buf.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	buf_vtx::buf_vtx(gfx_engine& graphics) :
		a_gfx_buf(graphics), t_cmp(),
		m_stride(0u), m_offset(0u)
	{
	}
	buf_vtx::buf_vtx(gfx_engine& graphics, size nof_bytes, cptr buffer, size stride, size offset) :
		buf_vtx(graphics)
	{
		if (!remake_bytes(nof_bytes, buffer, stride, offset)) { throw init_error(__FILE__, __LINE__); return; }
	}
	buf_vtx::~buf_vtx()
	{ 
	}
	// --setters
	void buf_vtx::set_data_bytes(size nof_bytes, cptr buffer, size offset) {
		glBufferSubData(GL_ARRAY_BUFFER, offset, nof_bytes, buffer);
	}
	// --==<core_methods>==--
	bit buf_vtx::remake_bytes(size nof_bytes, cptr buffer, size stride, size offset)
	{
		m_data_size = nof_bytes;
		m_offset = offset;
		m_stride = stride;
		if (m_handle != 0) { glDeleteBuffers(1, &m_handle); m_handle = 0; }
		if (m_data_size <= 0 || m_stride <= 0) { return false; }
		if (m_stride >= m_data_size || m_offset >= m_data_size) { return false; }
		
		glGenBuffers(1, &m_handle);
		glBindBuffer(GL_ARRAY_BUFFER, m_handle);
		glBufferData(GL_ARRAY_BUFFER, nof_bytes, buffer, buffer == nullptr ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
		
		return true;
	}
	void buf_vtx::on_draw()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_handle);
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	buf_vtx::buf_vtx(gfx_engine& graphics) :
		a_gfx_buf(graphics), t_cmp(),
		m_stride(0), m_offset(0)
	{
	}
	buf_vtx::buf_vtx(gfx_engine& graphics, size nof_bytes, cptr buffer, size stride, size offset) :
		buf_vtx(graphics)
	{
		if (!remake_bytes(nof_bytes, buffer, stride, offset)) { throw init_error(__FILE__, __LINE__); return; }
	}
	buf_vtx::~buf_vtx()
	{
	}
	// --setters
	void buf_vtx::set_data_bytes(size nof_bytes, cptr buffer, size offset) {
		D3D11_MAPPED_SUBRESOURCE msub_rsc{ 0 };
		m_gfx->get_ctxh()->Map(m_handle, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &msub_rsc);
		memcpy(static_cast<ubyte*>(msub_rsc.pData) + m_offset + offset, buffer, nof_bytes);
		m_gfx->get_ctxh()->Unmap(m_handle, 0u);
	}
	// --==<core_methods>==--
	bit buf_vtx::remake_bytes(size nof_bytes, cptr buffer, size stride, size offset) {
		m_data_size = nof_bytes;
		m_stride = stride;
		m_offset = offset;
		if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; }
		if (m_data_size <= 0 || m_stride <= 0) { return false; }
		if (m_stride >= m_data_size || m_offset >= m_data_size) { return false; }
		
		D3D11_BUFFER_DESC buf_desc{ 0 };
		buf_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		buf_desc.MiscFlags = 0u;
		buf_desc.StructureByteStride = m_stride;
		buf_desc.ByteWidth = m_data_size;

		if (buffer == nullptr) {
			buf_desc.Usage = D3D11_USAGE_DYNAMIC;
			buf_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			m_gfx->get_dvch()->CreateBuffer(&buf_desc, nullptr, &m_handle);
		}
		else {
			buf_desc.Usage = D3D11_USAGE_DEFAULT;
			buf_desc.CPUAccessFlags = 0u;
			D3D11_SUBRESOURCE_DATA sub_data{ 0 };
			sub_data.pSysMem = buffer;
			m_gfx->get_dvch()->CreateBuffer(&buf_desc, &sub_data, &m_handle);
		}


		if (m_handle == nullptr) { throw init_error(__FILE__, __LINE__); return false; }
		return true;
	}
	void buf_vtx::on_draw()
	{
		m_gfx->get_ctxh()->IASetVertexBuffers(0, 1, &m_handle, reinterpret_cast<UINT*>(&m_stride), reinterpret_cast<UINT*>(&m_offset));
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI