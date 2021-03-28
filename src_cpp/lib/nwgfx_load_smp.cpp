#include "nwgfx_pch.hpp"
#include "nwgfx_load_smp.h"
#if (defined NW_GAPI)
#include "nwgfx_load.h"
#if (NW_GAPI & NW_GAPI_OGL)
namespace NWGFX
{
	v1b gfx_load_smp() {
		// general
		glGenSamplers = (pfn_ogl_smp_gen)(gfx_get_proc("glGenSamplers"));
		glDeleteSamplers = (pfn_ogl_smp_del)(gfx_get_proc("glDeleteSamplers"));
		glBindSampler = (pfn_ogl_smp_bind)(gfx_get_proc("glBindSampler"));
		// params
		glSamplerParameteri = (pfn_ogl_smp_param_i)(gfx_get_proc("glSamplerParameteri"));
		glSamplerParameteriv = (pfn_ogl_smp_param_iv)(gfx_get_proc("glSamplerParameteriv"));
		glSamplerParameterf = (pfn_ogl_smp_param_f)(gfx_get_proc("glSamplerParameterf"));
		glSamplerParameterfv = (pfn_ogl_smp_param_fv)(gfx_get_proc("glSamplerParameterfv"));
		
		return true;
	}
}
namespace NWGFX
{
	// general
	pfn_ogl_smp_gen glGenSamplers = NULL;
	pfn_ogl_smp_del glDeleteSamplers = NULL;
	pfn_ogl_smp_bind glBindSampler = NULL;
	// params
	pfn_ogl_smp_param_i glSamplerParameteri = NULL;
	pfn_ogl_smp_param_iv glSamplerParameteriv = NULL;
	pfn_ogl_smp_param_f glSamplerParameterf = NULL;
	pfn_ogl_smp_param_fv glSamplerParameterfv = NULL;
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NWGFX
{
	v1b gfx_load_smp() {
		return true;
	}
}
#endif
#endif	// NW_GAPI