#ifndef NWG_DRAWABLE_H
#define NWG_DRAWABLE_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include <core/nwg_cmp.h>
#include <cmp/mtl/nwg_mtl.h>
namespace NW
{
	/// abstract drawable class
	class NW_API a_drb : public t_cmp<a_drb, a_gfx_cmp>
	{
		/// storable resource reference
		using cmp = mem_ref<a_gfx_cmp>;
		/// resource refs
		using cmps = darray<mem_ref<a_gfx_cmp>>;
		/// material reference
		using mtl = mem_ref<gfx_mtl>;
	protected:
		a_drb(gfx_engine& graphics);
	public:
		virtual ~a_drb();
		// --getters
		inline cmps& get_cmps()			{ return m_cmps; }
		inline cmp& get_cmp(ui8 idx)	{ return m_cmps[idx % m_cmps.size()]; }
		inline mtl& get_mtl()			{ return m_mtl; }
		// --setters
		void set_mtl(mtl& ref);
		// --core_methods
		void add_cmp(cmp& ref);
		template<class gtype> void add_cmp(mem_ref<gtype>& ref) { mem_ref<a_gfx_cmp> a_ref(ref); add_cmp(a_ref); }
		void rmv_cmp(ui8 idx);
		virtual void on_draw() override;
	protected:
		mtl m_mtl;
		cmps m_cmps;
	};
}
#endif	// NW_GAPI
#endif	// NWG_DRAWABLE_H