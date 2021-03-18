#ifndef NWG_DEPTH_STATE_H
#define NWG_DEPTH_STATE_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "nwg_stt.h"
namespace NW
{
	/// state_depth class
	class NW_API stt_depth : public a_gfx_stt
	{
		using fn_type = depth_configs;
	public:
		stt_depth(gfx_engine& graphics);
		~stt_depth();
		// --getters
		inline bit get_mask() const		{ return m_mask; }
		inline fn_type get_func() const	{ return m_function; }
		// --setters
		void set_mask(bit enable);
		void set_func(fn_type function);
		// --predicates
		// --core_methods
		virtual void on_draw() override;
	private:
		bit m_mask;
		fn_type m_function;
	};
}
#endif	// NW_GAPI
#endif	// NW_DEPTH_STATE_H