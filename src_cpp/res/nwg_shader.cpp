#include <nwg_pch.hpp>
#include "nwg_shader.h"
#if (defined NWG_GAPI)
#include <core/nwg_engine.h>
#include <res/nwg_shader_prog.h>
#include <res/nwg_shd_buf.h>
namespace NWG
{
	ShaderInfo::ShaderInfo(GfxApiTypes graphicsApiType, ShaderTypes shaderType, const char* sName, const char* sSourceCode) :
	gapiType(graphicsApiType), shdType(shaderType), strName(sName), strSrc(sSourceCode) { }
	// --operators
	OutStream& ShaderInfo::operator<<(OutStream& rStream) const {
		return rStream <<
			"--==<shader_info>==--" << std::endl <<
			"gapi:" << gapiType <<	";" << std::endl <<
			"type:" << shdType <<	";" << std::endl <<
			"name:" << strName <<	";" << std::endl <<
			"src:" << strSrc <<		";" << std::endl <<
			"--==</shader_info>==--" << std::endl;
	}
	InStream& ShaderInfo::operator>>(InStream& rStream) {
		Char strBuf[256];
		UInt32 unGApi = 0;
		UInt32 unShdType = 0;
		
		rStream.getline(strBuf, 256, ':');
		if (!(rStream >> unGApi)) { throw Exception("invalid format"); }
		rStream.get();
		rStream.getline(strBuf, 256, ':');
		if (!(rStream >> unShdType)) { throw Exception("invalid format"); }
		rStream.get();
		
		rStream.getline(strBuf, 256, ':');
		std::getline(rStream, strName, ';');
		rStream.get();
		rStream.getline(strBuf, 256, ':');
		std::getline(rStream, strSrc, ';');
		rStream.get();
		
		gapiType = static_cast<GfxApiTypes>(unGApi);
		shdType = static_cast<ShaderTypes>(unShdType);
		
		return rStream;
	}
}
#if (NWG_GAPI & NWG_GAPI_OGL)
#include <lib/nwg_ogl_v2.h>
namespace NWG
{
	Shader::Shader(GfxEngine& rGfx, const char* strName, ShaderTypes shdType) :
		AGfxRes(rGfx), ADataRes(strName),
		m_Info{ GAPI_DEFAULT, shdType, strName, "" },
		m_pProg(nullptr) { }
	Shader::~Shader() { if (m_unRId != 0) { glDeleteShader(m_unRId); m_unRId = 0; } }
	// --setters
	void Shader::SetCode(const char* strCode) { m_Info.strSrc = strCode; }
	void Shader::SetProg(ShaderProg* pProg) {
		if (m_unRId == 0) { throw Exception("shader was not created"); }
		if (m_pProg != nullptr) { glDetachShader(m_pProg->GetRenderId(), m_unRId); }
		if ((m_pProg = pProg) != nullptr) { glAttachShader(m_pProg->GetRenderId(), m_unRId); }
	}
	// --==<core_methods>==--
	bool Shader::Remake(const ShaderInfo& rInfo) {
		if (rInfo.gapiType != GAPI_DEFAULT) { return false; }
		if (rInfo.strSrc == "default") { return false; }
		if (rInfo.shdType != GetType()) { return false; }
		SetName(&rInfo.strName[0]);
		
		if (!DataSys::LoadFile(&rInfo.strSrc[0], m_Info.strSrc)) { SetCode(&rInfo.strSrc[0]); }
		return Compile();
	}
	// --==</core_methods>==--

