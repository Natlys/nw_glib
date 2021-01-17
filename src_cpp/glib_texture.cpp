#include <glib_pch.hpp>
#include "glib_texture.h"

#if (defined GLIB_GAPI)
#include <glib_engine.h>

GLIB::UByte GLIB::ATexture::s_ClearColorData[4] = { 255, 255, 255, 255 };

namespace GLIB
{
	ATexture::ATexture(const char* strName) :
		m_strName(strName), m_unRId(0), m_unTexSlot(0),
		m_TexInfo(TextureInfo()), m_ImgInfo(ImageInfo()) { }
	ATexture::~ATexture() { }

	// --==<ATexture1d>==--
	ATexture1d::ATexture1d(const char* strName) :
	ATexture(strName) { }
	ATexture1d::~ATexture1d() { }
	// --==</ATexture1d>==--

	// --==<ATexture2d>==--
	ATexture2d::ATexture2d(const char* strName) :
		ATexture(strName) { }
	ATexture2d::~ATexture2d() { }

	void ATexture2d::SetSubTexs(const DArray<SubTexture2d>& rSubTexs) {
		m_SubTexs = rSubTexs;
		for (auto& rSub : m_SubTexs) { rSub.pOverTex = this; rSub.whOverTexSize = { m_ImgInfo.nWidth, m_ImgInfo.nHeight }; }
	}
	// --==</ATexture2d>==--

	// --==<ATexture3d>==--
	ATexture3d::ATexture3d(const char* strName) :
		ATexture(strName) { }
	ATexture3d::~ATexture3d() { }
	// --==</ATexture3d>==--

	ATexture1d* ATexture1d::Create(const char* strName) {
		ATexture1d* pTex = nullptr;
		switch (GEngine::Get().GetGApi()->GetType()) {
	#if (GLIB_GAPI & GLIB_GAPI_OGL)
		case GAPI_OPENGL: pTex = new Texture1dOgl(strName); break;
	#endif	// GLIB_GAPI
		default: break;
		}
		return pTex;
	}
	ATexture2d* ATexture2d::Create(const char* strName) {
		ATexture2d* pTex = nullptr;
		switch (GEngine::Get().GetGApi()->GetType()) {
	#if (GLIB_GAPI & GLIB_GAPI_OGL)
		case GAPI_OPENGL: pTex = new Texture2dOgl(strName); break;
	#endif	// GLIB_GAPI
		default: break;
		}
		return pTex;
	}
	ATexture3d* ATexture3d::Create(const char* strName) {
		ATexture3d* pTex = nullptr;
		switch (GEngine::Get().GetGApi()->GetType()) {
	#if (GLIB_GAPI & GLIB_GAPI_OGL)
		case GAPI_OPENGL: pTex = new Texture3dOgl(strName); break;
	#endif	// GLIB_GAPI
		default: break;
		}
		return pTex;
	}
}
#endif	// GLIB_GAPI
#if (GLIB_GAPI & GLIB_GAPI_OGL)
#include <glad/glad.h>
namespace GLIB
{
	// Texture1d
	Texture1dOgl::Texture1dOgl(const char* strName) :
		ATexture1d(strName)
	{ }
	Texture1dOgl::~Texture1dOgl()
	{ }

	// --setters
	void Texture1dOgl::SetInfo(const TextureInfo& rTexInfo) {
		m_TexInfo = rTexInfo;
	}
	void Texture1dOgl::SetInfo(const ImageInfo& rImgInfo) {
		if (rImgInfo.nWidth < 1 || rImgInfo.nHeight < 1 || rImgInfo.nChannels < 1) { return; }
		if (m_ImgInfo.ClrData != &s_ClearColorData[0] && m_ImgInfo.ClrData != rImgInfo.ClrData && m_ImgInfo.ClrData != nullptr) {
			delete[] m_ImgInfo.ClrData;
			m_ImgInfo.ClrData = nullptr;
		}

		m_ImgInfo = rImgInfo;
	}

