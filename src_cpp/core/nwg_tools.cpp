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
	InStream& GfxContextInfo::operator>>(InStream& rStream) {
		return rStream >>
			strVersion >> strRenderer >> strVersion >> strVendor >> strShdLang;
	}
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
#if (NWG_GAPI & NWG_GAPI_OGL)
#include <lib/nwg_ogl_v1.h>
#include <lib/nwg_ogl_v2.h>
#include <lib/nwg_ogl_v3.h>
#include <lib/nwg_ogl_arb.h>
// --functions
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
		if (shaderType != SHD_PROG) {
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
#include <lib/nwg_dx_loader.h>
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