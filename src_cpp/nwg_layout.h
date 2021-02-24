#ifndef NWG_LAYOUT_H
#define NWG_LAYOUT_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <nwg_res.h>
#include <nwg_tools.h>
namespace NWG
{
	/// BufElem structure
	/// --Contains all relevant data for shader usage of vertex buffer data
	struct NWG_API BufElem
	{
	public:
		Char strName[128] = "default";
		DataTypes sdType = DT_DEFAULT;
		UInt32 unCount = 0;
		UInt32 unNum = 0;
		Size szOffset = 0;
		Bit bNormalized = false;
	public:
		BufElem() { }
		BufElem(const char* sName, DataTypes dataType, UInt32 Count, bool Normalized) :
			strName(""), sdType(dataType),
			unCount(Count), bNormalized(Normalized), szOffset(0) {
			strcpy(strName, sName);
		}
	};
	struct NWG_API ShaderBlock
	{
	public:
		Char strName[128];
		UInt8 unBindPoint;
		DArray<BufElem> Elems;
		Size szOffset;
		Size szAll;
	public:
		ShaderBlock() = default;
		ShaderBlock(const char* sName, UInt8 unBindPoint);
	};
}

namespace NWG
{
	/// VertexLayout class
	class NWG_API VertexLayout
	{
	public:
		// --getters
		inline const Size GetStride() const { return m_szStride; }
		inline BufElem& GetElem(UInt8 nIdx) { return m_Elems[nIdx]; }
		inline DArray<BufElem>& GetElems() { return m_Elems; }
		// --setters
		void SetElements(const DArray<BufElem>& rBufElems);
		void AddElement(const BufElem& rBufElem, Int8 nElems = 1);
		void AddElement(const char* strName, DataTypes sdType, UInt8 unCount, Int8 nElems = 1);
		// --core_methods
		void Remake();
	private:
		Size m_szStride;
		DArray<BufElem> m_Elems;
	};
	/// ShaderLayout class
	class NWG_API ShaderLayout
	{
	public:
		ShaderLayout();
		// --getters
		inline Size GetDataSize() const { return m_szData; }
		inline ShaderBlock& GetBlock(UInt8 unIdx = 0) { return m_Blocks.at(unIdx); }
		inline DArray<ShaderBlock>& GetBlocks() { return m_Blocks; }
		// --setters
		void SetBlocks(const DArray<ShaderBlock>& rBlocks);
		void AddBlock(const ShaderBlock& rBlock, Int8 nElems = 1);
		void Remake();
	private:
		Size m_szData;
		DArray<ShaderBlock> m_Blocks;
	};
}

namespace NWG
{
	/// InputLayout class
	/// Description:
	/// --default input assembler tool for vertex shaders;
	/// --equivalent to the vertex array in opengl;
	class NWG_API InputLayout : public TEntity<InputLayout>, public AGfxRes
	{
	public:
		InputLayout(GfxEngine& rGfx);
		virtual ~InputLayout();
		// --getters
		inline VertexShader* GetShader() { return m_pShader; }
		// --setters
		void SetShader(VertexShader* pShader);
		// --core_methods
		virtual void Bind() override;
		bool Remake();
	private:
		VertexShader* m_pShader;
#if (NWG_GAPI & NWG_GAPI_DX)
		ID3D11InputLayout* m_pNative;
#endif
	};
}
#endif	// NWG_GAPI
#endif	// NWG_LAYOUT_H