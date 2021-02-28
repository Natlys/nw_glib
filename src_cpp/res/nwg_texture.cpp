#include <nwg_pch.hpp>
#include "nwg_texture.h"
#if (defined NWG_GAPI)
#include <core/nwg_engine.h>
namespace NWG
{
	// --operators
	TextureInfo& TextureInfo::operator=(const ImageBmpInfo& rInfo) {
		ImageInfo::operator=(rInfo);
		return *this;
	}
	TextureInfo& TextureInfo::operator=(const ImagePngInfo& rInfo) {
		ImageInfo::operator=(rInfo);
		return *this;
	}
	TextureInfo& TextureInfo::operator=(const ImageInfo& rInfo) {
		ImageInfo::operator=(rInfo);
		return *this;
	}
	OutStream& TextureInfo::operator<<(OutStream& rStream) const { return rStream; }
	InStream& TextureInfo::operator>>(InStream& rStream) { return ImageInfo::operator>>(rStream); }
}
#if (NWG_GAPI & NWG_GAPI_OGL)
#include <lib/nwg_ogl_v1.h>
#include <lib/nwg_ogl_v4.h>
#include <lib/nwg_ogl_arb.h>
namespace NWG
{
	Texture::Texture(GfxEngine& rGfx, const char* strName, TextureTypes texType) :
		AGfxRes(rGfx), ADataRes(strName),
		m_Info(TextureInfo()), m_unSlot(0) { }
	Texture::~Texture() { if (m_unRId != 0) { glDeleteTextures(1, &m_unRId); m_unRId = 0; } }
	// --setters
	void Texture::SetSlot(UInt8 unSlot) { m_unSlot = unSlot; }
}
namespace NWG
{
	Texture2d::Texture2d(GfxEngine& rGfx, const char* strName) :
		Texture(rGfx, strName, TXT_2D) { }
	Texture2d::~Texture2d() { }
	// --==<core_methods>==--
	void Texture2d::OnDraw() { glActiveTexture(GL_TEXTURE0 + m_unSlot); glBindTexture(GL_TEXTURE_2D, m_unRId); }
	bool Texture2d::Remake(const TextureInfo& rInfo)
	{
		if (m_unRId != 0) { glDeleteTextures(1, &m_unRId); m_unRId = 0; }
		if (m_Info.nSamples == 0) { return false; }
		if (m_Info.nWidth <= 0 || m_Info.nHeight <= 0 || m_Info.nChannels <= 0) { return false; }
		glGenTextures(1, &m_unRId);
		glBindTexture(GL_TEXTURE_2D, m_unRId);

		if (m_Info.nSamples == 1) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ConvertEnum<TextureFilters, UInt32>(m_Info.Filter));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ConvertEnum<TextureFilters, UInt32>(m_Info.Filter));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ConvertEnum<TextureWraps, UInt32>(m_Info.WrapS));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ConvertEnum<TextureWraps, UInt32>(m_Info.WrapT));
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &m_Info.rgbaBorder[0]);
			glTexImage2D(GL_TEXTURE_2D, 0, ConvertEnum<TextureFormats, UInt32>(m_Info.texFormat),
				m_Info.nWidth, m_Info.nHeight, 0,
				ConvertEnum<TextureFormats, UInt32>(m_Info.texFormat), GL_UNSIGNED_BYTE, &m_Info.pxlData[0]);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else if (m_Info.nSamples > 1) {
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_Info.nSamples,
				ConvertEnum<PixelFormats, UInt32>(m_Info.pxlFormat),
				m_Info.nWidth, m_Info.nHeight, false);
		}
		return true;
	}
	void Texture2d::Clear(Ptr pValue) {
		glClearTexImage(m_unRId, 0,
			ConvertEnum<PixelFormats, UInt32>(m_Info.pxlFormat),
			ConvertEnum<PixelFormats, UInt32>(m_Info.pxlFormat),
			pValue);
	}
	// --==</core_methods>==--
	// --==<data_methods>==--
	bool Texture2d::SaveF(const char* strFPath) { return true; }
	bool Texture2d::LoadF(const char* strFPath)
	{
		const char* strFormat = CStrGetPartL(&strFPath[0], '.');
		if (CStrIsEqual(strFormat, ".txr")) {
			if (!DataSys::LoadFile(strFPath, m_Info)) { return false; }
		}
		else if (CStrIsEqual(strFormat, ".bmp")) {
			ImageBmpInfo bmpInfo;
			if (!DataSys::LoadFile(strFPath, bmpInfo)) { return false; }
			m_Info = bmpInfo;
		}
		else if (CStrIsEqual(strFormat, ".png")) {
		}
		return Remake(m_Info);
	}
	// --==</data_methods>==--
}
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
#include <lib/nwg_dx_loader.h>
namespace NWG
{
	Texture::Texture(GfxEngine& rGfx, const char* strName, TextureTypes texType) :
		AGfxRes(rGfx), ADataRes(strName),
		m_Info(TextureInfo()), m_unSlot(0),
		m_pRes(nullptr), m_pSampler(nullptr) { }
	Texture::~Texture() {
		if (m_pRes != nullptr) { m_pRes->Release(); m_pRes = nullptr; }
		if (m_pSampler != nullptr) { m_pSampler->Release(); m_pSampler = nullptr; }
	}
	// --setters
	void Texture::SetSlot(UInt8 unSlot) { m_unSlot = unSlot; }
}
namespace NWG
{
	Texture2d::Texture2d(GfxEngine& rGfx, const char* strName) :
		Texture(rGfx, strName, TXT_2D) { }
	Texture2d::~Texture2d() { }
	// --==<core_methods>==--
	void Texture2d::Bind()
	{
		m_pGfx->GetContext()->PSSetShaderResources(0, 1, &m_pRes);
		m_pGfx->GetContext()->PSSetSamplers(0, 1, &m_pSampler);
	}
	bool Texture2d::Remake(const TextureInfo& rInfo)
	{
		if (m_pRes != nullptr) { m_pRes->Release(); m_pRes = nullptr; }
		if (m_pNative != nullptr) { m_pNative->Release(); m_pNative = nullptr; }
		if (m_pSampler != nullptr) { m_pSampler->Release(); m_pSampler = nullptr; }
		
		if (m_Info.nWidth <= 0 || m_Info.nHeight <= 0 || m_Info.nChannels <= 0) { return false; }
		if (m_Info.WrapS == TXW_DEFAULT || m_Info.WrapT == TXW_DEFAULT || m_Info.WrapR == TXW_DEFAULT) { return false; }
		if (m_Info.Filter == TXF_DEFAULT) { return false; }
		// create texture itself
		D3D11_TEXTURE2D_DESC texDesc{ 0 };
		texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		texDesc.CPUAccessFlags = m_Image.GetData() == nullptr ? D3D11_CPU_ACCESS_WRITE : 0u;
		texDesc.Format = ConvertEnum<PixelFormats, DXGI_FORMAT>(m_Info.pxlFormat);
		texDesc.MiscFlags = 0u;
		texDesc.Width = m_Info.nWidth;
		texDesc.Height = m_Info.nHeight;
		texDesc.MipLevels = 1;
		texDesc.ArraySize = 1;
		texDesc.SampleDesc.Count = 1;
		texDesc.SampleDesc.Quality = 0;

		D3D11_SUBRESOURCE_DATA subData{ 0 };
		subData.pSysMem = m_Image.GetData() == nullptr ? m_Image.GetData() : MemSys::GetMemory().GetDataBeg();
		subData.SysMemPitch = m_Info.nWidth * m_Info.nChannels;	// adjacent bytes between rows

		ID3D11Texture2D* pTexture = nullptr;
		m_pGfx->GetDevice()->CreateTexture2D(&texDesc, &subData, &pTexture);
		if (pTexture == nullptr) { throw Exception("failed to create a texture"); }

		// create resource view to display the texture
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{ };
		srvDesc.Format = ConvertEnum<PixelFormats, DXGI_FORMAT>(m_Info.pxlFormat);
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = 1;

		m_pGfx->GetDevice()->CreateShaderResourceView(pTexture, &srvDesc, &m_pRes);
		pTexture->Release();
		if (m_pNative == nullptr) { throw Exception("unsupported texture type"); return false; }
		
		// create sampler for right texture representation
		D3D11_SAMPLER_DESC smpDesc{ };
		smpDesc.AddressU = ConvertEnum<TextureWraps, D3D11_TEXTURE_ADDRESS_MODE>(m_Info.WrapS);
		smpDesc.AddressV = ConvertEnum<TextureWraps, D3D11_TEXTURE_ADDRESS_MODE>(m_Info.WrapT);
		smpDesc.AddressW = ConvertEnum<TextureWraps, D3D11_TEXTURE_ADDRESS_MODE>(m_Info.WrapR);
		smpDesc.Filter = ConvertEnum<TextureFilters, D3D11_FILTER>(m_Info.Filter);
		smpDesc.BorderColor;	// for the "border" wrapper
		smpDesc.ComparisonFunc;	//
		smpDesc.MaxAnisotropy;	// for the filter "anostropy"
		smpDesc.MinLOD;			// minimal level of details
		smpDesc.MaxLOD;			// maximal level of details
		smpDesc.MipLODBias;		// level of details for mipmapping
		m_pGfx->GetDevice()->CreateSamplerState(&smpDesc, &m_pSampler);
		if (m_pNative == nullptr) { throw Exception("sampler was not created"); return false; }
		
		return true;
	}
	void Texture2d::Clear(Ptr pValue) { }
	// --==</core_methods>==--
	// --==<data_methods>==--
	bool Texture2d::SaveF(const char* strFPath) { return true; }
	bool Texture2d::LoadF(const char* strFPath)
	{
		String strFile("");
		UByte s_texErr[] = {
			0u,	255u,	0u,		255u,
			0u,	0u,		255u,	255u,
			0u,	0u,		255u,	255u,
			0u,	255u,	0u,		255u
		};
		ImageInfo imgInfo(2, 2, 4);
		Image imgData = Image(imgInfo, &s_texErr[0]);

		if (!DataSys::LoadFImage(strFPath, imgData)) {
			if (!DataSys::LoadFString(strFPath, strFile)) {
				m_Info.Filter = TXF_NEAREST;
				m_Info.WrapS = m_Info.WrapT = m_Info.WrapR = TXW_REPEAT;
				return false;
			}
			else {
				StrStream stmFile(strFile);
				stmFile >> m_Info;
				imgInfo.nWidth = m_Info.nWidth;
				imgInfo.nHeight = m_Info.nHeight;
				imgInfo.nChannels = m_Info.nChannels;
				imgInfo.pxlFormat = m_Info.pxlFormat;
				UByte* pData = MemSys::NewTArr<UByte>(imgInfo.GetSize());
				imgData.SetData(pData, imgInfo);
			}
		}
		return Remake(m_Info);
	}
	// --==</data_methods>==--
}
#endif
#endif	// NWG_GAPI