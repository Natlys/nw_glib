#include <glib_pch.hpp>
#include "glib_engine.h"

#include <glib_api.h>

#include <glib_window.h>
#include <glib_framebuf.h>

#include <glib_camera.h>
#include <glib_shader.h>
#include <glib_material.h>
#include <glib_texture.h>

#include <glib_event.h>

#include <stb_image.h>

namespace GLIB
{
	GEngine::GEngine() :
		m_bIsRunning(false),
		m_pGApi(nullptr), m_pWindow(nullptr),
		m_DInfo(GEngineInfo()) { }
	GEngine::~GEngine() {}

	// --setters
	GLayer* GEngine::AddLayer(const char* strName) {
		if (GetLayer(strName) != nullptr) { return nullptr; }
		m_GLayers.push_back(GLayer(strName));
		return &m_GLayers.back();
	}
	void GEngine::RmvLayer(const char* strName){
		Layers::iterator& itDest = FIND_BY_NAME(m_GLayers, GLayer&, strName, .GetName);
		if (itDest != m_GLayers.end()) { return; }
		m_GLayers.erase(itDest);
	}
	void GEngine::ChangeLayerOrder(const char* strName, bool bPushUp) {
		Layers::iterator itLayer = std::find_if(m_GLayers.begin(), m_GLayers.end(),
			[=](GLayer& rObj)->bool {return strcmp(&rObj.GetName()[0], strName) == 0; });
		Layers::iterator itLayerChanged = itLayer;
		if (bPushUp) { std::swap(itLayerChanged, ++itLayer); }
		else { std::swap(itLayerChanged, --itLayer); }
	}
	// --==<core_methods>==--
	bool GEngine::Init(WApiTypes WindowApiType, GApiTypes GraphicsApiType)
	{
		m_bIsRunning = true;

		WindowInfo WindowInfo{ "graphics_engine", 1200, 1200 / 4 * 3, true, nullptr };
		m_pWindow = AWindow::Create(WindowInfo, WindowApiType);
		if (!m_pWindow->Init()) { m_pWindow->OnQuit(); return false; }
		ImageInfo imgInfo;
		if (LoadFImage("D:/dev/native_world/nw_glib/data/ico/nw_bat.png", &imgInfo)) {
			m_pWindow->SetIcon(imgInfo.ClrData, imgInfo.nWidth, imgInfo.nHeight);
			delete[] imgInfo.ClrData;
		}
		m_pWindow->SetEventCallback([this](AEvent& rEvt)->void {
			if (rEvt.EvtType == ET_MOUSE_PRESS) {
				MouseEvent* pmEvt = static_cast<MouseEvent*>(&rEvt);
				switch (pmEvt->nButton) {
				default: break;
				}
			}
			else if (rEvt.EvtType == ET_MOUSE_RELEASE) {
				MouseEvent* pmEvt = static_cast<MouseEvent*>(&rEvt);
				switch (pmEvt->nButton) {
				default: break;
				}
			}
			else if (rEvt.EvtType == ET_KEY_PRESS) {
				KeyboardEvent* pkEvt = static_cast<KeyboardEvent*>(&rEvt);
				switch (pkEvt->unKeyCode) {
				case GLIB_KEY_ESCAPE_27: Quit();
				default: break;
				}
			}
			else if (rEvt.EvtType == ET_KEY_RELEASE) {
				KeyboardEvent* pkEvt = static_cast<KeyboardEvent*>(&rEvt);
				switch (pkEvt->unKeyCode) {
				default: break;
				}
			}
			else if (rEvt.EvtType == ET_WINDOW_CLOSE) { Quit(); }
			else if (rEvt.EvtType == ET_WINDOW_RESIZE) {
				WindowEvent* pwEvt = static_cast<WindowEvent*>(&rEvt);
			}
			else if (rEvt.EvtType == ET_WINDOW_FOCUS) {
				WindowEvent* pwEvt = static_cast<WindowEvent*>(&rEvt);
				if (pwEvt->bIsFocused) { m_pWindow->SetOpacity(1.0f); }
				else { m_pWindow->SetOpacity(0.8f); }
			}
			});

		m_pGApi = AGApi::Create(GraphicsApiType);
		m_pGApi->SetClearColor(0.1f, 0.2f, 0.3f);

		if (!m_bIsRunning) { Quit(); }

		AddLayer("del_default");
		AddLayer("del_lines");
		m_GLayer = m_GLayers.begin();

		return true;
	}
	void GEngine::Quit()
	{
		if (!m_bIsRunning) { return; }
		m_bIsRunning = false;
		
		m_GLayers.clear();
		delete m_pGApi;
		m_pWindow->OnQuit();
		delete m_pWindow;
	}
	void GEngine::Run() {
		m_thrRun = std::thread([this]()->void { while (m_bIsRunning) { Update(); } });
	}
	inline void GEngine::Update()
	{
		m_pWindow->Update();

		m_DInfo.Reset();
		
		for (m_GLayer = m_GLayers.begin(); m_GLayer != m_GLayers.end(); m_GLayer++) { m_GLayer->Update(); }
		m_GLayer = m_GLayers.begin();
	}
	// --==</core_methods>==--

	// --==<data_methods>==--
	bool GEngine::LoadFImage(const char* strFPath, ImageInfo* pImg) {
		UByte* pDataTemp = stbi_load(strFPath, &pImg->nWidth, &pImg->nHeight, &pImg->nChannels, 4);
		if (pDataTemp == nullptr) { return false; }
		pImg->ClrData = pDataTemp;
		return true;
	}
	// --==</data_methods>==--

	// --==<drawing>==--
	void GEngine::DrawCall(DrawTools& rDTools)
	{
		rDTools.pGMtl->Enable();

		rDTools.pShdBuf->SetSubData(rDTools.szShdData, &rDTools.pShdData[0]);
		rDTools.pVtxBuf->SetSubData(rDTools.szVtxData, &rDTools.pVtxData[0]);
		rDTools.pIdxBuf->SetSubData(rDTools.szIdxData, &rDTools.pIdxData[0]);

		rDTools.pShdBuf->SetLayout(rDTools.pGMtl->GetShader()->GetShdLayout());
		rDTools.pVtxBuf->SetLayout(rDTools.pGMtl->GetShader()->GetVertexLayout());
		rDTools.pVtxBuf->Bind();
		rDTools.pIdxBuf->Bind();
		m_pGApi->DrawIndexed(rDTools.szIdxData / sizeof(UInt32));
		rDTools.pIdxBuf->Unbind();
		rDTools.pVtxBuf->Unbind();
		rDTools.pShdBuf->Unbind();

		rDTools.pGMtl->Disable();

		m_DInfo.szShd = m_DInfo.szShd + rDTools.szShdData;
		m_DInfo.szVtx = m_DInfo.szVtx + rDTools.szVtxData;
		m_DInfo.szIdx = m_DInfo.szIdx + rDTools.szIdxData;
		if (m_DInfo.unTex < rDTools.unTexCount) { m_DInfo.unTex = rDTools.unTexCount; }
		m_DInfo.unDrawCalls++;
	}
	// --==<drawing>==--
}

/// OnDraw (AShape)
	/// Description:
	/// -- Shapes have a vertex data, indices and bound AGMaterial
	/// -- GEngine collects all the Vertex and Index data into some arrays from given object
	/// -- AGMaterial of the object provides GEngine's AGMaterial with textures
	/// -- Every new texture from new AGMaterial will be bound to the current GMtl
	/// -- In the EndDraw it will bind all owned textures and will set their samplerIDs to the own shader
	/// -- There is also default white texture which will be used if we don not have other textures