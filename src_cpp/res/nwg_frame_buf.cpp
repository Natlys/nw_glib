#include <nwg_pch.hpp>
#include "nwg_frame_buf.h"
#if (defined NWG_GAPI)
#include <res/nwg_texture.h>
#if (NWG_GAPI & NWG_GAPI_OGL)
#include <lib/nwg_ogl_v1.h>
#include <lib/nwg_ogl_v2.h>
#include <lib/nwg_ogl_arb.h>
namespace NWG
{
	FrameBuf::FrameBuf(GfxEngine& rGfx, const char* strName, const FrameBufInfo& rInfo) :
		AGfxRes(rGfx), ADataRes(strName),
		m_Info(rInfo), m_rgbaClear{ 0.5f, 0.5f, 0.5f, 1.0f } { }
	FrameBuf::~FrameBuf() { if (m_unRId != 0) { glDeleteFramebuffers(1, &m_unRId); m_unRId = 0; } }
	// --setters
	void FrameBuf::SetViewport(V4i rectViewport) { m_Info.rectViewport = rectViewport; }
	void FrameBuf::SetClearColor(V4f rgbaClear) { m_rgbaClear = rgbaClear; }
	void FrameBuf::AttachTexture(RefKeeper<Texture>& rTex) { m_Attachments.push_back(rTex); }
	void FrameBuf::DetachTexture(UInt32 unIdx) { m_Attachments.erase(m_Attachments.begin() + unIdx); }
	// --==<core_methods>==--
	void FrameBuf::OnDraw() {
		glBindFramebuffer(GL_FRAMEBUFFER, m_unRId);
		glViewport(0, 0, GetSizeW(), GetSizeH());
	}
	void FrameBuf::Remake()
	{
		if (m_unRId != 0) { glDeleteFramebuffers(1, &m_unRId); m_unRId = 0; }
		if (m_Info.GetSizeW() < 1 || m_Info.GetSizeH() < 1) { return; }

		glGenFramebuffers(1, &m_unRId);
		glBindFramebuffer(GL_FRAMEBUFFER, m_unRId);

		m_Info.bHasStencil = m_Info.bHasDepth = false;
		m_Info.unColorCount = 0;
		UInt32 ColorIds[GL_MAX_COLOR_ATTACHMENTS] { 0 };

		for (UInt32 txi = 0; txi < m_Attachments.size(); txi++) {
			if (m_Attachments[txi] == nullptr) { NWL_ERR("Null attachment!"); DetachTexture(txi); }
			auto& rTex = *m_Attachments[txi];
			TextureInfo texInfo = rTex.GetInfo();
			if (m_Info.bResizable) {
				texInfo.nWidth = GetSizeW();
				texInfo.nHeight = GetSizeH();
			}
			rTex.Remake(texInfo);
			glBindTexture(GL_TEXTURE_2D, rTex.GetRenderId());
			UInt32 unAttachType = 0;
			if (texInfo.pxlFormat== PXF_R32_SINT32 || texInfo.pxlFormat == PXF_R32_UINT32 ||
				texInfo.pxlFormat== PXF_R8G8B8_SINT32 || texInfo.pxlFormat == PXF_R8G8B8_UINT32 ||
				texInfo.pxlFormat== PXF_R8G8B8A8_SINT32 || texInfo.pxlFormat== PXF_R8G8B8A8_UINT32)
			{
				unAttachType = GL_COLOR_ATTACHMENT0 + m_Info.unColorCount;
				ColorIds[m_Info.unColorCount] = rTex.GetRenderId();
				m_Info.unColorCount++;
			}
			else if (texInfo.pxlFormat== PXF_D32_SINT32 || texInfo.pxlFormat== PXF_D32_UINT32) {
				m_Info.bHasDepth = true;
				unAttachType = GL_DEPTH_ATTACHMENT;
			}
			else if (texInfo.pxlFormat== PXF_S8_SINT8 || texInfo.pxlFormat== PXF_S8_UINT8) {
				m_Info.bHasStencil = true;
				unAttachType = GL_STENCIL_ATTACHMENT;
			}
			else if (texInfo.pxlFormat== PXF_D24S8_SINT32 || texInfo.pxlFormat== PXF_D24S8_UINT32) {
				m_Info.bHasDepth = m_Info.bHasStencil = true;
				unAttachType = GL_DEPTH_STENCIL_ATTACHMENT;
			}
			glFramebufferTexture2D(GL_FRAMEBUFFER, unAttachType, ConvertEnum<TextureTypes, UInt32>(rTex.GetTexType()), rTex.GetRenderId(), 0);
		}
		if (m_Info.unColorCount > 0) { glDrawBuffers(m_Info.unColorCount, &ColorIds[0]); }
		else { glDrawBuffer(GL_NONE); }

		bool bIsCompleted = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
		NWL_ASSERT(bIsCompleted, "FrameBufOgl is not created!");
	}
	void FrameBuf::Clear() {
		UInt32 unMask = 0;
		unMask |= m_Info.unColorCount > 0 ? GL_COLOR_BUFFER_BIT : 0u;
		unMask |= m_Info.bHasDepth ? GL_DEPTH_BUFFER_BIT : 0u;
		unMask |= m_Info.bHasStencil ? GL_STENCIL_BUFFER_BIT : 0u;
		glClearColor(m_rgbaClear.r, m_rgbaClear.g, m_rgbaClear.b, m_rgbaClear.a);
		glClear(unMask);
	}

