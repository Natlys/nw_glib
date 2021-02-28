#ifndef NWG_MATERIAL_H
#define NWG_MATERIAL_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <res/nwg_res.h>
#include <res/nwg_shader_prog.h>
#include <core/nwg_tools.h>
namespace NWG
{
	struct NWG_API GfxMaterialInfo : public AInfo
	{
	public:
		String strName = "default";
		GfxApiTypes gapiType = GAPI_DEFAULT;
	public:
		// --operation
		virtual OutStream& operator<<(OutStream& rStream) const override;
		virtual InStream& operator>>(InStream& rStream) override;
	};
}
namespace NWG
{
	/// GraphicsMaterial Class
	/// Description:
	/// -- This is a wrapper for shader which sets up uniforms
	/// -- Graphics material is responsible for colors and maps settings
	/// -- There are also few attributes it needs to set,
	/// but generally this is concerned about drawable object properties
	class NWG_API GfxMaterial : public AGfxRes, public ADataRes
	{
	public:
		using Textures = HashMap<String, RefKeeper<Texture>>;
		using Colors = HashMap<String, V4f>;
	public:
		GfxMaterial(GfxEngine& rGfx, const char* strName);
		virtual ~GfxMaterial();
		// --getters
		inline RefKeeper<ShaderProg>& GetShaderProg() { return m_pShdProg; }
		inline UInt8 GetTexCount() { return m_Textures.size(); }
		inline Textures& GetTextures() { return m_Textures; }
		inline Colors& GetColors() { return m_Colors; }
		inline RefKeeper<Texture>& GetTexture(const char* strType = "");
		inline V4f* GetColor(const char* strType = "");
		// --setters
		void SetShaderProg(RefKeeper<ShaderProg>& rshdProg);
		void SetTexture(RefKeeper<Texture>& rTex, const char* strType = "");
		void SetColor(const V4f& rgbaClr, const char* strType = "");
		// --core_methods
		virtual void OnDraw() override;
		// --data_methods
		virtual bool SaveF(const char* strFPath) override;
		virtual bool LoadF(const char* strFPath) override;
	private:
		String m_strName;
		RefKeeper<ShaderProg> m_pShdProg;
		Textures m_Textures;
		Colors m_Colors;
	};
	inline RefKeeper<Texture>& GfxMaterial::GetTexture(const char* strType) {
		if (strcmp(strType, "") == 0) { return m_Textures.begin()->second; }
		auto itTex = m_Textures.find(&strType[0]);
		return itTex == m_Textures.end() ? m_Textures.begin()->second : itTex->second;
	}
	inline V4f* GfxMaterial::GetColor(const char* strType) {
		if (strcmp(strType, "") == 0) { return &m_Colors.begin()->second; }
		auto itClr = m_Colors.find(&strType[0]);
		return itClr == m_Colors.end() ? nullptr : &itClr->second;
	}
}
#endif	// NWG_GAPI
#endif // NWG_MATERIAL_H