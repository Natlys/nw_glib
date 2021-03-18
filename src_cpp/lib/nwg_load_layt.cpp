#include <nwg_pch.hpp>
#include "nwg_load_layt.h"
#if (defined NW_GAPI)
#include "nwg_load.h"
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	bit gfx_load_layt() {
		// general
		glGenVertexArrays = (pfn_ogl_varr_gen)(gfx_get_proc("glGenVertexArrays"));
		glDeleteVertexArrays = (pfn_ogl_varr_del)(gfx_get_proc("glDeleteVertexArrays"));
		glBindVertexArray = (pfn_ogl_varr_bind)(gfx_get_proc("glBindVertexArray"));
		// data
		glEnableVertexAttribArray = (pfn_ogl_varr_enable_atb)(gfx_get_proc("glEnableVertexAttribArray"));
		glDisableVertexAttribArray = (pfn_ogl_varr_disable_atb)(gfx_get_proc("glEnableVertexAttribArray"));
		glVertexAttribPointer = (pfn_ogl_varr_set_atb)(gfx_get_proc("glVertexAttribPointer"));

		return true;
	}
}
namespace NW
{
	// general
	pfn_ogl_varr_gen glGenVertexArrays = NULL;
	pfn_ogl_varr_del glDeleteVertexArrays = NULL;
	pfn_ogl_varr_bind glBindVertexArray = NULL;
	// data
	pfn_ogl_varr_enable_atb glEnableVertexAttribArray = NULL;
	pfn_ogl_varr_disable_atb glDisableVertexAttribArray = NULL;
	pfn_ogl_varr_set_atb glVertexAttribPointer = NULL;
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	bit gfx_load_layt() {
		return true;
	}
}
#endif
#endif	// NW_GAPI