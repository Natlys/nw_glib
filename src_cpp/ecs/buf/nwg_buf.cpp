#include <nwg_pch.hpp>
#include "nwg_buf.h"
#if (defined NW_GAPI)
#include <core/nwg_engine.h>
#include <lib/nwg_load_buf.h>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	a_gfx_buf::a_gfx_buf(gfx_engine& graphics) :
		a_gfx_cmp(graphics),
		m_handle(0),
		m_data_size(0)
	{
	}
	a_gfx_buf::~a_gfx_buf() { if (m_handle != 0) { glDeleteBuffers(1, &m_handle); m_handle = 0; } }
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	a_gfx_buf::a_gfx_buf(gfx_engine& graphics) :
		a_gfx_cmp(graphics),
		m_handle(nullptr),
		m_data_size(0)
	{
	}
	a_gfx_buf::~a_gfx_buf() { if (m_handle != nullptr) { m_handle->Release(); m_handle = nullptr; } }
}
#endif
#endif	// NW_API