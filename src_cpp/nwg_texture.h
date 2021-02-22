#ifndef NWG_TEXTURE_H
#define NWG_TEXTURE_H
#include <nwg_core.hpp>
#include <nwg_res.h>
#if (defined NWG_GAPI)
#include <nwg_tools.h>
namespace NWG
{
	struct NWG_API TextureInfo
	{
	public:
	public:
		TextureInfo();
		// --operators
		OutStream& operator<<(OutStream& rStream) const;
		InStream& operator>>(InStream& rStream);
	};
	OutStream& operator<<(OutStream& rStream, const TextureInfo& rInfo);
	InStream& operator>>(InStream& rStream, TextureInfo& rInfo);
}
namespace NWG
{
	/// Texture class
	/// Description:
	class NWG_API Texture : public TEntity<Texture>, public AGfxRes, public ADataRes
	{
	public:
		TextureWraps m_WrapS, m_WrapT, m_WrapR;
		TextureFilters m_Filter;
		V4f m_rgbaBorder;
	public:
		Texture(GfxEngine& rGfx, const char* strName, TextureTypes texTypes);
		virtual ~Texture();
		// --getters
		inline UInt8 GetTexSlot() const { return m_unSlot; }
		inline TextureTypes GetTexType() const { return m_texType; }
		inline const Image& GetImage() const { return m_img; }
		// --setters
		void SetSlot(UInt8 unSlot);
		void SetImage(const Image& rImage);
		// --core_methods
		virtual void Bind() override;
		virtual bool Remake(const TextureInfo& rInfo) = 0;
		virtual void Clear(Ptr pValue) = 0;
		// --data_methods
		virtual bool SaveF(const char* strFPath) = 0;
		virtual bool LoadF(const char* strFPath) = 0;
	protected:
		TextureTypes m_texType;
		UInt8 m_unSlot;
		Image m_img;
#if (NWG_GAPI & NWG_GAPI_DX)
		ID3D11ShaderResourceView* m_pNative;
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
		virtual void Bind() override;
		virtual bool Remake(const TextureInfo& rInfo) override;
		virtual void Clear(Ptr pValue) override;
		// --data_methods
		virtual bool SaveF(const char* strFPath) override;
		virtual bool LoadF(const char* strFPath) override;
	private:
#if (NWG_GAPI & NWG_GAPI_DX)
#endif
	};
}
#endif	// NWG_GAPI
#endif // GFX_TEXTURE_H