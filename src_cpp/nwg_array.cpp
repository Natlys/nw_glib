#include <nwg_pch.hpp>
#include "nwg_array.h"
#if (defined NWG_GAPI)
#include <nwg_engine.h>
#include <nwg_loader.h>
#include <nwg_layout.h>
#pragma warning(disable:4267)
#if (NWG_GAPI & NWG_GAPI_OGL)
namespace NWG
{
	VertexArr::VertexArr(GfxEngine& rGfx) :
		TEntity(), AGfxRes(rGfx), m_gpType(GPT_TRIANGLES) { glCreateVertexArrays(1, &m_unRId); }
	VertexArr::~VertexArr() { glDeleteVertexArrays(1, &m_unRId); }
	// --setters
	// --==<core_methods>==--
	void VertexArr::Bind() {
		glBindVertexArray(m_unRId);
	}
	void VertexArr::CreateVtxBuffer(Size szData, Ptr pData)
	{
	}
	void VertexArr::CreateIdxBuffer(Size szData, Ptr pData)
	{
	}
	// --==</core_methods>==--
	// --==<implementation_methods>==--
	// --==</implementation_methods>==--
}
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
namespace NWG
{
	VertexArr::VertexArr(GfxEngine& rGfx) :
		TEntity(), AGfxRes(rGfx),
		m_gpType(GPT_DEFAULT), m_idxBuf(nullptr) { }
	VertexArr::~VertexArr() { while (!m_vtxBufs.empty()) { RmvVtxBuf(); } RmvIdxBuf(); }
	// --setters
	void VertexArr::AddVtxBuf(const GfxDataInfo& rInfo) {
		m_vtxBufs.push_back(nullptr);
		m_vtxInfo.push_back(rInfo);
		
		D3D11_BUFFER_DESC bufDesc = { 0 };
		bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufDesc.Usage = rInfo.pData == nullptr ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
		bufDesc.CPUAccessFlags = rInfo.pData == nullptr ? D3D11_CPU_ACCESS_WRITE : 0u;
		bufDesc.MiscFlags = NULL;
		bufDesc.ByteWidth = rInfo.szData;
		bufDesc.StructureByteStride = rInfo.szStride;

		D3D11_SUBRESOURCE_DATA subData = { 0 };
		subData.pSysMem = rInfo.pData;

		m_pGfx->GetDevice()->CreateBuffer(&bufDesc, &subData, &m_vtxBufs.back());
	}
	void VertexArr::RmvVtxBuf(UInt32 nIdx) {
		if (m_vtxBufs[nIdx] != nullptr) { m_vtxBufs[nIdx]->Release(); }
		m_vtxBufs.erase(m_vtxBufs.begin() + nIdx);
		m_vtxInfo.erase(m_vtxInfo.begin() + nIdx);
	}
	void VertexArr::AddIdxBuf(const GfxDataInfo& rInfo) {
		RmvIdxBuf();
		m_idxInfo = rInfo;

		D3D11_BUFFER_DESC bufDesc = { 0 };
		bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufDesc.Usage = rInfo.pData == nullptr ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
		bufDesc.CPUAccessFlags = rInfo.pData == nullptr ? D3D11_CPU_ACCESS_WRITE : 0;
		bufDesc.MiscFlags = NULL;
		bufDesc.ByteWidth = rInfo.szData;
		bufDesc.StructureByteStride = rInfo.szStride;

		D3D11_SUBRESOURCE_DATA subData = { 0 };
		subData.pSysMem = rInfo.pData;

		m_pGfx->GetDevice()->CreateBuffer(&bufDesc, &subData, &m_idxBuf);
	}
	void VertexArr::RmvIdxBuf() { if (m_idxBuf != nullptr) { m_idxBuf->Release(); m_idxBuf = nullptr;  } }
	// --==<core_methods>==--
	void VertexArr::Bind() {
		m_pGfx->GetContext()->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(m_gpType));
		if (m_vtxBufs.size() > 0) {
			for (auto& itInfo : m_vtxInfo) {
				m_pGfx->GetDrawInfo().szVtx += itInfo.szData;
				m_pGfx->GetDrawInfo().unVtx += itInfo.szData / itInfo.szStride;
			}
			m_pGfx->GetContext()->IASetVertexBuffers(0, m_vtxBufs.size(), &m_vtxBufs[0], &m_vtxInfo[0].szStride, &m_vtxInfo[0].szOffset);
		}
		if (m_idxBuf != nullptr) {
			m_pGfx->GetDrawInfo().szIdx += m_idxInfo.szData;
			m_pGfx->GetDrawInfo().unIdx += m_idxInfo.szData / m_idxInfo.szStride;
			m_pGfx->GetContext()->IASetIndexBuffer(m_idxBuf, static_cast<DXGI_FORMAT>(m_idxInfo.sdType), 0);
		}
	}
	// --==</core_methods>==--
}
#endif
#endif	// NWG_GAPI