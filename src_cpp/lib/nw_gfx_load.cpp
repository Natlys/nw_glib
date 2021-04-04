#include "nw_gfx_pch.hpp"
#include "nw_gfx_load.h"
#if (defined NW_GAPI)
#include "nw_gfx_load_buf.h"
#include "nw_gfx_load_fmbuf.h"
#include "nw_gfx_load_layt.h"
#include "nw_gfx_load_smp.h"
#include "nw_gfx_load_txr.h"
#include "nw_gfx_load_shd.h"
#include "nw_gfx_load_mtl.h"
#include "nw_gfx_load_wapi.h"
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	gfx_lib_loader::gfx_lib_loader() :
		m_handle(NULL),
		m_ver_num(0), m_ver_str("default"),
		m_drawer("default"),
		m_vendor("default"),
		m_shd_lang("default"),
		m_pxl_range(0),
		m_pxl_gran(0),
		m_max_slot_txr(0),
		m_max_slot_atb(0)
	{
	}
	gfx_lib_loader::~gfx_lib_loader()
	{
	}
	// --getters
	ptr gfx_lib_loader::get_proc(cstr name) {
		
		ptr resource = wglGetProcAddress(name);
		if (resource == NULL) { resource = ::GetProcAddress(m_handle, name); }

		return resource;
	}
	// --==<core_methods>==--
	bool gfx_lib_loader::init()
	{
		if (m_handle == NULL) { return FALSE; }

		if (gfx_load_core() == TRUE) {
			if (glGetIntegerv == NULL) { return FALSE; }

			v1s version_nums[2] = { 0, 0 };
			glGetIntegerv(GL_MAJOR_VERSION, &version_nums[0]);
			glGetIntegerv(GL_MINOR_VERSION, &version_nums[1]);
			m_ver_num = (version_nums[0] * 100) + (version_nums[1] * 10);

			m_ver_str = reinterpret_cast<cstr>(glGetString(GL_VERSION));
			//m_ext_str = reinterpret_cast<cstr>(glGetString(GL_EXTENSIONS));
			m_drawer = reinterpret_cast<cstr>(glGetString(GL_RENDERER));
			m_vendor = reinterpret_cast<cstr>(glGetString(GL_VENDOR));
			m_shd_lang = reinterpret_cast<cstr>(glGetString(GL_SHADING_LANGUAGE_VERSION));

			glGetIntegerv(GL_POINT_SIZE_RANGE, &m_pxl_range);
			glGetIntegerv(GL_POINT_SIZE_GRANULARITY, &m_pxl_gran);
			glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &m_max_slot_txr);
			glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS, &m_max_slot_atb);
		}
		else { return FALSE; }
		if (gfx_load_buf() == TRUE) {
		}
		else { return FALSE; }
		if (gfx_load_fmbuf() == TRUE) {
		}
		else { return FALSE; }
		if (gfx_load_layt() == TRUE) {
		}
		else { return FALSE; }
		if (gfx_load_smp() == TRUE) {
		}
		else { return FALSE; }
		if (gfx_load_txr() == TRUE) {
		}
		else { return FALSE; }
		if (gfx_load_shd() == TRUE) {
		}
		else { return FALSE; }
		if (gfx_load_mtl() == TRUE) {
		}
		else { return FALSE; }
		// extensions
		if (gfx_ext_load_wapi() == TRUE) {
		}
		else { return FALSE; }

		return TRUE;
	}
	bool gfx_lib_loader::quit()
	{
		if (m_handle != NULL) { return FALSE; }
		
		m_ver_str = "default";
		m_drawer = "default";
		m_vendor = "default";
		m_shd_lang = "default";

		m_ver_num = 0;
		m_max_slot_atb = 0;
		m_max_slot_txr = 0;

		return TRUE;
	}
	bool gfx_lib_loader::load()
	{
		if (m_handle != NULL) { return FALSE; }

		m_handle = ::LoadLibrary("opengl32.dll");
		if (gfx_load_wapi() == TRUE) {
		}
		else { return FALSE; }

		return TRUE;
	}
	bool gfx_lib_loader::free()
	{
		if (m_handle == NULL) { return FALSE; }

		::FreeLibrary(m_handle);
		m_handle = NULL;

		return TRUE;
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_D3D)
#include "dxgi.h"
#include "d3dcompiler.h"
namespace NW
{
	static inline library_handle libh_comp = NULL;
	static inline library_handle libh_dxgi = NULL;

	gfx_lib_loader::gfx_lib_loader() :
		m_handle(NULL),
		m_ver_num(0), m_ver_str("default"),
		m_drawer("default"),
		m_vendor("default"),
		m_shd_lang("default"),
		m_pxl_range(0),
		m_pxl_gran(0),
		m_max_slot_txr(0),
		m_max_slot_atb(0)
	{
	}
	gfx_lib_loader::~gfx_lib_loader() { quit(); }
	// --getters
	ptr gfx_lib_loader::get_proc(cstr name) {
		ptr resource = NULL;

		resource = ::GetProcAddress(m_handle, name);
		if (resource == NULL) {
			resource = ::GetProcAddress(libh_dxgi, name);
		}
		if (resource == NULL) {
			resource = ::GetProcAddress(libh_comp, name);
		}

		return resource;
	}
	// --==<core_methods>==--
	bool gfx_lib_loader::init() {
		if (m_handle == NULL) { return FALSE; }

		if (gfx_load_core() == TRUE) {
		}
		else { return FALSE; }
		if (gfx_load_buf() == TRUE) {
		}
		else { return FALSE; }
		if (gfx_load_fmbuf() == TRUE) {
		}
		else { return FALSE; }
		if (gfx_load_layt() == TRUE) {
		}
		else { return FALSE; }
		if (gfx_load_smp() == TRUE) {
		}
		else { return FALSE; }
		if (gfx_load_txr() == TRUE) {
		}
		else { return FALSE; }
		if (gfx_load_shd() == TRUE) {
		}
		else { return FALSE; }
		if (gfx_load_mtl() == TRUE) {
		}
		else { return FALSE; }
		// extensions
		if (gfx_ext_load_wapi() == TRUE) {
		}
		else { return FALSE; }

		return TRUE;
	}
	bool gfx_lib_loader::quit()
	{
		if (m_handle != NULL) { return FALSE; }
		
		m_ver_str = "default";
		m_drawer = "default";
		m_vendor = "default";
		m_shd_lang = "default";

		m_ver_num = 0;
		m_max_slot_atb = 0;
		m_max_slot_txr = 0;

		return TRUE;
	}
	bool gfx_lib_loader::load()
	{
		if (m_handle != NULL) { return FALSE; }
		m_handle = ::LoadLibrary("d3d11.dll");
		
		if (libh_dxgi != NULL) { return FALSE; }
		libh_dxgi = ::LoadLibrary("dxgi.dll");
		
		if (libh_comp != NULL) { return FALSE; }
		libh_comp = ::LoadLibrary(D3DCOMPILER_DLL);

		if (gfx_load_wapi() == TRUE) {
		}
		else { return FALSE; }
		
		return TRUE;
	}
	bool gfx_lib_loader::free()
	{
		if (m_handle == NULL) { return FALSE; }
		::FreeLibrary(m_handle);
		m_handle = NULL;

		if (libh_dxgi == NULL) { return FALSE; }
		::FreeLibrary(libh_dxgi);
		libh_dxgi = NULL;

		if (libh_comp == NULL) { return FALSE; }
		::FreeLibrary(libh_comp);
		libh_comp = NULL;

		return TRUE;
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI