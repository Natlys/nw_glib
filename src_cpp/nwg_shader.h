#ifndef NWG_SHADER_H
#define NWG_SHADER_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <nwg_res.h>
#include <nwg_buffer.h>
#include <nwg_layout.h>
namespace NWG
{
	class NWG_API Shader : public TEntity<Shader>, public AGfxRes, public ACodeRes
	{
	public:
		Shader(GfxEngine& rGfx, ShaderTypes sdType);
		virtual ~Shader();
		// --getters
		inline ShaderTypes GetType() { return m_sdType; }
		inline ShaderProgram* GetProgram() { return m_psProg; }
#if (NWG_GAPI & NWG_GAPI_DX)
		inline ID3DBlob* GetBlob() { return m_pBlob; }
#endif
		// --setters
		void SetProgram(ShaderProgram* psProg);
		// --core_methods
		virtual void Bind() = 0;
		virtual bool Compile() = 0;
		// --data_methods
		virtual bool SaveF(const char* strFPath) override;
		virtual bool LoadF(const char* strFPath) override;
	protected:
		ShaderTypes m_sdType;
		ShaderProgram* m_psProg;
#if(NWG_GAPI & NWG_GAPI_DX)
		ID3DBlob* m_pBlob;
#endif
	};
	class NWG_API VertexShader : public Shader
	{
	public:
		VertexShader(GfxEngine& rGfx);
		virtual ~VertexShader();
		// --getters
		inline VertexLayout& GetVtxLayout() { return m_vtxLayout; }
		// --core_methods
		virtual void Bind() override;
		virtual bool Compile() override;
	private:
		VertexLayout m_vtxLayout;
#if(NWG_GAPI & NWG_GAPI_DX)
		ID3D11VertexShader* m_pNative;
		InputLayout m_inLayout;
#endif
	};
	class NWG_API PixelShader : public Shader
	{
	public:
		PixelShader(GfxEngine& rGfx);
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
namespace NWG
{
	/// Shader Class
	class NWG_API ShaderProgram : public TEntity<ShaderProgram>, public AGfxRes, public ADataRes
	{
	public:
		using Uniforms = HashMap<String, Int32>;
		using Blocks = HashMap<String, Int32>;
	public:
		ShaderProgram(GfxEngine& rGfx, const char* strName);
		 virtual ~ShaderProgram();
		// --getters
		inline ShaderLayout& GetShdLayout() { return m_shdLayout; }
		inline Blocks& GetBlocks() const { return m_Blocks; }
#if (NWG_GAPI & NWG_GAPI_OGL)
		inline const Uniforms& GetUniforms() const { return m_Elems; }
#endif
		inline Shader* GetShader(ShaderTypes sdType);
		// --setters
		void SetBool(const char* strName, bool value) const;
		void SetInt(const char* strName, int value) const;
		void SetIntArray(const char* strName, Int32* pIntArr, UInt32 unCount) const;
		void SetUIntArray(const char* strName, UInt32* pUIntArr, UInt32 unCount) const;
		void SetFloat(const char* strName, float value) const;
		void SetFloatArray(const char* strName, float* pFloatArr, UInt32 unCount) const;
		void SetV2f(const char* strName, const V2f& value) const;
		void SetV3f(const char* strName, const V3f& value) const;
		void SetV4f(const char* strName, const V4f& value) const;
		void SetM4f(const char* strName, const Mat4f& value) const;
		// --core_methods
		virtual void Bind() override;
		void Remake();
		// --data_methods
		bool SaveF(const char* strFPath) override;
		bool LoadF(const char* strFPath) override;
	private:
		inline bool AddShader(ShaderTypes shdType, const char* strCode);
#if (NWG_GAPI & NWG_GAPI_OGL)
		inline Int32 GetUniformLoc(const char* strName) const;
		inline Int32 GetBlockIdx(const char* strName) const;
#endif
	private:
		ShaderLayout m_shdLayout;
		DArray<RefKeeper<Shader>> m_Shaders;
		mutable Blocks m_Blocks;
#if(NWG_GAPI & NWG_GAPI_OGL)
		mutable Uniforms m_Uniforms;
#endif
	};
	inline Shader* ShaderProgram::GetShader(ShaderTypes sdType) { for (auto& itSub : m_Shaders) { if (itSub->GetType() == sdType) { return itSub; } } }
}
#endif	// NWG_GAPI
#endif // NWG_SHADER_H