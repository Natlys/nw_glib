#ifndef NWG_ARRAY_H
#define NWG_ARRAY_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <nwg_buffer.h>
namespace NWG
{
	/// VertexArray class
	class VertexArr : public TEntity<VertexArr>, public AGfxRes
	{
		friend class GfxEngine;
	public:
		VertexArr(GfxEngine& rGfx);
		virtual ~VertexArr();
		// --getters
		inline GfxPrimitives GetDrawPrimitive() const { return m_gpType; }
		// --setters
		void SetDrawPrimitive(GfxPrimitives gpType);
		void AddVtxBuf(const GfxDataInfo& rInfo);
		void RmvVtxBuf(UInt32 nIdx = 0);
		void AddIdxBuf(const GfxDataInfo& rInfo);
		void RmvIdxBuf();
		// --core_methods
		virtual void Bind() override;
	private:
		GfxPrimitives m_gpType;
		DArray<GfxDataInfo> m_vtxInfo;
		GfxDataInfo m_idxInfo;
#if(NWG_GAPI & NWG_GAPI_DX)
		DArray<ID3D11Buffer*> m_vtxBufs;
		ID3D11Buffer* m_idxBuf;
#endif
	};
}
#endif	// NWG_GAPI
#endif	// NWG_ARRAY_H