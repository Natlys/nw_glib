#ifndef NWG_COMPONENT_H
#define NWG_COMPONENT_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <res/nwg_res.h>
#include <res/nwg_vtx_buf.h>
#include <res/nwg_idx_buf.h>
namespace NWG
{
	/// Abstract Drawable class
	class NWG_API ADrawCmp : public AGfxRes
	{
		using Resources = DArray<RefKeeper<AGfxRes>>;
	public:
		ADrawCmp(GfxEngine& rGfx);
		virtual ~ADrawCmp();
		// --getters
		inline UInt8 GetOrder() const { return m_unOrder; }
		inline Resources& GetResources() { return m_Resources; }
		inline RefKeeper<AGfxRes>& GetResource(UInt8 nIdx) { return m_Resources[nIdx % m_Resources.size()]; }
		// --setters
		void SetOrder(UInt8 unOrder);
		// --core_methods
		virtual void OnDraw() override;
		void AddResource(RefKeeper<AGfxRes>& rRes);
		template<class GType>
		void AddResource(RefKeeper<GType>& rRes) { RefKeeper<AGfxRes> Res(rRes); AddResource(Res); }
		void RmvResource(UInt8 nIdx);
	protected:
		Resources m_Resources;
		UInt8 m_unOrder;
	};
}
namespace NWG
{
	/// DrawVertexCmp class
	class NWG_API DrawVtxCmp : public ADrawCmp
	{
		using VtxBufs = DArray<RefKeeper<VertexBuf>>;
	public:
		DrawVtxCmp(GfxEngine& rGfx);
		template<typename VType>
		DrawVtxCmp(GfxEngine& rGfx, UInt32 unVtxCount, VType* pVtxData = nullptr);
		// --getters
		inline VtxBufs& GetVtxBufs() { return m_vtxBufs; }
		inline RefKeeper<VertexBuf>& GetVtxBuf(UInt8 unIdx) { return m_vtxBufs[unIdx % m_vtxBufs.size()]; }
		// --setters
		void AddVtxBuf(RefKeeper<VertexBuf>& rBuf);
		void RmvVtxBuf(UInt8 unIdx);
		// --core_methods
		virtual void OnDraw() override;
	protected:
		VtxBufs m_vtxBufs;
	};
	template<typename VType>
	DrawVtxCmp::DrawVtxCmp(GfxEngine& rGfx, UInt32 unVtxCount, VType* pVtxData) :
		DrawVtxCmp(rGfx)
	{
		m_vtxBufs.push_back(RefKeeper<VertexBuf>());
		m_pGfx->NewRes<VertexBuf>(m_vtxBufs.back());
		m_vtxBufs.back()->SetData<VType>(unVtxCount, pVtxData);
	}
}
namespace NWG
{
	/// DrawIdxCmp class
	class NWG_API DrawIdxCmp : public ADrawCmp
	{
	public:
		DrawIdxCmp(GfxEngine& rGfx);
		template<typename IType>
		DrawIdxCmp(GfxEngine& rGfx, UInt32 unIdxCount, IType* pIdxData = nullptr);
		template<typename IType, typename VType>
		DrawIdxCmp(GfxEngine& rGfx, UInt32 unIdxCount, IType* pIdxData, UInt32 unVtxCount, VType* pVtxData = nullptr);
		// --getters
		inline IndexBuf* GetIdxBuf() { return m_idxBuf; }
		// --setters
		void SetIdxBuf(RefKeeper<IndexBuf>& rBuf);
		// --core_methods
		virtual void OnDraw() override;
	protected:
		RefKeeper<IndexBuf> m_idxBuf;
	};
	template<typename IType>
	DrawIdxCmp::DrawIdxCmp(GfxEngine& rGfx, UInt32 unIdxCount, IType* pIdxData) :
		DrawIdxCmp(rGfx) {
		m_idxBuf = RefKeeper<IndexBuf>();
		m_pGfx->NewRes<IndexBuf>(m_idxBuf);
		m_idxBuf->SetData<IType>(unIdxCount, pIdxData);
	}
	template<typename IType, typename VType>
	DrawIdxCmp::DrawIdxCmp(GfxEngine& rGfx, UInt32 unIdxCount, IType* pIdxData, UInt32 unVtxCount, VType* pVtxData) :
		DrawIdxCmp(rGfx, unIdxCount, pIdxData)
	{
		RefKeeper<VertexBuf> vtxBuf;
		m_pGfx->NewRes<VertexBuf>(vtxBuf);
		vtxBuf->SetData<VType>(unVtxCount, pVtxData);
		AddResource(vtxBuf);
	}
}
#endif
#endif	// NWG_COMPONENT_H