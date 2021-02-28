#ifndef NWG_SHADER_H
#define NWG_SHADER_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <res/nwg_res.h>
#include <res/nwg_layout.h>
namespace NWG
{
	struct NWG_API ShaderInfo : public AInfo
	{
	public:
		GfxApiTypes gapiType = GAPI_DEFAULT;
		ShaderTypes shdType = SHD_DEFAULT;
		String strName = "default";
		String strSrc = "default";
	public:
		ShaderInfo(GfxApiTypes graphicsApiType = GAPI_DEFAULT, ShaderTypes shaderType = SHD_DEFAULT,
			const char* sName = "default", const char* sSourceCode = "default");
		// --operators
		virtual OutStream& operator<<(OutStream& rStream) const override;
		virtual InStream& operator>>(InStream& rStream) override;
	};
}
namespace NWG
{
	class NWG_API Shader : public AGfxRes, public ADataRes
	{
		using Buffers = DArray<RefKeeper<ShaderBuf>>;
	public:
		Shader(GfxEngine& rGfx, const char* strName, ShaderTypes sdType);
		virtual ~Shader();
		// --getters
		inline ShaderTypes GetType() const	{ return m_Info.shdType; }
		inline const char* GetCode() const	{ return &m_Info.strSrc[0]; }
		inline const ShaderInfo& GetInfo() const { return m_Info; }
		inline ShaderProg* GetProg()		{ return m_pProg; }
		inline Buffers& GetBuffers()		{ return m_Bufs; }
#if (NWG_GAPI & NWG_GAPI_DX)
		inline ID3DBlob* GetBlob()		{ return m_pBlob; }
#endif
		// --setters
		void SetCode(const char* strCode);
		void SetProg(ShaderProg* psProg);
		// --core_methods
		virtual void OnDraw() = 0;
		virtual bool Compile() = 0;
		bool Remake(const ShaderInfo& rInfo);
		// --data_methods
		virtual bool SaveF(const char* strFPath) override;
		virtual bool LoadF(const char* strFPath) override;
	protected:
		ShaderInfo m_Info;
		ShaderProg* m_pProg;
		Buffers m_Bufs;
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
		virtual void OnDraw() override;
		virtual bool Compile() override;
	private:
		bool CodeProc();
	private:
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
		virtual void OnDraw() override;
		virtual bool Compile() override;
	private:
		bool CodeProc();
	private:
#if(NWG_GAPI & NWG_GAPI_DX)
		ID3D11PixelShader* m_pNative;
#endif
	};
}
namespace NWG
{
	class NWG_API GeometryShader : public Shader
	{
	public:
		GeometryShader(GfxEngine& rGfx, const char* strName);
		virtual ~GeometryShader();
		// --core_methods
		virtual void OnDraw() override;
		virtual bool Compile() override;
	private:
		bool CodeProc();
	private:
#if(NWG_GAPI & NWG_GAPI_DX)
		ID3D11PixelShader* m_pNative;
#endif
	};
}
#endif	// NWG_GAPI
#endif // NWG_SHADER_H