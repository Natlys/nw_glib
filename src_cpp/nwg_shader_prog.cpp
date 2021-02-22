#include <nwg_pch.hpp>
#include "nwg_shader_prog.h"
#if (defined NWG_GAPI)
#include <nwg_engine.h>
#include <nwg_loader.h>
#include <nwg_shader.h>
#if (NWG_GAPI & NWG_GAPI_OGL)
namespace NWG
{
	OutStream& ShaderProgInfo::operator<<(OutStream& rStream) const {
		return rStream <<
			"--==<shader_program_info>==--" << std::endl <<
			"name:" << &strName[0] << std::endl <<
			"gapi:" << &strGApi[0] << std::endl <<
			"vtx_file:" << &strVtxFile[0] << std::endl <<
			"pxl_file:" << &strPxlFile[0] << std::endl <<
			"gmt_file:" << &strGmtFile[0] << std::endl <<
			"--==</shader_program_info>==--" << std::endl;
	}
	InStream& ShaderProgInfo::operator>>(InStream& rStream) {
		Char strBuf[256];
		rStream.getline(strBuf, 256, ':');
		rStream.getline(&strName[0], 128, ';'); rStream.get();
		rStream.getline(strBuf, 256, ':');
		rStream.getline(&strGApi[0], 8, ';'); rStream.get();
		rStream.getline(strBuf, 256, ':');
		rStream.getline(&strVtxFile[0], 256, ';'); rStream.get();
		rStream.getline(strBuf, 256, ':');
		rStream.getline(&strPxlFile[0], 256, ';'); rStream.get();
		rStream.getline(strBuf, 256, ':');
		rStream.getline(&strGmtFile[0], 256, ';'); rStream.get();
		return rStream;
	}

	OutStream& operator<<(OutStream& rStream, const ShaderProgInfo& rInfo) { return rInfo.operator<<(rStream); }
	InStream& operator>>(InStream& rStream, ShaderProgInfo& rInfo) { return rInfo.operator>>(rStream); }
}
namespace NWG
{
	ShaderProg::ShaderProg(GfxEngine& rGfx, const char* strName) :
		TEntity(), AGfxRes(rGfx), ADataRes(strName) { }
	ShaderProg::~ShaderProg() { if (m_unRId != 0) { glDeleteProgram(m_unRId); m_unRId = 0; } }
	// --setters
	// void ShaderProg::SetBool(const char* name, bool value) const { glUniform1i(GetUniformLoc(name), value); }
	// void ShaderProg::SetInt(const char* name, int value) const { glUniform1i(GetUniformLoc(name), value); }
	// void ShaderProg::SetIntArray(const char* name, Int32* pIntArr, UInt32 unCount) const { glUniform1iv(GetUniformLoc(name), unCount, pIntArr); }
	// void ShaderProg::SetUIntArray(const char* name, UInt32* pUIntArr, UInt32 unCount) const { glUniform1uiv(GetUniformLoc(name), unCount, pUIntArr); }
	// void ShaderProg::SetFloat(const char* name, float value) const { glUniform1f(GetUniformLoc(name), value); }
	// void ShaderProg::SetFloatArray(const char* name, float* pFloatArr, UInt32 unCount) const { glUniform1fv(GetUniformLoc(name), unCount, pFloatArr); }
	// void ShaderProg::SetV2f(const char* name, const V2f& value) const { glUniform2fv(GetUniformLoc(name), 1, &(value[0])); }
	// void ShaderProg::SetV3f(const char* name, const V3f& value) const { glUniform3fv(GetUniformLoc(name), 1, &(value[0])); }
	// void ShaderProg::SetV4f(const char* name, const V4f& value) const { glUniform4fv(GetUniformLoc(name), 1, &(value[0])); }
	// void ShaderProg::SetM4f(const char* name, const Mat4f& value) const { glUniformMatrix4fv(GetUniformLoc(name), 1, GL_FALSE, &value[0][0]); }
	// --==<core_methods>==--
	void ShaderProg::Bind() {
		glUseProgram(m_unRId);
		for (UInt8 bi = 0; bi < m_shdLayout.GetBlocks().size(); bi++) {
			glUniformBlockBinding(m_unRId, bi, m_shdLayout.GetBlock(bi).unBindPoint);
		}
		for (auto& itShd : m_Shaders) { itShd->Bind(); }
	}
	bool ShaderProg::Remake(const ShaderProgInfo& rInfo)
	{
		if (m_unRId != 0) { glDeleteShader(m_unRId); m_unRId = 0; }
		m_unRId = glCreateProgram();
		m_Shaders.clear();

		if (!CStrIsEqual(&rInfo.strGApi[0], "opengl")) { throw Exception("wrong shader structure!"); }
		SetName(&rInfo.strName[0]);

		if (!CStrIsEqual(rInfo.strVtxFile, "default")) {
			m_Shaders.push_back(RefKeeper<Shader>());
			m_pGfx->CreateRes<Shader, VertexShader>(m_Shaders.back(), &m_strName[0]);
			if (!m_Shaders.back()->LoadF(rInfo.strVtxFile)) { throw Exception("shader was not loaded"); }
			m_Shaders.back()->SetProg(this);
		}
		if (!CStrIsEqual(rInfo.strPxlFile, "default")) {
			m_Shaders.push_back(RefKeeper<Shader>());
			m_pGfx->CreateRes<Shader, PixelShader>(m_Shaders.back(), &m_strName[0]);
			if (!m_Shaders.back()->LoadF(rInfo.strPxlFile)) { throw Exception("shader was not loaded"); }
			m_Shaders.back()->SetProg(this);
		}
		if (!CStrIsEqual(rInfo.strGmtFile, "default")) {
			//m_Shaders.push_back(RefKeeper<Shader>());
			//m_pGfx->CreateRes<Shader, GeometryShader>(m_Shaders.back(), &m_strName[0]);
			//m_Shaders.back()->SetProg(this);
			//if (!m_Shaders.back()->LoadF(rInfo.strGmtFile)) { throw Exception("shader was not loaded"); }
		}

		glLinkProgram(m_unRId);
		return (OglErrLogShader(SHD_SHADER, m_unRId));
	}
	// --==</core_methods>==--
		// --==<data_methods>==--
	bool ShaderProg::SaveF(const char* strFPath)
	{
		ShaderProgInfo spInfo{ 0 };
		strcpy_s(&spInfo.strName[0], 128, &m_strName[0]);
		strcpy_s(&spInfo.strGApi[0], 16, "directx");
		strcpy_s(&spInfo.strVtxFile[0], 256, "default");
		strcpy_s(&spInfo.strPxlFile[0], 256, "default");
		strcpy_s(&spInfo.strGmtFile[0], 256, "default");

		StrStream stmFile;
		stmFile << spInfo;

		return DataSys::SaveFString(strFPath, &stmFile.str()[0], stmFile.str().size());
	}
	bool ShaderProg::LoadF(const char* strFPath)
	{
		String strFile = "";
		if (!DataSys::LoadFString(strFPath, strFile)) { throw(Exception("failed to load a shader")); }
		StrStream stmFile(strFile);

		ShaderProgInfo spInfo{ 0 };
		stmFile >> spInfo;

		return Remake(spInfo);
	}
	// --==</data_methods>==--

