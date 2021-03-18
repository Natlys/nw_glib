#ifndef NWG_ENGINE_H
#define NWG_ENGINE_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "nwg_cmp.h"
#include "../lib/nwg_tools.h"
namespace NW
{
	/// graphics_engine class
	class NW_API gfx_engine : public a_mem_user
	{
	public:
		using info = gfx_context_info;
		using device = device_handle;
		using context = context_handle;
		using config = gfx_config;
		using window = window_handle;
#if (NW_GAPI & NW_GAPI_DX)
		using swap_chain = IDXGISwapChain*;
		using draw_target = ID3D11RenderTargetView*;
#endif
		/// storable resource reference
		using cmp = mem_ref<a_gfx_cmp>;
		/// table for cmp_id - cmp_ref association
		using cmps = dictionary<ui32, cmp>;
		/// table for type_id - cmp_refs association;
		using registry = dictionary<ui32, cmps>;
	public:
		gfx_engine(window wnd);
		gfx_engine(const gfx_engine& copy) = delete;
		virtual ~gfx_engine();
		// --getters
		inline const info& get_info() const		{ return m_info; }
		inline const config& get_config() const	{ return m_config; }
		inline device get_device()				{ return m_device; }
		inline context get_context()			{ return m_context; }
		inline cmps& get_cmps(ui32 type_id)				{ return m_reg[type_id]; }
		template<class ctype> cmps& get_cmps()			{ return get_cmps(type_indexator::get_id<ctype>()); }
		inline cmp& get_cmp(ui32 type_id, ui32 cmp_id)	{ return m_reg[type_id][cmp_id]; }
		template<class ctype> cmp& get_cmp(ui32 cmp_id)	{ return get_cmp(type_indexator::get_id<ctype>(), cmp_id); }
		inline bit has_cmp(ui32 type_id, ui32 cmp_id)	{ return m_reg[type_id].find(cmp_id) != m_reg[type_id].end(); }
		template<class ctype> bit has_cmp(ui32 cmp_id)	{ return has_cmp(type_indexator::get_id<ctype>(), cmp_id); }
		// --setters
		void set_viewport(v4si viewport);
		void set_viewport(si32 crd_x, si32 crd_y, si32 size_x, si32 size_y);
		void set_clear_color(f32 red, f32 green, f32 blue, f32 alpha);
		void set_primitive(gfx_primitives primitive_topology);
		void set_vsync(bit enable);
		// --predicates
		inline bit is_vsync() const	{ return m_config.swap_interval == 1; }
		// --core_methods
		void update();
		/// --create new graphical resource by the ref of appropriate type
		template<typename ctype, typename ... args>
		mem_ref<ctype> new_cmp(args&& ... arguments);
		/// --create new graphical resource by the ref of abstract type
		template<typename actype, typename ctype, typename ... args>
		mem_ref<actype> new_cmp(args&& ... arguments);
		// delete any graphical resource
		void del_cmp(ui32 type_id, ui32 cmp_id);
		template<typename ctype> void del_cmp(ui32 cmp_id)	{ del_cmp(type_indexator::get_id<ctype>(), cmp_id); }
	private:
		info m_info;
		config m_config;
		window m_wnd;
		device m_device;
		context m_context;
		registry m_reg;
#if (NW_GAPI & NW_GAPI_DX)
		swap_chain m_swap_chain;
		draw_target m_draw_target;
#endif
	};
	template<typename ctype, typename ... args>
	mem_ref<ctype> gfx_engine::new_cmp(args&& ... arguments) {
		mem_ref<ctype> ref;
		ref.make_ref<ctype>(*this, std::forward<args>(arguments)...);
		m_reg[ref->get_type_id()][ref->get_cmp_id()].set_ref(ref);
		return ref;
	}
	template<typename actype, typename ctype, typename ... args>
	mem_ref<actype> gfx_engine::new_cmp(args&& ... arguments) {
		mem_ref<actype> ref;
		ref.make_ref<ctype>(*this, std::forward<args>(arguments)...);
		m_reg[ref->get_type_id()][ref->get_cmp_id()].set_ref<actype>(ref);
		return ref;
	}
}
#endif	// NW_GAPI
#endif	// NWG_ENGINE_H