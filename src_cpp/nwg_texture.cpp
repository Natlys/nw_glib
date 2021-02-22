#include <nwg_pch.hpp>
#include "nwg_texture.h"
#if (defined NWG_GAPI)
#include <nwg_engine.h>
#include <nwg_loader.h>
#if (NWG_GAPI & NWG_GAPI_OGL)
namespace NWG
{
	Texture::Texture(GfxEngine& rGfx, const char* strName, TextureTypes texType) :
		TEntity(), AGfxRes(rGfx), ADataRes(strName),
		m_texType(texType), m_unSlot(0),
		m_img(Image()) { }
	Texture::~Texture() { if (m_unRId != 0) { glDeleteTextures(1, &m_unRId); m_unRId = 0; } }
	// --setters
	void Texture::SetSlot(UInt8 unSlot) { m_unSlot = unSlot; }
	void Texture::SetImage(const Image& rImage) { m_img = rImage; }
	// --==<core_methods>==--
	void Texture::Bind() {
		glActiveTexture(GL_TEXTURE0 + m_unSlot);
		glBindTexture(m_texType, m_unRId);
	}
	void Texture::Remake()
	{
		if (m_unRId != 0) { glDeleteTextures(1, &m_unRId); m_unRId = 0; }
		
		glCreateTextures(m_texType, 1, &m_unRId);
		glBindTexture(m_texType, m_unRId);
		switch (m_texType) {
		case TXT_1D:
			glTextureParameteri(m_unRId, GL_TEXTURE_MIN_FILTER, ConvertEnum<TextureFilters, UInt32>(m_Filter));
			glTextureParameteri(m_unRId, GL_TEXTURE_MAG_FILTER, ConvertEnum<TextureFilters, UInt32>(m_Filter));
			glTextureParameteri(m_unRId, GL_TEXTURE_WRAP_S, ConvertEnum<TextureWraps, UInt32>(m_WrapS));
			glTexImage1D(GL_TEXTURE_1D, 0, ConvertEnum<PixelFormats, UInt32>(m_img.GetFormat()),
				m_img.GetSizeW(), 0,
				ConvertEnum<PixelFormats, UInt32>(m_img.GetFormat()), ConvertEnum<PixelFormats, UInt32>(m_img.GetFormat()), &m_img.GetData()[0]);
				glTexSubImage1D(GL_TEXTURE_1D, 0,
					0, m_img.GetSizeW(),
					ConvertEnum<PixelFormats, UInt32>(m_img.GetFormat()), ConvertEnum<PixelFormats, UInt32>(m_img.GetFormat()), &m_img.GetData()[0]);
			glGenerateMipmap(GL_TEXTURE_1D);
			break;
		case TXT_2D:
			glTextureParameteri(m_unRId, GL_TEXTURE_MIN_FILTER, ConvertEnum<TextureFilters, UInt32>(m_Filter));
			glTextureParameteri(m_unRId, GL_TEXTURE_MAG_FILTER, ConvertEnum<TextureFilters, UInt32>(m_Filter));
			glTextureParameteri(m_unRId, GL_TEXTURE_WRAP_S, ConvertEnum<TextureWraps, UInt32>(m_WrapS));
			glTextureParameteri(m_unRId, GL_TEXTURE_WRAP_T, ConvertEnum<TextureWraps, UInt32>(m_WrapT));
			glTexImage2D(GL_TEXTURE_2D, 0, ConvertEnum<PixelFormats, UInt32>(m_img.GetFormat()),
				m_img.GetSizeW(), m_img.GetSizeH(), 0,
				ConvertEnum<PixelFormats, UInt32>(m_img.GetFormat()), ConvertEnum<PixelFormats, UInt32>(m_img.GetFormat()), &m_img.GetData()[0]);
				glTexSubImage2D(GL_TEXTURE_2D, 0,
					0, 0, m_img.GetSizeW(), m_img.GetSizeH(),
					ConvertEnum<PixelFormats, UInt32>(m_img.GetFormat()), ConvertEnum<PixelFormats, UInt32>(m_img.GetFormat()), &m_img.GetData()[0]);
			glGenerateMipmap(GL_TEXTURE_2D);
			break;
		case TXT_3D:
			glTextureParameteri(m_unRId, GL_TEXTURE_MIN_FILTER, ConvertEnum<TextureFilters, UInt32>(m_Filter));
			glTextureParameteri(m_unRId, GL_TEXTURE_MAG_FILTER, ConvertEnum<TextureFilters, UInt32>(m_Filter));
			glTextureParameteri(m_unRId, GL_TEXTURE_WRAP_S, ConvertEnum<TextureWraps, UInt32>(m_WrapS));
			glTextureParameteri(m_unRId, GL_TEXTURE_WRAP_T, ConvertEnum<TextureWraps, UInt32>(m_WrapT));
			glTextureParameteri(m_unRId, GL_TEXTURE_WRAP_R, ConvertEnum<TextureWraps, UInt32>(m_WrapR));
			glTexImage3D(GL_TEXTURE_3D, 0, ConvertEnum<PixelFormats, UInt32>(m_img.GetFormat()),
				m_img.GetSizeW(), m_img.GetSizeH(), 1, 0,
				ConvertEnum<PixelFormats, UInt32>(m_img.GetFormat()), ConvertEnum<PixelFormats, UInt32>(m_img.GetFormat()), &m_img.GetData()[0]);
				glTexSubImage3D(GL_TEXTURE_3D, 0,
					0, 0, 0, m_img.GetSizeW(), m_img.GetSizeH(), 1,
					ConvertEnum<PixelFormats, UInt32>(m_img.GetFormat()), ConvertEnum<PixelFormats, UInt32>(m_img.GetFormat()), &m_img.GetData()[0]);
			glGenerateMipmap(GL_TEXTURE_3D);
		case TXT_2D_MULTISAMPLE:	// internal format required
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_img.GetSamples(), ConvertEnum<PixelFormats, UInt32>(m_img.GetFormat()),
				m_img.GetSizeW(), m_img.GetSizeH(), false);
			break;
		case TXT_3D_MULTISAMPLE:
			glTexImage3DMultisample(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, m_img.GetSamples(), ConvertEnum<PixelFormats, UInt32>(m_img.GetFormat()),
				m_img.GetSizeW(), m_img.GetSizeH(), 1, false);
			break;
		default: throw Exception("unspecified texture"); break;
		}
	}
	void Texture::Clear(Ptr pValue) { // internal and default formats required
		glClearTexImage(m_unRId, 0, ConvertEnum<PixelFormats, UInt32>(m_img.GetFormat()), ConvertEnum<PixelFormats, UInt32>(m_img.GetFormat()), pValue);
	}
	// --==</core_methods>==--
		// --==<data_methods>==--
	bool Texture::SaveF(const char* strFPath) { return true; }
	bool Texture::LoadF(const char* strFPath)
	{
		String strFile("");
		ImageInfo imgInfo;
		UByte s_texErr[] = {
			0u,	255u,	0u,		255u,
			0u,	0u,		255u,	255u,
			0u,	0u,		255u,	255u,
			0u,	255u,	0u,		255u
		};

		if (!DataSys::LoadFImage(strFPath, m_img)) {
			if (!DataSys::LoadFString(strFPath, strFile)) {
				imgInfo.nWidth = imgInfo.nHeight = 2;
				imgInfo.nChannels = 4;
				imgInfo.pxlFormat = PXF_R8G8B8A8_UINT32;
				m_Filter = TXF_NEAREST;
				m_WrapS = m_WrapT = m_WrapR = TXW_REPEAT;
				m_img.SetData(&s_texErr[0], imgInfo);
				return false;
			}
			else {
				StrStream stmFile(strFile);
				stmFile >> imgInfo;
				UByte* pData = MemSys::NewTArr<UByte>(imgInfo.GetSize());
				m_img.SetData(pData, imgInfo);
				Remake();
			}
		}
		else { Remake(); }
		return true;
	}
	// --==</data_methods>==--
}
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
namespace NWG
{
	Texture::Texture(GfxEngine& rGfx, const char* strName, TextureTypes texType) :
		TEntity(), AGfxRes(rGfx), ADataRes(strName),
		m_texType(texType), m_unSlot(0),
		m_imgInfo(ImageInfo()),
		m_pNative(nullptr), m_pSampler(nullptr)
	{
		m_WrapS = TXW_CLAMP;
		m_WrapT = TXW_CLAMP;
		m_WrapR = TXW_CLAMP;
		m_Filter = TXF_NEAREST;
	}
	Texture::~Texture() { m_img.GetSizeW() = -1; Remake(); }
	// --setters
	void Texture::SetSlot(UInt8 unSlot) { m_unSlot = unSlot; }
	void Texture::SetInfo(const ImageInfo& rImgInfo) {
		if ((m_texType == TXT_1D || m_texType == TXT_2D || m_texType == TXT_3D) && (m_img.GetSizeW() < 1)) { return; }
		else if ((m_texType == TXT_2D || m_texType == TXT_3D) && (m_img.GetSizeW() < 1 || m_img.GetSizeH() < 1)) { return; }
		else if ((m_texType == TXT_3D) && (m_img.GetSizeW() < 1 || m_img.GetSizeH() < 1 || m_imgInfo.nDepth < 1)) { return; }
		m_imgInfo = rImgInfo;
	}
	// --==<core_methods>==--
	void Texture::Bind() {
		m_pGfx->GetContext()->PSSetShaderResources(m_unSlot, 1u, &m_pNative);
		m_pGfx->GetContext()->PSSetSamplers(m_unSlot, 1u, &m_pSampler);
	}
	void Texture::Remake()
	{
		if (m_pNative != nullptr) { m_pNative->Release(); m_pNative = nullptr; }
		if (m_pSampler != nullptr) { m_pSampler->Release(); m_pSampler = nullptr; }
		if (m_img.GetSizeW() <= 0 || m_img.GetSizeH() <= 0 || m_imgInfo.nDepth <= 0 || m_imgInfo.nChannels <= 0) { return; }
		if (m_WrapS == TXW_DEFAULT || m_WrapT == TXW_DEFAULT || m_WrapR == TXW_DEFAULT) { return; }
		if (m_Filter == TXF_DEFAULT) { return; }
		// create texture itself
		switch (m_texType) {
		case TXT_1D: {
			break;
		}
		case TXT_2D: {
			D3D11_TEXTURE2D_DESC texDesc{ 0 };
			texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			texDesc.CPUAccessFlags = m_imgInfo.pData == nullptr ? D3D11_CPU_ACCESS_WRITE : 0u;
			texDesc.Format = ConvertEnum<PixelFormats, DXGI_FORMAT>(m_img.GetFormat());
			texDesc.MiscFlags = 0u;
			texDesc.Width = m_img.GetSizeW();
			texDesc.Height = m_img.GetSizeH();
			texDesc.MipLevels = 1;
			texDesc.ArraySize = 1;
			texDesc.SampleDesc.Count = 1;
			texDesc.SampleDesc.Quality = 0;

			D3D11_SUBRESOURCE_DATA subData{ 0 };
			subData.pSysMem = m_imgInfo.pData == nullptr ? m_imgInfo.pData : MemSys::GetMemory().GetDataBeg();
			subData.SysMemPitch = m_img.GetSizeW() * m_imgInfo.nChannels;	// adjacent bytes between rows
			subData.SysMemSlicePitch = m_img.GetSizeH() * m_imgInfo.nChannels;	// adjacent bytes between rows

			ID3D11Texture2D* pTexture = nullptr;
			m_pGfx->GetDevice()->CreateTexture2D(&texDesc, &subData, &pTexture);
			if (pTexture == nullptr) { throw Exception("failed to create a texture"); }

			// create resource view to display the texture
			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{ };
			srvDesc.Format = ConvertEnum<PixelFormats, DXGI_FORMAT>(m_img.GetFormat());
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MostDetailedMip = 0;
			srvDesc.Texture2D.MipLevels = 1;
			
			m_pGfx->GetDevice()->CreateShaderResourceView(pTexture, &srvDesc, &m_pNative);
			pTexture->Release();
			if (m_pNative == nullptr) { throw Exception("unsupported texture type"); }
			break;
		}
		case TXT_3D: {
			break;
		}
		default: throw Exception("unsupported texture type"); break;
		}
		// create sampler for right texture representation
		D3D11_SAMPLER_DESC smpDesc{ };
		smpDesc.AddressU = ConvertEnum<TextureWraps, D3D11_TEXTURE_ADDRESS_MODE>(m_WrapS);
		smpDesc.AddressV = ConvertEnum<TextureWraps, D3D11_TEXTURE_ADDRESS_MODE>(m_WrapT);
		smpDesc.AddressW = ConvertEnum<TextureWraps, D3D11_TEXTURE_ADDRESS_MODE>(m_WrapR);
		smpDesc.Filter = ConvertEnum<TextureFilters, D3D11_FILTER>(m_Filter);
		smpDesc.BorderColor;	// for the "border" wrapper
		smpDesc.ComparisonFunc;	//
		smpDesc.MaxAnisotropy;	// for the filter "anostropy"
		smpDesc.MinLOD;			// minimal level of details
		smpDesc.MaxLOD;			// maximal level of details
		smpDesc.MipLODBias;		// level of details for mipmapping
		m_pGfx->GetDevice()->CreateSamplerState(&smpDesc, &m_pSampler);
		if (m_pNative == nullptr) { throw Exception("sampler was not created"); }
	}
	void Texture::Clear(Ptr pValue) { }
	// --==</core_methods>==--
	// --==<data_methods>==--
	bool Texture::SaveF(const char* strFPath) { return true; }
	bool Texture::LoadF(const char* strFPath) {
		ImageInfo imgInfo;
		String strFile("");
		if (!DataSys::LoadFImage(strFPath, imgInfo)) {
			if (!DataSys::LoadFString(strFPath, strFile)) { return false; }
			StrStream stmFile(strFile);
			while (std::getline(stmFile, strFile, ':')) {
				if (strFile == "gapi") {
					std::getline(stmFile, strFile, ';');
					if (strFile == "directx") {}
					else { return false; }
				}
				else if (strFile == "name") {
					std::getline(stmFile, strFile, ';');
					SetName(&strFile[0]);
				}
				else if (strFile == "size") {
					std::getline(stmFile, strFile, ';');
				}
				else if (strFile == "channels") {
					std::getline(stmFile, strFile, ';');
				}
				else if (strFile == "pixel_format") {
					std::getline(stmFile, strFile, ';');
				}
				else if (strFile == "tex_wrap_repeat") {
					std::getline(stmFile, strFile, ';');
				}
				else if (strFile == "border_color") {
					std::getline(stmFile, strFile, ';');
				}
				else if (strFile == "tex_wrap") {
					std::getline(stmFile, strFile, ';');
				}
				else if (strFile == "tex_filter") {
					std::getline(stmFile, strFile, ';');
				}
				else if (strFile == "img_file") {
					std::getline(stmFile, strFile, ';');
					if (!DataSys::LoadFImage(&strFile[0], imgInfo)) { return false; }
				}
				else {}
				stmFile.get();
			}
		}

		if (imgInfo.nChannels == 1) { imgInfo.pxFormat = PXF_R32_UINT32; }
		else if (imgInfo.nChannels == 2) { imgInfo.pxFormat = PXF_R8G8_UINT16; }
		else if (imgInfo.nChannels == 3) { imgInfo.pxFormat = PXF_R8G8B8_UINT32; }
		else if (imgInfo.nChannels == 4) { imgInfo.pxFormat = PXF_R8G8B8A8_UINT32; }
		else { return false; }
		SetInfo(imgInfo);
		Remake();
		if (MemSys::GetMemory().HasBlock(imgInfo.pData)) { MemSys::Dealloc(imgInfo.pData, imgInfo.GetDataSize()); }
		else { delete[] imgInfo.pData; }

		return true;
	}
	// --==</data_methods>==--
}
#endif
#endif	// NWG_GAPI