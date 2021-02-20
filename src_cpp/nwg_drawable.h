#ifndef GFX_ADRAWABLE_H
#define GFX_ADRAWABLE_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <nwg_res.h>
#include <nwg_tools.h>
#include <nwg_buffer.h>
namespace NWG
{
	/// Abstract Drawable class
	class NWG_API ADrawable : public TEntity<ADrawable>, public AGfxRes
	{
	public:
		ADrawable(GfxEngine& rGfx);
		virtual ~ADrawable();
		// --getters
		//inline DArray<AGfxRes*>& GetResources() { return m_Resources; }
		//inline AGfxRes* GetResource(UInt8 nIdx) { return m_Resources[nIdx]; }
		// --setters
		//void AddResoruce(AGfxRes& rgRes) { m_Resources.push_back(&rgRes); }
		//void RmvResource(UInt8 nIdx) { m_Resources.erase(m_Resources.begin() + nIdx); }
		// --core_methods
		virtual void Draw() = 0;
		virtual void Bind() = 0;
	protected:
		//DArray<AGfxRes*> m_Resources;
	};
}
namespace NWG
{
	/// VertexedDrawable class
	class NWG_API VertexedDrawable : public ADrawable
	{
	public:
		VertexedDrawable(GfxEngine& rGfx);
		// --getters
		inline DArray<RefKeeper<VertexBuf>>& GetVtxBufs() { return m_vtxBufs; }
		inline VertexBuf* GetVtxBuf(UInt8 nIdx) { return m_vtxBufs[nIdx]; }
		// --setters
		template<typename VType>
		inline void AddVtxBuf(UInt32 unCount, VType* pData);
		inline void RmvVtxBuf(UInt8 nIdx) { m_vtxBufs.erase(m_vtxBufs.begin() + nIdx); }
		// --core_methods
		virtual void Draw() override;
		virtual void Bind() override;
	protected:
		DArray<RefKeeper<VertexBuf>> m_vtxBufs;
	};
	template<typename VType>
	inline void VertexedDrawable::AddVtxBuf(UInt32 unCount, VType* pData) {
		m_vtxBufs.push_back(RefKeeper<VertexBuf>());
		m_pGfx->CreateRes<VertexBuf, TVertexBuf<VType>>(m_vtxBufs.back(), unCount, pData);
	}
	/// IndexedDrawable class
	class NWG_API IndexedDrawable : public VertexedDrawable
	{
	public:
		IndexedDrawable(GfxEngine& rGfx);
		// --getters
		inline IndexBuf* GetIdxBuf() { return m_idxBuf; }
		// --setters
		template<typename IType>
		void SetIdxBuf(UInt32 nCount, IType* pData) { m_pGfx->CreateRes<IndexBuf, TIndexBuf<IType>>(m_idxBuf, nCount, pData); }
		// --core_methods
		virtual void Draw() override;
		virtual void Bind() override;
	protected:
		RefKeeper<IndexBuf> m_idxBuf;
	};
}
#endif
#endif	// GFX_DRAWABLE_H