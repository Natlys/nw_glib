#ifndef NWG_ENGINE_H
#define NWG_ENGINE_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <core/nwg_tools.h>
namespace NWG {
	/// GraphicsEngine class
	class NWG_API GfxEngine : public AMemUser
	{
	public:
		GfxEngine(HWND pWindow);
		GfxEngine(const GfxEngine& rCpy) = delete;
		virtual ~GfxEngine();
		// --getters
		inline GfxContextInfo& GetInfo()	{ return m_gInfo; }
		inline GfxConfig& GetConfigs()		{ return m_gConfig; }
		inline GfxDevice GetDevice()		{ return m_pDevice; }
		inline GfxContext GetContext()		{ return m_pContext; }
		inline Bit IsVSync() const			{ return m_gConfig.General.unSwapInterval; }
#if (NWG_GAPI & NWG_GAPI_DX)
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
		void SetVSync(Bit bSynchronize);
		// --core_methods
		void Update();
		void BeginDraw();
		void EndDraw();
		void OnDraw(ADrawCmp& rDrb);
		/// --create new graphical resource by the ref of appropriate type
		template<typename RType, typename ... Args>
		void NewRes(RefKeeper<RType>& rRes, Args&& ... Arguments);
		/// --create new graphical resource by the ref of abstract type
		template<typename ARType, typename RType, typename ... Args>
		void NewRes(RefKeeper<ARType>& rRes, Args&& ... Arguments);
		static void Create(RefKeeper<GfxEngine>& rEngine, HWND& rWindow);
	private:
		GfxContextInfo m_gInfo;
		GfxConfig m_gConfig;
		HWND m_pWindow;
		GfxDevice m_pDevice;
		GfxContext m_pContext;
#if (NWG_GAPI & NWG_GAPI_DX)
		IDXGISwapChain* m_pSwap;
		ID3D11RenderTargetView* m_pTarget;
#endif
	};
	template<typename RType, typename ... Args>
	void GfxEngine::NewRes(RefKeeper<RType>& rRes, Args&& ... Arguments) {
		rRes.MakeRef<RType>(*this, std::forward<Args>(Arguments)...);
	}
	template<typename ARType, typename RType, typename ... Args>
	void GfxEngine::NewRes(RefKeeper<ARType>& rRes, Args&& ... Arguments) {
		rRes.MakeRef<RType>(*this, std::forward<Args>(Arguments)...);
	}
}
#endif	// NWG_GAPI
#endif	// NWG_ENGINE_H