#ifndef GFX_DRAWABLE_H
#define GFX_DRAWABLE_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <nwg_res.h>
#include <nwg_tools.h>
#include <nwg_vtx_buf.h>
#include <nwg_idx_buf.h>
#include <nwg_material.h>
namespace NWG
{
	/// Abstract Drawable class
	class NWG_API Drawable : public TEntity<Drawable>, public AGfxRes
	{
		using Resources = DArray<RefKeeper<AGfxRes>>;
	public:
		Drawable(GfxEngine& rGfx);
		virtual ~Drawable();
		// --getters
		inline UInt8 GetOrder() const { return m_unOrder; }
		inline Resources& GetResources() { return m_Resources; }
		inline RefKeeper<AGfxRes>& GetResoruce(UInt8 unIdx) { return m_Resources[unIdx % m_Resources.size()]; }
		// --setters
		void SetOrder(UInt8 unOrder);
		void AddResource(RefKeeper<AGfxRes>& rRes);
		void RmvResource(UInt8 unIdx);
		template<class RType> void AddResource(RefKeeper<RType>& rRes);
		// --core_methods
		virtual void Bind() override;
	protected:
		UInt8 m_unOrder;
		Resources m_Resources;
	};
	template<class RType> void Drawable::AddResource(RefKeeper<RType>& rRes) {
		RefKeeper<AGfxRes> aRes; aRes.SetRef<RType>(rRes); AddResource(aRes);
	}
}
namespace NWG
{
	/// VtxDrawable class
	class NWG_API VtxDrawable : public Drawable
	{
		using VtxBufs = DArray<RefKeeper<VertexBuf>>;
	public:
		VtxDrawable(GfxEngine& rGfx);
		template<typename VType>
		VtxDrawable(GfxEngine& rGfx, UInt32 unVtxCount, VType* pVtxData = nullptr);
		// --getters
		inline VtxBufs& GetVtxBufs() { return m_vtxBufs; }
		inline RefKeeper<VertexBuf>& GetVtxBuf(UInt8 unIdx) { return m_vtxBufs[unIdx % m_vtxBufs.size()]; }
		// --setters
		void AddVtxBuf(RefKeeper<VertexBuf>& rBuf);
		void RmvVtxBuf(UInt8 unIdx);
		// --core_methods
		virtual void Bind() override;
	protected:
		VtxBufs m_vtxBufs;
	};
	template<typename VType>
	VtxDrawable::VtxDrawable(GfxEngine& rGfx, UInt32 unVtxCount, VType* pVtxData) :
		Drawable(rGfx)
	{
		m_vtxBufs.push_back(RefKeeper<VertexBuf>());
		m_pGfx->CreateRes<VertexBuf>(m_vtxBufs.back());
		m_vtxBufs.back()->SetData<VType>(unVtxCount, pVtxData);
	}
	/// IdxDrawable class
	class NWG_API IdxDrawable : public Drawable
	{
	public:
		IdxDrawable(GfxEngine& rGfx);
		template<typename IType>
		IdxDrawable(GfxEngine& rGfx, UInt32 unIdxCount, IType* pIdxData = nullptr);
		template<typename IType, typename VType>
		IdxDrawable(GfxEngine& rGfx, UInt32 unIdxCount, IType* pIdxData, UInt32 unVtxCount, VType* pVtxData = nullptr);
		// --getters
		inline IndexBuf* GetIdxBuf() { return m_idxBuf; }
		// --setters
		void SetIdxBuf(RefKeeper<IndexBuf>& rBuf);
		// --core_methods
		virtual void Bind() override;
	protected:
		RefKeeper<IndexBuf> m_idxBuf;
	};
	template<typename IType>
	IdxDrawable::IdxDrawable(GfxEngine& rGfx, UInt32 unIdxCount, IType* pIdxData) :
		Drawable(rGfx) {
		m_idxBuf = RefKeeper<IndexBuf>();
		m_pGfx->CreateRes<IndexBuf>(m_idxBuf);
		m_idxBuf->SetData<IType>(unIdxCount, pIdxData);
	}
	template<typename IType, typename VType>
	IdxDrawable::IdxDrawable(GfxEngine& rGfx, UInt32 unIdxCount, IType* pIdxData, UInt32 unVtxCount, VType* pVtxData) :
		IdxDrawable(rGfx, unIdxCount, pIdxData)
	{
		m_Resources.push_back(RefKeeper<AGfxRes>());
		RefKeeper<VertexBuf> vtxBuf;
		m_pGfx->CreateRes<VertexBuf>(vtxBuf);
		vtxBuf->SetData<VType>(unVtxCount, pVtxData);
		m_Resources.back().SetRef<VertexBuf>(vtxBuf);
	}
}
#endif
#endif	// GFX_DRAWABLE_H