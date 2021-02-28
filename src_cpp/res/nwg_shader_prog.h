#ifndef NWG_SHADER_PROG_H
#define NWG_SHADER_PROG_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <res/nwg_res.h>
#include <res/nwg_shd_buf.h>
#include <res/nwg_shader.h>
namespace NWG
{
	struct NWG_API ShaderProgInfo : public AInfo
	{
	public:
		GfxApiTypes gapiType = GAPI_DEFAULT;
		String strName = "default";
		String strSrcVtx = "default";
		String strSrcPxl = "default";
		String strSrcGmt = "default";
	public:
		// --operators
		virtual OutStream& operator<<(OutStream& rStream) const override;
		virtual InStream& operator>>(InStream& rStream) override;
	};
}
namespace NWG
{
	/// ShaderProg Class
	class NWG_API ShaderProg : public AGfxRes, public ADataRes
	{
	public:
		using Blocks = HashMap<String, Int32>;
	public:
		ShaderProg(GfxEngine& rGfx, const char* strName);
		virtual ~ShaderProg();
		// --getters
		inline ShaderLayout& GetShdLayout() { return m_shdLayout; }
		inline Shader* GetShader(ShaderTypes sdType);
		inline const ShaderProgInfo& GetInfo() const { return m_Info; }
		// --setters
		template<typename VType> void SetValue(UInt32 unIdx, const VType& rData);
		template<typename VType> void SetArray(UInt32 unIdx, const VType& rData, UInt32 unCount);
		// --core_methods
		virtual void OnDraw() override;
		bool Remake(const ShaderProgInfo& rInfo);
		// --data_methods
		bool SaveF(const char* strFPath) override;
		bool LoadF(const char* strFPath) override;
	private:
#if (NWG_GAPI & NWG_GAPI_OGL)
		Int32 GetBlockIdx(const char* strName);
#endif
	private:
		ShaderProgInfo m_Info;
		ShaderLayout m_shdLayout;
		DArray<RefKeeper<Shader>> m_Shaders;
		Blocks m_Blocks;
	};
	inline Shader* ShaderProg::GetShader(ShaderTypes sdType) { for (auto& itSub : m_Shaders) { if (itSub->GetType() == sdType) { return itSub; } } return nullptr; }
}

#endif	// NWG_GAPI
#endif	// NWG_SHADER_PROG_H