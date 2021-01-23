#ifndef GLIB_LAYER_H
#define GLIB_LAYER_H

#include <glib_camera.h>
#include <glib_tools.h>

namespace GLIB
{
	/// Abstract GLayer struct
	/// Description:
	/// -- GEngine works via this class
	/// -- This is set of data required for organized rendering
	/// -- Here are all relevant setting for every draw call
	/// -- Every layer has own configuration and only one shader
	/// -- It unites some data for draw call as a result
	/// -- Rendering is sorted in orders
	struct GLIB_API GLayer
	{
		using OnDrawData = HashMap<GMaterial*, DArray<DrawObjectData>>;
	public:
		String strName = "gel_default";
		Bit bIsEnabled = false;
		UInt32 unDrawOrder = 0;

		DrawConfig DConfig;
		OnDrawData Drawables;
		DrawSceneData DSData;

		V4f xywhViewport = { 0, 0, 800, 600 };
		GCamera Camera = GCamera();

		UInt32 unDrawCalls = 0;
		// --vertex_data
		Byte* pVtxData = nullptr;
		Byte* pVtxIter = nullptr;
		Size szVtxData = 0;
		UInt32 unVtxData = 0;
		// --index_data
		UInt32* pIdxIter = nullptr;
		UInt32* pIdxData = nullptr;
		Size szIdxData = 0;
		UInt32 unIdxData = 0;
		// --shader_data
		Byte* pShdData = nullptr;
		Byte* pShdIter = nullptr;
		Size szShdData = 0;
		// --objects
		AShader* pShader = nullptr;
		RefOwner<AFrameBuf> pFrameBuf;
		RefOwner<AVertexBuf> pVtxBuf;
		RefOwner<AIndexBuf> pIdxBuf;
		RefOwner<AShaderBuf> pShdBuf;
	public:
		GLayer(const char* sName);
		GLayer(const GLayer& rCpy);
		~GLayer();

		// --setters
		void SetShader(AShader* pShader);
		void SetViewport(const V4f& xywhViewport);
		void AddDrawData(const DrawObjectData& rDOData);
		// --core_methods
		void OnDraw(AGApi* pGApi);
		bool UploadVtxData(const DrawObjectData& rDOData);
		bool UploadShdData(const DrawSceneData& rDSData);
		inline void ResetData();
		// --operators
		inline bool operator>	(GLayer& rLayer)	{ return rLayer.unDrawOrder > unDrawOrder; }
		inline bool operator<	(GLayer& rLayer)	{ return rLayer.unDrawOrder < unDrawOrder; }
	};
	inline void GLayer::ResetData() {
		pVtxIter = &pVtxData[0];
		szVtxData = unVtxData = 0;
		pIdxIter = &pIdxData[0];
		szIdxData = unIdxData = 0;
		pShdIter = &pShdData[0];
		szShdData = 0;
		unDrawCalls = 0;
	}
}

#endif	// GLIB_LAYER_H