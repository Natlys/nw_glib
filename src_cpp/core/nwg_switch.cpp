#include <nwg_pch.hpp>
#include "nwg_switch.h"
#ifdef NWG_GAPI
namespace NWG
{
	template<> const char* ConvertEnum<DataTypes, const char*>(DataTypes dType) {
		switch (dType) {
		case DT_BOOL: return "DT_BOOL";
		case DT_SINT8: return "DT_SINT8";
		case DT_VEC2_SINT8: return "DT_VEC2_UINT8";
		case DT_VEC3_SINT8: return "DT_VEC3_SINT8";
		case DT_VEC4_SINT8:	return "DT_VEC4_SINT8";

		case DT_UINT8: return "DT_UINT8";
		case DT_VEC2_UINT8: return "DT_VEC2_UINT8";
		case DT_VEC3_UINT8: return "DT_VEC3_UINT8";
		case DT_VEC4_UINT8: return "DT_VEC4_UINT8";

		case DT_SINT16: return "DT_SINT16";
		case DT_VEC2_SINT16: return "DT_VEC2_SINT16";
		case DT_VEC3_SINT16: return "DT_VEC3_SINT16";
		case DT_VEC4_SINT16: return "DT_VEC4_SINT16";

		case DT_UINT16: return "DT_UINT16";
		case DT_VEC2_UINT16: return "DT_VEC2_UINT16";
		case DT_VEC3_UINT16: return "DT_VEC3_UINT16";
		case DT_VEC4_UINT16: return "DT_VEC4_UINT16";

		case DT_SINT32: return "DT_SINT32";
		case DT_VEC2_SINT32: return "DT_VEC2_SINT32";
		case DT_VEC3_SINT32: return "DT_VEC3_SINT32";
		case DT_VEC4_SINT32: return "DT_VEC4_SINT32";

		case DT_UINT32: return "DT_UINT32";
		case DT_VEC2_UINT32: return "DT_VEC2_UINT32";
		case DT_VEC3_UINT32: return "DT_VEC3_UINT32";
		case DT_VEC4_UINT32: return "DT_VEC4_UINT32";

		case DT_FLOAT32: return "DT_FLOAT32";
		case DT_VEC2_FLOAT32: return "DT_VEC2_FLOAT32";
		case DT_VEC3_FLOAT32: return "DT_VEC3_FLOAT32";
		case DT_VEC4_FLOAT32: return "DT_VEC4_FLOAT32";

		case DT_USER_DATA: return "DT_USER_DATA";

		default: throw Exception("unsupported format", ERC_NO_SUPPORT); break;
		}
		return "DT_DEFAULT";
	}
	template<> const char* ConvertEnum<PixelFormats, const char*>(PixelFormats pxlFormat) {
		switch (pxlFormat) {
		case PXF_R8_SINT8: return "PXF_R8_SINT8"; break;

		case PXF_R32_SINT32: return "PXF_R32_SINT32"; break;
		case PXF_R16G16_SINT32: return "PXF_R16G16_SINT32"; break;
		case PXF_R8G8B8_SINT32: return "PXF_R8G8B8_SINT32"; break;
		case PXF_R8G8B8A8_SINT32: return "PXF_R8G8B8A8_SINT32"; break;

		case PXF_R32_UINT32: return "PXF_R32_UINT32"; break;
		case PXF_R16G16_UINT32: return "PXF_R16G16_UINT32"; break;
		case PXF_R8G8B8_UINT32: return "PXF_R8G8B8_UINT32"; break;
		case PXF_R8G8B8A8_UINT32: return "PXF_R8G8B8A8_UINT32"; break;

		case PXF_D24S8_UINT32: return "PXF_D24S8_UINT32"; break;
		default: throw Exception("unsupported pixel format", ERC_NO_SUPPORT); break;
		}
		return "PXF_DEFAULT";
	}
	template<> const char* ConvertEnum<ShaderTypes, const char*>(ShaderTypes shdType) {
		switch (shdType) {
		case SHD_PROG: return "SHD_PROG"; break;
		case SHD_VERTEX: return "SHD_VERTEX"; break;
		case SHD_PIXEL: return "SHD_PIXEL"; break;
		case SHD_GEOMETRY: return "SHD_GEOMETRY"; break;
		default: throw Exception("unsupported pixel format", ERC_NO_SUPPORT); break;
		}
		return "SHD_DEFAULT";
	}
}
namespace NWG
{
	template<>DataTypes ConvertEnum<Int8, DataTypes>() { return DT_SINT8; }
	template<>DataTypes ConvertEnum<V2i8, DataTypes>() { return DT_VEC2_SINT8; }
	template<>DataTypes ConvertEnum<V3i8, DataTypes>() { return DT_VEC3_SINT8; }
	template<>DataTypes ConvertEnum<V4i8, DataTypes>() { return DT_VEC4_SINT8; }

