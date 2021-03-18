#ifndef NWG_STENCIL_STATE_H
#define NWG_STENCIL_STATE_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "nwg_stt.h"
namespace NW
{
	/// stencil_state class
	class NW_API stt_stenc : public a_gfx_stt
	{
		using func_type = stencil_configs;
		using oper_type = stencil_configs;
	public:
		stt_stenc(gfx_engine& graphics);
		~stt_stenc();
		// --getters
		inline ui8 get_mask() const			{ return m_mask; }
		inline func_type get_func() const	{ return m_func; }
		inline oper_type get_oper() const	{ return m_oper; }
		// --setters
		void set_mask(ui8 stencil_mask);
		void set_func(func_type stencil_function);
		void set_oper(oper_type stencil_operation);
		// --predicates
		// --core_methods
		virtual void on_draw() override;
	private:
		ui8 m_mask;
		func_type m_func;
		oper_type m_oper;
	};
}
#endif	// NW_GAPI
#endif	// NWG_STENCIL_STATE_H