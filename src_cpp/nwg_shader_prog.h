#ifndef NWG_SHADER_PROG_H
#define NWG_SHADER_PROG_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <nwg_res.h>
#include <nwg_shd_buf.h>
#include <nwg_shader.h>
namespace NWG
{
	struct NWG_API ShaderProgInfo
	{
	public:
		Char strName[128] = "default";
		Char strGApi[16] = "default";
		Char strVtxFile[256] = "default";
		Char strPxlFile[256] = "default";
		Char strGmtFile[256] = "default";
	public:
		// --operators
		OutStream& operator<<(OutStream& rStream) const;
		InStream& operator>>(InStream& rStream);
	};
	OutStream& operator<<(OutStream& rStream, const ShaderProgInfo& rInfo);
	InStream& operator>>(InStream& rStream, ShaderProgInfo& rInfo);
}
namespace NWG
{
	/// ShaderProg Class
	class NWG_API ShaderProg : public TEntity<ShaderProg>, public AGfxRes, public ADataRes
	{
	public:
		using Blocks = HashMap<String, Int32>;
	public:
		ShaderProg(GfxEngine& rGfx, const char* strName);
		virtual ~ShaderProg();
		// --getters
		inline ShaderLayout& GetShdLayout() { return m_shdLayout; }
		inline Blocks& GetBlocks() const { return m_Blocks; }
		inline Shader* GetShader(ShaderTypes sdType);
		// --setters
		// --core_methods
		virtual void Bind() override;
		bool Remake(const ShaderProgInfo& rInfo);
		// --data_methods
		bool SaveF(const char* strFPath) override;
		bool LoadF(const char* strFPath) override;
	private:
#if (NWG_GAPI & NWG_GAPI_OGL)
		Int32 GetBlockIdx(const char* strName) const;
#endif
	private:
		ShaderLayout m_shdLayout;
		DArray<RefKeeper<Shader>> m_Shaders;
		mutable Blocks m_Blocks;
	};
	inline Shader* ShaderProg::GetShader(ShaderTypes sdType) { for (auto& itSub : m_Shaders) { if (itSub->GetType() == sdType) { return itSub; } } }
}

#endif	// NWG_GAPI
#endif	// NWG_SHADER_PROG_H