	// --==<Interface Methods>==--
	void Texture1dOgl::Bind(UInt32 unTexSlot)
	{
		m_unTexSlot = unTexSlot;
		glActiveTexture(GL_TEXTURE0 + m_unTexSlot);
		glBindTexture(GL_TEXTURE_1D, m_unRId);
	}
	void Texture1dOgl::Unbind()
	{
		glActiveTexture(GL_TEXTURE0 + m_unTexSlot);
		glBindTexture(GL_TEXTURE_1D, 0);
		m_unTexSlot = 0;
	}
	void Texture1dOgl::Remake()
	{
		if (m_unRId != 0) { glDeleteTextures(1, &m_unRId); m_unRId = 0; }
		glCreateTextures(GL_TEXTURE_1D, 1, &m_unRId);

		switch (m_ImgInfo.nChannels) {
		case 1: m_TexInfo.InterFormat = m_TexInfo.Format = TC_FORMAT_RED; break;
		case 2: GLIB_ERR("Unknown format!"); break;
		case 3: m_TexInfo.InterFormat = m_TexInfo.Format = TC_FORMAT_RGB; break;
		case 4: m_TexInfo.InterFormat = m_TexInfo.Format = TC_FORMAT_RGBA; break;
		default: return;
		}
		Bind(m_unTexSlot);
		glTextureParameteri(m_unRId, GL_TEXTURE_MIN_FILTER, m_TexInfo.FilterMin);
		glTextureParameteri(m_unRId, GL_TEXTURE_MAG_FILTER, m_TexInfo.FilterMag);
		glTextureParameteri(m_unRId, GL_TEXTURE_WRAP_S, m_TexInfo.WrapTypeS);

		glTexImage1D(GL_TEXTURE_1D, 0, m_TexInfo.InterFormat,
			m_ImgInfo.nWidth, 0,
			m_TexInfo.Format, GL_UNSIGNED_BYTE, &m_ImgInfo.ClrData[0]);
		glTexSubImage1D(GL_TEXTURE_1D, 0,
			0, m_ImgInfo.nWidth,
			m_TexInfo.Format, GL_UNSIGNED_BYTE, &m_ImgInfo.ClrData[0]);

		glGenerateMipmap(GL_TEXTURE_1D);
		Unbind();
	}
	// --==</core_methods>==--
	// Texture2d
	Texture2dOgl::Texture2dOgl(const char* strName) :
		ATexture2d(strName)
	{ }
	Texture2dOgl::~Texture2dOgl()
	{ }

	// --setters
	void Texture2dOgl::SetInfo(const TextureInfo& rTexInfo) {
		m_TexInfo = rTexInfo;
	}
	void Texture2dOgl::SetInfo(const ImageInfo& rImgInfo) {
		if (rImgInfo.nWidth < 1 || rImgInfo.nHeight < 1 || rImgInfo.nChannels < 1) { return; }
		if (m_ImgInfo.ClrData != &s_ClearColorData[0] && m_ImgInfo.ClrData != rImgInfo.ClrData && m_ImgInfo.ClrData != nullptr) {
			delete [] m_ImgInfo.ClrData;
			m_ImgInfo.ClrData = nullptr;
		}
		m_ImgInfo = rImgInfo;
		SetSubTexs(GetSubTexs());
	}

	// --==<Interface Methods>==--
	void Texture2dOgl::Bind(UInt32 unTexSlot)
	{
		m_unTexSlot = unTexSlot;
		glActiveTexture(GL_TEXTURE0 + m_unTexSlot);
		glBindTexture(GL_TEXTURE_2D, m_unRId);
	}
	void Texture2dOgl::Unbind()
	{
		glActiveTexture(GL_TEXTURE0 + m_unTexSlot);
		glBindTexture(GL_TEXTURE_2D, 0);
		m_unTexSlot = 0;
	}
	void Texture2dOgl::Remake()
	{
		if (m_unRId != 0) { glDeleteTextures(1, &m_unRId); m_unRId = 0; }
		glCreateTextures(GL_TEXTURE_2D, 1, &m_unRId);

		Bind(m_unTexSlot);
		glTextureParameteri(m_unRId, GL_TEXTURE_MIN_FILTER, m_TexInfo.FilterMin);
		glTextureParameteri(m_unRId, GL_TEXTURE_MAG_FILTER, m_TexInfo.FilterMag);
		glTextureParameteri(m_unRId, GL_TEXTURE_WRAP_S, m_TexInfo.WrapTypeS);
		glTextureParameteri(m_unRId, GL_TEXTURE_WRAP_T, m_TexInfo.WrapTypeT);

		glTexImage2D(GL_TEXTURE_2D, 0, m_TexInfo.InterFormat,
			m_ImgInfo.nWidth, m_ImgInfo.nHeight, 0,
			m_TexInfo.Format, GL_UNSIGNED_BYTE, &m_ImgInfo.ClrData[0]);
		glTexSubImage2D(GL_TEXTURE_2D, 0,
			0, 0, m_ImgInfo.nWidth, m_ImgInfo.nHeight,
			m_TexInfo.Format, GL_UNSIGNED_BYTE, &m_ImgInfo.ClrData[0]);
	
		glGenerateMipmap(GL_TEXTURE_2D);
		Unbind();
	}
	// --==</core_methods>==--
	
	// Texture3d
	Texture3dOgl::Texture3dOgl(const char* strName) :
		ATexture3d(strName)
	{ }
	Texture3dOgl::~Texture3dOgl() { }

	// --setters
	void Texture3dOgl::SetInfo(const TextureInfo& rTexInfo) {
		m_TexInfo = rTexInfo;
	}
	void Texture3dOgl::SetInfo(const ImageInfo& rImgInfo) {
		if (rImgInfo.nWidth < 1 || rImgInfo.nHeight < 1 || rImgInfo.nChannels < 1) { return; }
		if (m_ImgInfo.ClrData != &s_ClearColorData[0] && m_ImgInfo.ClrData != rImgInfo.ClrData && m_ImgInfo.ClrData != nullptr) {
			delete [] m_ImgInfo.ClrData;
		}
		m_ImgInfo = rImgInfo;
	}

	// --==<Interface Methods>==--
	void Texture3dOgl::Bind(UInt32 unTexSlot)
	{
		m_unTexSlot = unTexSlot;
		glActiveTexture(GL_TEXTURE0 + m_unTexSlot);
		glBindTexture(GL_TEXTURE_3D, m_unRId);
	}
	void Texture3dOgl::Unbind()
	{
		glActiveTexture(GL_TEXTURE0 + m_unTexSlot);
		glBindTexture(GL_TEXTURE_3D, 0);
		m_unTexSlot = 0;
	}
	void Texture3dOgl::Remake()
	{
		if (m_unRId != 0) { glDeleteTextures(1, &m_unRId); m_unRId = 0; }
		glCreateTextures(GL_TEXTURE_3D, 1, &m_unRId);

		switch (m_ImgInfo.nChannels) {
		case 1: m_TexInfo.InterFormat = m_TexInfo.Format = TC_FORMAT_RED;
			break;
		case 3: m_TexInfo.InterFormat = m_TexInfo.Format = TC_FORMAT_RGB;
			break;
		case 4: m_TexInfo.InterFormat = m_TexInfo.Format = TC_FORMAT_RGBA;
			break;
		default: return;
		}
		Bind(m_unTexSlot);
		glTextureParameteri(m_unRId, GL_TEXTURE_MIN_FILTER, m_TexInfo.FilterMin);
		glTextureParameteri(m_unRId, GL_TEXTURE_MAG_FILTER, m_TexInfo.FilterMag);
		glTextureParameteri(m_unRId, GL_TEXTURE_WRAP_S, m_TexInfo.WrapTypeS);
		glTextureParameteri(m_unRId, GL_TEXTURE_WRAP_T, m_TexInfo.WrapTypeT);
		glTextureParameteri(m_unRId, GL_TEXTURE_WRAP_R, m_TexInfo.WrapTypeR);

		glTexImage3D(GL_TEXTURE_3D, 0, m_TexInfo.InterFormat,
			m_ImgInfo.nWidth, m_ImgInfo.nHeight, m_ImgInfo.nDepth, 0,
			m_TexInfo.Format, GL_UNSIGNED_BYTE, &m_ImgInfo.ClrData[0]);
		glTexSubImage3D(GL_TEXTURE_3D, 0,
			0, 0, 0, m_ImgInfo.nWidth, m_ImgInfo.nHeight, m_ImgInfo.nDepth,
			m_TexInfo.Format, GL_UNSIGNED_BYTE, &m_ImgInfo.ClrData[0]);

		glGenerateMipmap(GL_TEXTURE_3D);
		Unbind();
	}
	// --==</core_methods>==--
}
#endif // GLIB_GAPI