#ifndef NW_GFX_FRAMEBUFFER_H
#define NW_GFX_FRAMEBUFFER_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#include "../nw_gfx_cmp.h"
#include "../txr/nw_gfx_txr.h"
namespace NW
{
	/// framebuffer class
	class NW_API fmbuf : public t_cmp<fmbuf>, public a_gfx_cmp, public a_io_cmp
	{
		using depth = mem_ref<a_gfx_txr>;
		using stencil = mem_ref<a_gfx_txr>;
		using target = mem_ref<a_gfx_txr>;
		using targets = darray<target>;
#if (NW_GAPI & NW_GAPI_OGL)
		using handle = GLuint;
#endif
#if (NW_GAPI & NW_GAPI_D3D)
		using handle = ID3D11RenderTargetView*;
#endif
	public:
		fmbuf(gfx_engine& graphics);
		virtual ~fmbuf();
		// --getters
		inline handle get_handle()         { return m_handle; }
		inline v1s get_size_x() const      { return m_size[0]; }
		inline v1s get_size_y() const      { return m_size[1]; }
		inline depth& get_depth()          { return m_depth; }
		inline stencil& get_stencil()      { return m_stencil; }
		inline target& get_target(v1u idx) { return m_targets[idx % m_targets.size()]; }
		// --setters
		void add_target(target& ref);
		void rmv_target(v1u idx);
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const override;
		virtual stm_in& operator>>(stm_in& stm) override;
		// --core_methods
		v1b remake(v2u size_xy);
		void read_pixels(ptr data_ptr, v1u target_idx, const v4s& read_rect);
		void draw_pixels(cptr data_ptr, v1u target_idx, const v4s& draw_rect);
		void clear();
		virtual void on_draw() override;
	protected:
		handle m_handle;
		v2u m_size;
		depth m_depth;
		stencil m_stencil;
		targets m_targets;
	};
}
#endif	// NW_GAPI
#endif // NW_GFX_FRAMEBUFFER_H
