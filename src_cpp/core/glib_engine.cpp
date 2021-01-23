#include <glib_pch.hpp>
#include "core/glib_engine.h"

#include <core/glib_api.h>

#include <glib_framebuf.h>

#include <glib_camera.h>
#include <glib_shader.h>
#include <glib_material.h>
#include <glib_texture.h>

#include <stb_image.h>

#include <../src_glsl/shd_screen.hpp>

namespace GLIB
{
	GEngine::GEngine() :
		m_bIsRunning(false),
		m_pGApi(nullptr), m_pGMtlScreen(nullptr),
		m_DInfo(GEngineInfo()) { }
	GEngine::~GEngine() { }

	// --setters
	GLayer* GEngine::AddLayer(const char* strName) {
		if (GetLayer(strName) != nullptr) { return nullptr; }
		m_GLayers.push_back(GLayer(strName));
		return &m_GLayers.back();
	}
	void GEngine::RmvLayer(const char* strName) {
		Layers::iterator& itDest = std::find_if(m_GLayers.begin(), m_GLayers.end(),
			[=](GLayer& rObj)->bool {return rObj.strName == strName; });
		if (itDest != m_GLayers.end()) { return; }
		m_GLayers.erase(itDest);
	}
	// --==<core_methods>==--
	bool GEngine::Init(Size szMemory)
	{
		GetMemory() = MemArena(malloc(szMemory), szMemory);
		m_bIsRunning = true;

		m_pGApi = AGApi::Create(GAPI_OPENGL);
		m_pGApi->SetClearColor(0.1f, 0.2f, 0.3f);

		if (true) {
			if (!AShader::Create("shd_3d_batch")->LoadF("D:/dev/native_world/nw_glib/src_glsl/shd_3d_batch.glsl")) { Quit(); return false; }
			AShader* pShader = AShader::Create("shd_screen");
			pShader->SetCode(strScreenShaderCode);
			if (!pShader->Compile()) { Quit(); return false; }
		}
		if (true) {
			ATexture2d::Create("tex_white")->LoadF("");
			ImageInfo imgInfo;
			TextureInfo texInfo;
		}
		if (true) {
			GMaterial* pGMtl = nullptr;
			m_pGMtlScreen = pGMtl = new GMaterial("gmt_screen");
			pGMtl->SetShader(ADataRes::GetDataRes<AShader>("shd_screen"));
			pGMtl = new GMaterial("gmt_3d_batch");
			pGMtl->SetShader(ADataRes::GetDataRes<AShader>("shd_3d_batch"));
			pGMtl->SetTexture(ADataRes::GetDataRes<ATexture>("tex_2d_bat"));
		}
		AddLayer("gel_3d_batch");
		m_GLayer = m_GLayers.begin();
		m_GLayer->SetShader(ADataRes::GetDataRes<AShader>("shd_3d_batch"));

		return true;
	}
	void GEngine::Quit()
	{
		if (!m_bIsRunning) { return; }
		m_bIsRunning = false;

		free(GetMemory().GetDataBeg());
		GetMemory() = MemArena(nullptr, 0);

		if (true) {
			delete ADataRes::GetDataRes<GMaterial>("gmt_3d_batch");
		}
		if (true) {
			delete ADataRes::GetDataRes<ATexture>("tex_white");
			delete ADataRes::GetDataRes<ATexture>("tex_2d_batch");
		}
		if (true) {
			delete ADataRes::GetDataRes<AShader>("shd_3d_batch");
		}
		
		m_GLayers.clear();
		delete m_pGApi;
	}
	void GEngine::Run() {
		m_thrRun = std::thread([this]()->void { while (m_bIsRunning) { Update(); } });
	}
	inline void GEngine::Update()
	{
		m_DInfo.Reset();

		std::sort(m_GLayers.begin(), m_GLayers.end());
		for (m_GLayer = m_GLayers.begin(); m_GLayer != m_GLayers.end(); m_GLayer++) {
			if (!m_GLayer->bIsEnabled) { continue; }
			m_GLayer->OnDraw(m_pGApi);
			m_DInfo.szShd = m_DInfo.szShd + m_GLayer->szShdData;
			m_DInfo.szVtx = m_DInfo.szVtx + m_GLayer->szVtxData;
			m_DInfo.szIdx = m_DInfo.szIdx + m_GLayer->szIdxData;
			m_DInfo.unDrawCalls += m_GLayer->unDrawCalls;
		}
		m_GLayer = m_GLayers.begin();
	}
	// --==</core_methods>==--

	// --==<data_methods>==--
	bool GEngine::SaveFImage(const char* strFPath, ImageInfo* pImg) {
		return true;
	}
	bool GEngine::LoadFImage(const char* strFPath, ImageInfo* pImg) {
		UByte* pDataTemp = stbi_load(strFPath, &pImg->nWidth, &pImg->nHeight, &pImg->nChannels, 4);
		if (pDataTemp == nullptr) { return false; }
		pImg->ClrData = pDataTemp;
		return true;
	}
	bool GEngine::SaveFShaderCode(const char* strFPath, AShader* pShader)
	{
		return true;
	}
	bool GEngine::LoadFShaderCode(const char* strFPath, AShader* pShader)
	{
		std::stringstream strStream;
		std::fstream fStream;
		fStream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
		try {
			fStream.open(strFPath);
			strStream << fStream.rdbuf();
			pShader->SetCode(&strStream.str()[0]);
			fStream.close();
		}
		catch (std::exception Ex){
			NWL_ERR(Ex.what());
			return false;
		}
		return true;
	}
	// --==</data_methods>==--
}

/// OnDraw (AShape)
	/// Description:
	/// -- Shapes have a vertex data, indices and bound AGMaterial
	/// -- GEngine collects all the Vertex and Index data into some arrays from given object
	/// -- AGMaterial of the object provides GEngine's AGMaterial with textures
	/// -- Every new texture from new AGMaterial will be bound to the current GMtl
	/// -- In the EndDraw it will bind all owned textures and will set their samplerIDs to the own shader
	/// -- There is also default white texture which will be used if we don not have other textures