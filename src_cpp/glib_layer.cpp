#include "glib_pch.hpp"
#include "glib_layer.h"

#include <glib_engine.h>
#include <glib_buffer.h>
#include <glib_framebuf.h>
#include <glib_shader.h>
#include <glib_material.h>

namespace GLIB
{
	GLayer::GLayer(const char* strName) :
		m_strName(strName),
		m_xywhViewport{ 0, 0, 800, 600 },
		m_GCamera(GCamera()), m_pFrameBuf(nullptr),
		m_DTools(DrawTools())
	{
        FrameBufInfo fbInfo;
        fbInfo.unWidth = m_xywhViewport.z - m_xywhViewport.x;
        fbInfo.unHeight = m_xywhViewport.w - m_xywhViewport.y;
        fbInfo.unSamples = 1;
		m_pFrameBuf = AFrameBuf::Create(&("fmb_" + m_strName)[0], fbInfo);
		
		m_DTools.pVtxBuf = AVertexBuf::Create(2 << 10);
		m_DTools.pIdxBuf = AIndexBuf::Create(2 << 10);
		m_DTools.pShdBuf = AShaderBuf::Create(2 << 10);

		m_DTools.pVtxData = new UByte[m_DTools.pVtxBuf->GetDataSize()];
		m_DTools.pIdxData = new UInt32[m_DTools.pIdxBuf->GetDataSize()];
		m_DTools.pShdData = new UByte[m_DTools.pShdBuf->GetDataSize()];
	}
	GLayer::GLayer(const GLayer& rCpy) : GLayer(&rCpy.m_strName[0]) { }
	GLayer::~GLayer() {
		delete[] m_DTools.pVtxData;
		delete[] m_DTools.pIdxData;
		delete[] m_DTools.pShdData;

		delete m_pFrameBuf;
		delete m_DTools.pVtxBuf;
		delete m_DTools.pIdxBuf;
		delete m_DTools.pShdBuf;
	}

	// --setters
	void GLayer::SetViewport(const V4f& xywhViewport) {
		m_xywhViewport = xywhViewport;
		V2f whSize = { xywhViewport.z - xywhViewport.x, xywhViewport.w - xywhViewport.y };
		m_pFrameBuf->SetSizeWH(whSize.x, whSize.y);
	}
	void GLayer::AddDrawData(const DrawObjectData& rDOData) { }
	void GLayer::RmvDrawData(UInt32 unId) {
		Drawables::iterator itDOData = m_Drawables.begin();
		while (itDOData != m_Drawables.end()) {
			auto& itDrb = std::find_if(itDOData->second.begin(), itDOData->second.end(),
				[=](DrawObjectData& rDOData)->bool {return rDOData.unId == unId; });
			if (itDrb == itDOData->second.end()) { return; }
			itDOData->second.erase(itDrb);
		}
	}
	// --core_methods
	void GLayer::Update()
	{
		m_DTools.ResetData();
		m_GCamera.nAspectRatio = (m_xywhViewport.z - m_xywhViewport.x) / (m_xywhViewport.w - m_xywhViewport.y);

		AGApi* pGApi = GEngine::Get().GetGApi();
		pGApi->SetViewport(m_xywhViewport.x, m_xywhViewport.y, m_xywhViewport.z, m_xywhViewport.w);

		if (DConfig.General.GPrimitive != pGApi->GetPrimitiveType()) { pGApi->SetPrimitiveType(DConfig.General.GPrimitive); }
		pGApi->SetPixelSize(DConfig.General.nPixelSize);
		pGApi->SetLineWidth(DConfig.General.nLineWidth);

		if (DConfig.Blending.bEnable) { pGApi->SetBlendFunc(DConfig.Blending.FactorSrc, DConfig.Blending.FactorDest); }
		pGApi->SetModes(DConfig.Blending.bEnable, PM_BLEND);
		if (DConfig.DepthTest.bEnable) {}
		pGApi->SetModes(DConfig.DepthTest.bEnable, PM_DEPTH_TEST);


		DrawSceneData DSData;
		DSData.m4Proj = m_GCamera.GetProjMatrix();
		DSData.m4View = m_GCamera.GetViewMatrix();
		UploadShaderData(DSData.GetData(), DSData.GetDataSize());

		m_pFrameBuf->Bind();
		m_pFrameBuf->Clear(FB_COLOR | FB_DEPTH | FB_STENCIL);
		for (auto& itDrbs : m_Drawables) {
			m_DTools.pGMtl = itDrbs.first;
			std::sort(itDrbs.second.begin(), itDrbs.second.end());
			for (auto& itDrb : itDrbs.second) {
			}
			GEngine::Get().DrawCall(m_DTools);
			m_DTools.ResetData();
		}
		m_pFrameBuf->Unbind();
	}

	void GLayer::UploadObjectData(const void* pVtx, Size szVtx, const UInt32* pIdx, Size szIdx)
	{
		if (m_DTools.szVtxData + szVtx > m_DTools.pVtxBuf->GetDataSize() ||
			m_DTools.szIdxData + szIdx > m_DTools.pIdxBuf->GetDataSize()) { return; }

		// vtx_data:
		memcpy(m_DTools.pVtxIter, pVtx, szVtx);
		m_DTools.pVtxIter += szVtx;
		m_DTools.szVtxData += szVtx;
		// idx_data:
		memcpy(m_DTools.pIdxIter, pIdx, szIdx);
		m_DTools.pIdxIter += szIdx;
		m_DTools.szIdxData += szIdx;
	}
	void GLayer::UploadShaderData(const void* pShd, Size szShd)
	{
		if (m_DTools.szShdData + szShd > m_DTools.pShdBuf->GetDataSize()) { return; }
		// shd_data
		memcpy(m_DTools.pShdData, pShd, szShd);
		m_DTools.pShdIter += szShd;
		m_DTools.szShdData += szShd;
	}
}