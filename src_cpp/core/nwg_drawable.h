#ifndef NWG_DRAWABLE_H
#define NWG_DRAWABLE_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <core/nwg_cmp.h>
#include <cmp/nwg_vtx_buf.h>
#include <cmp/nwg_idx_buf.h>
namespace NWG
{
	/// abstract drawable class
	class NWG_API a_drawable : public a_gfx_cmp
	{
		/// storable component reference
		using cmp_ref = mem_ref<a_gfx_cmp>;
		/// component refs
		using cmps = darray<mem_ref<a_gfx_cmp>>;
	public:
		a_drawable(gfx_engine& graphics);
		virtual ~a_drawable();
		// --getters
		virtual inline ptr get_native() override	{ return &m_order; }
		inline cmps& get_cmps()						{ return m_cmps; }
		inline cmp_ref& get_cmp(ui8 idx)			{ return m_cmps[idx % m_cmps.size()]; }
		// --setters
		void set_order(ui8 order);
		// --core_methods
		void add_cmp(cmp_ref& ref);
		template<class gtype> void add_cmp(mem_ref<gtype>& ref) { mem_ref<a_gfx_cmp> a_ref(ref); add_cmp(a_ref); }
		void rmv_cmp(ui8 idx);
		virtual void on_draw() = 0;
	protected:
		ui8 m_order;
		cmps m_cmps;
	};
}
namespace NWG
{
	/// indexed drawable class
	class NWG_API idx_drawable : public a_drawable, public t_cmp<idx_drawable>
	{
		using buffer = mem_ref<idx_buf>;
	public:
		idx_drawable(gfx_engine& graphics);
		virtual ~idx_drawable();
		// --getters
		buffer& get_buffer()			{ return m_ibuf; }
		// --setters
		// --core_methods
		virtual void on_draw() override;
	private:
		buffer m_ibuf;
	};
}
#endif
#endif	// NWG_DRAWABLE_H