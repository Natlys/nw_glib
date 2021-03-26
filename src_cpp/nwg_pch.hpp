#ifndef NWG_PCH_HPP
#define NWG_PCH_HPP

#include <nwl.hpp>

#if (defined NW_WAPI)
#endif	// NW_WAPI
#if (defined NW_GAPI)
#	if (NW_GAPI & NW_GAPI_OGL)
#	endif
#	if (NW_GAPI & NW_GAPI_DX)
#		include <d3d11.h>
#	endif
#endif	// NW_GAPI

#endif	// NWG_PCH_HPP