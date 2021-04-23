#ifndef NW_GFX_MATERIAL_H
#define NW_GFX_MATERIAL_H
#include "nw_gfx_core.hpp"
#if (defined NW_GAPI)
#include "cmp/nw_gfx_cmp.h"
#include "../shd/nw_gfx_shd.h"
#include "../txr/nw_gfx_txr.h"
#include "../buf/nw_gfx_buf_shd.h"
namespace NW
{
	/// material class
	class NW_API gfx_mtl : public t_cmp<gfx_mtl>, public a_gfx_cmp, public a_iop_cmp
	{
	public:
		using shd_t = mem_ref<a_gfx_shd>;
		using shd_tc = const shd_t;
		using shds_t = t_darray<shd_t>;
		using shds_tc = const shd_t;
		using buf_t = a_gfx_shd::buf_t;
		using bufs_t = a_gfx_shd::bufs_tc;
		using txr_t = a_gfx_shd::txr_t;
		using txrs_t = a_gfx_shd::txrs_tc;
#if (NW_GAPI & NW_GAPI_OGL)
		using handle = GLuint;
#endif
#if (NW_GAPI & NW_GAPI_D3D)
		using handle = ptr;
#endif
	public:
		gfx_mtl();
		virtual ~gfx_mtl();
		// --getters
		inline shd_t& get_shd(cv1u key) { return m_shds[key]; }
		inline handle get_handle()    { return m_handle; }
		// --setters
		v1nil set_buf(cv1u key, buf_t& ref, cv1u buf_key);
		v1nil set_txr(cv1u shd_key, txr_t& ref, cv1u txr_key);
		v1nil add_shd(shd_t& ref);
		v1nil rmv_shd(cv1u key);
		// --operators
		virtual op_stream_t& operator<<(op_stream_t& stm) const override;
		virtual ip_stream_t& operator>>(ip_stream_t& stm) override;
		// --core_methods
		v1b remake();
		virtual v1nil on_draw() override;
	private:
		shds_t m_shds;
		handle m_handle;
	};
}

#endif	// NW_GAPI
#endif	// NW_GFX_MATERIAL_H
