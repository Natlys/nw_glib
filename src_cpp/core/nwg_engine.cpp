#include <nwg_pch.hpp>
#include "nwg_engine.h"
#if (defined NW_GAPI)
#include <lib/nwg_load.h>
#include <lib/nwg_load_core.h>
#include <lib/nwg_load_fmbuf.h>
#include <lib/nwg_load_buf.h>
#include <lib/nwg_load_layt.h>
#include <lib/nwg_load_txr.h>
#include <lib/nwg_load_smp.h>
#include <lib/nwg_load_shd.h>
#include <lib/nwg_load_mtl.h>
#if (NW_GAPI & NW_GAPI_OGL)
#include <lib/nwg_load_wgl.h>
namespace NW
{
	gfx_engine::gfx_engine(window wnd) :
		m_info(info()), m_config(config()),
		m_wnd(wnd),
		m_device(nullptr), m_context(nullptr),
		m_reg(registry())
	{
		if (m_wnd == nullptr) { throw init_error(__FILE__, __LINE__); return; }
		// get device context of the window;
		// get default device context;
		// only one devic context can be used in a single thread at one time;
		m_device = ::GetWindowDC(m_wnd);
		// setup device pixel format and only then make render context;
		PIXELFORMATDESCRIPTOR pxf_desc{ 0 };
		pxf_desc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pxf_desc.nVersion = 1;
		pxf_desc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
		pxf_desc.iPixelType = PFD_TYPE_RGBA;
		pxf_desc.iLayerType = PFD_MAIN_PLANE;
		pxf_desc.cColorBits = 24;
		pxf_desc.cRedBits = 0; pxf_desc.cGreenBits = 0; pxf_desc.cBlueBits = 0; pxf_desc.cAlphaBits = 0;
		pxf_desc.cRedShift = 0; pxf_desc.cGreenShift = 0; pxf_desc.cBlueShift = 0; pxf_desc.cAlphaShift = 0;
		pxf_desc.cAccumBits = 0;
		pxf_desc.cAccumRedBits = 0; pxf_desc.cAccumGreenBits = 0; pxf_desc.cAccumBlueBits = 0; pxf_desc.cAccumAlphaBits = 0;
		pxf_desc.cAuxBuffers = 0;
		pxf_desc.cDepthBits = 24;
		pxf_desc.cStencilBits = 8;
		pxf_desc.bReserved = 0;
		pxf_desc.dwVisibleMask = 0; pxf_desc.dwLayerMask = 0; pxf_desc.dwDamageMask = 0;
		// get the best availabple pixel format for device context;
		si32 pxl_format = ::ChoosePixelFormat(m_device, &pxf_desc);
		if (pxl_format == 0) { NW_ERR("Failed to get a pixel format"); return; }
		// pixel format can be set to some window only once
		if (!::SetPixelFormat(m_device, pxl_format, &pxf_desc)) { throw init_error(__FILE__, __LINE__); return; }
		::DescribePixelFormat(m_device, pxl_format, pxf_desc.nSize, &pxf_desc);
		// create opengl context and associate that with the device context;
		// it will be attached to the current thread and dc;
		// this is only one current context we can use;
		if (!gfx_open_lib()) { throw init_error(__FILE__, __LINE__); return; }
		m_context = wglCreateContext(m_device);
		wglMakeContextCurrent(m_device, m_context);
		if (!gfx_load_lib()) { throw init_error(__FILE__, __LINE__); return; }

		strcpy(&m_info.renderer[0], &((cstr)glGetString(GL_RENDERER))[0]);
		strcpy(&m_info.version[0], &((cstr)glGetString(GL_VERSION))[0]);
		strcpy(&m_info.vendor[0], &((cstr)glGetString(GL_VENDOR))[0]);
		strcpy(&m_info.shd_language[0], &((cstr)glGetString(GL_SHADING_LANGUAGE_VERSION))[0]);
		std::cout << m_info;
		// also add "GL_MAX_COMBINED_IMAGE_UNITS"
		// and "GL_POINT_SIZE_RANGE" + "GL_POINT_SIZE_GRANUALITY"

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		
		set_primitive(GPT_TRIANGLES);
		set_viewport(0, 0, 800, 600);
	}
	gfx_engine::~gfx_engine()
	{
		// break the connection between our thread and the rendering context;
		wglMakeContextCurrent(NULL, NULL);
		// release the associated dc and delete the rendering context;
		ReleaseDC(m_wnd, m_device);
		// before delete - we need to release that;
		// DeleteDC(m_context);	// delete only created device context;
		// before this call device context must be released or deleted;
		wglDeleteContext(m_context);
		if (!gfx_close_lib()) { quit_error(__FILE__, __LINE__); }
	}
	// --setters
	void gfx_engine::set_viewport(v4si viewport) {
		m_config.viewport = viewport;
		glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
	}
	void gfx_engine::set_viewport(si32 crd_x, si32 crd_y, si32 size_x, si32 size_y) {
		m_config.viewport[0] = crd_x;
		m_config.viewport[1] = crd_y;
		m_config.viewport[2] = size_x;
		m_config.viewport[3] = size_y;
		glViewport(crd_x, crd_y, size_x, size_y);
	}
	void gfx_engine::set_clear_color(f32 red, f32 green, f32 blue, f32 alpha) {
		m_config.clear_color[0] = red;
		m_config.clear_color[1] = green;
		m_config.clear_color[2] = blue;
		m_config.clear_color[3] = alpha;
	};
	void gfx_engine::set_primitive(gfx_primitives primitive_topology) {
		m_config.prim_type = primitive_topology;
	}
	void gfx_engine::set_vsync(bit enable) {
		m_config.swap_interval = enable ? 1u : 0u;
	}
	// --==<core_methods>==--
	void gfx_engine::update()
	{
		SwapBuffers(m_device);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(
			m_config.clear_color[0], m_config.clear_color[1],
			m_config.clear_color[2], m_config.clear_color[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void gfx_engine::del_cmp(ui32 type_id, ui32 cmp_id)
	{
		if (!has_cmp(type_id, cmp_id)) { return; }
		m_reg[type_id].erase(cmp_id);
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	gfx_engine::gfx_engine(window_handle wnd) :
		m_wnd(wnd),
		m_device(nullptr), m_context(nullptr),
		m_reg(registry()),
		m_swap_chain(nullptr), m_draw_target(nullptr)
	{
		if (m_wnd == nullptr) { throw init_error(__FILE__, __LINE__); return; }
		DXGI_SWAP_CHAIN_DESC swap_desc{ 0 };
		swap_desc.BufferDesc.Width = 0;
		swap_desc.BufferDesc.Height = 0;
		//swap_desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		swap_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swap_desc.BufferDesc.RefreshRate.Numerator = 0;
		swap_desc.BufferDesc.RefreshRate.Denominator = 0;
		swap_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swap_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swap_desc.SampleDesc.Count = 1;
		swap_desc.SampleDesc.Quality = 0;
		swap_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_desc.BufferCount = 1;
		swap_desc.OutputWindow = wnd;
		swap_desc.Windowed = TRUE;
		//swap_desc.Windowed = FALSE;
		swap_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swap_desc.Flags = 0;

		if (!gfx_open_lib()) { throw init_error(__FILE__, __LINE__); return; }
		if (!gfx_load_lib()) { throw init_error(__FILE__, __LINE__); return; }
		gfx_new_context_and_swap_chain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG,
			nullptr, NULL, D3D11_SDK_VERSION, &swap_desc, &m_swap_chain, &m_device, nullptr, &m_context);
		if (m_device == nullptr) { throw init_error(__FILE__, __LINE__); }
		if (m_context == nullptr) { throw init_error(__FILE__, __LINE__); }
		if (m_swap_chain == nullptr) { throw init_error(__FILE__, __LINE__); }

		ID3D11Resource* back_buffer = nullptr;
		m_swap_chain->GetBuffer(NULL, __uuidof(ID3D11Resource), reinterpret_cast<ptr*>(&back_buffer));
		m_device->CreateRenderTargetView(back_buffer, nullptr, &m_draw_target);
		m_context->OMSetRenderTargets(1u, &m_draw_target, nullptr);
		
		set_viewport(0, 0, 800, 600);
		set_primitive(GPT_TRIANGLES);
	}
	gfx_engine::~gfx_engine()
	{
		if (m_draw_target != nullptr) { m_draw_target->Release(); }
		if (m_swap_chain != nullptr) { m_swap_chain->Release(); }
		if (m_device != nullptr) { m_device->Release(); }
		if (m_context != nullptr) { m_context->Release(); }
		if (!gfx_close_lib()) { throw quit_error(__FILE__, __LINE__); return; }
	}
	// -- setters
	void gfx_engine::set_viewport(v4si viewport) {
		m_config.viewport = viewport;
		D3D11_VIEWPORT dx_viewport;
		dx_viewport.TopLeftX = viewport[0];
		dx_viewport.TopLeftY = viewport[1];
		dx_viewport.Width = viewport[2];
		dx_viewport.Height = viewport[3];
		dx_viewport.MinDepth = 0.01f;
		dx_viewport.MaxDepth = 1.00f;
		m_context->RSSetViewports(1, &dx_viewport);
	}
	void gfx_engine::set_viewport(si32 crd_x, si32 crd_y, si32 size_x, si32 size_y) {
		m_config.viewport[0] = crd_x;
		m_config.viewport[1] = crd_y;
		m_config.viewport[2] = size_x;
		m_config.viewport[3] = size_y;
		D3D11_VIEWPORT dx_viewport;
		dx_viewport.TopLeftX = crd_x;
		dx_viewport.TopLeftY = crd_y;
		dx_viewport.Width = size_y;
		dx_viewport.Height = size_y;
		dx_viewport.MinDepth = 0.01f;
		dx_viewport.MaxDepth = 1.00f;
		m_context->RSSetViewports(1, &dx_viewport);
	}
	void gfx_engine::set_clear_color(f32 red, f32 green, f32 blue, f32 alpha) {
		m_config.clear_color[0] = red;
		m_config.clear_color[1] = green;
		m_config.clear_color[2] = blue;
		m_config.clear_color[3] = alpha;
	};
	void gfx_engine::set_primitive(gfx_primitives primitive_topology) {
		m_config.prim_type = primitive_topology;
		m_context->IASetPrimitiveTopology(convert_enum<gfx_primitives, D3D11_PRIMITIVE_TOPOLOGY>(primitive_topology));
	}
	void gfx_engine::set_vsync(bit enable) {
		m_config.swap_interval = enable ? 1u : 0u;
	}
	// --==<core_methods>==--
	void gfx_engine::update()
	{
		HRESULT h_result;
		if ((h_result = m_swap_chain->Present(m_config.swap_interval, 0u)) != S_OK) { throw(run_error("something went wrong")); }
		m_context->ClearRenderTargetView(m_draw_target, &m_config.clear_color[0]);
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI