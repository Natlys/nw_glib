#include <nwg_pch.hpp>
#include <nwg_drawable.h>
#if (defined NWG_GAPI)
#include <nwg_engine.h>
#if (NWG_GAPI & NWG_GAPI_OGL)
#include <ogl/nwg_ogl_loader.h>

namespace NWG
{
	Drawable::Drawable(GfxEngine& rGfx) :
		TEntity(), AGfxRes(rGfx),
		m_unOrder(0) { }
	Drawable::~Drawable() { }
	// --setters
	void Drawable::SetOrder(UInt8 unOrder) { m_unOrder = unOrder; }
	void Drawable::AddResource(RefKeeper<AGfxRes>& rRes) { m_Resources.push_back(rRes); }
	void Drawable::RmvResource(UInt8 unIdx) { m_Resources.erase(m_Resources.begin() + unIdx); }
	// --core_methods
	void Drawable::Bind() { for (auto& itRes : m_Resources) { itRes->Bind(); } }
}

namespace NWG
{
	VtxDrawable::VtxDrawable(GfxEngine& rGfx) : Drawable(rGfx) { }
	// --setters
	void VtxDrawable::AddVtxBuf(RefKeeper<VertexBuf>& rBuf) { m_vtxBufs.push_back(rBuf); }
	void VtxDrawable::RmvVtxBuf(UInt8 unIdx) { m_vtxBufs.erase(m_vtxBufs.begin() + unIdx); }
	// --core_methods
	void VtxDrawable::Bind() {
		Size szData = 0;
		Size unCount = 0;
		for (auto& itRes : m_Resources) { itRes->Bind(); }
		for (auto& itBuf : m_vtxBufs) {
			itBuf->Bind();
			szData += itBuf->GetDataSize();
			unCount += itBuf->GetDataCount();
		}
		glDrawArrays(GL_TRIANGLES, unCount, szData);
	}
}

namespace NWG
{
	IdxDrawable::IdxDrawable(GfxEngine& rGfx) : Drawable(rGfx) { }
	void IdxDrawable::SetIdxBuf(RefKeeper<IndexBuf>& rBuf) { m_idxBuf.SetRef<IndexBuf>(rBuf); }
	// --core_methods
	void IdxDrawable::Bind() {
		for (auto& itRes : m_Resources) { itRes->Bind(); }
		m_idxBuf->Bind();
		glDrawElements(GL_TRIANGLES, m_idxBuf->GetDataCount(), ConvertEnum<DataTypes, UInt32>(m_idxBuf->GetDataType()), nullptr);
	}
}
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
#include <dx/nwg_dx_loader.h>
namespace NWG
{
	Drawable::Drawable(GfxEngine& rGfx) :
		TEntity(), AGfxRes(rGfx),
		m_unOrder(0) { }
	Drawable::~Drawable() { }
	// --setters
	void Drawable::SetOrder(UInt8 unOrder) { m_unOrder = unOrder; }
	void Drawable::AddResource(RefKeeper<AGfxRes>& rRes) { m_Resources.push_back(rRes); }
	void Drawable::RmvResource(UInt8 unIdx) { m_Resources.erase(m_Resources.begin() + unIdx); }
	// --core_methods
	void Drawable::Bind() { for (auto& itRes : m_Resources) { itRes->Bind(); } }
}

namespace NWG
{
	VtxDrawable::VtxDrawable(GfxEngine& rGfx) : Drawable(rGfx) { }
	// --setters
	void VtxDrawable::AddVtxBuf(RefKeeper<VertexBuf>& rBuf) { m_vtxBufs.push_back(rBuf); }
	void VtxDrawable::RmvVtxBuf(UInt8 unIdx) { m_vtxBufs.erase(m_vtxBufs.begin() + unIdx); }
	// --core_methods
	void VtxDrawable::Bind() {
		Size szData = 0;
		Size unCount = 0;
		for (auto& itRes : m_Resources) { itRes->Bind(); }
		for (auto& itBuf : m_vtxBufs) {
			itBuf->Bind();
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
	void IdxDrawable::Bind() {
		for (auto& itRes : m_Resources) { itRes->Bind(); }
		m_idxBuf->Bind();
		m_pGfx->GetContext()->DrawIndexed(m_idxBuf->GetDataCount(), 0u, 0);
	}
}
#endif
#endif	// NWG_GAPI