	// --==<data_methods>==--
	bool Shader::SaveF(const char* strFPath)
	{
		StrStream stmFile;
		stmFile << m_Info;

		return DataSys::SaveFile(strFPath, stmFile.str());
	}
	bool Shader::LoadF(const char* strFPath)
	{
		StrStream stmFile;
		if (!DataSys::LoadFile(strFPath, stmFile.str())) { return false; }
		
		ShaderInfo shdInfo;
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
	void VertexShader::OnDraw() {
		m_inLayout.OnDraw();
		for (auto& itBuf : m_Bufs) { itBuf->OnDraw(); }
	}
	bool VertexShader::Compile()
	{
		if (m_unRId != 0) { glDeleteShader(m_unRId); m_unRId = 0; }
		m_unRId = glCreateShader(GL_VERTEX_SHADER);

		if (!CodeProc()) { return false; }
		const char* strSource = &GetCode()[0];
		glShaderSource(m_unRId, 1, &strSource, nullptr);
		glCompileShader(m_unRId);
		glAttachShader(m_pProg == nullptr ? 0 : m_pProg->GetRenderId(), m_unRId);

		return OglErrLogShader(GetType(), m_unRId);
	}
	bool VertexShader::CodeProc() {
		if (m_Info.strSrc.empty() || m_Info.strSrc == "default") { return false; }
		StrStream stmCode(GetCode());
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
					ShaderLayout shdLayout;

					stmCode.seekg(-static_cast<Int32>(strBuf.length()) + nCurr, std::ios_base::cur);
					stmCode >> strBuf;	// read the token ")uniform{"

					stmCode >> strName;	// read the name
					if ((nCurr = strName.find("{")) != -1) {
						if (strName.length() > nCurr) { stmCode.seekg(-static_cast<Int32>(strName.length()), std::ios_base::cur); }
						strName = strName.substr(0, nCurr);
					}
					shdLayout.AddBlock(ShaderBlock(&strName[0], shdLayout.GetBlocks().size()));
					// come back and read the entire uniform block
					stmCode.seekg(-static_cast<Int32>(strBuf.length()) + nCurr, std::ios_base::cur);
					std::getline(stmCode, strBuf, '{');
					std::getline(stmCode, strBuf, '}');
					StrStream stmBlock(strBuf);
					while (stmBlock >> strBuf) {				// read the type
						std::getline(stmBlock, strName, ';');	// read the name
						shdLayout.GetBlocks().back().Elems.push_back(BufElem(&strName[0],
							ConvertEnum<const char*, DataTypes>(&strBuf[0]), nCount, false));
					
						m_Bufs.push_back(RefKeeper<ShaderBuf>());
						m_pGfx->NewRes<ShaderBuf>(m_Bufs.back());
						m_Bufs.back()->SetLayout(shdLayout);
					}
				}
			}
		}
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
	void PixelShader::OnDraw() { for (auto& itBuf : m_Bufs) { itBuf->OnDraw(); } }
	bool PixelShader::Compile()
	{
		if (m_unRId != 0) { glDeleteShader(m_unRId); m_unRId = 0; }
		m_unRId = glCreateShader(GL_FRAGMENT_SHADER);

		if (!CodeProc()) { return false; }
		const char* strSource = &GetCode()[0];
		glShaderSource(m_unRId, 1, &strSource, nullptr);
		glCompileShader(m_unRId);
		glAttachShader(m_pProg == nullptr ? 0 : m_pProg->GetRenderId(), m_unRId);

		return OglErrLogShader(GetType(), m_unRId);
	}
	bool PixelShader::CodeProc() {
		return true;
	}
}
namespace NWG
{
	GeometryShader::GeometryShader(GfxEngine& rGfx, const char* strName) :
		Shader(rGfx, strName, SHD_GEOMETRY) { }
	GeometryShader::~GeometryShader() { }
	// --core_methods
	void GeometryShader::OnDraw() { for (auto& itBuf : m_Bufs) { itBuf->OnDraw(); } }
	bool GeometryShader::Compile()
	{
		if (m_unRId != 0) { glDeleteShader(m_unRId); m_unRId = 0; }
		m_unRId = glCreateShader(GL_FRAGMENT_SHADER);

		if (!CodeProc()) { return false; }
		const char* strSource = &GetCode()[0];
		glShaderSource(m_unRId, 1, &strSource, nullptr);
		glCompileShader(m_unRId);
		glAttachShader(m_pProg == nullptr ? 0 : m_pProg->GetRenderId(), m_unRId);

		return OglErrLogShader(GetType(), m_unRId);
	}
	bool GeometryShader::CodeProc() {
		return true;
	}
}
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
#include <lib/nwg_dx_loader.h>
namespace NWG
{
	Shader::Shader(GfxEngine& rGfx, const char* strName, ShaderTypes sType) :
		TEnt(), AGfxRes(rGfx), ACodeRes(strName),
		m_sType(sType), m_pProg(nullptr), m_shdLayout(ShaderLayout()),
		m_pBlob(nullptr) { }
	Shader::~Shader() { if (m_pBlob != nullptr) { m_pBlob->Release(); m_pBlob = nullptr; } }
	// --setters
	void Shader::SetProg(ShaderProg* pProg) { m_pProg = pProg; }
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
		Shader(rGfx, strName, SHD_VERTEX),
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
		if (m_pBlob != nullptr) { m_pBlob->Release(); m_pBlob = nullptr; }
		
