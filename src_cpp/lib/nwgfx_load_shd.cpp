#include "nwgfx_pch.hpp"
#include "nwgfx_load_shd.h"
#if (defined NW_GAPI)
#include "nwgfx_load.h"
#include "nwgfx_load_mtl.h"
#if (NW_GAPI & NW_GAPI_OGL)
namespace NWGFX
{
	v1b gfx_load_shd() {
		// general
		glCreateShader = (pfn_ogl_shd_crt)gfx_get_proc("glCreateShader");
		glDeleteShader = (pfn_ogl_shd_del)gfx_get_proc("glDeleteShader");
		glCompileShader = (pfn_ogl_shd_compile)gfx_get_proc("glCompileShader");
		// getters
		glGetShaderiv = (pfn_ogl_shd_get_iv)gfx_get_proc("glGetShaderiv");
		glGetShaderInfoLog = (pfn_ogl_shd_get_info_log)gfx_get_proc("glGetShaderInfoLog");
		// setters
		glShaderSource = (pfn_ogl_shd_set_source)gfx_get_proc("glShaderSource");
		// predicates
		glIsShader = (pfn_ogl_shd_is_shader)gfx_get_proc("glIsShader");
		
		return true;
	}
	/// shader debugging
	v1b gfx_check_shader(v1u shd_id) {
		if (shd_id == 0) { return false; }
		v1s32 success_code = 0;
		v1s32 log_size = 0;
		dstr log_string;
		if (glIsShader(shd_id)) {
			glGetShaderiv(shd_id, GL_COMPILE_STATUS, &success_code);
			if (success_code == 0) {
				glGetShaderiv(shd_id, GL_INFO_LOG_LENGTH, &log_size);
				log_string.resize(log_size);
				glGetShaderInfoLog(shd_id, log_size, NULL, &log_string[0]);
				throw a_error(&log_string[0], ERC_COMPILLATION, __FILE__, __LINE__);
				return success_code == 1;
			}
		}
		else {
			glGetProgramiv(shd_id, GL_LINK_STATUS, &success_code);
			if (success_code == 0) {
				glGetProgramiv(shd_id, GL_INFO_LOG_LENGTH, &log_size);
				log_string.resize(log_size);
				glGetProgramInfoLog(shd_id, log_size, NULL, &log_string[0]);
				throw a_error(&log_string[0], ERC_LINKAGE, __FILE__, __LINE__);
				return false;
			}
		}
		return success_code == 1;
	}
}
namespace NWGFX
{
	// general
	pfn_ogl_shd_crt glCreateShader = NULL;
	pfn_ogl_shd_del glDeleteShader = NULL;
	pfn_ogl_shd_compile glCompileShader = NULL;
	// getters
	pfn_ogl_shd_get_iv glGetShaderiv = NULL;
	pfn_ogl_shd_get_info_log glGetShaderInfoLog = NULL;
	// setters
	pfn_ogl_shd_set_source glShaderSource = NULL;
	// predicates
	pfn_ogl_shd_is_shader glIsShader = NULL;
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NWGFX
{
	v1b gfx_load_shd()
	{
		D3DCompile = (pfn_gfx_shd_compile)gfx_get_proc("D3DCompile");

		return true;
	}
}
namespace NWGFX
{
	pfn_gfx_shd_compile D3DCompile = NULL;
}
#endif
#endif	// NW_GAPI