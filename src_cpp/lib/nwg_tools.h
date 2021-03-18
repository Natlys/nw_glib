#ifndef NWG_TOOLS_H
#define NWG_TOOLS_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include <lib/nwg_switch.h>
namespace NW
{
	struct NW_API gfx_context_info : public a_info
	{
	public:
		sbyte renderer[256], version[256], vendor[256], shd_language[256];
		si32 max_vtx_attribs = 0;
		si32 max_textures = 0;
	public:
		gfx_context_info(cstr str_renderer = "default", cstr str_version = "default",
			cstr str_vendor = "default", cstr str_shd_lang = "default");
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const override;
		virtual stm_in& operator>>(stm_in& stm) override;
	};
}
namespace NW
{
	struct NW_API gfx_config
	{
		gfx_primitives prim_type = GPT_DEFAULT;
		si32 swap_interval = 1u;
		v4si viewport = { 0, 0, 800, 600 };
		v4f clear_color = { 0.3f, 0.5f, 0.7f, 1.0f };
	};
}
namespace NW
{
	extern NW_API void gfx_clear_err();
	extern NW_API bit gfx_get_err_log(cstr* info, cstr location, si32 line);
	extern NW_API bit gfx_get_err_log(shd_types shd_type, si32 shd_id);
}
#	if (defined NW_DEBUG)
#		define NW_DEBUG_CALL(code) ( gfx_clear_err(); (code) if (gfx_get_err_log(#code, __FILE__, __LINE__, "GL_ERROR: ") == false) { NW_BREAK(); } )
#	else
#		define NW_DEBUG_CALL(code) (code)
#	endif
#endif	// NW_GAPI
#endif	// NWG_TOOLS_H