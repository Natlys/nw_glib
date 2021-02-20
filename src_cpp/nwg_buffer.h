#ifndef NWG_BUFFER_H
#define NWG_BUFFER_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <nwg_tools.h>
#include <nwg_res.h>
#include <nwg_layout.h>
namespace NWG
{
	struct Vtx2f
	{
		V2f vtxCrd = { 0.0f, 0.0f };
	};
	struct Vtx3f
	{
		V3f vtxCrd = { 0.0f, 0.0f, 0.0f };
	};
}
namespace NWG
{
	class NWG_API VertexBuf : public TEntity<VertexBuf>, public AGfxRes
	{
	public:
		VertexBuf(GfxEngine& rGfx, GfxDataInfo& rInfo);
		virtual ~VertexBuf();
		// --getters
		inline Size GetDataSize() const { return m_gdInfo.szData; }
		inline Size GetDataStride() const { return m_gdInfo.szStride; }
		inline UInt32 GetDataCount() const { return m_gdInfo.szData / m_gdInfo.szStride; }
		inline ShaderDataTypes GetDataType() { return m_gdInfo.sdType; }
		// --setters
		void SetSubData(Size szData, const Ptr pData, Size szOffset = 0);
		// --core_methods
		virtual void Bind() override;
	protected:
		GfxDataInfo m_gdInfo;
#if (NWG_GAPI & NWG_GAPI_DX)
		ID3D11Buffer* m_pNative;
#endif
	};
	class NWG_API IndexBuf : public TEntity<IndexBuf>, public AGfxRes
	{
	public:
		IndexBuf(GfxEngine& rGfx, GfxDataInfo& rInfo);
		virtual ~IndexBuf();
		// --getters
		inline Size GetDataSize() const { return m_gdInfo.szData; }
		inline Size GetDataStride() const { return m_gdInfo.szStride; }
		inline UInt32 GetDataCount() const { return m_gdInfo.szData / m_gdInfo.szStride; }
		inline ShaderDataTypes GetDataType() { return m_gdInfo.sdType; }
		// --setters
		void SetSubData(Size szData, const Ptr pData, Size szOffset = 0);
		// --core_methods
		virtual void Bind() override;
	protected:
		GfxDataInfo m_gdInfo;
#if (NWG_GAPI & NWG_GAPI_DX)
		ID3D11Buffer* m_pNative;
#endif
	};
}
namespace NWG
{
	/// Templated VertexBuffer Class
	template<typename VType>
	class NWG_API TVertexBuf : public VertexBuf
	{
	public:
		TVertexBuf(GfxEngine& rGfx, UInt32 nCount, VType* pData = nullptr) :
		VertexBuf(rGfx, GfxDataInfo(nCount * sizeof(VType), sizeof(VType), 0, pData, SDT_DEFAULT)) { }
	};
}
namespace NWG
{
	/// Templated IndexBuffer Class
	template<typename IType>
	class NWG_API TIndexBuf : public IndexBuf
	{
	public:
		TIndexBuf(GfxEngine& rGfx, UInt32 nCount, IType* pData = nullptr):
		IndexBuf(rGfx, GfxDataInfo(nCount * sizeof(IType), sizeof(IType), 0, pData, GetSdType<IType>())){}
	};
}
namespace NWG
{
#if (false)
	/// ShaderBuffer class
	/// Description:
	/// -- Is used by shaders as opengl uniform setter, or as directx constant buffer
	class NWG_API ShaderBuf : public TEntity<ShaderBuf>, public AGfxRes
	{
	public:
		ShaderBuf(GfxEngine& rGfx);
		virtual ~ShaderBuf();
		// --getters
		inline const GfxDataInfo& GetInfo() const { return m_gInfo; }
		// --setters
		void SetSubData(Size szData, const Ptr pData, Size szOffset = 0);
		// --core_methods
		virtual void Bind() override;
		void Bind(UInt32 unPoint);
		void Bind(UInt32 unPoint, Size szData, Size szOffset = 0);
		void Remake(const ShaderLayout& rShdLayout);
	private:
		GfxDataInfo m_gInfo;
#if (NWG_GAPI & NWG_GAPI_DX)
		ID3D11Buffer* m_pNative;
#endif
	};
#endif
}
#endif	// NWG_GAPI
#endif	// NWG_BUFFER_H