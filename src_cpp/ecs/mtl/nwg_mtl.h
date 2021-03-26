#ifndef NWG_MATERIAL_H
#define NWG_MATERIAL_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include "../nwg_cmp.h"
#include "../shd/nwg_shd.h"
#include "../txr/nwg_txr.h"
#include "../buf/nwg_buf_shd.h"
namespace NW
{
	/// material class
	class NW_API gfx_mtl : public t_cmp<gfx_mtl>, public a_gfx_cmp, public a_data_cmp
	{
	public:
		using shd = mem_ref<a_shd>;
		using shds = darray<shd>;
		using buf = a_shd::buf;
		using bufs = a_shd::bufs;
		using txr = a_shd::txr;
		using txrs = a_shd::txrs;
#if (NW_GAPI & NW_GAPI_OGL)
		using handle = GLuint;
#endif
#if (NW_GAPI & NW_GAPI_DX)
		using handle = ptr;
#endif
	public:
		gfx_mtl(gfx_engine& graphics);
		virtual ~gfx_mtl();
		// --getters
		inline shd& get_shd(v1ui idx) { return m_shds[idx % m_shds.size()]; }
		inline handle get_handle()    { return m_handle; }
		// --setters
		void set_buf(v1ui shd_idx, buf& ref, v1ui buf_idx);
		void set_txr(v1ui shd_idx, txr& ref, v1ui txr_idx);
		void add_shd(shd& ref);
		void rmv_shd(v1ui idx);
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const override;
		virtual stm_in& operator>>(stm_in& stm) override;
		// --core_methods
		bit remake();
		virtual void on_draw() override;
	private:
		shds m_shds;
		handle m_handle;
	};
}

#endif	// NW_GAPI
#endif	// NWG_MATERIAL_H