		HRESULT hRes = 0;
		if ((hRes = D3DCompile(
			&m_strCode[0],		// source code
			m_strCode.length(),	// source code length
			NULL,				// source name
			NULL,				// defines
			NULL,				// includes
			"main",				// entry point name
			"vs_4_0",			// target
			0u,					// flags1
			0u,					// flags2
			&m_pBlob,			// where to store the code
			NULL				// blob for error messages
		)) < 0u) { return false; }
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
		Shader(rGfx, strName, SHD_PIXEL),
		m_pNative(nullptr) { }
	PixelShader::~PixelShader() { if (m_pNative != nullptr) { m_pNative->Release(); m_pNative = nullptr; } }
	// --core_methods
	void PixelShader::Bind() { m_pGfx->GetContext()->PSSetShader(m_pNative, NULL, NULL); }
	bool PixelShader::Compile()
	{
		if (m_pNative != nullptr) { m_pNative->Release(); m_pNative = nullptr; }
		if (m_pBlob != nullptr) { m_pBlob->Release(); m_pBlob = nullptr; }

		HRESULT hRes = 0;
		if ((hRes = D3DCompile(
			&m_strCode[0],		// source code
			m_strCode.length(),	// source code length
			NULL,				// source name
			NULL,				// defines
			NULL,				// includes
			"main",				// entry point name
			"ps_4_0",			// target
			0u,					// flags1
			0u,					// flags2
			&m_pBlob,			// where to store the code
			NULL				// blob for error messages
		)) < 0u) {
			return false;
		}
		if (m_pBlob == nullptr) { return false; }

		m_pGfx->GetContext()->PSSetShader(m_pNative, NULL, NULL);
		m_pGfx->GetDevice()->CreatePixelShader(m_pBlob->GetBufferPointer(), m_pBlob->GetBufferSize(), NULL, &m_pNative);
		
		return true;
	}
}
namespace NWG
{
	GeometryShader::GeometryShader(GfxEngine& rGfx, const char* strName) :
		Shader(rGfx, strName, SHD_GEOMETRY) { }
	GeometryShader::~GeometryShader() { }
	// --core_methods
	void GeometryShader::Bind() { for (auto& itBuf : m_Bufs) { itBuf->Bind(); } }
	bool GeometryShader::Compile()
	{
		if (m_unRId != 0) { glDeleteShader(m_unRId); m_unRId = 0; }
		m_unRId = glCreateShader(GL_FRAGMENT_SHADER);

		if (!CodeProc()) { return false; }
		const char* strSource = &m_strCode[0];
		glShaderSource(m_unRId, 1, &strSource, nullptr);
		glCompileShader(m_unRId);
		glAttachShader(m_pProg == nullptr ? 0 : m_pProg->GetRenderId(), m_unRId);

		return OglErrLogShader(m_sType, m_unRId);
	}
	bool GeometryShader::CodeProc() {
		return true;
	}
}
#endif
#endif	// NWG_GAPI