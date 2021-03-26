#ifndef NWG_CONSTANT_H
#define NWG_CONSTANT_H
#include <nwg_core.hpp>
#ifdef NW_GAPI
namespace NW
{
	enum primitives : v1ui {
		PRIM_DEFAULT = 0,
		PRIM_POINTS = 1,
		PRIM_LINES,
		PRIM_LINE_LOOP,
		PRIM_LINE_STRIP,
		PRIM_TRIANGLES,
		PRIM_TRIANGLE_STRIP,
		PRIM_TRIANGLE_FAN,
	};
	enum fill_modes : v1ui {
		FILL_DEFAULT = 0,
		FILL_LINE,
		FILL_FACE,
	};
	enum cull_modes : v1ui {
		CULL_DEFAULT = 0,
		CULL_CW,
		CULL_CCW,
	};
	enum blend_factors : v1ui {
		BLEND_SRC_DEFAULT = 0,
		BLEND_DST_DEFAULT = 0,
		BLEND_SRC_ALPHA,
		BLEND_DST_ALPHA,
		BLEND_SRC_COLOR,
		BLEND_DST_COLOR,
		BLEND_ONE_MINUS_SRC_ALPHA,
		BLEND_ONE_MUNUS_DST_ALPHA,
		BLEND_ONE_MINUS_SRC_COLOR,
		BLEND_ONE_MINUS_DST_COLOR,
	};
	enum stencil_opers : v1ui {
		STENC_DEFAULT = 0,
		STENC_INCR,
		STENC_DECR,
		STENC_KEEP,
		STENC_ZERO,
		STENC_REPL,
		STENC_INVERT,
	};
	enum texture_wraps : v1ui {
		TXW_DEFAULT = 0,
		TXW_REPEAT,
		TXW_CLAMP,
		TXW_BORDER,
	};
	enum texture_filters : v1ui {
		TXFL_DEFAULT = 0,
		TXFL_LINEAR,
		TXFL_NEAREST,
	};
	enum texture_formats : v1ui {
		TXF_DEFAULT = 0u,
		TXF_RGB,
		TXF_RGBA,
		TXF_MONO,
		TXF_IDX,
		TXF_DEPTH,
		TXF_STENCIL,
		TXF_DEPTH_STENCIL,
	};
}
#endif	// NW_GAPI
#endif	// NWG_CONSTANT_H