#include "nw_gfx_pch.hpp"
#include "nw_gfx_buf_shd.h"
#if (defined NW_GAPI)
#include "core/nw_gfx_engine.h"
#include "lib/nw_gfx_load_buf.h"
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	gfx_buf_shd::gfx_buf_shd(gfx_engine& graphics) :
		t_cmp(), a_gfx_buf(graphics), info_layt(),
		m_slot(0u)
	{
	}
	gfx_buf_shd::gfx_buf_shd(gfx_engine& graphics, size nof_bytes, cptr buffer, size offset) :
		gfx_buf_shd(graphics)
	{
		if (!remake_bytes(nof_bytes, buffer, offset)) { throw init_error(__FILE__, __LINE__); }
	}
	gfx_buf_shd::~gfx_buf_shd()
	{
	}
	// --setters
	void gfx_buf_shd::set_slot(v1u bind_slot) {
		m_slot = bind_slot;
	}
	void gfx_buf_shd::set_offset(size offset) {
		m_offset = offset;
	}
	void gfx_buf_shd::set_data_bytes(size nof_bytes, cptr buffer, size offset) {
		glBufferSubData(GL_UNIFORM_BUFFER, m_offset + offset, nof_bytes, buffer);
	}
	// --==<core_methods>==--
	v1b gfx_buf_shd::remake_bytes(size nof_bytes, cptr buffer, size offset)
	{
		m_size = nof_bytes;
		m_offset = offset;
		m_stride = nof_bytes;
		if (m_handle != 0) { glDeleteBuffers(1, &m_handle); m_handle = 0; }
		if (m_size <= 0) { return false; }
		if (m_elems.empty() || m_offset >= m_size) { return false; }
		
		size temp = 0;
		for (auto& elem : m_elems) {
			elem.offset += temp;
			temp += elem.get_size();
		}
		
		glGenBuffers(1, &m_handle);
		glBindBuffer(GL_UNIFORM_BUFFER, m_handle);
		glBufferData(GL_UNIFORM_BUFFER, m_size, nullptr, GL_DYNAMIC_DRAW);
		
		return true;
	}
	void gfx_buf_shd::on_draw()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_handle);
		//glBindBufferBase(GL_UNIFORM_BUFFER, m_slot, m_handle);
		glBindBufferRange(GL_UNIFORM_BUFFER, m_slot, m_handle, m_offset, m_size);
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_D3D)
namespace NW
{
	gfx_buf_shd::gfx_buf_shd(gfx_engine& graphics) :
		t_cmp(), a_gfx_buf(graphics), info_layt(),
		m_slot(0u)
	{
	}
	gfx_buf_shd::gfx_buf_shd(gfx_engine& graphics, size nof_bytes, cptr buffer, size offset) :
		gfx_buf_shd(graphics)
	{
		if (!remake_bytes(nof_bytes, buffer, offset)) { throw init_error(__FILE__, __LINE__); }
	}
	gfx_buf_shd::~gfx_buf_shd()
	{
	}
	// --setters
	void gfx_buf_shd::set_slot(v1u bind_slot) {
		m_slot = bind_slot;
	}
	void gfx_buf_shd::set_offset(size offset) {
		m_offset = offset;
	}
	void gfx_buf_shd::set_data_bytes(size nof_bytes, cptr buffer, size offset) {
		D3D11_MAPPED_SUBRESOURCE msub_res{ 0 };
		m_gfx->get_ctxh()->Map(m_handle, 0u, D3D11_MAP_WRITE_NO_OVERWRITE, 0u, &msub_res);
		memcpy(static_cast<ubyte*>(msub_res.pData) + m_offset + offset, buffer, nof_bytes);
		m_gfx->get_ctxh()->Unmap(m_handle, 0u);
	}
	// --==<core_methods>==--
	v1b gfx_buf_shd::remake_bytes(size nof_bytes, cptr buffer, size offset)
	{
		m_size = nof_bytes;
		m_offset = offset;
		m_stride = nof_bytes;
		if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; }
		if (m_size <= 0) { return false; }
		if (m_offset >= m_size || m_elems.size() == 0) { return false; }

		D3D11_BUFFER_DESC buf_desc{ 0 };
		buf_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		buf_desc.MiscFlags = 0u;
		buf_desc.StructureByteStride = m_size;
		buf_desc.ByteWidth = m_size;

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
	void gfx_buf_shd::on_draw()
	{
		m_gfx->get_ctxh()->VSSetConstantBuffers(m_slot, 1u, &m_handle);
		m_gfx->get_ctxh()->PSSetConstantBuffers(m_slot, 1u, &m_handle);
		m_gfx->get_ctxh()->GSSetConstantBuffers(m_slot, 1u, &m_handle);
		m_gfx->get_ctxh()->HSSetConstantBuffers(m_slot, 1u, &m_handle);
		m_gfx->get_ctxh()->DSSetConstantBuffers(m_slot, 1u, &m_handle);
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI