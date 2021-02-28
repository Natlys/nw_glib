#include <nwg_pch.hpp>
#include "nwg_ogl_v4.h"
#include "nwg_ogl_loader.h"
namespace NWG
{
	void OglLoadV4() {
#ifdef GL_VERSION_4_0
		OglMinSampleShading = (PFNGLMINSAMPLESHADINGPROC)OglGetProc("glMinSampleShading");
		OglBlendEquationi = (PFNGLBLENDEQUATIONIPROC)OglGetProc("glBlendEquationi");
		OglBlendEquationSeparatei = (PFNGLBLENDEQUATIONSEPARATEIPROC)OglGetProc("glBlendEquationSeparatei");
		OglBlendFunci = (PFNGLBLENDFUNCIPROC)OglGetProc("glBlendFunci");
		OglBlendFuncSeparatei = (PFNGLBLENDFUNCSEPARATEIPROC)OglGetProc("glBlendFuncSeparatei");
#endif	// GL_VERSION_4_0
#ifdef GL_VERSION_4_1
#endif	// GL_VERSION_4_1
#ifdef GL_VERSION_4_2
#endif	// GL_VERSION_4_2
#ifdef GL_VERSION_4_3
#endif	// GL_VERSION_4_3
#ifdef GL_VERSION_4_4
		OglClearTexImage = (PFNGLCLEARTEXIMAGE)OglGetProc("glClearTexImage");
#endif	// GL_VERSION_4_4
#ifdef GL_VERSION_4_5
#endif	// GL_VERSION_4_5
#ifdef GL_VERSION_4_6
#endif	// GL_VERSION_4_6
	}
}
#if (defined GL_VERSION_4_0)
PFNGLMINSAMPLESHADINGPROC OglMinSampleShading;
PFNGLBLENDEQUATIONIPROC OglBlendEquationi;
PFNGLBLENDEQUATIONSEPARATEIPROC OglBlendEquationSeparatei;
PFNGLBLENDFUNCIPROC OglBlendFunci;
PFNGLBLENDFUNCSEPARATEIPROC OglBlendFuncSeparatei;
#endif	// GL_VERSION_4_0

#ifdef GL_VERSION_4_1
#endif	// GL_VERSION_4_1

#ifdef GL_VERSION_4_2
#endif	// GL_VERSION_4_2

#ifdef GL_VERSION_4_3
#endif	// GL_VERSION_4_3

#ifdef GL_VERSION_4_4
PFNGLCLEARTEXIMAGE OglClearTexImage = NULL;
#endif	// GL_VERSION_4_4

#ifdef GL_VERSION_4_5
#endif	// GL_VERSION_4_5

#ifdef GL_VERSION_4_6
#endif	// GL_VERSION_4_6