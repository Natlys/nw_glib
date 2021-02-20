#include <nwg_pch.hpp>
#include "nwg_buffer.h"
#pragma warning(disable : 4312)
#pragma warning(disable : 4267)
#if (defined NWG_GAPI)
#include <nwg_engine.h>
#include <nwg_loader.h>
#if (NWG_GAPI & NWG_GAPI_OGL)
namespace NWG
{
	VertexBuf::VertexBuf() : TEntity(), AGfxRes(), m_szData(0), m_sdType(SDT_FLOAT32) { }
	VertexBuf::~VertexBuf() { SetData(0, nullptr); }
	// --setters
	void VertexBuf::SetSubData(Size szData, const Ptr pVtxData, Size szOffset) {
		glBufferSubData(GL_ARRAY_BUFFER, szOffset, szData, pVtxData);
	}
	void VertexBuf::SetData(Size szData, const Ptr pVtxData) {
		m_szData = szData;
		if (m_unRId != 0) { glDeleteBuffers(1, &m_unRId); m_unRId = 0; }
		if (szData == 0) { return; }
		glGenBuffers(1, &m_unRId);
		glBindBuffer(GL_ARRAY_BUFFER, m_unRId);
		glBufferData(GL_ARRAY_BUFFER, szData, pVtxData, pVtxData == nullptr ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	}
	void VertexBuf::Bind() {
		glBindBuffer(GL_ARRAY_BUFFER, m_unRId);
	}
}
namespace NWG
{
	IndexBuf::IndexBuf() : TEntity(), AGfxRes(), m_szData(0), m_sdType(SDT_UINT32) { }
	IndexBuf::~IndexBuf() { SetData(0, nullptr); }
	// --setters
	void IndexBuf::SetSubData(Size szData, const Ptr pVtxData, Size szOffset) {
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, szOffset, szData, pVtxData);
	}
	void IndexBuf::SetData(Size szData, const Ptr pVtxData) {
		m_szData = szData;
		if (m_unRId != 0) { glDeleteBuffers(1, &m_unRId); m_unRId = 0; }
		if (szData == 0) { return; }
		glGenBuffers(1, &m_unRId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_unRId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, szData, pVtxData, pVtxData == nullptr ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	}
	void IndexBuf::Bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_unRId);
	}
}
namespace NWG
{
	ShaderBuf::ShaderBuf() : TEntity(), AGfxRes(), m_szData(0), m_sdType(SDT_FLOAT32) { }
	ShaderBuf::~ShaderBuf() { SetData(0, nullptr); }
	// --setters
	void ShaderBuf::SetSubData(Size szData, const Ptr pVtxData, Size szOffset) {
		glBufferSubData(GL_UNIFORM_BUFFER, szOffset, szData, pVtxData);
	}
	void ShaderBuf::SetData(Size szData, const Ptr pVtxData) {
		m_szData = szData;
		if (m_unRId != 0) { glDeleteBuffers(1, &m_unRId); m_unRId = 0; }
		if (szData == 0) { return; }
		glGenBuffers(1, &m_unRId);
		glBindBuffer(GL_UNIFORM_BUFFER, m_unRId);
		glBufferData(GL_UNIFORM_BUFFER, szData, pVtxData, pVtxData == nullptr ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	}
	// --core_methods
	void ShaderBuf::Bind() { glBindBuffer(GL_UNIFORM_BUFFER, m_unRId); }
	void ShaderBuf::Bind(UInt32 unPoint) const { glBindBufferBase(GL_UNIFORM_BUFFER, unPoint, m_unRId); }
	void ShaderBuf::Bind(UInt32 unPoint, Size szData, Size szOffset) const { glBindBufferRange(GL_UNIFORM_BUFFER, unPoint, m_unRId, szOffset, szData); }
	void ShaderBuf::Remake(const ShaderLayout& rBufLayout) {
		if (m_szData < rBufLayout.GetSize()) { SetData(rBufLayout.GetSize()); }
		for (auto& rBlock : rBufLayout.GetBlocks()) { Bind(rBlock.unBindPoint, rBlock.szAll, rBlock.szOffset); }
	}
}
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
namespace NWG
{
	VertexBuf::VertexBuf(GfxEngine& rGfx, GfxDataInfo& rInfo) :
		TEntity(), AGfxRes(rGfx),
		m_gdInfo(rInfo)
	{
		if (m_gdInfo.szData == 0) { throw Exception("buffer without size!", NWL_ERR_NO_DATA, __FILE__, __LINE__); }

		D3D11_BUFFER_DESC bufDesc{ 0 };
		bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufDesc.Usage = rInfo.pData == nullptr ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
		bufDesc.CPUAccessFlags = rInfo.pData == nullptr ? D3D11_CPU_ACCESS_WRITE : 0u;
		bufDesc.MiscFlags = 0u;
		bufDesc.StructureByteStride = rInfo.szStride;
		bufDesc.ByteWidth = rInfo.szData;

		D3D11_SUBRESOURCE_DATA subData{ 0 };
		subData.pSysMem = rInfo.pData;

		rGfx.GetDevice()->CreateBuffer(&bufDesc, &subData, &m_pNative);
		if (m_pNative == nullptr) { throw Exception("Failed to create buffer!"); }
	}
	VertexBuf::~VertexBuf() { if (m_pNative != nullptr) { m_pNative->Release(); m_pNative = nullptr; } }
	// --setters
	void VertexBuf::SetSubData(Size szData, const Ptr pData, Size szOffset) { }
	// --core_methods
	void VertexBuf::Bind() { m_pGfx->GetContext()->IASetVertexBuffers(0, 1, &m_pNative, &m_gdInfo.szStride, &m_gdInfo.szOffset); }
}
namespace NWG
{
	IndexBuf::IndexBuf(GfxEngine& rGfx, GfxDataInfo& rInfo) :
		TEntity(), AGfxRes(rGfx),
		m_gdInfo(rInfo)
	{
		if (m_gdInfo.szData == 0) { throw Exception("buffer without size!", NWL_ERR_NO_DATA, __FILE__, __LINE__); }

		D3D11_BUFFER_DESC bufDesc{ 0 };
		bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufDesc.Usage = rInfo.pData == nullptr ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
		bufDesc.CPUAccessFlags = rInfo.pData == nullptr ? D3D11_CPU_ACCESS_WRITE : 0u;
		bufDesc.MiscFlags = 0u;
		bufDesc.StructureByteStride = rInfo.szStride;
		bufDesc.ByteWidth = rInfo.szData;

		D3D11_SUBRESOURCE_DATA subData{ 0 };
		subData.pSysMem = rInfo.pData;

		rGfx.GetDevice()->CreateBuffer(&bufDesc, &subData, &m_pNative);
		if (m_pNative == nullptr) { throw Exception("Failed to create buffer!"); }
	}
	IndexBuf::~IndexBuf() { if (m_pNative != nullptr) { m_pNative->Release(); m_pNative = nullptr; } }
	// --setters
	void IndexBuf::SetSubData(Size szData, const Ptr pData, Size szOffset) { }
	// --core_methods
	void IndexBuf::Bind() { m_pGfx->GetContext()->IASetIndexBuffer(m_pNative, static_cast<DXGI_FORMAT>(m_gdInfo.sdType), 0); }
}
namespace NWG
{
#if false
	ShaderBuf::ShaderBuf(GfxEngine& rGfx) :
		TEntity(), AGfxRes(rGfx),
		m_gInfo(GfxDataInfo()), m_pNative(nullptr)
	{
		if (m_gInfo.szData == 0) { throw Exception("buffer without size!", NWL_ERR_NO_DATA, __FILE__, __LINE__); }
	}
	ShaderBuf::~ShaderBuf() { if (m_pNative != nullptr) { m_pNative->Release(); } }
	// --setters
	void ShaderBuf::SetSubData(Size szData, const Ptr pVtxData, Size szOffset) {
	}
	// --core_methods
	void ShaderBuf::Bind() {
		m_pGfx->GetContext()->VSSetConstantBuffers(0, 1, &m_pNative);
		m_pGfx->GetContext()->PSSetConstantBuffers(0, 1, &m_pNative);
		m_pGfx->GetContext()->GSSetConstantBuffers(0, 1, &m_pNative);
	}
	void ShaderBuf::Bind(UInt32 unPoint) { }
	void ShaderBuf::Bind(UInt32 unPoint, Size szData, Size szOffset) { }
	void ShaderBuf::Remake(const ShaderLayout& rBufLayout) {
		for (auto& rBlock : rBufLayout.GetBlocks()) { Bind(rBlock.unBindPoint, rBlock.szAll, rBlock.szOffset); }
	}
#endif
}
#endif
#endif	// NWG_GAPI