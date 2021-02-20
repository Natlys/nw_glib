#ifndef NWG_TOOLS_H
#define NWG_TOOLS_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#pragma warning(disable:4267)
namespace NWG
{
	template<typename SDType> inline ShaderDataTypes GetSdType() { return SDT_DEFAULT; }
	template<> inline ShaderDataTypes GetSdType<Int8>() { return SDT_SINT8; }
	template<> inline ShaderDataTypes GetSdType<UInt8>() { return SDT_UINT8; }
	template<> inline ShaderDataTypes GetSdType<Int16>() { return SDT_SINT16; }
	template<> inline ShaderDataTypes GetSdType<UInt16>() { return SDT_UINT16; }
	template<> inline ShaderDataTypes GetSdType<Int32>() { return SDT_SINT32; }
	template<> inline ShaderDataTypes GetSdType<UInt32>() { return SDT_UINT32; }
	template<> inline ShaderDataTypes GetSdType<Float32>() { return SDT_FLOAT32; }
	template<> inline ShaderDataTypes GetSdType<V2f>() { return SDT_FLOAT32_VEC2; }
	template<> inline ShaderDataTypes GetSdType<V3f>() { return SDT_FLOAT32_VEC3; }
	template<> inline ShaderDataTypes GetSdType<V4f>() { return SDT_FLOAT32_VEC4; }
	inline Size SdTypeGetSize(ShaderDataTypes sDataType, UInt32 unCount = 1) {
		Size szData = 0;
		switch (sDataType) {
		case SDT_BOOL: case SDT_SINT8: case SDT_UINT8:	szData = 1;	break;
		case SDT_SINT16: case SDT_UINT16:	szData = 2;	break;
		case SDT_SINT32: case SDT_UINT32:	szData = 4;	break;
		case SDT_SAMPLER:		szData = 4;		break;
		case SDT_FLOAT64:			szData = 8;	break;
		case SDT_FLOAT32:		szData = 4;						break;
		case SDT_FLOAT32_VEC2:									szData = 8 * 2;	break;
		case SDT_FLOAT32_VEC3:									szData = 8 * 3;	break;
		case SDT_FLOAT32_VEC4:									szData = 8 * 4;	break;
		default:	NWL_ERR("Invalid shader data type");		szData = 0;	break;
		}
		return szData * unCount;
	}
	inline Size SdTypeGetAllignedSize(ShaderDataTypes sDataType, UInt32 unCount = 1) {
		Size szAll = 0;
		switch (sDataType) {
		case SDT_BOOL: case SDT_SINT8: case SDT_UINT8:			szAll = 4;	break;
		case SDT_SINT16: case SDT_UINT16:						szAll = 4;	break;
		case SDT_SINT32: case SDT_UINT32: case SDT_SAMPLER:		szAll = 4;	break;
		case SDT_FLOAT32:										szAll = 4;	break;
		case SDT_FLOAT64:										szAll = 8;	break;
		default:	NWL_ERR("Invalid shader data type");		szAll = 0;	break;
		}
		return szAll * ((unCount + (szAll - 1)) & ~(szAll - 1));
	}
	inline const char* SdTypeGetStr(ShaderDataTypes sdType) {
		return sdType == SDT_BOOL ? "boolean" :
			sdType == SDT_SINT8 ? "byte" : sdType == SDT_UINT8 ? "unsigned byte" :
			sdType == SDT_SINT16 ? "short" : sdType == SDT_UINT16 ? "unsigned short" :
			sdType == SDT_SINT32 ? "integer" : sdType == SDT_UINT32 ? "unsigned integer" :
			sdType == SDT_FLOAT32 ? "float" : sdType == SDT_FLOAT64 ? "double" :
			"unknown";
	}
}
namespace NWG
{
	struct GfxDataInfo
	{
	public:
		Size szData = 0;
		UInt32 szStride = 0;
		UInt32 szOffset = 0;
		Ptr pData = nullptr;
		ShaderDataTypes sdType = SDT_DEFAULT;
	public:
		GfxDataInfo() = default;
		GfxDataInfo(Size sizeOfData, Size sizeOfStride, Size sizeOfOffset,
			Ptr ptrToData, ShaderDataTypes dataType) :
			szData(sizeOfData), szStride(sizeOfStride), szOffset(sizeOfOffset),
			pData(ptrToData), sdType(dataType) {}
		GfxDataInfo(Size sizeOfData, Size sizeOfStride, Size sizeOfOffset,
			Ptr ptrToData) :
			szData(sizeOfData), szStride(sizeOfStride), szOffset(sizeOfOffset),
			pData(ptrToData), sdType(SDT_DEFAULT) {}
	};
}
#if (NWG_GAPI & NWG_GAPI_OGL)
// --functions
namespace NWG
{
	/// Clear GL error buffer
	void OglClearErr();
	/// Return suitable error message accordingly to glGetError()
	bool OglErrLog(const char* strInfo, const char* strFile, int nLine);
	/// Get compile and linking status return true if there are errors
	int OglErrLogShader(ShaderTypes ShaderType, UInt32 unShaderId);
}
	#if (defined NWG_DEBUG)
			#define OGL_CALL(call) OglClearErr();\
				call;\
				NWL_ASSERT(OglErrLog(#call, NWL_FNAME_APATH((std::string)__FILE__), __LINE__), "GL_ERROR: ")
			#define NWL_OGL_SHADER_ERR_LOG(errType, objectID) (OglErrLogShader(errType, objectID))
			#define NWL_OGL_SHADER_ERR_LOG(errType, objectID) (OglErrLogShader(errType, objectID))
	#else
		#define OGL_CALL(function);
	#endif
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
#include <C:\Program Files (x86)\Windows Kits\10\Include\10.0.18362.0\shared\dxgiformat.h>
// --functions
namespace NWG
{
	bool DxErrLog(const char* strInfo, const char* strFile, int nLine);
	DXGI_FORMAT SdToDxFormat(ShaderDataTypes sdType);
}
#endif
#endif	// NWG_GAPI
#endif	// NWG_TOOLS_H