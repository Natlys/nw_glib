#include <nwg_pch.hpp>
#include "nwg_ogl_v4.h"

#if (defined GL_VERSION_4_0)
PFNGLMINSAMPLESHADINGPROC OglMinSampleShading;
PFNGLBLENDEQUATIONIPROC OglBlendEquationi;
PFNGLBLENDEQUATIONSEPARATEIPROC OglBlendEquationSeparatei;
PFNGLBLENDFUNCIPROC OglBlendFunci;
PFNGLBLENDFUNCSEPARATEIPROC OglBlendFuncSeparatei;
#endif	// GL_VERSION_4_0