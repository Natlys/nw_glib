#include <nwg_pch.hpp>
#include "nwg_frame_buf.h"
#if (defined NWG_GAPI)
#include <nwg_texture.h>
#include <nwg_loader.h>
#if (NWG_GAPI & NWG_GAPI_OGL)
namespace NWG
{
	FrameBuf::FrameBuf(GfxEngine& rGfx, const char* strName, const FrameBufInfo& rInfo) :
		TEntity(), AGfxRes(rGfx), ADataRes(strName),
		m_Info(rInfo), m_rgbaClear{ 0.5f, 0.5f, 0.5f, 1.0f } { }
	FrameBuf::~FrameBuf() { if (m_unRId != 0) { glDeleteFramebuffers(1, &m_unRId); m_unRId = 0; } }
	// --setters
	void FrameBuf::SetViewport(V4i rectViewport) { m_Info.rectViewport = rectViewport; }
	void FrameBuf::SetClearColor(V4f rgbaClear) { m_rgbaClear = rgbaClear; }
	void FrameBuf::AttachTexture(Texture& rTex) { m_Attachments.push_back(RefKeeper<Texture>{ *EntSys::GetEnt<Texture>(rTex.GetRenderId()) }); }
	void FrameBuf::DetachTexture(UInt32 unIdx) { m_Attachments.erase(m_Attachments.begin() + unIdx); }
	// --==<core_methods>==--
	void FrameBuf::Bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, m_unRId);
		glViewport(0, 0, GetWidth(), GetHeight());
	}
	void FrameBuf::Remake()
	{
		if (m_unRId != 0) { glDeleteFramebuffers(1, &m_unRId); m_unRId = 0; }
		if (m_Info.GetHeight() < 1 || m_Info.GetWidth() < 1) { return; }

		glCreateFramebuffers(1, &m_unRId);
		glBindFramebuffer(GL_FRAMEBUFFER, m_unRId);

		m_Info.bHasStencil = m_Info.bHasDepth = false;
		m_Info.unColorCount = 0;
		UInt32 ColorIds[GL_MAX_COLOR_ATTACHMENTS] { 0 };

		for (UInt32 txi = 0; txi < m_Attachments.size(); txi++) {
			if (m_Attachments[txi] == nullptr) { NWL_ERR("Null attachment!"); DetachTexture(txi); }
			auto& rTex = *m_Attachments[txi];
			ImageInfo imgInfo = rTex.GetImage().GetInfo();
			if (m_Info.bResizable) {
				imgInfo.nWidth = GetWidth();
				imgInfo.nHeight = GetHeight();
			}
			Image rImg = rTex.GetImage();
			rTex.SetImage(rImg);
			rTex.Remake();
			rTex.Bind();
			UInt32 unAttachType = 0;
			if (rImg.GetFormat()== PXF_R32_SINT32 || rImg.GetFormat()== PXF_R32_UINT32 ||
				rImg.GetFormat()== PXF_R8G8B8_SINT32 || rImg.GetFormat()== PXF_R8G8B8_UINT32 ||
				rImg.GetFormat()== PXF_R8G8B8A8_SINT32 || rImg.GetFormat()== PXF_R8G8B8A8_UINT32)
			{
				unAttachType = GL_COLOR_ATTACHMENT0 + m_Info.unColorCount;
				ColorIds[m_Info.unColorCount] = rTex.GetRenderId();
				m_Info.unColorCount++;
			}
			else if (rImg.GetFormat()== PXF_D32_SINT32 || rImg.GetFormat()== PXF_D32_UINT32) {
				m_Info.bHasDepth = true;
				unAttachType = GL_DEPTH_ATTACHMENT;
			}
			else if (rImg.GetFormat()== PXF_S8_SINT8 || rImg.GetFormat()== PXF_S8_UINT8) {
				m_Info.bHasStencil = true;
				unAttachType = GL_STENCIL_ATTACHMENT;
			}
			else if (rImg.GetFormat()== PXF_D24S8_SINT32 || rImg.GetFormat()== PXF_D24S8_UINT32) {
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
		const Image& rImg = GetAttachment()->GetImage();
		glReadBuffer(GL_COLOR_ATTACHMENT0 + unAttachIdx);
		// --error is guaranteed, internal and usual formats are different
		glReadPixels(nX, nY, nW, nH, ConvertEnum<PixelFormats, UInt32>(rImg.GetFormat()), ConvertEnum<PixelFormats, UInt32>(rImg.GetFormat()), pData);
	}
	void FrameBuf::WritePixels(Ptr pData, UInt32 unAttachIdx, Int32 nX, Int32 nY, Int32 nW, Int32 nH)
	{
		const Image& rImg = GetAttachment()->GetImage();
		glRasterPos2i(nX, nY);
		glDrawPixels(nW, nH, ConvertEnum<PixelFormats, UInt32>(rImg.GetFormat()), ConvertEnum<PixelFormats, UInt32>(rImg.GetFormat()), pData);
	}
	// --==</core_methods>==--
	// --==<data_methods>==--
	bool FrameBuf::SaveF(const char* strFPath) { return true; }
	bool FrameBuf::LoadF(const char* strFPath) { return true; }
	// --==</data_methods>==--
}
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
namespace NWG
{
	FrameBuf::FrameBuf(GfxEngine& rGfx, const char* strName, const FrameBufInfo& rInfo) :
		TEntity(), AGfxRes(rGfx), ADataRes(strName),
		m_Info(rInfo),
		m_rgbaClear{ 0.5f, 0.5f, 0.5f, 1.0f } { }
	FrameBuf::~FrameBuf() { }
	// --setters
	void FrameBuf::SetViewport(V4i rectViewport) { m_Info.rectViewport = rectViewport; }
	void FrameBuf::SetClearColor(V4f rgbaClear) { m_rgbaClear = rgbaClear; }
	void FrameBuf::AttachTexture(Texture& rTex) { m_Attachments.push_back(RefKeeper<Texture>{ *EntSys::GetEnt<Texture>(rTex.GetRenderId()) }); }
	void FrameBuf::DetachTexture(UInt32 unIdx) { m_Attachments.erase(m_Attachments.begin() + unIdx); }
	// --==<core_methods>==--
	void FrameBuf::Bind() {
	}
	void FrameBuf::Remake()
	{
	}
	void FrameBuf::Clear(UInt32 bitMask) {
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