#include <nwg_pch.hpp>
#include "nwg_buf_shd.h"
#if (defined NW_GAPI)
#include <core/nwg_engine.h>
#include <lib/nwg_load_buf.h>
namespace NW
{
	shd_elem::shd_elem(cstr element_name, data_types data_type, si32 idx, si32 count) :
		name(""), type(data_type),
		idx(idx), count(count), offset_size(0)
	{
		strcpy(name, element_name);
	}
}
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	buf_shd::buf_shd(gfx_engine& graphics) :
		t_cmp(graphics),
		m_elems(elems()),
		m_slot(0),
		m_offset_size(0)
	{
	}
	buf_shd::~buf_shd() { }
	// --setters
	void buf_shd::set_slot(ui8 bind_slot) {
		m_slot = bind_slot;
	}
	void buf_shd::set_offset(size offset_size) {
		m_offset_size = offset_size;
	}
	void buf_shd::set_data(size data_size, const ptr data_ptr, size offset_size) {
		glBufferSubData(GL_UNIFORM_BUFFER, offset_size, data_size, data_ptr);
	}
	void buf_shd::add_elem(const elem& element, si8 count) {
		while (count-- > 0) {
			m_elems.push_back(element);
			m_elems.back().idx = m_elems.size() - 1;
		}
	}
	void buf_shd::rmv_elem(ui8 idx) {
		m_elems.erase(m_elems.begin() + idx % m_elems.size());
	}
	// --==<core_methods>==--
	bit buf_shd::remake(size data_size, const ptr data_ptr, size offset_size)
	{
		m_data_size = data_size;
		m_offset_size = offset_size;
		if (m_handle != 0) { glDeleteBuffers(1, &m_handle); m_handle = 0; }
		if (m_data_size <= 0) { return false; }
		if (m_elems.empty() || m_offset_size >= m_data_size) { return false; }
		
		size temp = 0;
		for (auto& elem : m_elems) {
			elem.offset_size += temp;
			temp += dt_get_aligned_size(elem.type, elem.count);
		}
		
		glGenBuffers(1, &m_handle);
		glBindBuffer(GL_UNIFORM_BUFFER, m_handle);
		glBufferData(GL_UNIFORM_BUFFER, m_data_size, nullptr, GL_DYNAMIC_DRAW);
		
		return true;
	}
	void buf_shd::on_draw()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_handle);
		//glBindBufferBase(GL_UNIFORM_BUFFER, m_slot, m_handle);
		glBindBufferRange(GL_UNIFORM_BUFFER, m_slot, m_handle, m_offset_size, m_data_size);
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	buf_shd::buf_shd(gfx_engine& graphics) :
		t_cmp(graphics),
		m_slot(0), m_offset_size(0),
		m_elems(elems())
	{
	}
	buf_shd::~buf_shd() { }
	// --setters
	void buf_shd::set_slot(ui8 bind_slot) {
		m_slot = bind_slot;
	}
	void buf_shd::set_offset(size offset_size) {
		m_offset_size = offset_size;
	}
	void buf_shd::set_data(size data_size, const ptr data_ptr, size offset_size) {
		D3D11_MAPPED_SUBRESOURCE msub_res{ 0 };
		m_gfx->get_context()->Map(m_handle, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &msub_res);
		memcpy(msub_res.pData, data_ptr, data_size);
		m_gfx->get_context()->Unmap(m_handle, 0u);
	}
	void buf_shd::add_elem(const shd_elem& element, si8 count) {
		while (count-- > 0) {
			m_elems.push_back(element);
			m_elems.back().idx = m_elems.size() - 1;
		}
	}
	void buf_shd::rmv_elem(ui8 idx) {
		m_elems.erase(m_elems.begin() + idx % m_elems.size());
	}
	// --==<core_methods>==--
	bit buf_shd::remake(size data_size, const ptr data_ptr, size offset_size) {
		m_data_size = data_size;
		m_offset_size = offset_size;
		if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; }
		if (m_data_size <= 0) { return false; }
		if (m_offset_size >= m_data_size || m_elems.size() == 0) { return false; }

		D3D11_BUFFER_DESC buf_desc{ 0 };
		buf_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		buf_desc.MiscFlags = 0u;
		buf_desc.StructureByteStride = m_data_size;
		buf_desc.ByteWidth = m_data_size;

		buf_desc.Usage = D3D11_USAGE_DYNAMIC;
		buf_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sub_data{ 0 };
		sub_data.pSysMem = mem_sys::get_memory().get_data();

		m_gfx->get_device()->CreateBuffer(&buf_desc, &sub_data, &m_handle);
		if (m_handle == nullptr) { throw init_error(__FILE__, __LINE__); return false; }
		return true;
	}
	void buf_shd::on_draw() {
		m_gfx->get_context()->VSSetConstantBuffers(m_slot, 1, &m_handle);
		m_gfx->get_context()->PSSetConstantBuffers(m_slot, 1, &m_handle);
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI