#ifndef NWG_FRAMEBUFFER_H
#define NWG_FRAMEBUFFER_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include <core/nwg_cmp.h>
#include <cmp/txr/nwg_txr.h>
namespace NW
{
	/// framebuffer class
	class NW_API fmbuf : public t_cmp<fmbuf, a_gfx_cmp>, public a_data_rsc
	{
		using depth = mem_ref<a_txr>;
		using stencil = mem_ref<a_txr>;
		using color = mem_ref<a_txr>;
		using colors = darray<color>;
#if (NW_GAPI & NW_GAPI_OGL)
		using handle = GLuint;
#endif
#if (NW_GAPI & NW_GAPI_DX)
		using handle = ID3D11RenderTargetView*;
#endif
	public:
		fmbuf(gfx_engine& graphics, cstr name);
		virtual ~fmbuf();
		// --getters
		inline handle get_handle()			{ return m_handle; }
		inline si32 get_size_x() const		{ return m_viewport[2] - m_viewport[0]; }
		inline si32 get_size_y() const		{ return m_viewport[3] - m_viewport[1]; }
		inline v4si get_viewport() const	{ return m_viewport; }
		inline v4f get_clear_color() const	{ return m_clear_color; }
		inline depth& get_depth_buf()		{ return m_depth; }
		inline stencil& get_stencil_buf()	{ return m_stencil; }
		inline color& get_color(ui8 idx)	{ return m_colors[idx % m_colors.size()]; }
		// --setters
		void set_viewport(const v4si& viewport_rect);
		void set_clear_color(const v4f& clear_color);
		void add_draw_target(color& ref);
		void rmv_draw_target(ui8 idx);
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const override;
		virtual stm_in& operator>>(stm_in& stm) override;
		// --core_methods
		bit remake();
		void clear();
		void read_pixels(ptr data_ptr, ui8 attach_idx, const v4si& read_rect);
		void draw_pixels(ptr data_ptr, ui8 attach_idx, const v4si& draw_rect);
		virtual void on_draw() override;
	protected:
		handle m_handle;
		v4f m_clear_color;
		v4si m_viewport;
		bit is_swap_chain_target;
		depth m_depth;
		stencil m_stencil;
		colors m_colors;
		darray<ui32> color_ids;
	};
}
#endif	// NW_GAPI
#endif // NWG_FRAMEBUFFER_H