#include <nwg_pch.hpp>
#include <core/nwg_component.h>
#if (defined NWG_GAPI)
#include <core/nwg_engine.h>
#if (NWG_GAPI & NWG_GAPI_OGL)
#include <lib/nwg_ogl_v1.h>
namespace NWG
{
	ADrawCmp::ADrawCmp(GfxEngine& rGfx) :
		AGfxRes(rGfx),
		m_unOrder(0) { }
	ADrawCmp::~ADrawCmp() { }
	// --setters
	void ADrawCmp::SetOrder(UInt8 unOrder) { m_unOrder = unOrder; }
	// --core_methods
	void ADrawCmp::OnDraw() {
		for (auto& itRes : m_Resources) { itRes->OnDraw(); }
	}
	void ADrawCmp::AddResource(RefKeeper<AGfxRes>& rRes) { m_Resources.push_back(rRes); }
	void ADrawCmp::RmvResource(UInt8 nIdx) { m_Resources.erase(m_Resources.begin() + nIdx % m_Resources.size()); }
}
namespace NWG
{
	DrawVtxCmp::DrawVtxCmp(GfxEngine& rGfx) : ADrawCmp(rGfx) { }
	// --setters
	void DrawVtxCmp::AddVtxBuf(RefKeeper<VertexBuf>& rBuf) { m_vtxBufs.push_back(rBuf); }
	void DrawVtxCmp::RmvVtxBuf(UInt8 unIdx) { m_vtxBufs.erase(m_vtxBufs.begin() + unIdx); }
	// --core_methods
	void DrawVtxCmp::OnDraw() {
		Size szData = 0;
		Size unCount = 0;
		ADrawCmp::OnDraw();
		for (auto& itBuf : m_vtxBufs) {
			itBuf->OnDraw();
			szData += itBuf->GetDataSize();
			unCount += itBuf->GetDataCount();
		}
		glDrawArrays(GL_TRIANGLES, unCount, szData);
	}
}
namespace NWG
{
	DrawIdxCmp::DrawIdxCmp(GfxEngine& rGfx) : ADrawCmp(rGfx) { }
	void DrawIdxCmp::SetIdxBuf(RefKeeper<IndexBuf>& rBuf) { m_idxBuf.SetRef<IndexBuf>(rBuf); }
	// --core_methods
	void DrawIdxCmp::OnDraw() {
		ADrawCmp::OnDraw();
		m_idxBuf->OnDraw();
		glDrawElements(GL_TRIANGLES, m_idxBuf->GetDataCount(), ConvertEnum<DataTypes, UInt32>(m_idxBuf->GetDataType()), nullptr);
	}
}
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
#include <lib/nwg_dx_loader.h>
namespace NWG
{
	Drawable::Drawable(GfxEngine& rGfx) :
		TEnt(), AGfxRes(rGfx),
		m_unOrder(0) { }
	Drawable::~Drawable() { }
	// --setters
	void Drawable::SetOrder(UInt8 unOrder) { m_unOrder = unOrder; }
	void Drawable::AddResource(RefKeeper<AGfxRes>& rRes) { m_Resources.push_back(rRes); }
	void Drawable::RmvResource(UInt8 unIdx) { m_Resources.erase(m_Resources.begin() + unIdx); }
	// --core_methods
	void Drawable::OnDraw() { for (auto& itRes : m_Resources) { itRes->OnDraw(); } }
}

namespace NWG
{
	VtxDrawable::VtxDrawable(GfxEngine& rGfx) : Drawable(rGfx) { }
	// --setters
	void VtxDrawable::AddVtxBuf(RefKeeper<VertexBuf>& rBuf) { m_vtxBufs.push_back(rBuf); }
	void VtxDrawable::RmvVtxBuf(UInt8 unIdx) { m_vtxBufs.erase(m_vtxBufs.begin() + unIdx); }
	// --core_methods
	void VtxDrawable::OnDraw() {
		Size szData = 0;
		Size unCount = 0;
		for (auto& itRes : m_Resources) { itRes->OnDraw(); }
		for (auto& itBuf : m_vtxBufs) {
			itBuf->OnDraw();
			szData += itBuf->GetDataSize();
			unCount += itBuf->GetDataCount();
		}
		m_pGfx->GetContext()->Draw(unCount, 0u);
	}
}

namespace NWG
{
	IdxDrawable::IdxDrawable(GfxEngine& rGfx) : Drawable(rGfx) { }
	void IdxDrawable::SetIdxBuf(RefKeeper<IndexBuf>& rBuf) { m_idxBuf.SetRef<IndexBuf>(rBuf); }
	// --core_methods
	void IdxDrawable::OnDraw() {
		for (auto& itRes : m_Resources) { itRes->OnDraw(); }
		m_idxBuf->OnDraw();
		m_pGfx->GetContext()->DrawIndexed(m_idxBuf->GetDataCount(), 0u, 0);
	}
}
#endif
#endif	// NWG_GAPI