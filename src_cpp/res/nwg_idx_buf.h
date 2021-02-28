#ifndef NWG_INDEX_BUFFER_H
#define NWG_INDEX_BUFFER_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <res/nwg_buf.h>
namespace NWG
{
	/// IndexBuf class
	class NWG_API IndexBuf : public AGfxBuf
	{
	public:
		IndexBuf(GfxEngine& rGfx);
		virtual ~IndexBuf();
		// --setters
		template<typename IType> void SetData(UInt32 unCount, IType* pData = nullptr);
		void SetSubData(Size szData, const Ptr pData, Size szOffset = 0);
		// --core_methods
		virtual void OnDraw() override;
	private:
		bool Remake(const GfxBufInfo& rInfo);
	};
	template<typename IType>
	void IndexBuf::SetData(UInt32 unCount, IType* pData) {
		GfxBufInfo gInfo(unCount * sizeof(IType), sizeof(IType), 0, pData, ConvertEnum<IType, DataTypes>());
		Remake(gInfo);
	}
}
#endif	// NWG_GAPI
#endif	// NWG_INDEX_BUFFER_H