	template<>DataTypes ConvertEnum<UInt8, DataTypes>() { return DT_SINT8; }
	template<>DataTypes ConvertEnum<V2u8, DataTypes>() { return DT_VEC2_UINT8; }
	template<>DataTypes ConvertEnum<V3u8, DataTypes>() { return DT_VEC3_UINT8; }
	template<>DataTypes ConvertEnum<V4u8, DataTypes>() { return DT_VEC4_UINT8; }

	template<>DataTypes ConvertEnum<Int16, DataTypes>() { return DT_SINT16; }
	template<>DataTypes ConvertEnum<V2i16, DataTypes>() { return DT_VEC2_SINT16; }
	template<>DataTypes ConvertEnum<V3i16, DataTypes>() { return DT_VEC3_SINT16; }
	template<>DataTypes ConvertEnum<V4i16, DataTypes>() { return DT_VEC4_SINT16; }

	template<>DataTypes ConvertEnum<UInt16, DataTypes>() { return DT_UINT16; }
	template<>DataTypes ConvertEnum<V2u16, DataTypes>() { return DT_VEC2_UINT16; }
	template<>DataTypes ConvertEnum<V3u16, DataTypes>() { return DT_VEC3_UINT16; }
	template<>DataTypes ConvertEnum<V4u16, DataTypes>() { return DT_VEC4_UINT16; }

	template<>DataTypes ConvertEnum<Int32, DataTypes>() { return DT_SINT32; }
	template<>DataTypes ConvertEnum<V2i, DataTypes>() { return DT_VEC2_SINT32; }
	template<>DataTypes ConvertEnum<V3i, DataTypes>() { return DT_VEC3_SINT32; }
	template<>DataTypes ConvertEnum<V4i, DataTypes>() { return DT_VEC4_SINT32; }

	template<>DataTypes ConvertEnum<UInt32, DataTypes>() { return DT_UINT32; }
	template<>DataTypes ConvertEnum<V2u, DataTypes>() { return DT_VEC2_UINT32; }
	template<>DataTypes ConvertEnum<V3u, DataTypes>() { return DT_VEC3_UINT32; }
	template<>DataTypes ConvertEnum<V4u, DataTypes>() { return DT_VEC4_UINT32; }

