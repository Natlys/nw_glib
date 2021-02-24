#include <nwg_pch.hpp>
#include "nwg_res.h"
#if (defined NWG_GAPI)
#if (NWG_GAPI & NWG_GAPI_OGL)
#include <ogl/nwg_ogl_loader.h>
namespace NWG
{
	AGfxRes::AGfxRes(GfxEngine& rGfx) : m_pGfx(&rGfx), m_unRId(0) {}
	AGfxRes::~AGfxRes() {}
	// --setters
	// --core_methods
}
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
#include <dx/nwg_dx_loader.h>
namespace NWG
{
	AGfxRes::AGfxRes(GfxEngine& rGfx) : m_pGfx(&rGfx) {}
	AGfxRes::~AGfxRes() {}
	// --setters
	// --core_methods
}
#endif
#endif	// NWG_GAPI