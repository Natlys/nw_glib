#include "nwgfx_pch.hpp"
#include "nwgfx_const.h"
#if (defined NW_GAPI)
#include <lib/nwgfx_load_core.h>
#include <lib/nwgfx_load_txr.h>
#include <lib/nwgfx_load_buf.h>
#include <lib/nwgfx_load_fmbuf.h>
#include <lib/nwgfx_load_shd.h>
using namespace NWGFX;
namespace NWLIB
{
	template<> v1s convert<pixel_formats, v1s>(pixel_formats format) {
		switch (format) {
		case PXF_R8_S8: return 1;
		case PXF_R8_U8: return 1;
		case PXF_R16_S16: return 2;
		case PXF_R16_U16: return 2;
		case PXF_R8G8B8_S32: return 3;
		case PXF_R32_S32: return 4;
		case PXF_R32_U32: return 4;
		case PXF_R8G8B8A8_S32: return 4;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return 0;
	}
	template<> pixel_formats convert<v1s, pixel_formats>(v1s nof_channels) {
		switch (nof_channels) {
		case 1: return PXF_R8_U8;
		case 2: return PXF_R8G8_U16;
		case 3: return PXF_R8G8B8_U32;
		case 4: return PXF_R8G8B8A8_U32;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return PXF_DEFAULT;
	}
	template<> v1s convert<texture_formats, v1s>(texture_formats format) {
		switch (format) {
		case PXF_R8_S8: return 1;
		case PXF_R8_U8: return 1;
		case PXF_R16_S16: return 2;
		case PXF_R16_U16: return 2;
		case PXF_R8G8B8_S32: return 3;
		case PXF_R32_S32: return 4;
		case PXF_R32_U32: return 4;
		case PXF_R8G8B8A8_S32: return 4;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return 0;
	}
	template<> texture_formats convert<v1s, texture_formats>(v1s nof_channels) {
		switch (nof_channels) {
		case 1: return TXF_IDX;
		case 2: return TXF_MONO;
		case 3: return TXF_RGB;
		case 4: return TXF_RGBA;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return TXF_DEFAULT;
	}
}
#if (NW_GAPI & NW_GAPI_OGL)
namespace NWLIB
{
	template<> value_types convert<const GLchar*, value_types>(const GLchar* type_string) {
		// value 8 bit boolean
		if (str_is_equal(type_string, "bool"))  { return NW_GET_VTYPE_ENUM_S(VTYPE_V1_BIT); }
		if (str_is_equal(type_string, "bvec2")) { return NW_GET_VTYPE_ENUM_S(VTYPE_V2_BIT); }
		if (str_is_equal(type_string, "bvec3")) { return NW_GET_VTYPE_ENUM_S(VTYPE_V3_BIT); }
		if (str_is_equal(type_string, "bvec4")) { return NW_GET_VTYPE_ENUM_S(VTYPE_V4_BIT); }
		// value 32 bit signed integer
		if (str_is_equal(type_string, "int"))        { return NW_GET_VTYPE_ENUM_D(VTYPE_V1_S32); }
		else if (str_is_equal(type_string, "ivec2")) { return NW_GET_VTYPE_ENUM_D(VTYPE_V2_S32); }
		else if (str_is_equal(type_string, "ivec3")) { return NW_GET_VTYPE_ENUM_D(VTYPE_V3_S32); }
		else if (str_is_equal(type_string, "ivec4")) { return NW_GET_VTYPE_ENUM_D(VTYPE_V4_S32); }
		// value 32 bit unsigned integer
		if (str_is_equal(type_string, "uint"))       { return NW_GET_VTYPE_ENUM_D(VTYPE_V4_U32); }
		else if (str_is_equal(type_string, "uvec2")) { return NW_GET_VTYPE_ENUM_D(VTYPE_V4_U32); }
		else if (str_is_equal(type_string, "uvec3")) { return NW_GET_VTYPE_ENUM_D(VTYPE_V4_U32); }
		else if (str_is_equal(type_string, "uvec4")) { return NW_GET_VTYPE_ENUM_D(VTYPE_V4_U32); }
		// value 32 bit float
		if (str_is_equal(type_string, "float"))     { return NW_GET_VTYPE_ENUM_D(VTYPE_V1_F32); }
		else if (str_is_equal(type_string, "vec2")) { return NW_GET_VTYPE_ENUM_D(VTYPE_V2_F32); }
		else if (str_is_equal(type_string, "vec3")) { return NW_GET_VTYPE_ENUM_D(VTYPE_V3_F32); }
		else if (str_is_equal(type_string, "vec4")) { return NW_GET_VTYPE_ENUM_D(VTYPE_V4_F32); }
		// value 64 bit float
		if (str_is_equal(type_string, "double"))     { return NW_GET_VTYPE_ENUM_D(VTYPE_V1_F64); }
		else if (str_is_equal(type_string, "dvec2")) { return NW_GET_VTYPE_ENUM_D(VTYPE_V2_F64); }
		else if (str_is_equal(type_string, "dvec3")) { return NW_GET_VTYPE_ENUM_D(VTYPE_V3_F64); }
		else if (str_is_equal(type_string, "dvec4")) { return NW_GET_VTYPE_ENUM_D(VTYPE_V4_F64); }
		// value sampler
		if (str_is_equal(type_string, "sampler1D")) { return NW_GET_VTYPE_ENUM_D(VTYPE_DEFAULT); }
		if (str_is_equal(type_string, "sampler2D")) { return NW_GET_VTYPE_ENUM_D(VTYPE_DEFAULT); }
		if (str_is_equal(type_string, "sampler3D")) { return NW_GET_VTYPE_ENUM_D(VTYPE_DEFAULT); }

		return VTYPE_DEFAULT;
	}
	template<> GLsizei convert<value_types, GLsizei>(value_types type) {
		switch (type) {
		case VTYPE_V1_BIT: return 1u;
		case VTYPE_V1_S8: case VTYPE_V1_U8: return 1u;
		case VTYPE_V1_S16: case VTYPE_V1_U16: return 1u;
		case VTYPE_V1_S32: case VTYPE_V1_U32: return 1u;
		case VTYPE_V1_S64: case VTYPE_V1_U64: return 1u;
		case VTYPE_V1_F32: case VTYPE_V1_F64: return 1u;
		case VTYPE_V2_BIT: return 1u;
		case VTYPE_V2_S8: case VTYPE_V2_U8: return 2u;
		case VTYPE_V2_S16: case VTYPE_V2_U16: return 2u;
		case VTYPE_V2_S32: case VTYPE_V2_U32: return 2u;
		case VTYPE_V2_S64: case VTYPE_V2_U64: return 2u;
		case VTYPE_V2_F32: case VTYPE_V2_F64: return 2u;
		case VTYPE_V3_S8: case VTYPE_V3_U8: return 3u;
		case VTYPE_V3_S16: case VTYPE_V3_U16: return 3u;
		case VTYPE_V3_S32: case VTYPE_V3_U32: return 3u;
		case VTYPE_V3_S64: case VTYPE_V3_U64: return 3u;
		case VTYPE_V3_F32: case VTYPE_V3_F64: return 3u;
		case VTYPE_V4_BIT: return 4u;
		case VTYPE_V4_S8: case VTYPE_V4_U8: return 4u;
		case VTYPE_V4_S16: case VTYPE_V4_U16: return 4u;
		case VTYPE_V4_S32: case VTYPE_V4_U32: return 4u;
		case VTYPE_V4_S64: case VTYPE_V4_U64: return 4u;
		case VTYPE_V4_F32: case VTYPE_V4_F64: return 4u;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return 0u;
	}
	template<> GLenum convert<value_types, GLenum>(value_types type) {
		switch (type) {
		case VTYPE_V1_BIT: case VTYPE_V2_BIT: case VTYPE_V3_BIT: case VTYPE_V4_BIT: return GL_BOOL;
		case VTYPE_V1_S8: case VTYPE_V2_S8: case VTYPE_V3_S8: case VTYPE_V4_S8: return GL_BYTE;
		case VTYPE_V1_U8: case VTYPE_V2_U8: case VTYPE_V3_U8: case VTYPE_V4_U8: return GL_UNSIGNED_BYTE;
		case VTYPE_V1_S16: case VTYPE_V2_S16: case VTYPE_V3_S16: case VTYPE_V4_S16: return GL_SHORT;
		case VTYPE_V1_U16: case VTYPE_V2_U16: case VTYPE_V3_U16: case VTYPE_V4_U16: return GL_UNSIGNED_SHORT;
		case VTYPE_V1_S32: case VTYPE_V2_S32: case VTYPE_V3_S32: case VTYPE_V4_S32: return GL_INT;
		case VTYPE_V1_U32: case VTYPE_V2_U32: case VTYPE_V3_U32: case VTYPE_V4_U32: return GL_UNSIGNED_INT;
		case VTYPE_V1_F32: case VTYPE_V2_F32: case VTYPE_V3_F32: case VTYPE_V4_F32: return GL_FLOAT;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return VTYPE_DEFAULT;
	}
	template<> GLenum convert<primitives, GLenum>(primitives prim) {
		switch (prim) {
		case PRIM_POINTS: return GL_POINTS;
		case PRIM_TRIANGLES: return GL_TRIANGLES;
		case PRIM_TRIANGLE_STRIP: return GL_TRIANGLE_STRIP;
		case PRIM_TRIANGLE_FAN: return GL_TRIANGLE_FAN;
		case PRIM_LINES: return GL_LINES;
		case PRIM_LINE_LOOP: return GL_LINE_LOOP;
		case PRIM_LINE_STRIP: return GL_LINE_STRIP;
		default: throw run_error(__FILE__, __LINE__);
		}
		return GL_TRIANGLES;
	}
	// configs
	template<> GLenum convert<fill_modes, GLenum>(fill_modes mode) {
		switch (mode) {
		case FILL_LINE: return GL_LINE; break;
		case FILL_FACE: return GL_FILL; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return FILL_DEFAULT;
	}
	template<> GLenum convert<faces, GLenum>(faces face) {
		switch (face) {
		case FACE_FRONT: return GL_FRONT; break;
		case FACE_BACK: return GL_BACK; break;
		case FACE_BACK_AND_FRONT: return GL_FRONT_AND_BACK; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return FACE_DEFAULT;
	}
	template<> GLenum convert<blend_factors, GLenum>(blend_factors factor) {
		switch (factor) {
		case BLEND_SRC_ALPHA: return GL_SRC_ALPHA; break;
		case BLEND_ONE_MINUS_SRC_ALPHA: return GL_ONE_MINUS_SRC_ALPHA; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return BLEND_SRC_DEFAULT;
	}
	template<> GLenum convert<logic_opers, GLenum>(logic_opers oper) {
		switch (oper) {
		case LOGIC_ALWAYS: return GL_ALWAYS; break;
		case LOGIC_NEVER: return GL_NEVER; break;
		case LOGIC_EQUAL: return GL_EQUAL; break;
		case LOGIC_GREATER: return GL_GREATER; break;
		case LOGIC_GEQUAL: return GL_GEQUAL; break;
		case LOGIC_LESSER: return GL_LESS; break;
		case LOGIC_LEQUAL: return GL_LEQUAL; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return LOGIC_DEFAULT;
	}
	template<> GLenum convert<stencil_opers, GLenum>(stencil_opers oper) {
		switch (oper) {
		case STENC_ZERO: return GL_ZERO; break;
		case STENC_INCR: return GL_INCR; break;
		case STENC_DECR: return GL_DECR; break;
		case STENC_KEEP: return GL_KEEP; break;
		case STENC_REPL: return GL_REPLACE; break;
		case STENC_INVERT: return GL_INVERT; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return STENC_DEFAULT;
	}
	// images
	template<> GLenum convert<pixel_formats, GLenum>(pixel_formats pxl_format) {
		switch (pxl_format) {
		case PXF_R8_S8: return GL_BYTE; break;

		case PXF_R32_S32: return GL_R32I; break;
		case PXF_R16G16_S32: return GL_RG32I; break;
		case PXF_R8G8B8_S32: return GL_RGB32I; break;
		case PXF_R8G8B8A8_S32: return GL_RGBA32I; break;

		case PXF_R32_U32: return GL_R32UI; break;
		case PXF_R16G16_U32: return GL_RG32UI; break;
		case PXF_R8G8B8A8_U32: return GL_RGBA32UI; break;

		case PXF_D24S8_U32: return GL_DEPTH24_STENCIL8; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return GL_RGB;
	}
	template<> GLenum convert<texture_formats, GLenum>(texture_formats format) {
		switch (format) {
		case TXF_IDX: return GL_RGBA; break;
		case TXF_MONO: return GL_RED; break;
		case TXF_RGB: return GL_RGB; break;
		case TXF_RGBA: return GL_RGBA; break;
		case TXF_DEPTH: return GL_DEPTH_ATTACHMENT; break;
		case TXF_STENCIL: return GL_STENCIL_ATTACHMENT; break;
		case TXF_DEPTH_STENCIL: return GL_DEPTH_STENCIL_ATTACHMENT; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return TXF_DEFAULT;
	}
	template<> GLenum convert<texture_filters, GLenum>(texture_filters mode) {
		switch (mode) {
		case TXFL_LINEAR: return GL_LINEAR; break;
		case TXFL_NEAREST: return GL_NEAREST; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return TXF_DEFAULT;
	}
	template<> GLenum convert<texture_wraps, GLenum>(texture_wraps mode) {
		switch (mode) {
		case TXW_REPEAT: return GL_REPEAT; break;
		case TXW_CLAMP: return GL_CLAMP_TO_BORDER; break;
		case TXW_BORDER: return GL_CLAMP_TO_BORDER; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return TXW_DEFAULT;
	}
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NWLIB
{
	// value_types
	template<> value_types convert<cstr, value_types>(cstr type_string) {
		if (str_is_equal(type_string, "int")) { return VTYPE_V1_S32; }
		if (str_is_equal(type_string, "int2")) { return VTYPE_V2_S32; }
		if (str_is_equal(type_string, "int3")) { return VTYPE_V3_S32; }
		if (str_is_equal(type_string, "int4")) { return VTYPE_V4_S32; }
		if (str_is_equal(type_string, "float")) { return VTYPE_V1_F32; }
		if (str_is_equal(type_string, "float2")) { return VTYPE_V2_F32; }
		if (str_is_equal(type_string, "float3")) { return VTYPE_V3_F32; }
		if (str_is_equal(type_string, "float4")) { return VTYPE_V4_F32; }
		return VTYPE_DEFAULT;
	}
	template<> size convert<DXGI_FORMAT, size>(DXGI_FORMAT type) {
		switch (type) {
		case DXGI_FORMAT_R8_SINT: return 1u;
		case DXGI_FORMAT_R8_UINT: return 1u;
		case DXGI_FORMAT_R8G8_SINT: return 2u;
		case DXGI_FORMAT_R8G8_UINT: return 2u;
		case DXGI_FORMAT_R8G8B8A8_SINT: return 4u;
		case DXGI_FORMAT_R8G8B8A8_UINT: return 4u;

		case DXGI_FORMAT_R16_SINT: return 2u;
		case DXGI_FORMAT_R16_UINT: return 2u;
		case DXGI_FORMAT_R16G16_SINT: return 4u;
		case DXGI_FORMAT_R16G16_UINT: return 4u;
		case DXGI_FORMAT_R16G16B16A16_SINT: return 8u;
		case DXGI_FORMAT_R16G16B16A16_UINT: return 8u;

		case DXGI_FORMAT_R32_SINT: return 4u;
		case DXGI_FORMAT_R32_UINT: return 4u;
		case DXGI_FORMAT_R32G32_SINT: return 8u;
		case DXGI_FORMAT_R32G32_UINT: return 8u;
		case DXGI_FORMAT_R32G32B32_SINT: return 12u;
		case DXGI_FORMAT_R32G32B32_UINT: return 12u;
		case DXGI_FORMAT_R32G32B32A32_SINT: return 16u;
		case DXGI_FORMAT_R32G32B32A32_UINT: return 16u;

		case DXGI_FORMAT_R8G8B8A8_SNORM: return 4u;
		case DXGI_FORMAT_R8G8B8A8_UNORM: return 4u;
		case DXGI_FORMAT_R32_FLOAT: return 4u;
		case DXGI_FORMAT_R32G32_FLOAT: return 8u;
		case DXGI_FORMAT_R32G32B32_FLOAT: return 16u;
		case DXGI_FORMAT_R32G32B32A32_FLOAT: return 32u;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return 0u;
	}
	template<> DXGI_FORMAT convert<value_types, DXGI_FORMAT>(value_types type) {
		switch (type) {
		// value 8 bit boolean
		case VTYPE_V1_BIT: return DXGI_FORMAT_R8_UINT;
		case VTYPE_V2_BIT: return DXGI_FORMAT_R8G8_UINT;
		case VTYPE_V4_BIT: return DXGI_FORMAT_R8G8B8A8_UINT;
		// value 8 bit signed int
		case VTYPE_V1_S8: return DXGI_FORMAT_R8_SINT;
		case VTYPE_V2_S8: return DXGI_FORMAT_R8G8_SINT;
		case VTYPE_V4_S8: return DXGI_FORMAT_R8G8B8A8_SINT;
		// value 8 bit unsigned int
		case VTYPE_V1_U8: return DXGI_FORMAT_R8_UINT;
		case VTYPE_V2_U8: return DXGI_FORMAT_R8G8_UINT;
		case VTYPE_V4_U8: return DXGI_FORMAT_R8G8B8A8_UINT;
		// value 16 bit signed int
		case VTYPE_V1_S16: return DXGI_FORMAT_R16_SINT;
		case VTYPE_V2_S16: return DXGI_FORMAT_R16G16_SINT;
		case VTYPE_V4_S16: return DXGI_FORMAT_R16G16B16A16_SINT;
		// value 16 bit unsigned int
		case VTYPE_V1_U16: return DXGI_FORMAT_R16_UINT;
		case VTYPE_V2_U16: return DXGI_FORMAT_R16G16_UINT;
		case VTYPE_V4_U16: return DXGI_FORMAT_R16G16B16A16_UINT;
		// value 32 bit signed int
		case VTYPE_V1_S32: return DXGI_FORMAT_R32_SINT;
		case VTYPE_V2_S32: return DXGI_FORMAT_R32G32_SINT;
		case VTYPE_V3_S32: return DXGI_FORMAT_R32G32B32_SINT;
		case VTYPE_V4_S32: return DXGI_FORMAT_R32G32B32A32_SINT;
		// value 32 bit unsigned int
		case VTYPE_V1_U32: return DXGI_FORMAT_R32_UINT;
		case VTYPE_V2_U32: return DXGI_FORMAT_R32G32_UINT;
		case VTYPE_V3_U32: return DXGI_FORMAT_R32G32B32_UINT;
		case VTYPE_V4_U32: return DXGI_FORMAT_R32G32B32A32_UINT;
		// value 32 bit float
		case VTYPE_V1_F32: return DXGI_FORMAT_R32_FLOAT;
		case VTYPE_V2_F32: return DXGI_FORMAT_R32G32_FLOAT;
		case VTYPE_V3_F32: return DXGI_FORMAT_R32G32B32_FLOAT;
		case VTYPE_V4_F32: return DXGI_FORMAT_R32G32B32A32_FLOAT;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return DXGI_FORMAT_R32_FLOAT;
	}
	template<> value_types convert<DXGI_FORMAT, value_types>(DXGI_FORMAT type) {
		switch (type) {
		// value 8 bit signed integer
		case DXGI_FORMAT_R8_SINT: return VTYPE_V1_S8;
		case DXGI_FORMAT_R8G8_SINT: return VTYPE_V2_S8;
		case DXGI_FORMAT_R8G8B8A8_SINT: return VTYPE_V4_S8;
		// value 8 bit unsigned integer
		case DXGI_FORMAT_R8_UINT: return VTYPE_V1_U8;
		case DXGI_FORMAT_R8G8_UINT: return VTYPE_V2_U8;
		case DXGI_FORMAT_R8G8B8A8_UINT: return VTYPE_V4_U8;
		// value 16 bit signed integer
		case DXGI_FORMAT_R16_SINT: return VTYPE_V1_S16;
		case DXGI_FORMAT_R16G16_SINT: return VTYPE_V2_S16;
		case DXGI_FORMAT_R16G16B16A16_SINT: return VTYPE_V4_S16;
		// value 16 bit unsigned integer
		case DXGI_FORMAT_R16_UINT: return VTYPE_V1_U16;
		case DXGI_FORMAT_R16G16_UINT: return VTYPE_V2_U16;
		case DXGI_FORMAT_R16G16B16A16_UINT: return VTYPE_V4_U16;
			// value 32 bit signed integer
		case DXGI_FORMAT_R32_SINT: return VTYPE_V1_S32;
		case DXGI_FORMAT_R32G32_SINT: return VTYPE_V2_S32;
		case DXGI_FORMAT_R32G32B32_SINT: return VTYPE_V3_S32;
		case DXGI_FORMAT_R32G32B32A32_SINT: return VTYPE_V4_S32;
		// value 32 bit unsigned integer
		case DXGI_FORMAT_R32_UINT: return VTYPE_V1_S32;
		case DXGI_FORMAT_R32G32_UINT: return VTYPE_V2_S32;
		case DXGI_FORMAT_R32G32B32_UINT: return VTYPE_V3_S32;
		case DXGI_FORMAT_R32G32B32A32_UINT: return VTYPE_V4_S32;
		// value 32 bit float
		case DXGI_FORMAT_R32_FLOAT: return VTYPE_V1_F32;
		case DXGI_FORMAT_R32G32_FLOAT: return VTYPE_V2_F32;
		case DXGI_FORMAT_R32G32B32_FLOAT: return VTYPE_V3_F32;
		case DXGI_FORMAT_R32G32B32A32_FLOAT: return VTYPE_V4_F32;
		default: throw run_error(__FILE__, __LINE__); break;
		}
	}
	// config
	template<> D3D11_STENCIL_OP convert<stencil_opers, D3D11_STENCIL_OP>(stencil_opers oper) {
		switch (oper) {
		case STENC_ZERO: return D3D11_STENCIL_OP_ZERO; break;
		case STENC_DECR: return D3D11_STENCIL_OP_DECR; break;
		case STENC_INCR: return D3D11_STENCIL_OP_INCR; break;
		case STENC_KEEP: return D3D11_STENCIL_OP_KEEP; break;
		case STENC_REPL: return D3D11_STENCIL_OP_REPLACE; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return D3D11_STENCIL_OP_KEEP;
	}
	template<> stencil_opers convert<D3D11_STENCIL_OP, stencil_opers>(D3D11_STENCIL_OP oper) {
		switch (oper) {
		case D3D11_STENCIL_OP_ZERO: return STENC_ZERO; break;
		case D3D11_STENCIL_OP_DECR: return STENC_DECR; break;
		case D3D11_STENCIL_OP_INCR: return STENC_INCR; break;
		case D3D11_STENCIL_OP_KEEP: return STENC_KEEP; break;
		case D3D11_STENCIL_OP_REPLACE: return STENC_REPL; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return STENC_DEFAULT;
	}
	template<> D3D11_COMPARISON_FUNC convert<logic_opers, D3D11_COMPARISON_FUNC>(logic_opers oper) {
		switch (oper) {
		case LOGIC_ALWAYS: return D3D11_COMPARISON_ALWAYS; break;
		case LOGIC_NEVER: return D3D11_COMPARISON_NEVER; break;
		case LOGIC_EQUAL: return D3D11_COMPARISON_EQUAL; break;
		case LOGIC_LESSER: return D3D11_COMPARISON_LESS; break;
		case LOGIC_LEQUAL: return D3D11_COMPARISON_LESS_EQUAL; break;
		case LOGIC_GREATER: return D3D11_COMPARISON_GREATER; break;
		case LOGIC_GEQUAL: return D3D11_COMPARISON_GREATER_EQUAL; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return D3D11_COMPARISON_ALWAYS;
	}
	template<> logic_opers convert<D3D11_COMPARISON_FUNC, logic_opers>(D3D11_COMPARISON_FUNC oper) {
		switch (oper) {
		case D3D11_COMPARISON_ALWAYS: return LOGIC_ALWAYS; break;
		case D3D11_COMPARISON_NEVER: return LOGIC_NEVER; break;
		case D3D11_COMPARISON_EQUAL: return LOGIC_EQUAL; break;
		case D3D11_COMPARISON_LESS: return LOGIC_LESSER; break;
		case D3D11_COMPARISON_LESS_EQUAL: return LOGIC_LEQUAL; break;
		case D3D11_COMPARISON_GREATER: return LOGIC_GREATER; break;
		case D3D11_COMPARISON_GREATER_EQUAL: return LOGIC_GEQUAL; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return LOGIC_DEFAULT;
	}
	// drawing
	template<> D3D11_PRIMITIVE_TOPOLOGY convert<primitives, D3D11_PRIMITIVE_TOPOLOGY>(primitives type) {
		switch (type) {
		case PRIM_POINTS: return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST; break;
		case PRIM_TRIANGLES: return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST; break;
		case PRIM_TRIANGLE_STRIP: return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; break;
		case PRIM_TRIANGLE_FAN: return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ; break;
		case PRIM_LINES: return D3D11_PRIMITIVE_TOPOLOGY_LINELIST; break;
		case PRIM_LINE_LOOP: return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ; break;
		case PRIM_LINE_STRIP: return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	}
	template<> primitives convert<D3D11_PRIMITIVE_TOPOLOGY, primitives>(D3D11_PRIMITIVE_TOPOLOGY type) {
		switch (type) {
		case D3D11_PRIMITIVE_TOPOLOGY_POINTLIST: return PRIM_POINTS; break;
		case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST: return PRIM_TRIANGLES; break;
		case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP: return PRIM_TRIANGLE_STRIP; break;
		case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ: return PRIM_TRIANGLE_FAN; break;
		case D3D11_PRIMITIVE_TOPOLOGY_LINELIST: return PRIM_LINES; break;
		case D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ: return PRIM_LINE_LOOP; break;
		case D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP: return PRIM_LINE_STRIP; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return PRIM_DEFAULT;
	}
	// images
	template<> DXGI_FORMAT convert <pixel_formats, DXGI_FORMAT>(pixel_formats format) {
		switch (format) {
		case PXF_R32_S32: return DXGI_FORMAT_R32_SINT; break;
		case PXF_R8G8B8_S32: return DXGI_FORMAT_R8G8B8A8_SNORM; break;
		case PXF_R8G8B8_U32: return DXGI_FORMAT_B8G8R8A8_UNORM; break;
		case PXF_R8G8B8A8_S32: return DXGI_FORMAT_R8G8B8A8_SNORM; break;
		case PXF_R8G8B8A8_U32: return DXGI_FORMAT_B8G8R8A8_UNORM; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return DXGI_FORMAT_R8G8B8A8_UNORM;
	}
	template<> pixel_formats convert <DXGI_FORMAT, pixel_formats>(DXGI_FORMAT format) {
		switch (format) {
		case DXGI_FORMAT_R32_SINT: return PXF_R32_S32; break;
		case DXGI_FORMAT_R8G8B8A8_SNORM: return PXF_R8G8B8A8_S32; break;
		case DXGI_FORMAT_B8G8R8A8_UNORM: return PXF_R8G8B8A8_U32; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return PXF_DEFAULT;
	}
	template<> DXGI_FORMAT convert<texture_formats, DXGI_FORMAT>(texture_formats format) {
		switch (format) {
		case TXF_RGB: return DXGI_FORMAT_R8G8B8A8_UNORM; break;
		case TXF_RGBA: return DXGI_FORMAT_R8G8B8A8_UNORM; break;
		case TXF_MONO: return DXGI_FORMAT_R32_UINT; break;
		case TXF_IDX: return DXGI_FORMAT_R8G8B8A8_UNORM; break;
		case TXF_DEPTH: return DXGI_FORMAT_D32_FLOAT; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return DXGI_FORMAT_R8G8B8A8_UINT;
	}
	template<> texture_formats convert<DXGI_FORMAT, texture_formats>(DXGI_FORMAT format) {
		switch (format) {
		case DXGI_FORMAT_R32_SINT: return TXF_MONO; break;
		case DXGI_FORMAT_R32_UINT: return TXF_MONO; break;
		case DXGI_FORMAT_R8G8B8A8_SINT: return TXF_RGBA; break;
		case DXGI_FORMAT_R8G8B8A8_UINT: return TXF_RGBA; break;
		case DXGI_FORMAT_D32_FLOAT: return TXF_DEPTH; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return TXF_DEFAULT;
	}
	template<> DXGI_FORMAT convert<v1s, DXGI_FORMAT>(v1s nof_channels) {
		switch (nof_channels) {
#if 1
		case 1: return DXGI_FORMAT_R16_UNORM;
		case 2: return DXGI_FORMAT_R8G8_UNORM;
		case 3: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case 4: return DXGI_FORMAT_R8G8B8A8_UNORM;
#else
		case 1: return DXGI_FORMAT_R32_UINT;
		case 2: return DXGI_FORMAT_R8G8_UINT;
		case 3: return DXGI_FORMAT_R8G8B8A8_UINT;
		case 4: return DXGI_FORMAT_R8G8B8A8_UINT;
#endif
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return DXGI_FORMAT_R8G8B8A8_UINT;
	}
	// texture sampling
	template<> D3D11_FILTER convert<texture_filters, D3D11_FILTER>(texture_filters mode) {
		switch (mode) {
		case TXFL_LINEAR: return D3D11_FILTER_MIN_MAG_MIP_LINEAR; break;
		case TXFL_NEAREST: return D3D11_FILTER_MIN_MAG_MIP_POINT; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return D3D11_FILTER_MIN_MAG_MIP_POINT;
	}
	template<> texture_filters convert<D3D11_FILTER, texture_filters>(D3D11_FILTER mode) {
		switch (mode) {
		case D3D11_FILTER_MIN_MAG_MIP_LINEAR: return TXFL_LINEAR; break;
		case D3D11_FILTER_MIN_MAG_MIP_POINT: return TXFL_NEAREST; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return TXFL_DEFAULT;
	}
	template<> D3D11_TEXTURE_ADDRESS_MODE convert<texture_wraps, D3D11_TEXTURE_ADDRESS_MODE>(texture_wraps mode) {
		switch (mode) {
		case TXW_REPEAT: return D3D11_TEXTURE_ADDRESS_WRAP; break;
		case TXW_CLAMP: return D3D11_TEXTURE_ADDRESS_CLAMP; break;
		case TXW_BORDER: return D3D11_TEXTURE_ADDRESS_CLAMP; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return D3D11_TEXTURE_ADDRESS_WRAP;
	}
	template<> texture_wraps convert<D3D11_TEXTURE_ADDRESS_MODE>(D3D11_TEXTURE_ADDRESS_MODE mode) {
		switch (mode) {
		case D3D11_TEXTURE_ADDRESS_WRAP: return TXW_REPEAT; break;
		case D3D11_TEXTURE_ADDRESS_CLAMP: return TXW_CLAMP; break;
		case D3D11_TEXTURE_ADDRESS_BORDER: return TXW_BORDER; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return TXW_DEFAULT;
	}
}
#endif
#endif	// NW_GAPI