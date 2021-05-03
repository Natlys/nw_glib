#ifndef NW_GFX_TFORM_H
#define NW_GFX_TFORM_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#	include "../buf/nw_gfx_buf_shd.h"
#	include "../nw_gfx_cmp.h"
namespace NW
{
	/// graphics_transform class
	class NW_API gfx_tform : public gfx_buf_shd
	{
	public:
		using tform_t = gfx_tform;
		using tform_tc = const tform_t;
	public:
		gfx_tform();
		gfx_tform(tform_tc& copy);
		gfx_tform(tform_t&& copy);
		virtual ~gfx_tform();
		// --getters
		inline v3f get_crd() const { return m_crd; }
		inline v3f get_rtn() const { return m_rtn; }
		inline v3f get_scl() const { return m_scl; }
		inline cm4f get_modl() const { return get_elem("modl").get<m4f>(); }
		// --setters
		tform_t& set_crd(cv3f& coord);
		tform_t& set_rtn(cv3f& rotat);
		tform_t& set_scl(cv3f& scale);
		tform_t& set_modl(cm4f& modl);
		// --predicates
		inline v1bit has_crd_x(cv1f coord) const { return m_crd[0] == coord; }
		inline v1bit has_crd_y(cv1f coord) const { return m_crd[1] == coord; }
		inline v1bit has_crd_z(cv1f coord) const { return m_crd[2] == coord; }
		inline v1bit has_crd_xyz(cv3f& coord) const { return m_crd[0] == coord[0] && m_crd[1] == coord[1] && m_crd[2] == coord[2]; }
		// --operators
		inline tform_t& operator=(tform_tc& copy) { gfx_buf_shd::operator=(copy); return *this; }
		inline tform_t& operator=(tform_t&& copy) { gfx_buf_shd::operator=(copy); return *this; }
		// --core_methods
		virtual v1bit remake() override;
		virtual v1nil on_draw() override;
	protected:
		v3f m_crd;
		v3f m_rtn;
		v3f m_scl;
	};
}
#endif
#endif	// NW_GFX_TFORM_H