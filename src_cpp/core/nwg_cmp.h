#ifndef NWG_COMPONENT_H
#define NWG_COMPONENT_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
namespace NW
{
	/// abstract graphics_resource class
	class NW_API a_gfx_cmp : public a_cmp
	{
	protected:
		a_gfx_cmp(gfx_engine& graphics);
	public:
		virtual ~a_gfx_cmp();
		// --getters
		virtual inline ui32 get_type_id() const = 0;
		virtual inline ui32 get_cmp_id() const = 0;
		// --core_methods
		virtual void on_draw() = 0;
	protected:
		gfx_engine* m_gfx;
	};
}
#endif	// NW_GAPI
#endif	// NWG_COMPONENT_H