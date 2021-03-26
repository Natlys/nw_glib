#ifndef NWG_DEPTH_STENCIL_STATE_H
#define NWG_DEPTH_STENCIL_STATE_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "nwg_stt.h"
namespace NW
{
	/// gfx_stt_depth_stencil class
	class NW_API gfx_stt_ds : public a_gfx_stt
	{
#if (NW_GAPI & NW_GAPI_OGL)
		using handle = GLuint;
#endif
#if (NW_GAPI & NW_GAPI_DX)
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
		inline v1ui8 get_mask_depth() const           { return m_mask_depth; }
		inline v1ui8 get_mask_stencil() const         { return m_mask_stencil; }
		inline stencil_opers get_oper_stencil() const { return convert<oper_stencil, stencil_opers>(m_oper_stencil); }
		inline logic_opers get_func_depth() const     { return convert<func_depth, logic_opers>(m_func_depth); }
		inline logic_opers get_func_stencil() const   { return convert<func_stencil, logic_opers>(m_func_stencil); }
		// --setters
		void set_mask_stencil(v1ui8 mask);
		void set_mask_depth(v1ui8 mask);
		void set_func_depth(logic_opers function);
		void set_func_stencil(logic_opers function);
		void set_oper_stencil(stencil_opers operation);
		void set_enabled_depth(bit enable);
		void set_enabled_stencil(bit enable);
		// --predicates
		bit is_enabled_depth() const     { return m_is_enabled_depth; }
		bit is_enabled_stencil() const   { return m_is_enabled_stencil; }
		// --core_methods
		bit remake();
		virtual void on_draw() override;
	private:
		handle m_handle;
		bit m_is_enabled_depth;
		bit m_is_enabled_stencil;
		v1ui8 m_mask_depth;
		v1ui8 m_mask_stencil;
		func_depth m_func_depth;
		func_stencil m_func_stencil;
		oper_stencil m_oper_stencil;
	};
}
#endif	// NW_GAPI
#endif	// NW_DEPTH_STATE_H