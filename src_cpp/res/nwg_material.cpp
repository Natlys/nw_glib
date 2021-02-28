#include <nwg_pch.hpp>
#include "nwg_material.h"
#if (defined NWG_GAPI)
#include <res/nwg_texture.h>
#include <res/nwg_shader_prog.h>
namespace NWG
{
	OutStream& GfxMaterialInfo::operator<<(OutStream& rStream) const { return rStream; }
	InStream& GfxMaterialInfo::operator>>(InStream& rStream) { return rStream; }
}
#if (NWG_GAPI & NWG_GAPI_OGL)
#include <lib/nwg_ogl_v2.h>
namespace NWG
{
	GfxMaterial::GfxMaterial(GfxEngine& rGfx, const char* strName) :
		AGfxRes(rGfx), ADataRes(strName) { m_Textures["tex_default"] = RefKeeper<Texture>(); }
	GfxMaterial::~GfxMaterial() { }

	// --setters
	void GfxMaterial::SetShaderProg(RefKeeper<ShaderProg>& rshdProg) {
		m_pShdProg = rshdProg;
		m_Textures.clear();
		m_Colors.clear();

		if (rshdProg.IsValid()) {
			for (auto& itGlob : rshdProg->GetShdLayout().GetBlock().Elems) {
				switch (itGlob.sdType) {
				case DT_FLOAT32: if (itGlob.unCount == 4) { m_Colors[itGlob.strName] = V4f{ 1.0f, 1.0f, 1.0f, 1.0f }; } break;
				case DT_USER_DATA: break;
				}
			}
		}
		if (m_Textures.empty()) { m_Textures["tex_default"] = RefKeeper<Texture>(); }
	}
	void GfxMaterial::SetTexture(RefKeeper<Texture>& rTex, const char* strType) {
		if (!rTex.IsValid()) { return; }
		if (strcmp(strType, "") == 0) { m_Textures.begin()->second.SetRef(rTex); }
		if (m_Textures.find(strType) != m_Textures.end()) { m_Textures[strType].SetRef(rTex); }
		else { }
	}
	void GfxMaterial::SetColor(const V4f& rgbaClr, const char* strType) {
		if (strcmp(strType, "") == 0) { m_Colors.begin()->second = rgbaClr; }
		if (m_Colors.find(strType) == m_Colors.end()) {	m_Colors[strType] = rgbaClr; }
		else { }
	}

	// --core_methods
	void GfxMaterial::OnDraw()
	{
		if (!m_pShdProg.IsValid()) { return; }
		m_pShdProg->OnDraw();
		for (auto& itClr : m_Colors) { }
		auto& itTex = m_Textures.begin();
		for (UInt8 txi = 0; txi < m_Textures.size(); txi++) {
			if (!itTex->second.IsValid()) { return; }
			itTex->second->SetSlot(txi);
			glUniform1i(txi, itTex->second->GetTexSlot());
			itTex->second->OnDraw();
			itTex++;
		}
	}
	// --data_methods
	bool GfxMaterial::SaveF(const char* strFPath) { return true; }
	bool GfxMaterial::LoadF(const char* strFPath) { return true; }
}
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
#endif
#endif	// NWG_GAPI