	// --==<implementation_methods>==-
	Int32 ShaderProg::GetBlockIdx(const char* strName) const {
		for (auto& itBlk : m_Blocks) { if (strcmp(itBlk.first.c_str(), strName) == 0) { return itBlk.second; } }
		Int32 nIdx = glGetUniformBlockIndex(m_unRId, &strName[0]);
		m_Blocks[strName] = nIdx;
		return nIdx;
	}
	// --==</implementation_methods>==--
}
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
namespace NWG
{
	ShaderProg::ShaderProg(GfxEngine& rGfx, const char* strName) :
		TEntity(), AGfxRes(rGfx), ADataRes(strName),
		m_shdLayout(ShaderLayout()) {  }
	ShaderProg::~ShaderProg() { Remake(); }
	// --==<core_methods>==--
	void ShaderProg::Bind() {
		for (auto& itShader : m_Shaders) {
			itShader->Bind();
		}
	}
	void ShaderProg::Remake()
	{
		m_shdLayout.Remake();
		m_Shaders.clear();
	}
	// --==</core_methods>==--
	// --==<data_methods>==--
	bool ShaderProg::SaveF(const char* strFPath)
	{
		ShaderProgInfo spInfo{ 0 };
		strcpy_s(&spInfo.strName[0], 128, &m_strName[0]);
		strcpy_s(&spInfo.strGApi[0], 16, "directx");

		StrStream stmFile;
		stmFile << spInfo;
		
		return DataSys::SaveFString(strFPath, &stmFile.str()[0], stmFile.str().size());
	}
	bool ShaderProg::LoadF(const char* strFPath)
	{
		String strFile = "";
		if (!DataSys::LoadFString(strFPath, strFile)) { throw(Exception("failed to load a shader")); }
		StrStream stmFile(strFile);
		
		ShaderProgInfo spInfo{ 0 };
		stmFile >> spInfo;

		return Remake(spInfo);
	}
	// --==</data_methods>==--
}
#endif
#endif	// NWG_GAPI