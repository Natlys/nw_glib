#ifndef GLIB_ENGINE_H
#define GLIB_ENGINE_H

#include <glib_layer.h>
#include <glib_api.h>
#include <glib_tools.h>
#include <glib_decl.hpp>

namespace GLIB
{
	/// GEngine singleton class
	class GLIB_API GEngine
	{
	public:
		using Layers = List2<GLayer>;
	private:
		GEngine();
		GEngine(const GEngine& rCpy) = delete;
		void operator=(const GEngine& rCpy) = delete;
	public:
		~GEngine();
		
		// --getters
		static inline GEngine& Get() { static GEngine s_GEngine; return s_GEngine; }
		inline std::thread& GetRunThread() { return m_thrRun; }
		inline AWindow* GetWindow() { return m_pWindow; }
		inline AGApi* GetGApi() { return m_pGApi; }
		const GEngineInfo& GetInfo() { return m_DInfo; }
		inline Layers& GetLayers() { return m_GLayers; }
		inline GLayer* GetLayer() { return &*m_GLayer; }
		inline GLayer* GetLayer(const char* strName);
		// --setters
		GLayer* AddLayer(const char* strName);
		void RmvLayer(const char* strName);
		void ChangeLayerOrder(const char* strName, bool bPushUp);
		// --predicates
		bool IsRunning() { return m_bIsRunning; }

		// --core_methods
		bool Init(WApiTypes WindowApiType, GApiTypes GraphicsApiType);
		void Quit();
		void Run();
		void DrawCall(DrawTools& rDTools);
		void Update();
		// --data_methods
		bool LoadFImage(const char* strFPath, ImageInfo* pImg);
	private:
		bool m_bIsRunning;
		std::thread m_thrRun;
		
		AWindow* m_pWindow;
		AGApi* m_pGApi;

		Layers m_GLayers;
		Layers::iterator m_GLayer;

		GEngineInfo m_DInfo;
	};
	inline GLayer* GEngine::GetLayer(const char* strName) {
		Layers::iterator itLayer = std::find_if(m_GLayers.begin(), m_GLayers.end(),
			[=](GLayer& rObj)->bool {return strcmp(&rObj.GetName()[0], strName) == 0; });
		return itLayer == m_GLayers.end() ? nullptr : &*itLayer;
	}
}

#endif // GLIB_ENGINE_H