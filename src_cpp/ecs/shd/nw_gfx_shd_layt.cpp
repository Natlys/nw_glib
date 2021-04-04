#include "nw_gfx_pch.hpp"
#include "nw_gfx_shd_layt.h"
#if(defined NW_GAPI)
#include "core/nw_gfx_engine.h"
#include "lib/nw_gfx_load_core.h"
#include "lib/nw_gfx_load_layt.h"
#include "../shd/nw_gfx_shd.h"
#if(NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	shd_layt::shd_layt(gfx_engine& graphics) :
		t_cmp(), a_gfx_cmp(graphics), info_layt(),
		m_handle(0)
	{
	}
	shd_layt::shd_layt(gfx_engine& graphics, shd& shader, celems& elements) :
		shd_layt(graphics)
	{
		if (!remake(shader, std::move(elements))) { throw init_error(__FILE__, __LINE__);  return; }
	}
	shd_layt::~shd_layt() { if (m_handle != 0) { glDeleteVertexArrays(1, &m_handle); m_handle = 0; } }
	// --setters
	// --==<core_methods>==--
	v1b shd_layt::remake(mem_ref<a_shd>& shader, celems& elements)
	{
		m_elems = elements;
		if (m_handle != 0) { glDeleteVertexArrays(1, &m_handle); m_handle = 0; }
		if (shader.is_valid() == false) { return false; }
		if (m_elems.size() == 0) { return false; }

		glGenVertexArrays(1, &m_handle);
		glBindVertexArray(m_handle);
		
		m_stride = 0;
		for (v1u bei = 0; bei < m_elems.size(); bei++) {
			auto& elem = m_elems[bei];
			elem.offset = m_stride;
			m_stride += elem.get_size();
		}
		for (v1u bei = 0; bei < m_elems.size(); bei++) {
			auto& ielem = m_elems[bei];
			glEnableVertexAttribArray(ielem.idx);
			GLsizei icount = convert<value_types, GLsizei>(ielem.get_type());
			GLenum itype = convert<value_types, GLenum>(ielem.get_type());
			glVertexAttribPointer( ielem.idx, icount, itype, GL_FALSE, m_stride, (GLvoid*)ielem.offset);
		}
		return true;
	}
	void shd_layt::on_draw()
	{
		glBindVertexArray(m_handle);
	}
	// --==</core_methods>==--
}

#endif
#if(NW_GAPI & NW_GAPI_D3D)
namespace NW
{
	shd_layt::shd_layt(gfx_engine& graphics) :
		t_cmp(), a_gfx_cmp(graphics), info_layt(),
		m_handle(nullptr)
	{
	}
	shd_layt::shd_layt(gfx_engine& graphics, shd& shader, celems& elements) :
		shd_layt(graphics)
	{
		if (!remake(shader, elements)) { throw init_error(__FILE__, __LINE__);  return; }
	}
	shd_layt::~shd_layt() { if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; } }
	// --setters
	// --==<core_methods>==--
	v1b shd_layt::remake(mem_ref<a_shd>& shader, celems& elements) {
		m_elems = elements;
		if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; }
		if (shader.is_valid() == false) { return false; }
		if (m_elems.size() == 0) { return false; }

		m_stride = 0;
		for (v1u bei = 0; bei < m_elems.size(); bei++) {
			auto& elem = m_elems[bei];
			elem.offset = m_stride;
			m_stride += elem.get_size();
		}

		darray<D3D11_INPUT_ELEMENT_DESC> dx_elems(m_elems.size());
		for (v1u bei = 0; bei < dx_elems.size(); bei++) {
			auto& ielem = m_elems[bei];
			auto& dx_elem = dx_elems[bei];
			dx_elem.Format = convert<value_types, DXGI_FORMAT>(ielem.get_type());
			dx_elem.SemanticName = ielem.name;
			dx_elem.SemanticIndex = 0u;
			dx_elem.InputSlot = 0u;		// dx_elem.InputSlot = ielem.idx; should not be set in this way;
			dx_elem.AlignedByteOffset = ielem.offset;
			dx_elem.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			dx_elem.InstanceDataStepRate = 0;
		}
		m_gfx->get_dvch()->CreateInputLayout(&dx_elems[0], dx_elems.size(),
			shader->get_handle()->GetBufferPointer(), shader->get_handle()->GetBufferSize(), &m_handle);
		if (m_handle == nullptr) { throw init_error(__FILE__, __LINE__); return false; }
		return true;
	}
	void shd_layt::on_draw()
	{
		m_gfx->get_ctxh()->IASetInputLayout(m_handle);
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI