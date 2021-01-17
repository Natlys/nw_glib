#ifndef GLIB_GLAYER_H
#define GLIB_GLAYER_H

#include <glib_camera.h>
#include <glib_tools.h>

namespace GLIB
{
	/// Abstract GLayer class
	/// Description:
	/// -- GEngine works via this class
	/// -- This is set of data required for organized rendering
	/// -- Here are all relevant setting for every draw call
	class GLIB_API GLayer
	{
		using Drawables = HashMap<GMaterial*, DArray<DrawObjectData>>;
		friend class GEngine;
	public:
		DrawConfig DConfig;
	public:
		GLayer(const char* sName);
		GLayer(const GLayer& rCpy);
		~GLayer();

		// --getters
		inline const char* GetName() { return &m_strName[0]; }
		inline GCamera* GetGCamera() { return &m_GCamera; }
		inline V4f GetViewport() { return m_xywhViewport; }
		inline Drawables GetDrawData() { return m_Drawables; }
		inline const AFrameBuf* GetFrameBuf() const { return m_pFrameBuf; }
		inline const AVertexBuf* GetVertexBuf() const { return m_DTools.pVtxBuf; }
		inline const AIndexBuf* GetIndexBuf() const { return m_DTools.pIdxBuf; }
		inline const AShaderBuf* GetShaderBuf() const { return m_DTools.pShdBuf; }
		// --setters
		void SetViewport(const V4f& xywhViewport);
		void AddDrawData(const DrawObjectData& rDOData);
		void RmvDrawData(UInt32 unId);
		// --core_methods
		void Update();
		void UploadObjectData(const void* pVtx, Size szVtx, const UInt32* pIdx, Size szIdx);
		void UploadShaderData(const void* pShd, Size szShd);
	private:
		String m_strName;
		V4f m_xywhViewport;
		GCamera m_GCamera;
		Drawables m_Drawables;
	
		AFrameBuf* m_pFrameBuf;
		DrawTools m_DTools;
	};
}

#endif	// GLIB_GLAYER_H