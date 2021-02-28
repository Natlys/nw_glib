#ifndef NWG_VERTEX_BUFFER_H
#define NWG_VERTEX_BUFFER_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <res/nwg_buf.h>
namespace NWG
{
	/// VertexBuf class
	class NWG_API VertexBuf : public AGfxBuf
	{
	public:
		VertexBuf(GfxEngine& rGfx);
		virtual ~VertexBuf();
		// --setters
		template<typename VType> void SetData(UInt32 unCount, VType* pData = nullptr);
		void SetSubData(Size szData, const Ptr pData, Size szOffset = 0);
		// --core_methods
		virtual void OnDraw() override;
	private:
		bool Remake(const GfxBufInfo& rInfo);
	};
	template<typename VType>
	void VertexBuf::SetData(UInt32 unCount, VType* pData) {
		GfxBufInfo gInfo(unCount * sizeof(VType), sizeof(VType), 0, pData, DT_DEFAULT);
		Remake(gInfo);
	}
}
#endif	// NWG_GAPI
#endif	// NWG_VERTEX_BUFFER_H