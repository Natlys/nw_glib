#include "nw_gfx_pch.hpp"
#include "nw_gfx_buf.h"
#if (defined NW_GAPI)
#include "core/nw_gfx_engine.h"
#include "lib/nw_gfx_load_buf.h"
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	a_gfx_buf::a_gfx_buf(gfx_engine& graphics) :
		a_gfx_cmp(graphics),
		m_handle(0),
		m_size(0u), m_stride(0u), m_offset(0u)
	{
	}
	a_gfx_buf::~a_gfx_buf() { if (m_handle != 0) { glDeleteBuffers(1, &m_handle); m_handle = 0; } }
}
#endif
#if (NW_GAPI & NW_GAPI_D3D)
namespace NW
{
	a_gfx_buf::a_gfx_buf(gfx_engine& graphics) :
		a_gfx_cmp(graphics),
		m_handle(nullptr),
		m_size(0u), m_stride(0u), m_offset(0u)
	{
	}
	a_gfx_buf::~a_gfx_buf() { if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; } }
}
#endif
#endif	// NW_API