	template<>DataTypes ConvertEnum<Float32, DataTypes>() { return DT_FLOAT32; }
	template<>DataTypes ConvertEnum<V2f, DataTypes>() { return DT_VEC2_FLOAT32; }
	template<>DataTypes ConvertEnum<V3f, DataTypes>() { return DT_VEC3_FLOAT32; }
	template<>DataTypes ConvertEnum<V4f, DataTypes>() { return DT_VEC4_FLOAT32; }
	template<>DataTypes ConvertEnum<Mat2f, DataTypes>() { return DT_MAT2_FLOAT32; }
	template<>DataTypes ConvertEnum<Mat3f, DataTypes>() { return DT_MAT3_FLOAT32; }
	template<>DataTypes ConvertEnum<Mat4f, DataTypes>() { return DT_MAT4_FLOAT32; }
}
#if (NWG_GAPI & NWG_GAPI_OGL)
#include <lib/nwg_ogl_v1.h>
#include <lib/nwg_ogl_v2.h>
#include <lib/nwg_ogl_v3.h>
#include <lib/nwg_ogl_v4.h>
#include <lib/nwg_ogl_arb.h>
namespace NWG
{
	template<> DataTypes ConvertEnum<const char*, DataTypes>(const char* strType) {
		if (CStrIsEqual(strType, "bool")) { return DT_BOOL; }

		if (CStrIsEqual(strType, "int")) { return DT_SINT32; }
		else if (CStrIsEqual(strType, "ivec2")) { return DT_VEC2_SINT32; }
		else if (CStrIsEqual(strType, "ivec3")) { return DT_VEC3_SINT32; }
		else if (CStrIsEqual(strType, "ivec4")) { return DT_VEC4_SINT32; }

		if (CStrIsEqual(strType, "uint")) { return DT_UINT32; }
		else if (CStrIsEqual(strType, "uvec2")) { return DT_VEC2_UINT32; }
		else if (CStrIsEqual(strType, "uvec3")) { return DT_VEC3_UINT32; }
		else if (CStrIsEqual(strType, "uvec4")) { return DT_VEC4_UINT32; }

		if (CStrIsEqual(strType, "float")) { return DT_FLOAT32; }
		else if (CStrIsEqual(strType, "vec2")) { return DT_VEC2_FLOAT32; }
		else if (CStrIsEqual(strType, "vec3")) { return DT_VEC3_FLOAT32; }
		else if (CStrIsEqual(strType, "vec4")) { return DT_VEC4_FLOAT32; }
		else if (CStrIsEqual(strType, "mat2")) { return DT_MAT2_FLOAT32; }
		else if (CStrIsEqual(strType, "mat3")) { return DT_MAT3_FLOAT32; }
		else if (CStrIsEqual(strType, "mat4")) { return DT_MAT4_FLOAT32; }

		if (CStrIsEqual(strType, "double")) { return DT_FLOAT64; }
		else if (CStrIsEqual(strType, "dvec2")) { return DT_VEC2_FLOAT64; }
		else if (CStrIsEqual(strType, "dvec3")) { return DT_VEC3_FLOAT64; }
		else if (CStrIsEqual(strType, "dvec4")) { return DT_VEC4_FLOAT64; }

		if (CStrIsEqual(strType, "sampler1D")) { return DT_USER_DATA; }
		if (CStrIsEqual(strType, "sampler2D")) { return DT_USER_DATA; }
		if (CStrIsEqual(strType, "sampler3D")) { return DT_USER_DATA; }

		return DT_DEFAULT;
	}
	template<> UInt32 ConvertEnum<DataTypes, UInt32>(DataTypes dType) {
		switch (dType) {
		case DT_BOOL: return GL_BOOL;
		case DT_SINT8: return GL_BYTE;
		case DT_VEC2_SINT8: return GL_BYTE;
		case DT_VEC3_SINT8: case DT_VEC4_SINT8: return GL_BYTE;

		case DT_UINT8: return GL_UNSIGNED_BYTE;
		case DT_VEC2_UINT8: return GL_UNSIGNED_BYTE;
		case DT_VEC3_UINT8: return GL_UNSIGNED_BYTE;
		case DT_VEC4_UINT8: return GL_UNSIGNED_BYTE;

		case DT_SINT16: return GL_SHORT;
		case DT_VEC2_SINT16: return GL_SHORT;
		case DT_VEC3_SINT16: return GL_SHORT;
		case DT_VEC4_SINT16: return GL_SHORT;

		case DT_UINT16: return GL_UNSIGNED_SHORT;
		case DT_VEC2_UINT16: return GL_UNSIGNED_SHORT;
		case DT_VEC3_UINT16: return GL_UNSIGNED_SHORT;
		case DT_VEC4_UINT16: return GL_UNSIGNED_SHORT;

		case DT_SINT32: return GL_INT;
		case DT_VEC2_SINT32: return GL_INT;
		case DT_VEC3_SINT32: return GL_INT;
		case DT_VEC4_SINT32: return GL_INT;

		case DT_UINT32: return GL_UNSIGNED_INT;
		case DT_VEC2_UINT32: return GL_UNSIGNED_INT;
		case DT_VEC3_UINT32: return GL_UNSIGNED_INT;
		case DT_VEC4_UINT32: return GL_UNSIGNED_INT;

		case DT_FLOAT32: return GL_FLOAT;
		case DT_VEC2_FLOAT32: return GL_FLOAT;
		case DT_VEC3_FLOAT32: return GL_FLOAT;
		case DT_VEC4_FLOAT32: return GL_FLOAT;

		default: throw Exception("unsupported format", ERC_NO_SUPPORT); break;
		}
		return DT_DEFAULT;
	}
	template<> UInt32 ConvertEnum<GfxPrimitives, UInt32>(GfxPrimitives gpType) {
		switch (gpType) {
		case GPT_POINTS: return GL_POINTS; break;
		case GPT_TRIANGLES: return GL_TRIANGLES; break;
		case GPT_TRIANGLE_STRIP: return GL_TRIANGLE_STRIP; break;
		case GPT_TRIANGLE_FAN: return GL_TRIANGLE_FAN; break;
		case GPT_LINES: return GL_LINES; break;
		case GPT_LINE_LOOP: return GL_LINE_LOOP; break;
		case GPT_LINE_STRIP: return GL_LINE_STRIP; break;
		default: throw Exception("unavailable primitive topology", ERC_INVALID_ENUM); break;
		}
		return GL_TRIANGLES;
	}
	template<> UInt32 ConvertEnum<TextureTypes, UInt32>(TextureTypes texType) {
		switch (texType) {
		case TXT_1D: return GL_TEXTURE_1D; break;
		case TXT_2D: return GL_TEXTURE_2D; break;
		case TXT_3D: return GL_TEXTURE_3D; break;
		case TXT_2D_MULTISAMPLE: return GL_TEXTURE_2D_MULTISAMPLE; break;
		case TXT_3D_MULTISAMPLE: return GL_TEXTURE_2D_MULTISAMPLE_ARRAY; break;
		default: throw Exception("unsupported texture type", ERC_NO_SUPPORT); break;
		}
		return GL_TEXTURE_2D;
	}
	template<> UInt32 ConvertEnum<PixelFormats, UInt32>(PixelFormats pxlFormat) {
		switch (pxlFormat) {
		case PXF_R8_SINT8: return GL_BYTE; break;

		case PXF_R32_SINT32: return GL_R32I; break;
		case PXF_R16G16_SINT32: return GL_RG32I; break;
		case PXF_R8G8B8_SINT32: return GL_RGB32I; break;
		case PXF_R8G8B8A8_SINT32: return GL_RGBA32I; break;

		case PXF_R32_UINT32: return GL_R32UI; break;
		case PXF_R16G16_UINT32: return GL_RG32UI; break;
		case PXF_R8G8B8_UINT32: return GL_RGB32UI; break;
		case PXF_R8G8B8A8_UINT32: return GL_RGBA32UI; break;

		case PXF_D24S8_UINT32: return GL_DEPTH24_STENCIL8; break;
		default: throw Exception("unsupported pixel format", ERC_NO_SUPPORT); break;
		}
		return GL_RGB;
	}
	template<> UInt32 ConvertEnum<ShaderTypes, UInt32>(ShaderTypes shdType) {
		switch (shdType) {
		case SHD_VERTEX: return GL_VERTEX_SHADER; break;
		case SHD_PIXEL: return GL_FRAGMENT_SHADER; break;
		case SHD_GEOMETRY: return GL_GEOMETRY_SHADER; break;
		case SHD_PROG: return GL_SHADER; break;
		default: throw Exception("unsupported pixel format", ERC_NO_SUPPORT); break;
		}
		return GL_SHADER;
	}
	template<> UInt32 ConvertEnum<ProcessingModes, UInt32>(ProcessingModes pMode) {
		switch (pMode) {
		case PM_BLEND: return GL_BLEND; break;
		case PM_MULTISAMPLE: return GL_MULTISAMPLE; break;
		case PM_DEPTH_TEST: return GL_DEPTH_TEST; break;
		case PM_STENCIL_TEST: return GL_STENCIL_TEST; break;
		default: throw Exception("undefined processing mode", ERC_INVALID_ENUM); break;
		}
		return PM_DEFAULT;
	}
	template<> UInt32 ConvertEnum<DrawModes, UInt32>(DrawModes dMode) {
		switch (dMode) {
		case DM_LINE: return GL_LINE; break;
		case DM_FILL: return GL_FILL; break;
		default: throw Exception("undefined draw mode", ERC_INVALID_ENUM); break;
		}
		return DM_DEFAULT;
	}
	template<> UInt32 ConvertEnum<FacePlanes, UInt32>(FacePlanes fcPlane) {
		switch (fcPlane) {
		case FACE_FRONT: return GL_FRONT; break;
		case FACE_BACK: return GL_BACK; break;
		case FACE_FRONT_AND_BACK: return GL_FRONT_AND_BACK; break;
		default: throw Exception("undefined face plane", ERC_INVALID_ENUM); break;
		}
		return FACE_DEFAULT;
	}
	template<> UInt32 ConvertEnum<BlendConfigs, UInt32>(BlendConfigs bConfig) {
		switch (bConfig) {
		case BC_SRC_ALPHA: return GL_SRC_ALPHA; break;
		case BC_ONE_MINUS_SRC_ALPHA: return GL_ONE_MINUS_SRC_ALPHA; break;
		default: throw Exception("invalid blending config", ERC_INVALID_ENUM); break;
		}
		return BC_SRC_DEFAULT;
	}
	template<> UInt32 ConvertEnum<DepthConfigs, UInt32>(DepthConfigs dConfig) {
		switch (dConfig) {
		case DTC_LESS: return GL_LESS; break;
		case DTC_GREATER: return GL_GREATER; break;
		default: throw Exception("invalid depth config", ERC_INVALID_ENUM); break;
		}
		return DTC_DEFAULT;
	}
	template<> UInt32 ConvertEnum<StencilConfigs, UInt32>(StencilConfigs sConfig) {
		switch (sConfig) {
		case STC_KEEP: return GL_KEEP; break;
		case STC_REPLACE: return GL_REPLACE; break;
		default: throw Exception("invalid depth config", ERC_INVALID_ENUM); break;
		}
		return STC_DEFAULT;
	}
	template<> UInt32 ConvertEnum<TextureFormats, UInt32>(TextureFormats texFormat) {
		switch (texFormat) {
		case TXF_RGB: return GL_RGB; break;
		case TXF_RGBA: return GL_RGBA; break;
		case TXF_GRAY: return GL_RED; break;
		case TXF_IDX: return GL_RGBA; break;
		case TXF_DEPTH: return GL_DEPTH_ATTACHMENT; break;
		case TXF_STENCIL: return GL_STENCIL_ATTACHMENT; break;
		case TXF_DEPTH_STENCIL: return GL_DEPTH_STENCIL_ATTACHMENT; break;
		default: throw Exception("invalid texture filter", ERC_INVALID_ENUM); break;
		}
		return TXF_DEFAULT;
	}
	template<> UInt32 ConvertEnum<TextureFilters, UInt32>(TextureFilters texFilter) {
		switch (texFilter) {
		case TXFL_LINEAR: return GL_LINEAR; break;
		case TXFL_NEAREST: return GL_NEAREST; break;
		default: throw Exception("invalid texture filter", ERC_INVALID_ENUM); break;
		}
		return TXF_DEFAULT;
	}
	template<> UInt32 ConvertEnum<TextureWraps, UInt32>(TextureWraps texWrap) {
		switch (texWrap) {
		case TXW_REPEAT: return GL_REPEAT; break;
		case TXW_CLAMP: return GL_CLAMP_TO_BORDER; break;
		case TXW_BORDER: return GL_CLAMP_TO_BORDER; break;
		default: throw Exception("invalid texture wrap", ERC_INVALID_ENUM); break;
		}
		return TXW_DEFAULT;
	}
}
namespace NWG
{
	UInt32 DtGetCount(DataTypes dType) {
		switch (dType) {
		case DT_BOOL: return 1;
		case DT_VEC2_BOOL: return 2;
		case DT_VEC3_BOOL: return 3;
		case DT_VEC4_BOOL: return 4;

		case DT_SINT8: return 1;
		case DT_VEC2_SINT8: return 2;
		case DT_VEC3_SINT8: return 3;
		case DT_VEC4_SINT8: return 4;

		case DT_UINT8: return 1;
		case DT_VEC2_UINT8: return 2;
		case DT_VEC3_UINT8: return 3;
		case DT_VEC4_UINT8: return 4;

		case DT_SINT16: return 1;
		case DT_VEC2_SINT16: return 2;
		case DT_VEC3_SINT16: return 3;
		case DT_VEC4_SINT16: return 4;

		case DT_UINT16: return 1;
		case DT_VEC2_UINT16: return 2;
		case DT_VEC3_UINT16: return 3;
		case DT_VEC4_UINT16: return 4;

		case DT_SINT32: return 1;
		case DT_VEC2_SINT32: return 2;
		case DT_VEC3_SINT32: return 3;
		case DT_VEC4_SINT32: return 4;

		case DT_UINT32: return 1;
		case DT_VEC2_UINT32: return 2;
		case DT_VEC3_UINT32: return 3;
		case DT_VEC4_UINT32: return 4;

		case DT_FLOAT32: return 1;
		case DT_VEC2_FLOAT32: return 2;
		case DT_VEC3_FLOAT32: return 3;
		case DT_VEC4_FLOAT32: return 4;
		default: throw(Exception("invalid data type")); break;
		}
		return 0;
	}
	Size DtGetSize(DataTypes sDataType, UInt32 unCount) {
		switch (sDataType) {
		case DT_BOOL:
		case DT_SINT8: case DT_UINT8:
			return 1;
		case DT_VEC2_SINT8: case DT_VEC2_UINT8:
		case DT_SINT16: case DT_UINT16:
			return 2;
		case DT_FLOAT32:
		case DT_SINT32: case DT_UINT32:
		case DT_VEC2_SINT16: case DT_VEC2_UINT16:
			return 4;

		case DT_VEC2_FLOAT32:
		case DT_VEC2_SINT32: case DT_VEC2_UINT32:
		case DT_VEC4_SINT16: case DT_VEC4_UINT16:
			return 4 * 2;
		case DT_VEC3_FLOAT32:
		case DT_VEC3_SINT32: case DT_VEC3_UINT32:
			return 4 * 3;
		case DT_VEC4_FLOAT32:
		case DT_VEC4_SINT32: case DT_VEC4_UINT32:
			return 4 * 4;

		case DT_USER_DATA: return 4;
		default: throw Exception("invalid data type", ERC_INVALID_ENUM); break;
		}
		return 0;
	}
	Size DtGetAlignedSize(DataTypes dType, UInt32 unCount) {
		Size szAll = 0;
		switch (dType) {
		case DT_BOOL: szAll = 4; break;

		case DT_SINT8: szAll = 4; break;

		case DT_UINT8: szAll = 4; break;

		case DT_SINT16: szAll = 4; break;

		case DT_UINT16: szAll = 4; break;

		case DT_SINT32: szAll = 4; break;

		case DT_UINT32: szAll = 4; break;

		case DT_FLOAT32: szAll = 4; break;
		case DT_VEC2_FLOAT32: szAll = 8; break;
		case DT_VEC3_FLOAT32: szAll = 16; break;
		case DT_VEC4_FLOAT32: szAll = 16; break;
		case DT_MAT2_FLOAT32: szAll = 32; break;
		case DT_MAT3_FLOAT32: szAll = 64; break;
		case DT_MAT4_FLOAT32: szAll = 64; break;

		case DT_USER_DATA: szAll = 4; break;

		default: throw Exception("invalid data type", ERC_INVALID_ENUM); szAll = 0; break;
		}
		return szAll * ((unCount + (szAll - 1)) & ~(szAll - 1));
	}
}
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
#include <lib/nwg_dx_loader.h>
namespace NWG
{
template<> DataTypes ConvertEnum<const char*, DataTypes>(const char* strType) {
	if (CStrIsEqual(strType, "int")) { return DT_SINT32; }
	if (CStrIsEqual(strType, "int2")) { return DT_VEC2_SINT32; }
	if (CStrIsEqual(strType, "int3")) { return DT_VEC3_SINT32; }
	if (CStrIsEqual(strType, "int4")) { return DT_VEC4_SINT32; }
	if (CStrIsEqual(strType, "float")) { return DT_FLOAT32; }
	if (CStrIsEqual(strType, "float2")) { return DT_VEC2_FLOAT32; }
	if (CStrIsEqual(strType, "float3")) { return DT_VEC3_FLOAT32; }
	if (CStrIsEqual(strType, "float4")) { return DT_VEC4_FLOAT32; }
	return DT_DEFAULT;
}
template<> DXGI_FORMAT ConvertEnum<DataTypes, DXGI_FORMAT>(DataTypes dType) {
	switch (dType) {
	case DT_BOOL: return DXGI_FORMAT_R8_UINT;
	case DT_SINT8: return DXGI_FORMAT_R8_SINT;
	case DT_VEC2_SINT8: return DXGI_FORMAT_R8_SINT;
	case DT_VEC3_SINT8: case DT_VEC4_SINT8: return DXGI_FORMAT_R8G8B8A8_SINT;

	case DT_UINT8: return DXGI_FORMAT_R8_UINT;
	case DT_VEC2_UINT8: return DXGI_FORMAT_R8_UINT;
	case DT_VEC3_UINT8: return DXGI_FORMAT_R8G8B8A8_UINT;
	case DT_VEC4_UINT8: return DXGI_FORMAT_R8G8B8A8_UINT;

	case DT_SINT16: return DXGI_FORMAT_R16_SINT;
	case DT_VEC2_SINT16: return DXGI_FORMAT_R16_SINT;
	case DT_VEC3_SINT16: return DXGI_FORMAT_R16G16B16A16_SINT;
	case DT_VEC4_SINT16: return DXGI_FORMAT_R16G16B16A16_SINT;

	case DT_UINT16: return DXGI_FORMAT_R16_UINT;
	case DT_VEC2_UINT16: return DXGI_FORMAT_R16_UINT;
	case DT_VEC3_UINT16: return DXGI_FORMAT_R16G16B16A16_UINT;
	case DT_VEC4_UINT16: return DXGI_FORMAT_R16G16B16A16_UINT;

	case DT_SINT32: return DXGI_FORMAT_R32_SINT;
	case DT_VEC2_SINT32: return DXGI_FORMAT_R32_SINT;
	case DT_VEC3_SINT32: return DXGI_FORMAT_R32G32B32_SINT;
	case DT_VEC4_SINT32: return DXGI_FORMAT_R32G32B32A32_SINT;

	case DT_UINT32: return DXGI_FORMAT_R32_UINT;
	case DT_VEC2_UINT32: return DXGI_FORMAT_R32_UINT;
	case DT_VEC3_UINT32: return DXGI_FORMAT_R32G32B32_UINT;
	case DT_VEC4_UINT32: return DXGI_FORMAT_R32G32B32A32_UINT;

	case DT_FLOAT32: return DXGI_FORMAT_R32_FLOAT;
	case DT_VEC2_FLOAT32: return DXGI_FORMAT_R32G32_FLOAT;
	case DT_VEC3_FLOAT32: return DXGI_FORMAT_R32G32B32_FLOAT;
	case DT_VEC4_FLOAT32: return DXGI_FORMAT_R32G32B32A32_FLOAT;

	default: throw Exception("unsupported format", ERC_NO_SUPPORT); break;
	}
	return DXGI_FORMAT_R32_FLOAT;
}
template<> D3D11_PRIMITIVE_TOPOLOGY ConvertEnum<GfxPrimitives, D3D11_PRIMITIVE_TOPOLOGY>(GfxPrimitives gpType) {
	switch (gpType) {
	case GPT_POINTS: return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST; break;
	case GPT_TRIANGLES: return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST; break;
	case GPT_TRIANGLE_STRIP: return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; break;
	case GPT_TRIANGLE_FAN: return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ; break;
	case GPT_LINES: return D3D11_PRIMITIVE_TOPOLOGY_LINELIST; break;
	case GPT_LINE_LOOP: return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ; break;
	case GPT_LINE_STRIP: return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP; break;
	default: throw Exception("unavailable primitive topology", ERC_INVALID_ENUM); break;
	}
	return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}
template<> UInt32 ConvertEnum<TextureTypes, UInt32>(TextureTypes texType) {
	switch (texType) {
	case TXT_1D: return 0; break;
	case TXT_2D: return 0; break;
	case TXT_3D: return 0; break;
	default: throw Exception("unsupported texture type", ERC_NO_SUPPORT); break;
	}
	return 0;
}
template<> DXGI_FORMAT ConvertEnum <PixelFormats, DXGI_FORMAT>(PixelFormats pxlFormat) {
	switch (pxlFormat) {
	case PXF_R32_SINT32: return DXGI_FORMAT_R32_SINT; break;
	case PXF_R8G8B8_SINT32: return DXGI_FORMAT_R8G8B8A8_SNORM; break;
	case PXF_R8G8B8_UINT32: return DXGI_FORMAT_B8G8R8A8_UNORM; break;
	case PXF_R8G8B8A8_SINT32: return DXGI_FORMAT_R8G8B8A8_SNORM; break;
	case PXF_R8G8B8A8_UINT32: return DXGI_FORMAT_B8G8R8A8_UNORM; break;
	default: throw Exception("unsupported pixel format", ERC_NO_SUPPORT); break;
	}
	return DXGI_FORMAT_R8G8B8A8_UNORM;
}
template<> D3D11_FILTER ConvertEnum <TextureFilters, D3D11_FILTER>(TextureFilters texFilter) {
	switch (texFilter) {
	case TXF_LINEAR: return D3D11_FILTER_MIN_MAG_MIP_LINEAR; break;
	case TXF_NEAREST: return D3D11_FILTER_MIN_MAG_MIP_POINT; break;
	default: throw Exception("unsupported pixel filter", ERC_NO_SUPPORT); break;
	}
	return D3D11_FILTER_MIN_MAG_MIP_POINT;
}
template<> D3D11_TEXTURE_ADDRESS_MODE ConvertEnum<TextureWraps, D3D11_TEXTURE_ADDRESS_MODE>(TextureWraps texWrap) {
	switch (texWrap) {
	case TXW_REPEAT: return D3D11_TEXTURE_ADDRESS_WRAP; break;
	case TXW_CLAMP: return D3D11_TEXTURE_ADDRESS_CLAMP; break;
	case TXW_BORDER: return D3D11_TEXTURE_ADDRESS_CLAMP; break;
	default: throw Exception("unsupported pixel filter", ERC_NO_SUPPORT); break;
	}
	return D3D11_TEXTURE_ADDRESS_WRAP;
}
}
#endif
#endif	// NWG_GAPI