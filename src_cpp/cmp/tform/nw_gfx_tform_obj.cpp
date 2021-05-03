#include "nw_gfx_pch.hpp"
#include "nw_gfx_tform_obj.h"
#if (defined NW_GAPI)
#	include "../../core/nw_gfx_engine.h"
namespace NW
{
	gfx_tform_obj::gfx_tform_obj() : gfx_tform()
	{
		set_layt(layt_tc("tform_obj", layt_t::elem_list_tc
			{
				mem_layt("modl", type_info::get_type<m4f>()),
			}
		)).set_count(1u);
	}
	gfx_tform_obj::gfx_tform_obj(obj_tc& copy) : gfx_tform_obj() { operator=(copy); }
	gfx_tform_obj::gfx_tform_obj(obj_t&& copy) : gfx_tform_obj() { operator=(copy); }
	gfx_tform_obj::~gfx_tform_obj() { }
	// --setters
	// --operators
	// --==<core_methods>==--
	v1bit gfx_tform_obj::remake()
	{
		NW_CHECK(gfx_tform::remake(), "remake error!", return NW_FALSE);

		return NW_TRUE;
	}
	v1nil gfx_tform_obj::on_draw()
	{
		gfx_tform::on_draw();
		//set_modl( m4f::make_rotat_xyz(get_rtn()) );
		//set_modl( m4f::make_coord(get_crd()) );
		set_modl( m4f::make_ident() );
	}
	// --==</core_methods>==--
}
#endif	// NW_GAPI