	void FrameBuf::ReadPixels(Ptr pData, UInt32 unAttachIdx, Int32 nX, Int32 nY, Int32 nW, Int32 nH)
	{
		const TextureInfo& texInfo = GetAttachment()->GetInfo();
		glReadBuffer(GL_COLOR_ATTACHMENT0 + unAttachIdx);
		// --error is guaranteed, internal and usual formats are different
		glReadPixels(nX, nY, nW, nH, ConvertEnum<PixelFormats, UInt32>(texInfo.pxlFormat),
			ConvertEnum<PixelFormats, UInt32>(texInfo.pxlFormat), pData);
	}
	void FrameBuf::WritePixels(Ptr pData, UInt32 unAttachIdx, Int32 nX, Int32 nY, Int32 nW, Int32 nH)
	{
		const TextureInfo& texInfo = GetAttachment()->GetInfo();
		glDrawBuffer(GL_COLOR_ATTACHMENT0 + unAttachIdx);
		glDrawPixels(nW, nH, ConvertEnum<PixelFormats, UInt32>(texInfo.pxlFormat),
			ConvertEnum<PixelFormats, UInt32>(texInfo.pxlFormat), pData);
	}
	// --==</core_methods>==--
	// --==<data_methods>==--
	bool FrameBuf::SaveF(const char* strFPath) { return true; }
	bool FrameBuf::LoadF(const char* strFPath) { return true; }
	// --==</data_methods>==--
}
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
#include <lib/nwg_dx_loader.h>
namespace NWG
{
	FrameBuf::FrameBuf(GfxEngine& rGfx, const char* strName, const FrameBufInfo& rInfo) :
		AGfxRes(rGfx), ADataRes(strName),
		m_Info(rInfo),
		m_rgbaClear{ 0.5f, 0.5f, 0.5f, 1.0f } { }
	FrameBuf::~FrameBuf() { }
	// --setters
	void FrameBuf::SetViewport(V4i rectViewport) { m_Info.rectViewport = rectViewport; }
	void FrameBuf::SetClearColor(V4f rgbaClear) { m_rgbaClear = rgbaClear; }
	void FrameBuf::AttachTexture(Texture& rTex) { m_Attachments.push_back(RefKeeper<Texture>{ *EntSys::GetEnt<Texture>(rTex.GetEntId()) }); }
	void FrameBuf::DetachTexture(UInt32 unIdx) { m_Attachments.erase(m_Attachments.begin() + unIdx); }
	// --==<core_methods>==--
	void FrameBuf::Bind() {
	}
	void FrameBuf::Remake()
	{
	}
	void FrameBuf::Clear() {
	}

	void FrameBuf::ReadPixels(Ptr pData, UInt32 unAttachIdx, Int32 nX, Int32 nY, Int32 nW, Int32 nH)
	{
	}
	void FrameBuf::WritePixels(Ptr pData, UInt32 unAttachIdx, Int32 nX, Int32 nY, Int32 nW, Int32 nH)
	{
	}
	// --==</core_methods>==--
	// --==<data_methods>==--
	bool FrameBuf::SaveF(const char* strFPath) { return true; }
	bool FrameBuf::LoadF(const char* strFPath) { return true; }
	// --==</data_methods>==--
}
#endif
#endif // NWG_GAPI