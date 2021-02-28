#ifndef NWG_TEXTURE_H
#define NWG_TEXTURE_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <res/nwg_res.h>
#include <core/nwg_tools.h>
namespace NWG
{
	struct NWG_API TextureInfo : public ImageInfo
	{
	public:
		GfxApiTypes gapiType = GAPI_DEFAULT;
		String strName = "default";
		UInt8 nSamples = 1;
		TextureTypes texType = TXT_2D;
		TextureFormats texFormat = TXF_RGBA;
		TextureWraps WrapS = TXW_BORDER;
		TextureWraps WrapT = TXW_BORDER;
		TextureWraps WrapR = TXW_BORDER;
		TextureFilters Filter = TXFL_NEAREST;
		V4f rgbaBorder = { 1.0f, 1.0f, 1.0f, 1.0f };
	public:
		// --operators
		TextureInfo& operator=(const ImageBmpInfo& rInfo);
		TextureInfo& operator=(const ImagePngInfo& rInfo);
		TextureInfo& operator=(const ImageInfo& rInfo);
		virtual OutStream& operator<<(OutStream& rStream) const override;
		virtual InStream& operator>>(InStream& rStream) override;
	};
}
namespace NWG
{
	/// Texture class
	/// Description:
	class NWG_API Texture : public AGfxRes, public ADataRes
	{
	public:
		Texture(GfxEngine& rGfx, const char* strName, TextureTypes texTypes);
		virtual ~Texture();
		// --getters
		inline UInt8 GetTexSlot() const { return m_unSlot; }
		inline TextureTypes GetTexType() const { return m_Info.texType; }
		inline const TextureInfo& GetInfo() const { return m_Info; }
		// --setters
		void SetSlot(UInt8 unSlot);
		// --core_methods
		virtual void OnDraw() = 0;
		virtual bool Remake(const TextureInfo& rInfo) = 0;
		virtual void Clear(Ptr pValue) = 0;
		// --data_methods
		virtual bool SaveF(const char* strFPath) = 0;
		virtual bool LoadF(const char* strFPath) = 0;
	protected:
		TextureInfo m_Info;
		UInt8 m_unSlot;
#if (NWG_GAPI & NWG_GAPI_DX)
		ID3D11ShaderResourceView* m_pRes;
		ID3D11SamplerState* m_pSampler;
#endif
	};
}
namespace NWG
{
	class NWG_API Texture2d : public Texture
	{
	public:
		Texture2d(GfxEngine& rGfx, const char* strName);
		~Texture2d();
		// --core_methods
		virtual void OnDraw() override;
		virtual bool Remake(const TextureInfo& rInfo) override;
		virtual void Clear(Ptr pValue) override;
		// --data_methods
		virtual bool SaveF(const char* strFPath) override;
		virtual bool LoadF(const char* strFPath) override;
	private:
#if (NWG_GAPI & NWG_GAPI_DX)
		ID3D11Texture2D* m_pNative;
#endif
	};
}
#endif	// NWG_GAPI
#endif // GFX_TEXTURE_H