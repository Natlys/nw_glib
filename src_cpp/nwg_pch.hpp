#ifndef NWG_PCH_HPP
#define NWG_PCH_HPP

#include <native_library.hpp>
using namespace NWL;

#if (defined NWG_PLATFORM_WINDOWS)
	#include <d3d11.h>
#endif	// NWG_PLATFORM

#endif	// NWG_PCH_HPP