#ifndef NWG_DATA_H
#define NWG_DATA_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include <lib/nwg_const.h>
namespace NW
{
	struct NW_API vtx_2f
	{
		v2f vtx_crd = { 0.0f, 0.0f };
	};
	struct NW_API vtx_2f2f
	{
		v2f vtx_crd = { 0.0f, 0.0f };
		v2f tex_crd = { 0.0f, 0.0f };
	};
	struct NW_API vtx_2f2f4ui8
	{
		v2f vtx_crd = { 0.0f, 0.0f };
		v2f tex_crd = { 0.0f, 0.0f };
		v4ui8 vtx_clr = { 0u, 0u, 0u, 0u };
	};
	struct NW_API vtx_3f
	{
		v3f vtx_crd = { 0.0f, 0.0f, 0.0f };
	};
	struct NW_API vtx_3f2f
	{
		v3f vtx_crd = { 0.0f, 0.0f, 0.0f };
		v2f txr_crd = { 0.0f, 0.0f };
	};
	struct NW_API vtx_3f2f3f
	{
		v3f vtx_crd = { 0.0f, 0.0f, 0.0f };
		v2f tex_crd = { 0.0f, 0.0f };
		v3f nrm_crd = { 0.0f, 0.0f, 0.0f };
	};
}
namespace NW
{
	struct NW_API buf_16f {
		m4f model = m4f32(1.0f);
	};
	struct NW_API buf_16f16f {
		m4f view = m4f32(1.0f);
		m4f proj = m4f32(1.0f);
	};
	struct NW_API buf_16f16f16f {
		m4f model = m4f32(1.0f);
		m4f view = m4f32(1.0f);
		m4f proj = m4f32(1.0f);
	};
}
namespace NW
{
	/// templated graphics_data class
	/// description:
	/// --makes render data for primitives;
	/// interface:
	/// --add vertex data one by one;
	/// --update_idx_data for required topology;
	/// --use index and vertex data for drawing;
	template<typename vtype, typename itype = v1ui>
	class NW_API t_gfx_data
	{
		using cvtype = const vtype;
		using citype = const itype;
		using vertices = darray<vtype>;
		using cvertices = const darray<vtype>;
		using indices = darray<itype>;
		using cindices = const darray<itype>;
	public:
		t_gfx_data() :
			m_vtxs(vertices()), m_idxs(indices()), m_iter(0) { }
		// --getters
		inline cvertices& get_vtx_buf() const  { return m_vtxs; }
		inline cvtype* get_vtx_data() const    { return &m_vtxs[0]; }
		inline size get_vtx_count()	const      { return m_vtxs.size(); }
		inline vtype get_vtx(v1ui idx) const   { return m_vtxs[idx % m_vtxs.size()]; }
		inline cindices& get_idx_buf() const   { return m_idxs; }
		inline citype* get_idx_data() const    { return &m_idxs[0]; }
		inline v1ui get_idx_count()	const      { return m_idxs.size(); }
		inline itype get_idx(v1ui idx) const   { return m_idxs[idx % m_idxs.size()]; }
		// --setters
		void set_vtx_buf(cvertices& buffer)    { m_vtxs = buffer; }
		void add_vtx_buf(cvertices& buffer)    { for (auto& ivtx : buffer) { add_vtx(ivtx); } }
		void add_vtx(cvtype& vtx)              { m_vtxs.push_back(vtx); }
		// --core_methods
		void update_indices(primitives primitive_topology) {
			switch (primitive_topology) {
				if (m_vtxs.size() < 1) { break; }
			case PRIM_POINTS:
			case PRIM_LINE_LOOP:
			case PRIM_LINE_STRIP:
			case PRIM_TRIANGLE_FAN: {
				while (m_iter < m_vtxs.size() - 0) {
					m_idxs.push_back(m_iter + 0);
					m_iter++;
				}
				m_iter++;
				break;
			}
			case PRIM_LINES: {
				if (m_vtxs.size() < 2) { break; }
				while (m_iter < m_vtxs.size() - 1) {
					m_idxs.push_back(m_iter + 0);
					m_idxs.push_back(m_iter + 1);
					m_iter++;
				}
				m_iter++;
				break;
			}
			case PRIM_TRIANGLES: {
				if (m_vtxs.size() < 3) { break; }
				v1ui first = m_iter;
				while (m_iter < m_vtxs.size() - 2) {
					m_idxs.push_back(first);
					m_idxs.push_back(m_iter + 1);
					m_idxs.push_back(m_iter + 2);
					m_iter++;
				}
				m_iter++;
				break;
			}
			case PRIM_TRIANGLE_STRIP: {
				if (m_vtxs.size() < 3) { break; }
				v1ui first = m_iter;
				while (m_iter < m_vtxs.size() - 0) {
					m_idxs.push_back(first);
					m_idxs.push_back(m_iter + 0);
					m_iter++;
				}
				m_iter++;
				break;
			}
			default: break;
			}
		}
		void remake() {
			m_vtxs.clear();
			m_idxs.clear();
			m_iter = 0;
		}
	private:
		vertices m_vtxs;
		indices m_idxs;
		v1ui m_iter;
	};
}
#endif	// NWG_GAPI
#endif	// NWG_DATA_H