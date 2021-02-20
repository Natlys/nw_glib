#ifndef NWG_RESOURCE_H
#define NWG_RESOURCE_H

#include <nwg_core.hpp>

#if (defined NWG_GAPI)
#if (NWG_GAPI & NWG_GAPI_OGL)
namespace NWG
{
	/// Abstract GraphicsResource class
	class NWG_API AGfxRes
	{
		friend class GfxEngine;
	protected:
		AGfxRes() : m_pGfx(nullptr), m_unRId(0) { }
	public:
		virtual ~AGfxRes() { }
		// --getters
		inline unsigned int const GetRenderId() const { return m_unRId; }
		// --core_methods
		virtual void Bind() = 0;
	protected:
		GfxEngine* m_pGfx;
		unsigned int m_unRId;
	};
}
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
namespace NWG
{
	/// Abstract GraphicsResource class
	class NWG_API AGfxRes
	{
		friend class GfxEngine;
	protected:
		AGfxRes(GfxEngine& rGfx) : m_pGfx(&rGfx) { }
	public:
		virtual ~AGfxRes() { }
		// --core_methods
		virtual void Bind() = 0;
	protected:
		GfxEngine* m_pGfx;
	};
}
#endif
#endif	// NWG_GAPI
#endif	// NWG_RESOURCE_H