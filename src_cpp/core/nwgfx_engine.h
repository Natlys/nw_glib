#ifndef NWGFX_ENGINE_H
#define NWGFX_ENGINE_H
#include "nwgfx_core.hpp"
#if (defined NW_GAPI)
#include <ecs/nwgfx_ent.h>
#include <ecs/nwgfx_cmp.h>
#include <lib/nwgfx_load.h>
namespace NWGFX
{
	/// graphics_engine class
	class NW_API gfx_engine : public t_ent_sys<a_gfx_ent>, public t_cmp_sys<a_gfx_cmp>, public a_mem_user
	{
	public:
		using dvch = device_handle;
		using ctxh = context_handle;
		using wndh = window_handle;
#	if (NW_GAPI & NW_GAPI_OGL)
		using prim = GLenum;
#	endif
#if (NW_GAPI & NW_GAPI_DX)
		using prim = D3D11_PRIMITIVE_TOPOLOGY;
		using swap_chain = IDXGISwapChain*;
		using draw_target = ID3D11RenderTargetView*;
#endif
	public:
		gfx_engine(wndh window);
		gfx_engine(const gfx_engine& copy) = delete;
		virtual ~gfx_engine();
		// --getters
		inline wndh get_wndh()          { return m_wndh; }
		inline wndh get_wndh() const    { return m_wndh; }
		inline dvch get_dvch()          { return m_dvch; }
		inline dvch get_dvch() const    { return m_dvch; }
		inline ctxh get_ctxh()          { return m_ctxh; }
		inline ctxh get_ctxh() const    { return m_ctxh; }
		inline cv4f& get_viewport() const  { return m_viewport; }
		inline cv4f& get_clear_clr() const { return m_clear_color; }
		inline v1u get_swap_delay() const  { return m_swap_delay; }
		inline primitives get_prim() const { return convert<prim, primitives>(m_prim); }
		// --setters
		void set_fbuf_size(v1u size_x, v1u size_y);
		void set_viewport(v4f viewport);
		void set_viewport(v1f crd_x, v1f crd_y, v1f size_x, v1f size_y);
		void set_clear_color(v4f clear_color);
		void set_clear_color(v1f red, v1f green, v1f blue, v1f alpha = 1.0f);
		void set_swap_delay(v1u swap_delay);
		void set_prim(primitives primitive);
		// --predicates
		// --core_methods
		void update();
		void draw_vtx(gfx_buf_vtx* buffer);
		void draw_vtx(v1u buffer_id);
		void draw_idx(gfx_buf_idx* buffer);
		void draw_idx(v1u buffer_id);
		// --entity_methods
		template<class et, typename ... args>
		ent<et> new_ent(args&& ... arguments) {
			static_assert(NW_CHECK_TYPE_BASE(a_gfx_ent, et), "entity type must be relative to the a_gfx_ent");
			ent<et> ref;
			ref.make_ref<et>(*this, std::forward<args>(arguments)...);
			m_ent_reg[ref->get_type()][ref->get_id()].set_ref(ref);
			return ref;
		}
		template<class aet, class et, typename ... args>
		ent<aet> new_ent(args&& ... arguments) {
			static_assert(NW_CHECK_TYPE_BASE(a_gfx_ent, et), "entity type must be relative to the a_gfx_ent");
			static_assert(NW_CHECK_TYPE_BASE(a_gfx_ent, aet), "abstract entity type must be relative to the a_gfx_ent");
			ent<aet> ref;
			ref.make_ref<et>(*this, std::forward<args>(arguments)...);
			m_ent_reg[ref->get_type()][ref->get_id()].set_ref(ref);
			return ref;
		}
		void del_ent(v1u t_id, v1u e_id) {
			if (!has_ent(t_id, e_id)) { return; }
			m_ent_reg[t_id].erase(e_id);
		}
		template<class et>
		void del_ent(v1u e_id) {
			if (!has_ent<et>(e_id)) { return; }
			m_ent_reg[et::get_type_static()].erase(e_id);
		}
		// --component_methods
		/// create particular type and get particular ref
		template<class ct, typename ... args>
		cmp<ct> new_cmp(args&& ... arguments) {
			static_assert(NW_CHECK_TYPE_BASE(a_gfx_cmp, ct), "component type must be relative to the a_gfx_ent");
			cmp<ct> ref;
			ref.make_ref<ct>(*this, std::forward<args&>(arguments)...);
			m_cmp_reg[ref->get_type()][ref->get_id()].set_ref(ref);
			return ref;
		}
		/// create particular type but get the abstract ref
		template<class act, class ct, typename ... args>
		cmp<act> new_cmp(args&& ... arguments) {
			static_assert(NW_CHECK_TYPE_BASE(a_gfx_cmp, ct), "component type must be relative to the a_gfx_ent");
			static_assert(NW_CHECK_TYPE_BASE(a_gfx_cmp, act), "abstract component type must be relative to the a_gfx_ent");
			cmp<act> ref;
			ref.make_ref<ct>(*this, std::forward<args&>(arguments)...);
			m_cmp_reg[ref->get_type()][ref->get_id()].set_ref(ref);
			return ref;
		}
		void del_cmp(v1u t_id, v1u c_id) {
			if (!has_cmp(t_id, c_id)) { return; }
			m_cmp_reg[t_id].erase(c_id);
		}
		template<class ct>
		void del_cmp(v1u c_id) {
			if (!has_cmp<ct>(c_id)) { return; }
			m_cmp_reg[ct::get_type_static()].erase(c_id);
		}
	private:
		wndh m_wndh;
		dvch m_dvch;
		ctxh m_ctxh;
		v4f m_clear_color;
		v4f m_viewport;
		v1u m_swap_delay;
		prim m_prim;
#if (NW_GAPI & NW_GAPI_DX)
		swap_chain m_swap_chain;
		draw_target m_draw_target;
#endif
	};
}
#endif	// NW_GAPI
#endif	// NWGFX_ENGINE_H