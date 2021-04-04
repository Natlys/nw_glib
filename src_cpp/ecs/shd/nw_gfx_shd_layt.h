#ifndef NW_GFX_SHADER_LAYOUT_H
#define NW_GFX_SHADER_LAYOUT_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#include "../nw_gfx_cmp.h"
namespace NW
{
	/// shader_layout class
	/// description:
	/// --default input assembler tool for vertex shaders;
	/// --equivalent of the vertex array in opengl;
	class NW_API shd_layt : public t_cmp<shd_layt>, public a_gfx_cmp, public info_layt
	{
		using shd = mem_ref<a_shd>;
#if (NW_GAPI & NW_GAPI_D3D)
		using handle = ID3D11InputLayout*;
#endif
#if (NW_GAPI & NW_GAPI_OGL)
		using handle = GLuint;
#endif
	public:
		shd_layt(gfx_engine& graphics);
		shd_layt(gfx_engine& graphics, shd& shader, celems& elements);
		virtual ~shd_layt();
		// --getters
		inline handle get_handle() const { return m_handle; }
		// --core_methods
		v1b remake(mem_ref<a_shd>& shader, celems& elements);
		virtual void on_draw() override;
	private:
		handle m_handle;
		size m_stride;
	};
}
#endif	// NW_GAPI
#endif	// NW_SHADER_LAYOUT_H