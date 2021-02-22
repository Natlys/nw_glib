#ifndef NWG_SHADER_H
#define NWG_SHADER_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <nwg_res.h>
#include <nwg_layout.h>
namespace NWG
{
	struct NWG_API ShaderInfo
	{
	public:
		Char strName[128] = "default";
		Char strGApi[16] = "default";
		ShaderTypes shdType = SHD_DEFAULT;
		Char strSrc[256] = "default";
	public:
		OutStream& operator<<(OutStream& rStream) const;
		InStream& operator>>(InStream& rStream);
	};
	OutStream& operator<<(OutStream& rStream, const ShaderInfo& rInfo);
	InStream& operator>>(InStream& rStream, ShaderInfo& rInfo);
}
namespace NWG
{
	class NWG_API Shader : public TEntity<Shader>, public AGfxRes, public ACodeRes
	{
	public:
		Shader(GfxEngine& rGfx, const char* strName, ShaderTypes sdType);
		virtual ~Shader();
		// --getters
		inline ShaderTypes GetType() { return m_sType; }
		inline ShaderProg* GetProg() { return m_pProg; }
		inline ShaderLayout& GetShdLayout() { return m_shdLayout; }
#if (NWG_GAPI & NWG_GAPI_DX)
		inline ID3DBlob* GetBlob() { return m_pBlob; }
#endif
		// --setters
		void SetProg(ShaderProg* psProg);
		// --core_methods
		virtual void Bind() = 0;
		virtual bool Compile() = 0;
		bool Remake(const ShaderInfo& rInfo);
		// --data_methods
		virtual bool SaveF(const char* strFPath) override;
		virtual bool LoadF(const char* strFPath) override;
	protected:
		ShaderTypes m_sType;
		ShaderProg* m_pProg;
		ShaderLayout m_shdLayout;
#if(NWG_GAPI & NWG_GAPI_DX)
		ID3DBlob* m_pBlob;
#endif
	};
}
namespace NWG
{
	class NWG_API VertexShader : public Shader
	{
	public:
		VertexShader(GfxEngine& rGfx, const char* strName);
		virtual ~VertexShader();
		// --getters
		inline VertexLayout& GetVtxLayout() { return m_vtxLayout; }
		// --core_methods
		virtual void Bind() override;
		virtual bool Compile() override;
	private:
		bool CodeProc();
		VertexLayout m_vtxLayout;
		InputLayout m_inLayout;
#if(NWG_GAPI & NWG_GAPI_DX)
		ID3D11VertexShader* m_pNative;
#endif
	};
}
namespace NWG
{
	class NWG_API PixelShader : public Shader
	{
	public:
		PixelShader(GfxEngine& rGfx, const char* strName);
		virtual ~PixelShader();
		// --core_methods
		virtual void Bind() override;
		virtual bool Compile() override;
	private:
#if(NWG_GAPI & NWG_GAPI_DX)
		ID3D11PixelShader* m_pNative;
#endif
	};
}
#endif	// NWG_GAPI
#endif // NWG_SHADER_H