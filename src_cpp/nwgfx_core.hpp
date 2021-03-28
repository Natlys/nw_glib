#ifndef NWGFX_CORE_HPP
#define NWGFX_CORE_HPP
// --==<configuration>==--
#define NW_BUILD_DLL
// --==</configurations>==--
#include "nwgfx_pch.hpp"
#if (defined NW_GAPI)
namespace NWGFX
{
	class NW_API gfx_engine;
	class NW_API a_gfx_cmp;

	class NW_API a_gfx_ent;
	class NW_API gfx_ent_vtx;
	class NW_API gfx_ent_idx;

	class NW_API gfx_mtl;
	
	class NW_API fmbuf;
	
	class NW_API gfx_buf_vtx;
	class NW_API gfx_buf_idx;
	class NW_API gfx_buf_shd;

	class NW_API a_shd;
	class NW_API shd_vtx;
	class NW_API shd_pxl;
	class NW_API shd_gmt;

	class NW_API a_img_cmp;
	class NW_API a_gfx_txr;
	class NW_API gfx_txr_1d;
	class NW_API gfx_txr_2d;
	class NW_API gfx_txr_2d_mulsmp;
	class NW_API gfx_txrfont;
	class NW_API gfx_txr_cube;
	class NW_API gfx_txr_smp;

	class NW_API a_gfx_stt;
	class NW_API gfx_stt_ds;
	class NW_API stt_stenc;
	class NW_API gfx_stt_draw;
	class NW_API stt_cull;
	class NW_API stt_blend;
	class NW_API stt_scis;
	class NW_API stt_viewp;

	class NW_API gfx_cam;
	class NW_API gfx_cam_lad;
#if (defined NW_GAPI)
#	if (NW_GAPI & NW_GAPI_OGL)
#	if (defined GLbyte)
#		undef GLbyte
#	endif	// GLbyte
	using GLbyte = signed char;
#	if (defined GLubyte)
#		undef GLubyte
#	endif	// GLubyte
	using GLubyte = unsigned char;
#	if (defined GLint)
#		undef GLint
#	endif	// GLint
	using GLint = signed int;
#	if (defined GLuint)
#		undef GLuint
#	endif	// GLuint
	using GLuint = unsigned int;
#	if (defined GLenum)
#		undef GLenum
#	endif	// GLenum
	using GLenum = unsigned int;
#	endif
#	if (NW_GAPI & NW_GAPI_DX)
#	endif
#endif	// NW_GAPI
}
#endif	// NW_GAPI
#endif	// NWGFX_CORE_HPP