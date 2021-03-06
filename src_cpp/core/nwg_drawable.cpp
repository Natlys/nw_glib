#include <nwg_pch.hpp>
#include "nwg_drawable.h"
#if (defined NWG_GAPI)
#include <core/nwg_engine.h>
#if (NWG_GAPI & NWG_GAPI_OGL)
#include <lib/nwg_ogl_v1.h>
namespace NWG
{
	a_drawable::a_drawable(gfx_engine& graphics) :
		a_gfx_cmp(graphics), m_order(0) { }
	a_drawable::~a_drawable() { }
	// --setters
	void a_drawable::set_order(ui8 order)	{ m_order = order; }
	void a_drawable::add_cmp(cmp_ref& ref)	{ m_cmps.push_back(ref); }
	void a_drawable::rmv_cmp(ui8 idx)		{ m_cmps.erase(m_cmps.begin() + idx); }
}
namespace NWG
{
	idx_drawable::idx_drawable(gfx_engine& graphics) :
		a_drawable(graphics), t_cmp()
	{
	}
	idx_drawable::~idx_drawable() { }
	// --==<core_methods>==--
	void idx_drawable::on_draw()
	{
		for (auto icmp : m_cmps) {
			icmp->on_draw();
		}
		m_ibuf->on_draw();
		glDrawElements(convert_enum<gfx_primitives, GLenum>(m_gfx->get_configs().prim_type),
			m_ibuf->get_data_count(), convert_enum<data_types, GLenum>(m_ibuf->get_data_type()), NULL);
	}
}
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
#include <lib/nwg_dx_loader.h>
namespace NWG
{
	//
}
#endif
#endif	// NWG_GAPI