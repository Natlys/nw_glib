#include <nwg_pch.hpp>
#include "nwg_tools.h"
#pragma warning (disable: 4312)
#if (defined NWG_GAPI)
namespace NWG
{
	GfxContextInfo::GfxContextInfo(const char* sRenderer, const char* sVersion, const char* sShaderLanguage) :
		strRenderer("default"), strVersion("default"), strShdLang("default")
	{
		strcpy_s(&strRenderer[0], 256, &sRenderer[0]);
		strcpy_s(&strVersion[0], 256, &sVersion[0]);
		strcpy_s(&strShdLang[0], 256, &sShaderLanguage[0]);
	}
	// --operators
	OutStream& GfxContextInfo::operator<<(OutStream& rStream) const {
		return rStream <<
			"--==<graphics_context_info>==--" << std::endl <<
			"graphics context: " << &strVersion[0] << std::endl <<
			"renderer: " << &strRenderer[0] << std::endl <<
			"version: " << &strVersion[0] << std::endl <<
			"vendor: " << &strVendor[0] << std::endl <<
			"shading language: " << &strShdLang[0] << std::endl <<
			"--==</graphics_info>==--" << std::endl;
	}
	OutStream& operator<<(OutStream& rStream, const GfxContextInfo& rInfo) { return rInfo.operator<<(rStream); }
}
namespace NWG
{
	GfxBufInfo::GfxBufInfo(Size sizeOfData, Size sizeOfStride, Size sizeOfOffset,
		Ptr ptrToData, DataTypes dataType) :
		szData(sizeOfData), szStride(sizeOfStride), szOffset(sizeOfOffset),
		pData(ptrToData), sdType(dataType) { }
	GfxBufInfo::GfxBufInfo(Size sizeOfData, Size sizeOfStride, Size sizeOfOffset, Ptr ptrToData) :
		szData(sizeOfData), szStride(static_cast<UInt32>(sizeOfStride)), szOffset(static_cast<UInt32>(sizeOfOffset)),
		pData(ptrToData), sdType(DT_DEFAULT) { }
	// --operators
	OutStream& GfxBufInfo::operator<<(OutStream& rStream) const {
		return rStream <<
			"--==<graphics_data_info>==--" << std::endl <<
			"--==</graphics_data_info>==--" << std::endl;
	}
	OutStream& operator<<(OutStream& rStream, const GfxBufInfo& rInfo) { return rInfo.operator<<(rStream); }
}
namespace NWG
{
	void GfxConfig::Reset() {
		General.DrawMode.dMode = DM_FILL;
		General.DrawMode.facePlane = FACE_DEFAULT;

		General.nLineWidth = 0.5f;
		General.nPixelSize = 0.5f;

		Blending.bEnable = false;
		Blending.FactorSrc = BC_SRC_ALPHA;
		Blending.FactorDest = BC_ONE_MINUS_SRC_ALPHA;

		DepthTest.bEnable = false;
		DepthTest.Func = DTC_GREATER;
	}
}
namespace NWG
{
	template<>DataTypes DtGet<Int8>() { return DT_SINT8; }
	template<>DataTypes DtGet<V2i8>() { return DT_VEC2_SINT8; }
	template<>DataTypes DtGet<V3i8>() { return DT_VEC3_SINT8; }
	template<>DataTypes DtGet<V4i8>() { return DT_VEC4_SINT8; }

	template<>DataTypes DtGet<UInt8>() { return DT_SINT8; }
	template<>DataTypes DtGet<V2u8>() { return DT_VEC2_UINT8; }
	template<>DataTypes DtGet<V3u8>() { return DT_VEC3_UINT8; }
	template<>DataTypes DtGet<V4u8>() { return DT_VEC4_UINT8; }

	template<>DataTypes DtGet<Int16>() { return DT_SINT16; }
	template<>DataTypes DtGet<V2i16>() { return DT_VEC2_SINT16; }
	template<>DataTypes DtGet<V3i16>() { return DT_VEC3_SINT16; }
	template<>DataTypes DtGet<V4i16>() { return DT_VEC4_SINT16; }

	template<>DataTypes DtGet<UInt16>() { return DT_UINT16; }
	template<>DataTypes DtGet<V2u16>() { return DT_VEC2_UINT16; }
	template<>DataTypes DtGet<V3u16>() { return DT_VEC3_UINT16; }
	template<>DataTypes DtGet<V4u16>() { return DT_VEC4_UINT16; }

	template<>DataTypes DtGet<Int32>() { return DT_SINT32; }
	template<>DataTypes DtGet<V2i>() { return DT_VEC2_SINT32; }
	template<>DataTypes DtGet<V3i>() { return DT_VEC3_SINT32; }
	template<>DataTypes DtGet<V4i>() { return DT_VEC4_SINT32; }

	template<>DataTypes DtGet<UInt32>() { return DT_UINT32; }
	template<>DataTypes DtGet<V2u>() { return DT_VEC2_UINT32; }
	template<>DataTypes DtGet<V3u>() { return DT_VEC3_UINT32; }
	template<>DataTypes DtGet<V4u>() { return DT_VEC4_UINT32; }

