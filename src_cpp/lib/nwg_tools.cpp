#include <nwg_pch.hpp>
#include "nwg_tools.h"
#pragma warning (disable: 4312)
#if (defined NW_GAPI)
#include <lib/nwg_load_core.h>
#include <lib/nwg_load_shd.h>
#include <lib/nwg_load_mtl.h>
namespace NW
{
	gfx_context_info::gfx_context_info(cstr str_renderer, cstr str_version,
		cstr str_vendor, cstr str_shd_lang) :
		renderer("default"), version("default"), vendor("default"), shd_language("default")
	{
		strcpy_s(&renderer[0], 256, &str_renderer[0]);
		strcpy_s(&version[0], 256, &str_version[0]);
		strcpy_s(&vendor[0], 256, &str_vendor[0]);
		strcpy_s(&shd_language[0], 256, &shd_language[0]);
	}
	// --operators
	stm_out& gfx_context_info::operator<<(stm_out& stm) const {
		return stm <<
			"--==<graphics_context_info>==--" << std::endl <<
			"graphics context: " << &version[0] << std::endl <<
			"renderer: " << &renderer[0] << std::endl <<
			"vendor: " << &vendor[0] << std::endl <<
			"shading language: " << &shd_language[0] << std::endl <<
			"--==</graphics_info>==--" << std::endl;
	}
	stm_in& gfx_context_info::operator>>(stm_in& stm) {
		return stm >> version >> renderer >> version >> vendor >> shd_language;
	}
}
#if (NW_GAPI & NW_GAPI_OGL)
// --functions
namespace NW
{
	void gfx_clear_err() { while (glGetError() != GL_NO_ERROR); }
	bit gfx_get_err_log(cstr strLoc, cstr strFile, si32 nLine)
	{
		si32 err_code = 0u;
		while ((err_code = glGetError()) != GL_NO_ERROR) {
			dstr err_comment;
			switch (err_code) {
			case GL_INVALID_ENUM: err_comment = "INVALID_ENUM"; break;
			case GL_INVALID_VALUE: err_comment = "INVALID_VALUE"; break;
			case GL_INVALID_OPERATION: err_comment = "INVALID_OPERATION"; break;
			case GL_STACK_OVERFLOW: err_comment = "STACK_OVERFLOW"; break;
			case GL_STACK_UNDERFLOW: err_comment = "STACK_UNDERFLOW"; break;
			case GL_OUT_OF_MEMORY: err_comment = "OUT_OF_MEMORY"; break;
			}
			throw (a_error(&err_comment[0], err_code, strLoc, nLine));
			return false;
		}
		return true;
	}
	bit gfx_get_err_log(shd_types shd_type, si32 idx)
	{
		if (idx == 0) { return false; }
		si32 success_code = 0;
		si32 log_size = 0;
		dstr log_string;
		cstr type_string = convert_enum<shd_types, cstr>(shd_type);
		if (shd_type != SHD_PROG) {
			glGetShaderiv(idx, GL_COMPILE_STATUS, &success_code);
			if (success_code == 0) {
				glGetShaderiv(idx, GL_INFO_LOG_LENGTH, &log_size);
				log_string.resize(log_size);
				glGetShaderInfoLog(idx, log_size, NULL, &log_string[0]);
				throw a_error(&log_string[0], ERC_COMPILLATION, __FILE__, __LINE__);
				return false;
			}
		}
		else {
			glGetProgramiv(idx, GL_LINK_STATUS, &success_code);
			if (success_code == 0) {
				glGetProgramiv(idx, GL_INFO_LOG_LENGTH, &log_size);
				log_string.resize(log_size);
				glGetProgramInfoLog(idx, log_size, NULL, &log_string[0]);
				throw a_error(&log_string[0], ERC_LINKAGE, __FILE__, __LINE__);
				return false;
			}
		}
		return success_code == 1;
	}
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	void gfx_err_log() {
		//
	}
	bit gfx_err_log(cstr stinfo, cstr strFile, int nLine) {
		return false;
	}
}
#endif
#endif	// NW_GAPI