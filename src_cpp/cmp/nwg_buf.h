#ifndef NWG_BUFFER_H
#define NWG_BUFFER_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <core/nwg_cmp.h>
#include <core/nwg_switch.h>
namespace NWG
{
	class NWG_API a_gfx_buf : public a_gfx_cmp
	{
	public:
		a_gfx_buf(gfx_engine& graphics);
		virtual ~a_gfx_buf();
		// --getters
		inline size get_data_size() const	{ return m_data_size; }
#if (NWG_GAPI & NWG_GAPI_OGL)
		virtual inline ptr get_native() override { return &m_native; }
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
		virtual inline ptr get_native() override { return m_native; }
#endif
		// --setters
		virtual void set_data(size data_size, const ptr data_ptr, size offset_size = 0) = 0;
		// --core_methods
		virtual void on_draw() = 0;
	protected:
		size m_data_size = 0;
		ptr m_data_ptr = nullptr;
#if (NWG_GAPI & NWG_GAPI_OGL)
		GLuint m_native;
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
		ID3D11Buffer* m_native;
#endif
	};
}
#endif	// NWG_GAPI
#endif	// NWG_BUFFER_H