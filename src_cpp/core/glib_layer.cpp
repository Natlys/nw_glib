#include "glib_pch.hpp"
#include "glib_layer.h"

#include <core/glib_api.h>
#include <core/glib_engine.h>
#include <glib_buffer.h>
#include <glib_framebuf.h>
#include <glib_texture.h>
#include <glib_shader.h>
#include <glib_material.h>

namespace GLIB
{
	GLayer::GLayer(const char* strName) :
		strName(strName)
	{
        FrameBufInfo fbInfo;
        fbInfo.unWidth = xywhViewport.z - xywhViewport.x;
        fbInfo.unHeight = xywhViewport.w - xywhViewport.y;
        fbInfo.unSamples = 1;
		pFrameBuf.MakeRef<FrameBufOgl>(GEngine::Get().GetMemory(), &("fmb_" + this->strName)[0], fbInfo);

		pVtxBuf.MakeRef<VertexBufOgl>(GEngine::Get().GetMemory());
		pVtxBuf->SetData(2 << 10, nullptr);
		pIdxBuf.MakeRef<IndexBufOgl>(GEngine::Get().GetMemory());
		pIdxBuf->SetData(2 << 10, nullptr);
		pShdBuf.MakeRef<ShaderBufOgl>(GEngine::Get().GetMemory());
		pShdBuf->SetData(2 << 10, nullptr);

		pVtxData = new Byte[pVtxBuf->GetDataSize()];
		pIdxData = new UInt32[pIdxBuf->GetDataSize()];
		pShdData = new Byte[pShdBuf->GetDataSize()];
	}
	GLayer::GLayer(const GLayer& rCpy) : GLayer(&rCpy.strName[0]) { }
	GLayer::~GLayer() {
		delete[] pVtxData;
		delete[] pIdxData;
		delete[] pShdData;
	}

	// --setters
	void GLayer::SetShader(AShader* pShader) {
		this->pShader = pShader;
		if (pShader == nullptr) { return; }
		pShdBuf->SetLayout(pShader->GetShdLayout());
		pVtxBuf->SetLayout(pShader->GetVtxLayout());
	}
	void GLayer::SetViewport(const V4f& xywhViewport) {
		this->xywhViewport = xywhViewport;
		V2f whSize = { xywhViewport.z - xywhViewport.x, xywhViewport.w - xywhViewport.y };
		pFrameBuf->SetSizeWH(whSize.x, whSize.y);
	}
	void GLayer::AddDrawData(const DrawObjectData& rDOData) {
		if (rDOData.pGMtl == nullptr) { return; }
		if (rDOData.pGMtl->GetShader() != pShader) { return; }
		Drawables[rDOData.pGMtl].push_back(rDOData);
	}
	void GLayer::OnDraw(AGApi* pGApi)
	{
		static auto fnDrawCall = [&](GMaterial* pGMtl)->void {
			pGMtl->Enable();
			pShdBuf->SetSubData(szShdData, pShdData);
			pVtxBuf->SetSubData(szVtxData, pVtxData);
			pIdxBuf->SetSubData(szIdxData, pIdxData);
			pShdBuf->Bind();
			pVtxBuf->Bind();
			pIdxBuf->Bind();
			pGApi->DrawIndexed(unIdxData);
			pIdxBuf->Unbind();
			pVtxBuf->Unbind();
			pShdBuf->Unbind();
			pGMtl->Disable();
			unDrawCalls++;
		};
		ResetData();
		Camera.nAspectRatio = (xywhViewport.z - xywhViewport.x) / (xywhViewport.w - xywhViewport.y);

		pGApi->SetViewport(xywhViewport.x, xywhViewport.y, xywhViewport.z, xywhViewport.w);

		if (DConfig.General.GPrimitive != pGApi->GetPrimitiveType()) { pGApi->SetPrimitiveType(DConfig.General.GPrimitive); }
		pGApi->SetPixelSize(DConfig.General.nPixelSize);
		pGApi->SetLineWidth(DConfig.General.nLineWidth);

		if (DConfig.Blending.bEnable) { pGApi->SetBlendFunc(DConfig.Blending.FactorSrc, DConfig.Blending.FactorDest); }
		pGApi->SetModes(DConfig.Blending.bEnable, PM_BLEND);
		if (DConfig.DepthTest.bEnable) {}
		pGApi->SetModes(DConfig.DepthTest.bEnable, PM_DEPTH_TEST);

		DSData.m4Proj = Camera.GetProjMatrix();
		DSData.m4View = Camera.GetViewMatrix();
		if (!UploadShdData(DSData)) { return; }

		pFrameBuf->Bind();
		pFrameBuf->Clear(FB_COLOR | FB_DEPTH | FB_STENCIL);
		for (auto& itDrbs : Drawables) {
			std::sort(itDrbs.second.begin(), itDrbs.second.end());
			for (auto& itDrb : itDrbs.second) { if (!UploadVtxData(itDrb)) { fnDrawCall(itDrbs.first); } }
			fnDrawCall(itDrbs.first);
		}
		pFrameBuf->Unbind();
		Drawables.clear();
	}
	// --core_methods
	bool GLayer::UploadVtxData(const DrawObjectData& rDOData)
	{
		Size szVtx = rDOData.GetVtxSize();
		Size szIdx = rDOData.GetIdxSize();
		UInt32 unVtx = szVtx / pVtxBuf->GetLayout().GetStride();
		UInt32 unIdx = rDOData.GetIdxCount();
		if (szVtxData + szVtx > pVtxBuf->GetDataSize() ||
			szIdxData + szIdx > pIdxBuf->GetDataSize()) { return false; }
		// vtx_data:
		memcpy(pVtxIter, rDOData.GetVtxData(), szVtx);
		pVtxIter += szVtx;
		// idx_data:
		for (UInt32 idi = 0; idi < unIdx; idi++) { *pIdxIter++ = rDOData.idxData[idi] + unVtxData; }
		
		szVtxData += szVtx;
		unVtxData += unVtx;
		szIdxData += szIdx;
		unIdxData += unIdx;
		return true;
	}
	bool GLayer::UploadShdData(const DrawSceneData& rDSData)
	{
		Size szData = rDSData.GetDataSize();
		if (szShdData + szData > pShdBuf->GetDataSize()) { return false; }
		// shd_data:
		memcpy(pShdIter, rDSData.GetData(), szData);
		pShdIter += szData;
		szShdData += szData;
		return true;
	}
}