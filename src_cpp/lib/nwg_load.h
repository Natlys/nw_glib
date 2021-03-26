#ifndef NWG_LOAD_H
#define NWG_LOAD_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
namespace NW
{
	/// graphics_library
	class NW_API gfx_lib_loader : public t_singleton<gfx_lib_loader>
	{
		friend class t_singleton<gfx_lib_loader>;
		using handle = library_handle;
		using chandle = const library_handle;
	private:
		gfx_lib_loader();
	public:
		~gfx_lib_loader();
		inline handle get_handle()           { return m_handle; }
		inline chandle get_handle() const    { return m_handle; }
		ptr get_proc(cstr proc_name);
		// --getters
		inline v1ui get_ver_num() const      { return m_ver_num; }
		inline v1ui get_ver_major() const    { return (m_ver_num / 100); }
		inline v1ui get_ver_minor() const    { return (m_ver_num / 10) % 10; }
		inline cstr get_ver_str() const      { return &m_ver_str[0]; }
		inline cstr get_ext_str() const      { return &m_ext_str[0]; }
		inline cstr get_drawer() const       { return &m_drawer[0]; }
		inline cstr get_vendor() const       { return &m_vendor[0]; }
		inline cstr get_shd_lang() const     { return &m_shd_lang[0]; }
		inline v1ui get_max_slot_atb() const { return m_max_slot_atb; }
		inline v1ui get_max_slot_txr() const { return m_max_slot_txr; }
		// --predicates
		inline bool has_support(v1ui major, v1ui minor) const {
			if (get_ver_major() == major) { return true; } return true;
		}
		// --core_methods
		bool init();
		bool quit();
		bool load();
		bool free();
	private:
		handle m_handle;
		v1ui m_ver_num;
		dstr m_ext_str;
		dstr m_ver_str;
		dstr m_drawer;
		dstr m_vendor;
		dstr m_shd_lang;
		v1si m_max_slot_atb;
		v1si m_max_slot_txr;
		v1si m_pxl_range;
		v1si m_pxl_gran;
	};
	inline library_handle gfx_get_lib()     { return gfx_lib_loader::get().get_handle(); }
	inline ptr gfx_get_proc(cstr proc_name) { return gfx_lib_loader::get().get_proc(proc_name); }
}
#endif	// NW_GAPI
#endif	// NWG_LOAD_H