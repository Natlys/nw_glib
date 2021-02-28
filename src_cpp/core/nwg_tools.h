#ifndef NWG_TOOLS_H
#define NWG_TOOLS_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <core/nwg_switch.h>
namespace NWG
{
	struct NWG_API GfxContextInfo : public AInfo
	{
	public:
		Char strRenderer[256], strVersion[256], strVendor[256], strShdLang[256];
		Int32 nMaxVertexAttribs = 0;
		Int32 nActiveTextureId = 0;
		Int32 nMaxTextures = 0;
	public:
		GfxContextInfo() = default;
		GfxContextInfo(const char* sRenderer, const char* sVersion, const char* sShaderLanguage);
		// --operators
		virtual OutStream& operator<<(OutStream& rStream) const override;
		virtual InStream& operator>>(InStream& rStream) override;
	};
}
namespace NWG
{
	struct NWG_API GfxConfig
	{
		struct {
			struct {
				DrawModes dMode = DM_DEFAULT;
				FacePlanes facePlane = FACE_DEFAULT;
				GfxPrimitives gPrimitive = GPT_DEFAULT;
			} DrawMode;
			Float32 nLineWidth = 0.5f;
			Float32 nPixelSize = 0.5f;
			UInt32 unSwapInterval = 1u;
			V4i rectViewport = { 0, 0, 800, 600 };
			V4f rgbaClear = { 0.3f, 0.5f, 0.7f, 1.0f };
		} General;
		struct {
			Bit bEnable = false;
			BlendConfigs FactorSrc = BC_SRC_ALPHA;
			BlendConfigs FactorDest = BC_ONE_MINUS_SRC_ALPHA;
		} Blending;
		struct {
			Bit bEnable = false;
			CullFaceConfigs CullFactor = CFC_DEFAULT;
		} Culling;
		struct {
			Bit bEnable = false;
			DepthConfigs Func = DTC_DEFAULT;
		} DepthTest;
		struct {
			Bit bEnable = false;
			StencilConfigs Func = STC_DEFAULT;
			UInt8 nBitMask = 0x0;
			UInt32 nRefValue = 0x0;
		} StencilTest;
	public:
		void Reset();
	};
}

#if (NWG_GAPI & NWG_GAPI_OGL)
namespace NWG
{
	void OglClearErr();
	bool OglErrLog(const char* strInfo, const char* strFile, int nLine);
	int OglErrLogShader(ShaderTypes ShaderType, UInt32 unShaderId);
}
	#if (defined NWG_DEBUG)
			#define NWG_DEBUG_CALL(code) ( OglClearErr(); code		\
			if (OglErrLog(#code, __FILE__, __LINE__, "GL_ERROR: ") == false) { NWL_BREAK(); } )
	#else
		#define NWG_DEBUG_CALL(code) (code)
	#endif
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
namespace NWG
{
	void DxClearErr();
	bool DxErrLog(const char* strInfo, const char* strFile, int nLine);
}
	#if (defined NWG_DEBUG)
		#define NWG_DEBUG_CALL(code) ( DxClearErr(); (code) NWL_ASSERT(DxErrLog(##code, __FILE__, __LINE__, "GL_ERROR: "))
	#else
		#define NWG_DEBUG_CALL(code) (code)
	#endif
#endif

#endif	// NWG_GAPI
#endif	// NWG_TOOLS_H