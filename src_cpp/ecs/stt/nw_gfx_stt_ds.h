#ifndef NW_GFX_DEPTH_STENCIL_STATE_H
#define NW_GFX_DEPTH_STENCIL_STATE_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#include "nw_gfx_stt.h"
namespace NW
{
	/// gfx_stt_depth_stencil class
	class NW_API gfx_stt_ds : public a_gfx_stt
	{
#if (NW_GAPI & NW_GAPI_OGL)
		using handle = GLuint;
		using oper_stencil = GLenum;
		using func_stencil = GLenum;
		using func_depth = GLenum;
#endif
#if (NW_GAPI & NW_GAPI_D3D)
		using handle = ID3D11DepthStencilState*;
		using oper_stencil = D3D11_STENCIL_OP;
		using func_stencil = D3D11_COMPARISON_FUNC;
		using func_depth = D3D11_COMPARISON_FUNC;
#endif
	public:
		gfx_stt_ds(gfx_engine& graphics);
		~gfx_stt_ds();
		// --getters
		inline handle get_handle()                    { return m_handle; }
		inline v1u8 get_mask_depth() const            { return m_mask_depth; }
		inline v1u8 get_mask_stencil() const          { return m_mask_stencil; }
		inline oper_stencil get_oper_stencil() const  { return m_oper_stencil; }
		inline func_depth get_func_depth() const      { return m_func_depth; }
		inline func_stencil get_func_stencil() const  { return m_func_stencil; }
		// --setters
		void set_mask_stencil(v1u8 mask);
		void set_mask_depth(v1u8 mask);
		void set_func_depth(func_depth function);
		void set_func_stencil(func_stencil function);
		void set_oper_stencil(stencil_opers operation);
		void set_enabled_depth(v1b enable);
		void set_enabled_stencil(v1b enable);
		// --predicates
		v1b is_enabled_depth() const     { return m_is_enabled_depth; }
		v1b is_enabled_stencil() const   { return m_is_enabled_stencil; }
		// --core_methods
		v1b remake();
		virtual void on_draw() override;
	private:
		handle m_handle;
		v1b m_is_enabled_depth;
		v1b m_is_enabled_stencil;
		v1u8 m_mask_depth;
		v1u8 m_mask_stencil;
		func_depth m_func_depth;
		func_stencil m_func_stencil;
		oper_stencil m_oper_stencil;
	};
}
#endif	// NW_GAPI
#endif	// NW_DEPTH_STATE_H