	template<>DataTypes DtGet<Float32>() { return DT_FLOAT32; }
	template<>DataTypes DtGet<V2f>() { return DT_VEC2_FLOAT32; }
	template<>DataTypes DtGet<V3f>() { return DT_VEC3_FLOAT32; }
	template<>DataTypes DtGet<V4f>() { return DT_VEC4_FLOAT32; }
	template<>DataTypes DtGet<Mat2f>() { return DT_MAT2_FLOAT32; }
	template<>DataTypes DtGet<Mat3f>() { return DT_MAT3_FLOAT32; }
	template<>DataTypes DtGet<Mat4f>() { return DT_MAT4_FLOAT32; }

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
		case SHD_SHADER: return "SHD_SHADER"; break;
		case SHD_VERTEX: return "SHD_VERTEX"; break;
		case SHD_PIXEL: return "SHD_PIXEL"; break;
		case SHD_GEOMETRY: return "SHD_GEOMETRY"; break;
		default: throw Exception("unsupported pixel format", ERC_NO_SUPPORT); break;
		}
		return "SHD_DEFAULT";
	}
}
#if (NWG_GAPI & NWG_GAPI_OGL)
#include <ogl/nwg_ogl_loader.h>
// --functions
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
		case SHD_SHADER: return GL_SHADER; break;
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
	template<> UInt32 ConvertEnum<TextureFilters, UInt32>(TextureFilters texFilter) {
		switch (texFilter) {
		case TXF_LINEAR: return GL_LINEAR; break;
		case TXF_NEAREST: return GL_NEAREST; break;
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
	const char* DtGetStr(DataTypes dType) {
		switch (dType) {
		case DT_BOOL: return "boolean";;
		case DT_SINT8: return "signed byte";
		case DT_UINT8: return "unsigned byte";
		case DT_SINT16: return "signed short";
		case DT_UINT16: return "unsigned short";
		case DT_SINT32: return "signed integer";
		case DT_UINT32: return "unsigned integer";
		case DT_FLOAT32: return "float";
		case DT_VEC2_FLOAT32: return "float vector 2d";
		case DT_VEC3_FLOAT32: return "float vector 3d";
		case DT_VEC4_FLOAT32: return "float vector 4d";
		default: break;
		}
		return "default";
	}
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
		Size szData = 0;
		switch (sDataType) {
		case DT_BOOL:
		case DT_SINT8: case DT_UINT8:
			szData = 1; break;
		case DT_VEC2_SINT8: case DT_VEC2_UINT8:
		case DT_SINT16: case DT_UINT16:
			szData = 2; break;
		case DT_FLOAT32:
		case DT_SINT32: case DT_UINT32:
		case DT_VEC2_SINT16: case DT_VEC2_UINT16:
		case DT_VEC2_SINT32: case DT_VEC2_UINT32:
			szData = 4; break;
		
		case DT_VEC2_FLOAT32:
			szData = 8 * 2;	break;
		case DT_VEC3_FLOAT32:
			szData = 8 * 3;	break;
		case DT_VEC4_FLOAT32:
			szData = 8 * 4;	break;

		case DT_USER_DATA: szData = 4; break;
		default: throw Exception("invalid data type", ERC_INVALID_ENUM); szData = 0; break;
		}
		return szData * unCount;
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
namespace NWG
{
	// glGetError gets last message and clears errorLog
	void OglClearErr() { while (glGetError() != GL_NO_ERROR); }
	bool OglErrLog(const char* strLoc, const char* strFile, int nLine)
	{
		UInt32 nErrCode = 0u;
		while ((nErrCode = glGetError()) != GL_NO_ERROR) {
			String strErr;
			switch (nErrCode) {
			case GL_INVALID_ENUM: strErr = "INVALID_ENUM"; break;
			case GL_INVALID_VALUE: strErr = "INVALID_VALUE"; break;
			case GL_INVALID_OPERATION: strErr = "INVALID_OPERATION"; break;
			case GL_STACK_OVERFLOW: strErr = "STACK_OVERFLOW"; break;
			case GL_STACK_UNDERFLOW: strErr = "STACK_UNDERFLOW"; break;
			case GL_OUT_OF_MEMORY: strErr = "OUT_OF_MEMORY"; break;
			}
			throw (Exception(&strErr[0], nErrCode, strLoc, nLine));
			return false;
		}
		return true;
	}

	int OglErrLogShader(ShaderTypes shaderType, UInt32 unId)
	{
		if (unId == 0) { return ERC_UNKNOWN_ID; }
		Int32 nSuccess = 0;
		Int32 nLogSize = 0;
		String strLog;
		const char* strType = ConvertEnum<ShaderTypes, const char*>(shaderType);
		if (shaderType != SHD_SHADER) {
			glGetShaderiv(unId, GL_COMPILE_STATUS, &nSuccess);
			if (nSuccess == false) {
				glGetShaderiv(unId, GL_INFO_LOG_LENGTH, &nLogSize);
				strLog.resize(nLogSize);
				glGetShaderInfoLog(unId, nLogSize, NULL, &strLog[0]);
				throw Exception(&strLog[0], ERC_COMPILLATION, __FILE__, __LINE__);
				return ERC_COMPILLATION;
			}
		}
		else {
			glGetProgramiv(unId, GL_LINK_STATUS, &nSuccess);
			if (nSuccess == false) {
				glGetProgramiv(unId, GL_INFO_LOG_LENGTH, &nLogSize);
				strLog.resize(nLogSize);
				glGetProgramInfoLog(unId, nLogSize, NULL, &strLog[0]);
				throw Exception(&strLog[0], ERC_LINKAGE, __FILE__, __LINE__);
				return ERC_LINKAGE;
			}
		}
		return nSuccess;
	}
}
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
#include <dx/nwg_dx_loader.h>
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
namespace NWG
{
	void DxClearErr() {
		//
	}
	bool DxErrLog(const char* strInfo, const char* strFile, int nLine) {
		return false;
	}
}
#endif
#endif	// NWG_GAPI