#ifndef GLIB_ENGINE_H
#define GLIB_ENGINE_H

#include <core/glib_layer.h>

namespace GLIB
{
	/// GEngine singleton class
	class GLIB_API GEngine
	{
	public:
		using Layers = DArray<GLayer>;
	private:
		GEngine();
		GEngine(const GEngine& rCpy) = delete;
		void operator=(const GEngine& rCpy) = delete;
	public:
		~GEngine();
		
		// --getters
		static inline GEngine& Get() { static GEngine s_GEngine; return s_GEngine; }
		inline AMemAllocator& GetMemory() { static MemArena m_Memory(nullptr, 0); return m_Memory; }
		inline std::thread* GetRunThread() { return &m_thrRun; }
		inline AGApi* GetGApi() { return m_pGApi; }
		const GEngineInfo& GetInfo() { return m_DInfo; }
		inline Layers& GetLayers() { return m_GLayers; }
		inline GLayer* GetLayer() { return &*m_GLayer; }
		inline GLayer* GetLayer(const char* strName);
		// --setters
		GLayer* AddLayer(const char* strName);
		void RmvLayer(const char* strName);
		// --predicates
		bool IsRunning() { return m_bIsRunning; }

		// --core_methods
		bool Init(Size szMemory);
		void Quit();
		void Run();
		void Update();
		// --data_methods
		bool SaveFImage(const char* strFPath, ImageInfo* pImgInfo);
		bool LoadFImage(const char* strFPath, ImageInfo* pImgInfo);
		bool SaveFShaderCode(const char* strFPath, AShader* pShader);
		bool LoadFShaderCode(const char* strFPath, AShader* pShader);
	private:
		bool m_bIsRunning;
		std::thread m_thrRun;

		AGApi* m_pGApi;
		GMaterial* m_pGMtlScreen;

		Layers m_GLayers;
		Layers::iterator m_GLayer;

		GEngineInfo m_DInfo;
	};
	inline GLayer* GEngine::GetLayer(const char* strName) {
		Layers::iterator itLayer = std::find_if(m_GLayers.begin(), m_GLayers.end(),
			[=](GLayer& rObj)->bool { return rObj.strName == strName; });
		return itLayer == m_GLayers.end() ? nullptr : &*itLayer;
	}
}

#endif // GLIB_ENGINE_H