#ifndef NWG_BUF_H
#define NWG_BUF_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <res/nwg_res.h>
namespace NWG
{
	struct NWG_API GfxBufInfo : public AInfo
	{
	public:
		Size szData = 0;
		UInt32 szStride = 0;
		UInt32 szOffset = 0;
		Ptr pData = nullptr;
		DataTypes sdType = DT_DEFAULT;
	public:
		GfxBufInfo() = default;
		GfxBufInfo(Size sizeOfData, Size sizeOfStride, Size sizeOfOffset,
			Ptr ptrToData, DataTypes dataType);
		GfxBufInfo(Size sizeOfData, Size sizeOfStride, Size sizeOfOffset, Ptr ptrToData);
		// --operators
		virtual OutStream& operator<<(OutStream& rStream) const override;
		virtual InStream& operator>>(InStream& rStream) override;
	};
}
namespace NWG
{
	class NWG_API AGfxBuf : public AGfxRes
	{
	public:
		AGfxBuf(GfxEngine& rGfx);
		virtual ~AGfxBuf();
		// --getters
		inline Size GetDataSize() const			{ return m_Info.szData; }
		inline Size GetDataStride() const		{ return m_Info.szStride; }
		inline Size GetDataCount() const		{ return m_Info.szData / m_Info.szStride; }
		inline DataTypes GetDataType() const	{ return m_Info.sdType; }
		// --setters
		// --core_methods
		virtual void OnDraw() = 0;
	protected:
		GfxBufInfo m_Info;
#if (NWG_GAPI & NWG_GAPI_DX)
		ID3D11Buffer* m_pNative;
#endif
	};
}
#endif	// NWG_GAPI
#endif	// NWG_BUF_H