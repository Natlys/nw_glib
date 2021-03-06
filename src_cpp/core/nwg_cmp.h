#ifndef NWG_COMPONENT_H
#define NWG_COMPONENT_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
namespace NWG
{
	/// abstract graphics_component class
	class NWG_API a_gfx_cmp
	{
	protected:
		a_gfx_cmp(gfx_engine& graphics);
	public:
		virtual ~a_gfx_cmp();
		// --getters
		virtual inline ptr get_native() = 0;
		// --core_methods
		virtual void on_draw() = 0;
	protected:
		gfx_engine* m_gfx;
	};
}
#endif	// NWG_GAPI
#endif	// NWG_COMPONENT_H