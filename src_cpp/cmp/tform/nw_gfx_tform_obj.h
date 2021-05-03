#ifndef NW_GFX_TRANSFORM_OBJECT_H
#define NW_GFX_TRANSFORM_OBJECT_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#	include "nw_gfx_tform.h"
namespace NW
{
	/// graphics_transform_object class
	class NW_API gfx_tform_obj : public gfx_tform
	{
	public:
		using obj_t = gfx_tform_obj;
		using obj_tc = const obj_t;
	public:
		gfx_tform_obj();
		gfx_tform_obj(obj_tc& copy);
		gfx_tform_obj(obj_t&& copy);
		virtual ~gfx_tform_obj();
		// --getters
		// --setters
		// --predicates
		// --operators
		inline obj_t& operator=(obj_tc& copy) { NW_CHECK(remake(), "remake error!", return *this); return *this; }
		inline obj_t& operator=(obj_t&& copy) { NW_CHECK(remake(), "remake error!", return *this); return *this; }
		// --core_methods
		virtual v1bit remake() override;
		virtual v1nil on_draw() override;
	protected:
	};
}
#endif	// NW_GAPI
#endif	// NW_GFX_TRANSFORM_OBJECT_H