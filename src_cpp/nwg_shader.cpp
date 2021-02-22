#include <nwg_pch.hpp>
#include "nwg_shader.h"
#if (defined NWG_GAPI)
#include <nwg_engine.h>
#include <nwg_shader_prog.h>
#include <nwg_shd_buf.h>
#include <nwg_loader.h>
#if (NWG_GAPI & NWG_GAPI_OGL)
namespace NWG
{
	OutStream& ShaderInfo::operator<<(OutStream& rStream) const {
		return rStream <<
			"--==<shader_info>==--" << std::endl <<
			"name:" << strName << std::endl <<
			"gapi:" << strGApi << std::endl <<
			"type:" << shdType << std::endl <<
			"source:" << strSrc << std::endl <<
			"--==</shader_info>==--" << std::endl;
	}
	InStream& ShaderInfo::operator>>(InStream& rStream) {
		Char strBuf[256];
		UInt32 unShdType;
		rStream.getline(strBuf, 256, ':');
		rStream.getline(strName, 128, ';'); rStream.get();
		rStream.getline(strBuf, 256, ':');
		rStream.getline(strGApi, 16, ';'); rStream.get();
		rStream.getline(strBuf, 256, ':');
		rStream >> unShdType; rStream.get();
		rStream.getline(strBuf, 256, ':');
		rStream.getline(strSrc, 256, ';'); rStream.get();
		shdType = static_cast<ShaderTypes>(unShdType);
		return rStream;
	}
	OutStream& operator<<(OutStream& rStream, const ShaderInfo& rInfo) { return rInfo.operator<<(rStream); }
	InStream& operator>>(InStream& rStream, ShaderInfo& rInfo) { return rInfo.operator>>(rStream); }
}
namespace NWG
{
	Shader::Shader(GfxEngine& rGfx, const char* strName, ShaderTypes sdType) :
		TEntity(), AGfxRes(rGfx), ACodeRes(strName),
		m_sType(sdType), m_pProg(nullptr), m_shdLayout(ShaderLayout()) { }
	Shader::~Shader() { if (m_unRId != 0) { glDeleteShader(m_unRId); m_unRId = 0; } }
	// --setters
	void Shader::SetProg(ShaderProg* pProg) {
		if (m_unRId == 0) { throw Exception("shader was not created"); }
		if (m_pProg != nullptr) { glDetachShader(m_pProg->GetRenderId(), m_unRId); } 
		m_pProg = pProg;
		if (m_pProg != nullptr) { glAttachShader(m_pProg->GetRenderId(), m_unRId); }
	}
	// --==<core_methods>==--
	bool Shader::Remake(const ShaderInfo& rInfo) {
		if (!CStrIsEqual(rInfo.strGApi, "opengl")) { return false; }
		if (CStrIsEqual(rInfo.strSrc, "default")) { return false; }
		if (m_sType != rInfo.shdType) { return false; }
		SetName(&rInfo.strName[0]);
		
		if (!DataSys::LoadFString(rInfo.strSrc, m_strCode)) { return false; }
		return Compile();
	}
	// --==</core_methods>==--
	// --==<data_methods>==--
	bool Shader::SaveF(const char* strFPath)
	{
		ShaderInfo shdInfo{ 0 };
		strcpy_s(shdInfo.strName, 128, &m_strName[0]);
		strcpy_s(shdInfo.strGApi, 16, "opengl");
		shdInfo.shdType = m_sType;
		strcpy_s(shdInfo.strSrc, 256, strFPath);
		
		StrStream stmFile;
		stmFile << shdInfo;

		return DataSys::SaveFString(strFPath, &stmFile.str()[0], stmFile.str().size());
	}
	bool Shader::LoadF(const char* strFPath)
	{
		String strFile = "";
		if (!DataSys::LoadFString(strFPath, strFile)) { return false; }
		StrStream stmFile(strFile);
		
		ShaderInfo shdInfo{ 0 };
		stmFile >> shdInfo;

		return Remake(shdInfo);
	}
	// --==</data_methods>==--
}
namespace NWG
{
	VertexShader::VertexShader(GfxEngine& rGfx, const char* strName) :
		Shader(rGfx, strName, SHD_VERTEX),
		m_inLayout(rGfx) { }
	VertexShader::~VertexShader() { }
	// --core_methods
	void VertexShader::Bind() { m_inLayout.Bind(); }
	bool VertexShader::Compile()
	{
		if (m_unRId != 0) { glDeleteShader(m_unRId); m_unRId = 0; }
		m_unRId = glCreateShader(GL_VERTEX_SHADER);

		if (!CodeProc()) { return false; }
		const char* strSource = &m_strCode[0];
		glShaderSource(m_unRId, 1, &strSource, nullptr);
		glCompileShader(m_unRId);
		glAttachShader(m_pProg == nullptr ? 0 : m_pProg->GetRenderId(), m_unRId);

		return OglErrLogShader(m_sType, m_unRId);
	}
	bool VertexShader::CodeProc() {
		if (m_strCode.empty() || m_strCode == "default") { return false; }
		StrStream stmCode(m_strCode);
		String strBuf = "";
		String strName = "";
		Int32 nCount = 1;
		Int32 nCurr = 0;
		
		while (std::getline(stmCode, strBuf, ' ')) {
			if ((nCurr = strBuf.find("layout")) != -1) {
				// go back to the beginning
				stmCode.seekg(-static_cast<Int32>(strlen(&strBuf[0])), std::ios_base::cur);
				std::getline(stmCode, strBuf, ';');
				if ((nCurr = strBuf.find("in ")) != -1) {
					stmCode.seekg(-static_cast<Int32>(strBuf.length()) + nCurr, std::ios_base::cur);
					stmCode >> strBuf;	// read the token "in "

					stmCode >> strBuf;	// read the type
					std::getline(stmCode, strName, ';');
					m_vtxLayout.AddElement(BufElem(&strName[0], ConvertEnum<const char*, DataTypes>(&strBuf[0]), nCount, false));
				}
				else if ((nCurr = strBuf.find("uniform ")) != -1) {
					stmCode.seekg(-static_cast<Int32>(strBuf.length()) + nCurr, std::ios_base::cur);
					stmCode >> strBuf;	// read the token ")uniform{"

					stmCode >> strName;	// read the name
					if ((nCurr = strName.find("{")) != -1) {
						if (strName.length() > nCurr) { stmCode.seekg(-static_cast<Int32>(strName.length()), std::ios_base::cur); }
						strName = strName.substr(0, nCurr);
					}
					m_shdLayout.AddBlock(ShaderBlock(&strName[0], m_shdLayout.GetBlocks().size()));
					// come back and read the entire uniform block
					stmCode.seekg(-static_cast<Int32>(strBuf.length()) + nCurr, std::ios_base::cur);
					std::getline(stmCode, strBuf, '{');
					std::getline(stmCode, strBuf, '}');
					StrStream stmBlock(strBuf);
					while (stmBlock >> strBuf) {				// read the type
						std::getline(stmBlock, strName, ';');	// read the name
						m_shdLayout.GetBlocks().back().Elems.push_back(BufElem(&strName[0],
							ConvertEnum<const char*, DataTypes>(&strBuf[0]), nCount, false));
					}
				}
			}
		}
		m_vtxLayout.Remake();
		m_shdLayout.Remake();
		m_inLayout.SetShader(this);
		return m_inLayout.Remake();
	}
}
namespace NWG
{
	PixelShader::PixelShader(GfxEngine& rGfx, const char* strName) :
		Shader(rGfx, strName, SHD_PIXEL) { }
	PixelShader::~PixelShader() { }
	// --core_methods
	void PixelShader::Bind() { }
	bool PixelShader::Compile()
	{
		if (m_unRId != 0) { glDeleteShader(m_unRId); m_unRId = 0; }
		m_unRId = glCreateShader(GL_FRAGMENT_SHADER);

		const char* strSource = &m_strCode[0];
		glShaderSource(m_unRId, 1, &strSource, nullptr);
		glCompileShader(m_unRId);
		glAttachShader(m_pProg == nullptr ? 0 : m_pProg->GetRenderId(), m_unRId);

		return OglErrLogShader(m_sType, m_unRId);
	}
}
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
namespace NWG
{
	Shader::Shader(GfxEngine& rGfx, const char* strName, ShaderTypes sdType) :
		TEntity(), AGfxRes(rGfx), ACodeRes(strName),
		m_sdType(sdType), m_pProg(nullptr), m_shdLayout(ShaderLayout()),
		m_pBlob(nullptr) {}
	Shader::~Shader() { if (m_pBlob != nullptr) { m_pBlob->Release(); m_pBlob = nullptr; } }
	// --setters
	void Shader::SetProgram(ShaderProgram* pProg) { m_pProg = pProg; }
	// --data_methods
	bool Shader::SaveF(const char* strFPath)
	{
		return true;
	}
	bool Shader::LoadF(const char* strFPath)
	{
		return true;
	}
}
namespace NWG
{
	VertexShader::VertexShader(GfxEngine& rGfx, const char* strName) :
		Shader(rGfx, strName, ST_VERTEX),
		m_inLayout(InputLayout(rGfx)),
		m_pNative(nullptr) { }
	VertexShader::~VertexShader() { if (m_pNative != nullptr) { m_pNative->Release(); m_pNative = nullptr; } }
	// --core_methods
	void VertexShader::Bind()
	{
		m_pGfx->GetContext()->VSSetShader(m_pNative, NULL, NULL);
		m_inLayout.Bind();
	}
	bool VertexShader::Compile()
	{
		if (m_pNative != nullptr) { m_pNative->Release(); m_pNative = nullptr; }
		
		WChar wstrFPath[256]{ 0 };
		mbstowcs(&wstrFPath[0], &m_strCode[0], 256);
		
		D3DReadFileToBlob(&wstrFPath[0], &m_pBlob);
		if (m_pBlob == nullptr) { return false; }
		m_pGfx->GetDevice()->CreateVertexShader(m_pBlob->GetBufferPointer(), m_pBlob->GetBufferSize(), NULL, &m_pNative);
		
		m_pGfx->GetContext()->VSSetShader(m_pNative, NULL, NULL);
		m_vtxLayout.AddElement(BufElem("vtx_crd", DtGet<V3f>(), 1, false));
		m_vtxLayout.AddElement(BufElem("tex_crd", DtGet<V2f>(), 1, false));
		m_vtxLayout.AddElement(BufElem("nrm_crd", DtGet<V3f>(), 1, false));
		m_inLayout.SetShader(this);
		m_inLayout.Remake();
		
		return true;
	}
}
namespace NWG
{
	PixelShader::PixelShader(GfxEngine& rGfx, const char* strName) :
		Shader(rGfx, strName, ST_PIXEL),
		m_pNative(nullptr) { }
	PixelShader::~PixelShader() { if (m_pNative != nullptr) { m_pNative->Release(); m_pNative = nullptr; } }
	// --core_methods
	void PixelShader::Bind() { m_pGfx->GetContext()->PSSetShader(m_pNative, NULL, NULL); }
	bool PixelShader::Compile()
	{
		if (m_pNative != nullptr) { m_pNative->Release(); m_pNative = nullptr; }
		
		WChar wstrFPath[256]{ 0 };
		mbstowcs(&wstrFPath[0], &m_strCode[0], 256);
		
		D3DReadFileToBlob(&wstrFPath[0], &m_pBlob);
		if (m_pBlob == nullptr) { return false; }
		m_pGfx->GetContext()->PSSetShader(m_pNative, NULL, NULL);
		m_pGfx->GetDevice()->CreatePixelShader(m_pBlob->GetBufferPointer(), m_pBlob->GetBufferSize(), NULL, &m_pNative);
		
		return true;
	}
}
#endif
#endif	// NWG_GAPI