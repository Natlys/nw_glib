#include <nwg_pch.hpp>
#include <nwg_drawable.h>
#if (defined NWG_GAPI)
#include <nwg_engine.h>
#if (NWG_GAPI & NWG_GAPI_OGL)
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
namespace NWG
{
	ADrawable::ADrawable(GfxEngine& rGfx) :
		TEntity(), AGfxRes(rGfx) { }
	ADrawable::~ADrawable() {}
	// --core_methods
}
namespace NWG
{
	VertexedDrawable::VertexedDrawable(GfxEngine& rGfx) : ADrawable(rGfx) {}
	// --core_methods
	void VertexedDrawable::Bind() {
		for (auto& itBuf : m_vtxBufs) { itBuf->Bind(); }
	}
	void VertexedDrawable::Draw() {
		Size szData = 0;
		UInt32 unCount = 0;
		for (auto& itBuf : m_vtxBufs) {
			itBuf->Bind();
			szData += itBuf->GetDataSize();
			unCount += itBuf->GetDataCount();
		}
		m_pGfx->GetContext()->Draw(unCount, 0);
	}
}
namespace NWG
{
	IndexedDrawable::IndexedDrawable(GfxEngine& rGfx) : VertexedDrawable(rGfx) {}
	// --core_methods
	void IndexedDrawable::Bind() {
		for (auto& itBuf : m_vtxBufs) { itBuf->Bind(); }
		m_idxBuf->Bind();
	}
	void IndexedDrawable::Draw() {
		for (auto& itBuf : m_vtxBufs) {
			itBuf->Bind();
		}
		m_idxBuf->Bind();
		m_pGfx->GetContext()->DrawIndexed(m_idxBuf->GetDataCount(), NULL, NULL);
	}
}
#endif
#endif	// NWG_GAPI