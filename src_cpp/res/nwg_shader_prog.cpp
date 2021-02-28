#include <nwg_pch.hpp>
#include "nwg_shader_prog.h"
#if (defined NWG_GAPI)
#include <core/nwg_engine.h>
#include <res/nwg_shader.h>
namespace NWG {
	OutStream& ShaderProgInfo::operator<<(OutStream& rStream) const {
		return rStream <<
			"--==<shader_program_info>==--" << std::endl <<
			"gapi:" << gapiType <<		";" << std::endl <<
			"name:" << strName <<		";" << std::endl <<
			"src_vtx:" << strSrcVtx <<	";" << std::endl <<
			"src_pxl:" << strSrcPxl <<	";" << std::endl <<
			"src_gmt:" << strSrcGmt <<	";" << std::endl <<
			"--==</shader_program_info>==--" << std::endl;
	}
	InStream& ShaderProgInfo::operator>>(InStream& rStream) {
		Char strBuf[256];
		UInt32 unGfxApi = 0;
		
		rStream.getline(strBuf, 256, ':');
		if (!(rStream >> unGfxApi)) { throw Exception("invalid format"); }
		rStream.get();
		
		rStream.getline(strBuf, 256, ':');
		std::getline(rStream, strName, ';');
		rStream.get();
		rStream.getline(strBuf, 256, ':');
		std::getline(rStream, strSrcVtx, ';');
		rStream.get();
		rStream.getline(strBuf, 256, ':');
		std::getline(rStream, strSrcPxl, ';');
		rStream.get();
		rStream.getline(strBuf, 256, ':');
		std::getline(rStream, strSrcGmt, ';');
		rStream.get();
		
		gapiType = static_cast<GfxApiTypes>(unGfxApi);

		return rStream;
	}
}
#if (NWG_GAPI & NWG_GAPI_OGL)
#include <lib/nwg_ogl_v2.h>
#include <lib/nwg_ogl_arb.h>
namespace NWG {
	ShaderProg::ShaderProg(GfxEngine& rGfx, const char* strName) :
		AGfxRes(rGfx), ADataRes(strName) { }
	ShaderProg::~ShaderProg() { if (m_unRId != 0) { glDeleteProgram(m_unRId); m_unRId = 0; } }
	// --setters
	template<> void ShaderProg::SetValue<Int32>(UInt32 unIdx, const Int32& rData) { glUniform1i(unIdx, rData); }
	template<> void ShaderProg::SetValue<Mat4f>(UInt32 unIdx, const Mat4f& rData) { glUniform4fv(unIdx, 1, &rData[0][0]); }
	// --==<core_methods>==--
	void ShaderProg::OnDraw() {
		glUseProgram(m_unRId);
		for (UInt8 bi = 0; bi < m_shdLayout.GetBlocks().size(); bi++) {
			glUniformBlockBinding(m_unRId, bi, m_shdLayout.GetBlock(bi).unBindPoint);
		}
		for (auto& itShd : m_Shaders) { itShd->OnDraw(); }
	}
	bool ShaderProg::Remake(const ShaderProgInfo& rInfo)
	{
		if (m_unRId != 0) { glDeleteShader(m_unRId); m_unRId = 0; }
		m_unRId = glCreateProgram();
		m_Shaders.clear();

		if (rInfo.gapiType != GAPI_OPENGL) { throw Exception("wrong shader structure!"); }
		SetName(&rInfo.strName[0]);

		ShaderInfo shdInfo;
		shdInfo.gapiType = GAPI_OPENGL;
		if (rInfo.strSrcVtx != "default") {
			m_Shaders.push_back(RefKeeper<Shader>());
			m_pGfx->NewRes<Shader, VertexShader>(m_Shaders.back(), "shd_vtx");
			if (!DataSys::LoadFile(&rInfo.strSrcVtx[0], shdInfo)) { return false; }
			if (!m_Shaders.back()->Remake(shdInfo)) { throw Exception("shader was not loaded"); }
			m_Shaders.back()->SetProg(this);
		}
		if (rInfo.strSrcVtx != "default") {
			m_Shaders.push_back(RefKeeper<Shader>());
			m_pGfx->NewRes<Shader, PixelShader>(m_Shaders.back(), "shd_pxl");
			if (!DataSys::LoadFile(&rInfo.strSrcPxl[0], shdInfo)) { return false; }
			if (!m_Shaders.back()->Remake(shdInfo)) { throw Exception("shader was not loaded"); }
			m_Shaders.back()->SetProg(this);
		}
		if (rInfo.strSrcGmt != "default" && false) {
			m_Shaders.push_back(RefKeeper<Shader>());
			m_pGfx->NewRes<Shader, GeometryShader>(m_Shaders.back(), "shd_gmt");
			m_Shaders.back()->SetProg(this);
			shdInfo.shdType = SHD_GEOMETRY;
			if (!DataSys::LoadFile(&rInfo.strSrcGmt[0], shdInfo)) { return false; }
			if (!m_Shaders.back()->Remake(shdInfo)) { throw Exception("shader was not loaded"); }
		}

		glLinkProgram(m_unRId);
		return (OglErrLogShader(SHD_PROG, m_unRId));
	}
	// --==</core_methods>==--
		// --==<data_methods>==--
	bool ShaderProg::SaveF(const char* strFPath)
	{
		ShaderProgInfo spInfo;

		spInfo.gapiType = GAPI_OPENGL;
		spInfo.strName = m_strName;
		if (auto pShd = GetShader(SHD_VERTEX)) { spInfo.strSrcVtx = pShd->GetCode(); }
		if (auto pShd = GetShader(SHD_PIXEL)) { spInfo.strSrcPxl = pShd->GetCode(); }
		if (auto pShd = GetShader(SHD_GEOMETRY)) { spInfo.strSrcGmt = pShd->GetCode(); }

		StrStream stmFile;
		stmFile << spInfo;

		return DataSys::SaveFile(strFPath, stmFile.str());
	}
	bool ShaderProg::LoadF(const char* strFPath)
	{
		if (!DataSys::LoadFile(strFPath, m_Info)) { throw(Exception("failed to load a shader")); }
		return Remake(m_Info);
	}
	// --==</data_methods>==--

	// --==<implementation_methods>==-
	Int32 ShaderProg::GetBlockIdx(const char* strName) {
		for (auto& itBlk : m_Blocks) { if (strcmp(itBlk.first.c_str(), strName) == 0) { return itBlk.second; } }
		Int32 nIdx = glGetUniformBlockIndex(m_unRId, &strName[0]);
		m_Blocks[strName] = nIdx;
		return nIdx;
	}
	// --==</implementation_methods>==--
}
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
#include <lib/nwg_dx_loader.h>
namespace NWG {
	ShaderProg::ShaderProg(GfxEngine& rGfx, const char* strName) :
		TEnt(), AGfxRes(rGfx), ADataRes(strName),
		m_shdLayout(ShaderLayout()) {  }
	ShaderProg::~ShaderProg() { }
	// --==<core_methods>==--
	void ShaderProg::Bind() {
		for (auto& itShader : m_Shaders) {
			itShader->Bind();
		}
	}
	bool ShaderProg::Remake(const ShaderProgInfo& rInfo)
	{
		return false;
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