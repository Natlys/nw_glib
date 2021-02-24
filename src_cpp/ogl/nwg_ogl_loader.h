#ifndef NWG_OGL_LOADER_H
#define NWG_OGL_LOADER_H
#include <ogl/nwg_ogl_native.h>
#include <ogl/nwg_ogl_arb.h>
#include <ogl/nwg_ogl_v1.h>
#include <ogl/nwg_ogl_v2.h>
#include <ogl/nwg_ogl_v3.h>
#include <ogl/nwg_ogl_v4.h>
namespace NWG
{
	struct OglVersion
	{
		int nMajor = 0;
		int nMinor = 0;
	};
}
namespace NWG
{
	// --getters
	extern void* OglGetProc(const char* strProc);
	// --predicates
	extern int OglIsSupported(int nMajor, int nMinor);
	// --==<core_methods>==--
	extern int OglInit();
	extern void OglOpen();
	extern void OglClose();
	extern void OglLoadProcs();
	// --==</core_methods>==--
}

#endif	// NWG_OGL_LOADER_H