#ifndef NWG_ENGINE_H
#define NWG_ENGINE_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <nwg_tools.h>
namespace NWG
{
	struct NWG_API GfxConfig {
		struct {
			struct {
				DrawModes dMode = DM_FILL;
				FacePlanes facePlane = FACE_DEFAULT;
			} PolyMode;
			Float32 nLineWidth = 0.5f;
			Float32 nPixelSize = 0.5f;
			UInt32 unSwapInterval = 1u;
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
		inline void Reset() {
			General.PolyMode.dMode = DM_FILL;
			General.PolyMode.facePlane = FACE_DEFAULT;

			General.nLineWidth = 0.5f;
			General.nPixelSize = 0.5f;

			Blending.bEnable = false;
			Blending.FactorSrc = BC_SRC_ALPHA;
			Blending.FactorDest = BC_ONE_MINUS_SRC_ALPHA;

			DepthTest.bEnable = false;
			DepthTest.Func = DTC_GREATER;
		}
	};
	struct NWG_API GfxContextInfo
	{
	public:
		Char strRenderer[256], strVersion[256], strVendor[256], strShdLang[256];
		Int32 nMaxVertexAttribs = 0;
		Int32 nActiveTextureId = 0;
		Int32 nMaxTextures = 0;
	public:
		inline OStream& operator<<(OStream& rStream);
	};
	inline OStream& GfxContextInfo::operator<<(OStream& rStream) {
		return rStream <<
			"--==<graphics_context_info>==--" << std::endl <<
			"graphics context: " << &strVersion[0] << std::endl <<
			"renderer: " << &strRenderer[0] << std::endl <<
			"version: " << &strVersion[0] << std::endl <<
			"vendor: " << &strVendor[0] << std::endl <<
			"shading language: " << &strShdLang[0] << std::endl <<
			"--==</graphics_info>==--" << std::endl;
	}
	inline OStream& operator<<(OStream& rStream, GfxContextInfo& rgInfo) { return rgInfo.operator<<(rStream); }
	struct NWG_API GfxDrawInfo
	{
	public:
		Size szVtx = 0;
		Size szIdx = 0;
		UInt32 unIdx = 0;
		UInt32 unVtx = 0;
		ShaderDataTypes sdIdx = SDT_UINT32;
	public:
		inline void Reset() { szVtx = szIdx = 0; unIdx = unVtx = 0; }
	};
}
namespace NWG
{
	/// GraphicsEngine class
	class NWG_API GfxEngine
	{
	public:
		GfxEngine(HWND pWindow);
		GfxEngine(const GfxEngine& rCpy) = delete;
		virtual ~GfxEngine();
		// --getters
		inline GfxContextInfo& GetInfo()	{ return m_gInfo; }
		inline GfxConfig& GetConfigs()		{ return m_gConfig; }
		inline GfxDrawInfo& GetDrawInfo()	{ return m_dInfo; }
#if (NWG_GAPI & NWG_GAPI_OGL)
		inline HDC GetDevice()				{ return m_pDevice; }
		inline HGLRC GetContext()			{ return m_pContext; }
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
		inline ID3D11Device* GetDevice() { return m_pDevice; }
		inline ID3D11DeviceContext* GetContext() { return m_pContext; }
		inline IDXGISwapChain* GetSwapChain() { return m_pSwap; }
#endif
		// --setters
		void SetVariable(GfxVariables gfxVar, Float32 nValue);
		void SetPrimitive(GfxPrimitives gfxPrimitiveTopology);
		void SetModes(Bit bEnable, ProcessingModes pmMode);
		void SetViewport(Int32 nX, Int32 nY, Int32 nWidth, Int32 nHeight);
		void SetDrawMode(DrawModes dmMode, FacePlanes fpFace);
		void SetBlendFunc(BlendConfigs bcFactorSrc, BlendConfigs bcFactorDest);
		void SetDepthFunc(DepthConfigs dcFunc);
		void SetStencilFunc(StencilConfigs scFunc, UInt32 unRefValue, UInt8 unBitMask);
		// --core_methods
		void Update();
		void BeginDraw();
		void EndDraw();
		void OnDraw(VertexedDrawable& rDrb);
		void OnDraw(IndexedDrawable& rDrb);
		template<class RType, typename ... Args>
		void CreateRes(RefKeeper<RType>& rRes, Args&& ... Arguments);
		template<class ARType, class RType, typename ... Args>
		void CreateRes(RefKeeper<ARType>& rRes, Args&& ... Arguments);
		static void Create(RefKeeper<GfxEngine>& rEngine, HWND& rWindow);
	private:
		GfxContextInfo m_gInfo;
		GfxDrawInfo m_dInfo;
		GfxConfig m_gConfig;
		HWND m_pWindow;
#if (NWG_GAPI & NWG_GAPI_OGL)
		HDC m_pDevice;
		HGLRC m_pContext;
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pContext;
		IDXGISwapChain* m_pSwap;
		ID3D11RenderTargetView* m_pTarget;
#endif
	};
	template<class RType, typename ... Args>
	void GfxEngine::CreateRes(RefKeeper<RType>& rRes, Args&& ... Arguments) {
		rRes.SetRef<RType>(EntSys::AddEnt<RType>(*this, std::forward<Args>(Arguments)...));
	}
	template<class ARType, class RType, typename ... Args>
	void GfxEngine::CreateRes(RefKeeper<ARType>& rRes, Args&& ... Arguments) {
		rRes.SetRef<ARType>(EntSys::AddEnt<RType>(*this, std::forward<Args>(Arguments)...));
	}
}
#endif	// NWG_GAPI
#endif	// NWG_ENGINE_H