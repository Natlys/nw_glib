#include <nwg_pch.hpp>
#include <nwg_layout.h>
#if(defined NWG_GAPI)
#include <nwg_engine.h>
#include <nwg_loader.h>
#include <nwg_shader.h>
#include <nwg_vtx_buf.h>
#include <nwg_idx_buf.h>
#pragma warning(disable : 4267)
namespace NWG
{
	ShaderBlock::ShaderBlock(const char* sName, UInt8 unBindPoint) :
		strName(""),
		unBindPoint(unBindPoint), szAll(0), szOffset(0) {
		strcpy(strName, sName);
	}
}
namespace NWG
{
	// --setters
	void VertexLayout::SetElements(const DArray<BufElem>& rBufElems) { m_Elems = rBufElems; }
	void VertexLayout::AddElement(const BufElem& rBufElem, Int8 nElems) {
		while (nElems-- > 0) {
			m_Elems.push_back(rBufElem);
			m_Elems.back().unNum = m_Elems.size() - 1;
		}
	}
	void VertexLayout::AddElement(const char* strName, DataTypes sdType, UInt8 unCount, Int8 nElems) {
		AddElement(BufElem(strName, sdType, unCount, false), nElems);
	}
	void VertexLayout::Remake() {
		if (m_Elems.size() == 0) { return; }
		m_szStride = 0;
		for (auto& rBufElem : m_Elems) {
			rBufElem.szOffset = m_szStride;
			m_szStride += DtGetSize(rBufElem.sdType, rBufElem.unCount);
		}
	}
}
namespace NWG
{
	ShaderLayout::ShaderLayout() : m_szData(0) {}
	// --setters
	void ShaderLayout::SetBlocks(const DArray<ShaderBlock>& rBlocks) { m_Blocks = rBlocks; Remake(); }
	void ShaderLayout::AddBlock(const ShaderBlock& rBlock, Int8 nElems) { while (nElems-- > 0) { m_Blocks.push_back(rBlock); } Remake(); }
	void ShaderLayout::Remake() {
		for (UInt8 bi = 0; bi < m_Blocks.size(); bi++) {
			m_szData = 0;
			auto& rBlock = m_Blocks[bi];
			rBlock.unBindPoint = bi;
			rBlock.szOffset = m_szData;
			for (auto& rElem : rBlock.Elems) {
				rElem.szOffset += rBlock.szAll;
				rBlock.szAll += DtGetAlignedSize(rElem.sdType, rElem.unCount);
			}
			m_szData += rBlock.szAll;
		}
	}
}
#if(NWG_GAPI & NWG_GAPI_OGL)
namespace NWG
{
	InputLayout::InputLayout(GfxEngine& rGfx) :
		TEntity(), AGfxRes(rGfx),
		m_pShader(nullptr) { }
	InputLayout::~InputLayout() { if (m_unRId != 0) { glDeleteVertexArrays(1, &m_unRId); m_unRId = 0; } }
	// --setters
	void InputLayout::SetShader(VertexShader* pShader) { m_pShader = pShader; }
	// --core_methods
	void InputLayout::Bind() { glBindVertexArray(m_unRId); }
	bool InputLayout::Remake()
	{
		if (m_pShader == nullptr) { return false; }
		if (m_unRId != 0) { glDeleteVertexArrays(1, &m_unRId); m_unRId = 0; }
		glCreateVertexArrays(1, &m_unRId);
		glBindVertexArray(m_unRId);
		
		auto& rElems = m_pShader->GetVtxLayout().GetElems();
		for (UInt32 bei = 0; bei < rElems.size(); bei++) {
			auto& itElem = rElems[bei];
			UInt32 nCount = 0;
			glEnableVertexAttribArray(itElem.unNum);
			glVertexAttribPointer(itElem.unNum, itElem.unCount * DtGetCount(itElem.sdType), ConvertEnum<DataTypes, UInt32>(itElem.sdType),
				itElem.bNormalized ? GL_TRUE : GL_FALSE, DtGetSize(itElem.sdType, itElem.unCount), reinterpret_cast<Ptr>(itElem.szOffset));
		}
		return true;
	}
}

#endif
#if(NWG_GAPI & NWG_GAPI_DX)
namespace NWG
{
	InputLayout::InputLayout(GfxEngine& rGfx) :
		TEntity(), AGfxRes(rGfx),
		m_pShader(nullptr), m_pNative(nullptr) { }
	InputLayout::~InputLayout() { if (m_pNative != nullptr) { m_pNative->Release(); m_pNative = nullptr; } }
	// --setters
	void InputLayout::SetShader(VertexShader* pShader) { m_pShader = pShader; }
	// --core_methods
	void InputLayout::Bind() { m_pGfx->GetContext()->IASetInputLayout(m_pNative); }
	bool InputLayout::Remake() {
		if (m_pNative != nullptr) { m_pNative->Release(); m_pNative = nullptr; }
		if (m_pShader == nullptr) { return; }
		
		auto& rLayout = m_pShader->GetVtxLayout();
		DArray<D3D11_INPUT_ELEMENT_DESC> dxElems(rLayout.GetElems().size());
		for (UInt32 bei = 0; bei < dxElems.size(); bei++) {
			auto& itElem = rLayout.GetElem(bei);
			auto& dxElem = dxElems[bei];
			dxElem.Format = ConvertEnum<DataTypes, DXGI_FORMAT>(itElem.sdType);
			dxElem.SemanticName = itElem.strName;
			dxElem.SemanticIndex = 0;
			dxElem.InputSlot = itElem.unNum;
			dxElem.AlignedByteOffset = itElem.szOffset;
			dxElem.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			dxElem.InstanceDataStepRate = 0;
		}
		m_pGfx->GetDevice()->CreateInputLayout(&dxElems[0], dxElems.size(),
			m_pShader->GetBlob()->GetBufferPointer(), m_pShader->GetBlob()->GetBufferSize(), &m_pNative);
		if (m_pNative == nullptr) { throw Exception("input layout is null!"); }
		m_pGfx->GetContext()->IASetInputLayout(m_pNative);
	}
}

#endif
#endif	// NWG_GAPI