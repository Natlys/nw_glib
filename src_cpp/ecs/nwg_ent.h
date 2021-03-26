#ifndef NWG_ENTITY_H
#define NWG_ENTITY_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "nwg_rsc.h"
#include "nwg_cmp.h"
namespace NW
{
	/// abstract graphics_entity class
	class NW_API a_gfx_ent : public t_ent<a_gfx_ent, a_gfx_cmp>, public a_gfx_rsc
	{
	public:
#	if (NW_GAPI & NW_GAPI_OGL)
		using prim = GLenum;
#	endif
#	if (NW_GAPI & NW_GAPI_DX)
		using prim = D3D11_PRIMITIVE_TOPOLOGY;
#	endif
	protected:
		a_gfx_ent(gfx_engine& graphics);
	public:
		virtual ~a_gfx_ent();
		// --getters
		inline primitives get_prim() const { return convert<prim, primitives>(m_prim); }
		// --setters
		void set_prim(primitives primitive);
		// --core_methods
		virtual void on_draw();
	protected:
		prim m_prim;
	};
}
#endif	// NW_GAPI
#endif	// NWG_ENTITY_H