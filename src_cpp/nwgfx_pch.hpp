#ifndef NWGFX_PCH_HPP
#define NWGFX_PCH_HPP

#include <nwlib.hpp>
namespace NWGFX { using namespace NWLIB; }

#if (defined NW_WAPI)
#endif	// NW_WAPI
#if (defined NW_GAPI)
#	if (NW_GAPI & NW_GAPI_OGL)
#	endif
#	if (NW_GAPI & NW_GAPI_DX)
#		include <d3d11.h>
#		include <dxgi.h>
#	endif
#endif	// NW_GAPI

#endif	// NWGFX_PCH_HPP