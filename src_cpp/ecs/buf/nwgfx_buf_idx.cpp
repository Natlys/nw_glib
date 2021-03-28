#include "nwgfx_pch.hpp"
#include "nwgfx_buf_idx.h"
#if (defined NW_GAPI)
#include <core/nwgfx_engine.h>
#include <lib/nwgfx_load_buf.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NWGFX
{
	gfx_buf_idx::gfx_buf_idx(gfx_engine& graphics) :
		t_cmp(), a_gfx_buf(graphics),
		m_data_type(convert<value_types, data_type>(VTYPE_V1_U32))
	{
	}
	gfx_buf_idx::gfx_buf_idx(gfx_engine& graphics, size nof_bytes, cptr buffer, value_types type) :
		gfx_buf_idx(graphics)
	{
		if (!remake_bytes(nof_bytes, buffer, type)) { throw init_error(__FILE__, __LINE__); return; }
	}
	gfx_buf_idx::~gfx_buf_idx()
	{
	}
	// --setters
	void gfx_buf_idx::set_data_bytes(size nof_bytes, cptr buffer, size offset) {
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, m_offset + offset, nof_bytes, buffer);
	}
	// --==<core_methods>==--
	v1b gfx_buf_idx::remake_bytes(size nof_bytes, cptr buffer, value_types type)
	{
		m_size = nof_bytes;
		m_stride = NW_GET_VTYPE_SIZE_D(type);
		m_data_type = convert<value_types, data_type>(type);
		if (m_handle != 0) { glDeleteBuffers(1, &m_handle); m_handle = 0; }
		if (m_size == 0) { return false; }
		
		glGenBuffers(1, &m_handle);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, nof_bytes, buffer, buffer == nullptr ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
		
		return true;
	}
	void gfx_buf_idx::on_draw()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NWGFX
{
	gfx_buf_idx::gfx_buf_idx(gfx_engine& graphics) :
		t_cmp(), a_gfx_buf(graphics),
		m_data_type(convert<value_types, data_type>(VTYPE_V1_U32))
	{
	}
	gfx_buf_idx::gfx_buf_idx(gfx_engine& graphics, size nof_bytes, cptr buffer, value_types type) :
		gfx_buf_idx(graphics)
	{
		if (!remake_bytes(nof_bytes, buffer, type)) { throw init_error(__FILE__, __LINE__); return; }
	}
	gfx_buf_idx::~gfx_buf_idx()
	{
	}
	// --setters
	void gfx_buf_idx::set_data_bytes(size nof_bytes, cptr buffer, size offset) {
		D3D11_MAPPED_SUBRESOURCE msub_rsc{ 0 };
		m_gfx->get_ctxh()->Map(m_handle, 0u, D3D11_MAP_WRITE_NO_OVERWRITE, 0u, &msub_rsc);
		memcpy(msub_rsc.pData, buffer, nof_bytes);
		m_gfx->get_ctxh()->Unmap(m_handle, 0u);
	}
	// --==<core_methods>==--
	v1b gfx_buf_idx::remake_bytes(size nof_bytes, cptr buffer, value_types type)
	{
		m_size = nof_bytes;
		m_stride = NW_GET_VTYPE_SIZE_D(type);
		m_data_type = convert<value_types, data_type>(type);
		if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; }
		if (m_size <= 0) { return false; }

		D3D11_BUFFER_DESC buf_desc{ 0 };
		buf_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		buf_desc.MiscFlags = 0u;
		buf_desc.StructureByteStride = m_stride;
		buf_desc.ByteWidth = nof_bytes;

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
	void gfx_buf_idx::on_draw()
	{
		m_gfx->get_ctxh()->IASetIndexBuffer(m_handle, m_data_type, 0);
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI