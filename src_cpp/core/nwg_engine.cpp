#include <nwg_pch.hpp>
#include "nwg_engine.h"
#if (defined NW_GAPI)
#include <nwg.hpp>
// loaders
#include <lib/nwg_load.h>
#include <lib/nwg_load_core.h>
#include <lib/nwg_load_wapi.h>
#include <lib/nwg_load_fmbuf.h>
// other
#include <core/nwg_data.hpp>
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
	gfx_engine::gfx_engine(wndh window) :
		m_wndh(window),
		m_dvch(::GetWindowDC(window)),
		m_ctxh(NULL),
		m_viewport{ 0.0f, 0.0f, 800.0f, 600.0f },
		m_clear_color{ 1.0f, 1.0f, 1.0f, 1.0f },
		m_swap_delay(0u),
		m_prim(convert<primitives, prim>(PRIM_TRIANGLES))
	{
		if (m_wndh == NULL) { throw init_error(__FILE__, __LINE__); return; }
		// get device context of the window;
		// get default device context;
		// only one devic context can be used in a single thread at one time;
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
		v1si pxl_format = ::ChoosePixelFormat(m_dvch, &pxf_desc);
		if (pxl_format == 0) { throw init_error(__FILE__, __LINE__); return; }
		// pixel format can be set to some window only once
		if (!::SetPixelFormat(m_dvch, pxl_format, &pxf_desc)) { throw init_error(__FILE__, __LINE__); return; }
		::DescribePixelFormat(m_dvch, pxl_format, pxf_desc.nSize, &pxf_desc);
		// create opengl context and associate that with the device context;
		// it will be attached to the current thread and dc;
		// this is only one current context we can use;
		if (!gfx_lib_loader::get().load()) { throw init_error(__FILE__, __LINE__); return; }
		m_ctxh = wglCreateContext(m_dvch);
		wglMakeContextCurrent(m_dvch, m_ctxh);
		if (!gfx_lib_loader::get().init()) { throw init_error(__FILE__, __LINE__); return; }

		glDisable(GL_CULL_FACE);
		
		set_swap_delay(0u);
		set_viewport(0, 0, 800, 600);
		set_clear_color(0.3f, 0.3f, 0.3f, 1.0f);
		set_primitive(GPT_TRIANGLES);

		{
			// buffers
			if constexpr (true) {
				mem_ref<buf_shd> sbuf = new_cmp<buf_shd>();
				sbuf->add_elem<v1f>("cst_model", 4 * 4, 0);
				sbuf->add_elem<v1f>("cst_view", 4 * 4, 1);
				sbuf->add_elem<v1f>("cst_proj", 4 * 4, 2);
				if (!sbuf->remake<buf_16f16f16f>(nullptr)) { throw init_error(__FILE__, __LINE__); }
				new_cmp<buf_vtx>(vtx_cube_3f2f3f);
				new_cmp<buf_idx>(idx_cube);
			}
			// samplers
			if constexpr (true) {
				new_cmp<txr_smp>(TXFL_NEAREST, TXW_REPEAT);
				new_cmp<txr_smp>(TXFL_LINEAR, TXW_REPEAT);
			}
			// textures
			if constexpr (true) {
				mem_ref<a_txr> txr;

				txr = new_cmp<a_txr, txr_2d>();
				if (!txr->load_file(R"(data\image\txr_wood_16.bmp)")) { throw init_error(__FILE__, __LINE__); return; }
				txr->set_smp(get_cmp<txr_smp>(0u));
				txr->set_slot(0u);

				txr = new_cmp<a_txr, txr_2d>();
				if (!txr->load_file(R"(data\image\nw_logo.bmp)")) { throw init_error(__FILE__, __LINE__); return; }
				txr->set_smp(get_cmp<txr_smp>(0u));
				txr->set_slot(1u);

				txr = new_cmp<a_txr, txr_2d>();
				if (!txr->load_file(R"(data\image\txr_stone_32.bmp)")) { throw init_error(__FILE__, __LINE__); return; }
				txr->set_smp(get_cmp<txr_smp>(0u));
				txr->set_slot(2u);
			}
			// shaders
			if constexpr (true) {
				{
					new_cmp<a_shd, shd_vtx>(shd_default_3d_vtx)->set_buf(get_cmp<buf_shd>(0u), 0u);
					new_cmp<a_shd, shd_pxl>(shd_default_3d_pxl)->set_txr(get_cmp<a_txr>(0u), 0u);

					new_cmp<a_shd, shd_vtx>(shd_default_3d_vtx)->set_buf(get_cmp<buf_shd>(0u), 0u);
					new_cmp<a_shd, shd_pxl>(shd_default_3d_pxl)->set_txr(get_cmp<a_txr>(1u), 0u);

					new_cmp<a_shd, shd_vtx>(shd_default_3d_vtx)->set_buf(get_cmp<buf_shd>(0u), 0u);
					new_cmp<a_shd, shd_pxl>(shd_default_3d_pxl)->set_txr(get_cmp<a_txr>(2u), 0u);
				}
			}
			// input layouts
			if constexpr (true) {
				new_cmp<shd_layt>(get_cmp<a_shd>(0u), darray<data_elem> {
					data_elem("vti_vtx_crd", NTP_FLOAT32_ARRAY, 3, 0),
						data_elem("vti_txr_crd", NTP_FLOAT32_ARRAY, 2, 1),
						data_elem("vti_nrm_crd", NTP_FLOAT32_ARRAY, 3, 2),
				});
		}
			// materials
			if constexpr (true) {
				mem_ref<gfx_mtl> mtl;

				mtl = new_cmp<gfx_mtl>();

				mtl->add_shd(get_cmp<a_shd>(0u));
				mtl->add_shd(get_cmp<a_shd>(1u));

				if (!mtl->remake()) { throw init_error(__FILE__, __LINE__); return; }

				mtl = new_cmp<gfx_mtl>();

				mtl->add_shd(get_cmp<a_shd>(2u));
				mtl->add_shd(get_cmp<a_shd>(3u));

				if (!mtl->remake()) { throw init_error(__FILE__, __LINE__); return; }

				mtl = new_cmp<gfx_mtl>();

				mtl->add_shd(get_cmp<a_shd>(4u));
				mtl->add_shd(get_cmp<a_shd>(5u));

				if (!mtl->remake()) { throw init_error(__FILE__, __LINE__); return; }
			}
			// states
			if constexpr (true) {
				new_cmp<gfx_stt_ds>(true);
				new_cmp<gfx_stt_ds>(false);
			}
		}
	}
	gfx_engine::~gfx_engine()
	{
		// break the connection between our thread and the rendering context;
		wglMakeContextCurrent(NULL, NULL);
		// release the associated dc and delete the rendering context;
		ReleaseDC(m_wndh, m_dvch);
		// before delete - we need to release that;
		// DeleteDC(m_ctxh);	// delete only created device context;
		// before this call device context must be released or deleted;
		wglDeleteContext(m_ctxh);
		m_ent_reg.clear();
		m_cmp_reg.clear();
		
		gfx_lib_loader::get().free();
		gfx_lib_loader::get().quit();
	}
	// --setters
	void gfx_engine::set_fbuf_size(v1ui size_x, v1ui size_y) {
		//
	}
	void gfx_engine::set_viewport(v4f viewport) {
		m_viewport = viewport;
		glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
	}
	void gfx_engine::set_viewport(v1f crd_x, v1f crd_y, v1f size_x, v1f size_y) {
		m_viewport[0] = crd_x;
		m_viewport[1] = crd_y;
		m_viewport[2] = size_x;
		m_viewport[3] = size_y;
		glViewport(crd_x, crd_y, size_x, size_y);
	}
	void gfx_engine::set_clear_color(v1f red, v1f green, v1f blue, v1f alpha) {
		m_clear_color[0] = red;
		m_clear_color[1] = green;
		m_clear_color[2] = blue;
		m_clear_color[3] = alpha;
	};
	void gfx_engine::set_primitive(prim_type primitive_topology) {
		m_prim_type = primitive_topology;
	}
	void gfx_engine::set_swap_delay(v1ui swap_delay) {
		m_swap_delay = swap_delay;
		wglSwapIntervalEXT(m_swap_delay);
	}
	// --==<core_methods>==--
	void gfx_engine::update()
	{
		::SwapBuffers(m_dvch);
		glClearColor(m_clear_color[0], m_clear_color[1], m_clear_color[2], m_clear_color[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	// --==</core_methods>==--
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
	gfx_engine::gfx_engine(wndh window) :
		m_wndh(window),
		m_dvch(nullptr),
		m_ctxh(nullptr),
		m_viewport{ 0.0f, 0.0f, 800.0f, 600.0f },
		m_clear_color{ 1.0f, 1.0f, 1.0f, 1.0f },
		m_swap_delay(0u),
		m_prim(convert<primitives, prim>(PRIM_TRIANGLES)),
		m_swap_chain(nullptr),
		m_draw_target(nullptr)
	{
		if (m_wndh == nullptr) { throw init_error(__FILE__, __LINE__); return; }
		DXGI_SWAP_CHAIN_DESC swap_desc{ 0 };
		swap_desc.BufferDesc.Width = 0;
		swap_desc.BufferDesc.Height = 0;
		swap_desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		//swap_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swap_desc.BufferDesc.RefreshRate.Numerator = 0;
		swap_desc.BufferDesc.RefreshRate.Denominator = 0;
		swap_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swap_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swap_desc.SampleDesc.Count = 1;
		swap_desc.SampleDesc.Quality = 0;
		swap_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_desc.BufferCount = 1;
		swap_desc.OutputWindow = window;
		swap_desc.Windowed = TRUE;
		//swap_desc.Windowed = FALSE;
		swap_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swap_desc.Flags = 0;

		if (!gfx_lib_loader::get().load()) { throw init_error(__FILE__, __LINE__); return; }
		if (!gfx_lib_loader::get().init()) { throw init_error(__FILE__, __LINE__); return; }
		D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			D3D11_CREATE_DEVICE_DEBUG,
			nullptr,
			0u,
			D3D11_SDK_VERSION,
			&swap_desc,
			&m_swap_chain,
			&m_dvch,
			nullptr,
			&m_ctxh
		);
		if (m_dvch == nullptr) { throw init_error(__FILE__, __LINE__); }
		if (m_ctxh == nullptr) { throw init_error(__FILE__, __LINE__); }
		if (m_swap_chain == nullptr) { throw init_error(__FILE__, __LINE__); }
		// configuration
		if constexpr (true) {
			// other stuff
			if constexpr (true) {
				set_swap_delay(0u);
				set_viewport(0, 0, 800, 600);
				set_fbuf_size(800, 600);
				set_clear_color(0.3f, 0.3f, 0.3f, 1.0f);
				set_prim(PRIM_TRIANGLES);
			}
		}
		// components initialization
		{
			// buffers
			if constexpr (true) {
				mem_ref<buf_shd> sbuf = new_cmp<buf_shd>();
				sbuf->add_elem<v1f>("cst_model", 4 * 4, 0);
				sbuf->add_elem<v1f>("cst_view", 4 * 4, 1);
				sbuf->add_elem<v1f>("cst_proj", 4 * 4, 2);
				if (!sbuf->remake<buf_16f16f16f>(nullptr)) { throw init_error(__FILE__, __LINE__); }
				t_gfx_data<vtx_3f2f3f> cube_data;
				if constexpr (false) {
					darray<vtx_3f2f3f> cube_lt = {
						{ { -0.5f,	-0.5f,	-0.5f },	{ 0.00f,	0.00f },	{ -1.0f,	+0.0f,	+0.0f } },
						{ { -0.5f,	-0.5f,	+0.5f },	{ 0.00f,	1.00f },	{ -1.0f,	+0.0f,	+0.0f } },
						{ { -0.5f,	+0.5f,	+0.5f },	{ 1.00f,	1.00f },	{ -1.0f,	+0.0f,	+0.0f } },
						{ { -0.5f,	+0.5f,	-0.5f },	{ 1.00f,	0.00f },	{ -1.0f,	+0.0f,	+0.0f } },
					};
					cube_data.add_vtx_buf(cube_lt);
					cube_data.update_indices(PRIM_TRIANGLES);
					darray<vtx_3f2f3f> cube_rt = {
						{ { +0.5f,	-0.5f,	-0.5f },	{ 0.00f,	0.00f },	{ +1.0f,	+0.0f,	+0.0f } },
						{ { +0.5f,	-0.5f,	+0.5f },	{ 0.00f,	1.00f },	{ +1.0f,	+0.0f,	+0.0f } },
						{ { +0.5f,	+0.5f,	+0.5f },	{ 1.00f,	1.00f },	{ +1.0f,	+0.0f,	+0.0f } },
						{ { +0.5f,	+0.5f,	-0.5f },	{ 1.00f,	0.00f },	{ +1.0f,	+0.0f,	+0.0f } },
					};
					cube_data.add_vtx_buf(cube_rt);
					cube_data.update_indices(PRIM_TRIANGLES);
					darray<vtx_3f2f3f> cube_bt = {
						{ { -0.5f,	-0.5f,	-0.5f },	{ 0.00f,	0.00f },	{ +0.0f,	-1.0f,	+0.0f } },
						{ { -0.5f,	-0.5f,	+0.5f },	{ 0.00f,	1.00f },	{ +0.0f,	-1.0f,	+0.0f } },
						{ { +0.5f,	-0.5f,	+0.5f },	{ 1.00f,	1.00f },	{ +0.0f,	-1.0f,	+0.0f } },
						{ { +0.5f,	-0.5f,	-0.5f },	{ 1.00f,	0.00f },	{ +0.0f,	-1.0f,	+0.0f } },
					};
					cube_data.add_vtx_buf(cube_bt);
					cube_data.update_indices(PRIM_TRIANGLES);
					darray<vtx_3f2f3f> cube_tp = {
						{ { -0.5f,	+0.5f,	-0.5f },	{ 0.00f,	1.00f },	{ +0.0f,	+1.0f,	+0.0f } },
						{ { -0.5f,	+0.5f,	-0.5f },	{ 0.00f,	1.00f },	{ +0.0f,	+1.0f,	+0.0f } },
						{ { +0.5f,	+0.5f,	+0.5f },	{ 1.00f,	1.00f },	{ +0.0f,	+1.0f,	+0.0f } },
						{ { +0.5f,	-0.5f,	+0.5f },	{ 1.00f,	0.00f },	{ +0.0f,	+1.0f,	+0.0f } },
					};
					cube_data.add_vtx_buf(cube_tp);
					cube_data.update_indices(PRIM_TRIANGLES);
					darray<vtx_3f2f3f> cube_bk = {
						{ { -0.5f,	-0.5f,	-0.5f },	{ 0.00f,	0.00f },	{ +0.0f,	+0.0f,	-1.0f} },
						{ { -0.5f,	+0.5f,	-0.5f },	{ 0.00f,	1.00f },	{ +0.0f,	+0.0f,	-1.0f} },
						{ { +0.5f,	+0.5f,	-0.5f },	{ 1.00f,	1.00f },	{ +0.0f,	+0.0f,	-1.0f} },
						{ { +0.5f,	-0.5f,	-0.5f },	{ 1.00f,	0.00f },	{ +0.0f,	+0.0f,	-1.0f} },
					};
					cube_data.add_vtx_buf(cube_bk);
					cube_data.update_indices(PRIM_TRIANGLES);
				}
				darray<vtx_3f2f3f> cube_ft = {
					{ { -0.5f,	-0.5f,	+0.5f },	{ 0.00f,	0.00f },	{ +0.0f,	+0.0f,	+1.0f } },
					{ { -0.5f,	+0.5f,	+0.5f },	{ 0.00f,	1.00f },	{ +0.0f,	+0.0f,	+1.0f } },
					{ { +0.5f,	+0.5f,	+0.5f },	{ 1.00f,	1.00f },	{ +0.0f,	+0.0f,	+1.0f } },
					{ { +0.5f,	-0.5f,	+0.5f },	{ 1.00f,	0.00f },	{ +0.0f,	+0.0f,	+1.0f } },
				};
				cube_data.add_vtx_buf(cube_ft);
				cube_data.update_indices(PRIM_TRIANGLES);
				
				new_cmp<buf_vtx>(cube_data.get_vtx_buf());
				new_cmp<buf_idx>(cube_data.get_idx_buf());
			}
			// samplers
			if constexpr (true) {
				new_cmp<txr_smp>(TXFL_NEAREST, TXW_REPEAT)->set_slot(0u);
				new_cmp<txr_smp>(TXFL_LINEAR, TXW_REPEAT)->set_slot(0u);
			}
			// textures
			if constexpr (true) {
				mem_ref<a_txr> txr;

				txr = new_cmp<a_txr, txr_2d>();
				if (!txr->load_file(R"(data\image\txr_wood_16.bmp)")) { throw init_error(__FILE__, __LINE__); return; }
				txr->set_smp(get_cmp<txr_smp>(0u));
				txr->set_slot(0u);

				txr = new_cmp<a_txr, txr_2d>();
				if (!txr->load_file(R"(data\image\nw_logo.bmp)")) { throw init_error(__FILE__, __LINE__); return; }
				txr->set_smp(get_cmp<txr_smp>(0u));
				txr->set_slot(0u);

				txr = new_cmp<a_txr, txr_2d>();
				if (!txr->load_file(R"(data\image\txr_stone_32.bmp)")) { throw init_error(__FILE__, __LINE__); return; }
				txr->set_smp(get_cmp<txr_smp>(0u));
				txr->set_slot(0u);
			}
			// shaders
			if constexpr (true) {
				{
					new_cmp<a_shd, shd_vtx>(shd_default_3d_vtx)->set_buf(get_cmp<buf_shd>(0u), 0u);
					new_cmp<a_shd, shd_pxl>(shd_default_3d_pxl)->set_txr(get_cmp<a_txr>(0u), 0u);

					new_cmp<a_shd, shd_vtx>(shd_default_3d_vtx)->set_buf(get_cmp<buf_shd>(0u), 0u);
					new_cmp<a_shd, shd_pxl>(shd_default_3d_pxl)->set_txr(get_cmp<a_txr>(1u), 0u);

					new_cmp<a_shd, shd_vtx>(shd_default_3d_vtx)->set_buf(get_cmp<buf_shd>(0u), 0u);
					new_cmp<a_shd, shd_pxl>(shd_default_3d_pxl)->set_txr(get_cmp<a_txr>(2u), 0u);
				}
			}
			// input layouts
			if constexpr (true) {
				new_cmp<shd_layt>(get_cmp<a_shd>(0u), darray<data_elem> {
					data_elem("vsi_vtx_crd", NTP_FLOAT32, 3, 0),
					data_elem("vsi_txr_crd", NTP_FLOAT32, 2, 1),
					data_elem("vsi_nrm_crd", NTP_FLOAT32, 3, 2),
				});
			}
			// materials
			if constexpr (true) {
				mem_ref<gfx_mtl> mtl;

				mtl = new_cmp<gfx_mtl>();

				mtl->add_shd(get_cmp<a_shd>(0u));
				mtl->add_shd(get_cmp<a_shd>(1u));

				if (!mtl->remake()) { throw init_error(__FILE__, __LINE__); return; }

				mtl = new_cmp<gfx_mtl>();

				mtl->add_shd(get_cmp<a_shd>(2u));
				mtl->add_shd(get_cmp<a_shd>(3u));

				if (!mtl->remake()) { throw init_error(__FILE__, __LINE__); return; }

				mtl = new_cmp<gfx_mtl>();

				mtl->add_shd(get_cmp<a_shd>(4u));
				mtl->add_shd(get_cmp<a_shd>(5u));

				if (!mtl->remake()) { throw init_error(__FILE__, __LINE__); return; }
			}
			// states
			if constexpr (true) {
				mem_ref<gfx_stt_ds> ds;
				ds = new_cmp<gfx_stt_ds>();
				ds->set_func_depth(LOGIC_LESSER);
				ds->set_mask_depth(true);
				if (!ds->remake()) { throw init_error(__FILE__, __LINE__); return; }
				ds = new_cmp<gfx_stt_ds>();
				ds->set_func_depth(LOGIC_DEFAULT);
				ds->set_mask_depth(false);
				if (!ds->remake()) { throw init_error(__FILE__, __LINE__); return; }
			}
		}
	}
	gfx_engine::~gfx_engine()
	{
		if (m_draw_target != nullptr) { m_draw_target->Release(); }
		if (m_swap_chain != nullptr) { m_swap_chain->Release(); }
		if (m_dvch != nullptr) { m_dvch->Release(); }
		if (m_ctxh != nullptr) { m_ctxh->Release(); }
		
		gfx_lib_loader::get().free();
		gfx_lib_loader::get().quit();
	}
	// -- setters
	void gfx_engine::set_fbuf_size(v1ui size_x, v1ui size_y) {
		if (m_draw_target != nullptr) { m_draw_target->Release(); m_draw_target = nullptr; }
		
		m_ctxh->OMSetRenderTargets(0u, nullptr, nullptr);
		ID3D11Resource* back_buf = nullptr;
		m_swap_chain->ResizeBuffers(1u, size_x, size_y, DXGI_FORMAT_UNKNOWN, 0u);
		m_swap_chain->GetBuffer(0u, __uuidof(ID3D11Resource), reinterpret_cast<ptr*>(&back_buf));
		m_dvch->CreateRenderTargetView(back_buf, nullptr, &m_draw_target);
		back_buf->Release();
		if (m_draw_target == nullptr) { throw init_error(__FILE__, __LINE__); return; }
		
		m_ctxh->OMSetRenderTargets(1u, &m_draw_target, nullptr);
	}
	void gfx_engine::set_viewport(v4f viewport) {
		m_viewport = viewport;
		D3D11_VIEWPORT dx_viewport;
		dx_viewport.TopLeftX = -viewport[0] / 2.0f;
		dx_viewport.TopLeftY = -viewport[1] / 2.0f;
		dx_viewport.Width = +viewport[2] / 2.0f;
		dx_viewport.Height = +viewport[3] / 2.0f;
		dx_viewport.MinDepth = 0.01f;
		dx_viewport.MaxDepth = 1.00f;
		m_ctxh->RSSetViewports(1u, &dx_viewport);
	}
	void gfx_engine::set_viewport(v1f crd_x, v1f crd_y, v1f size_x, v1f size_y) {
		if (size_x <= 1.0f || size_y <= 1.0f) { return; }
		m_viewport[0] = crd_x;
		m_viewport[1] = crd_y;
		m_viewport[2] = size_x;
		m_viewport[3] = size_y;
		D3D11_VIEWPORT dx_viewport;
		dx_viewport.TopLeftX = crd_x;
		dx_viewport.TopLeftY = crd_y;
		dx_viewport.Width = size_x;
		dx_viewport.Height = size_y;
		dx_viewport.MinDepth = 0.01f;
		dx_viewport.MaxDepth = 1.00f;
		m_ctxh->RSSetViewports(1u, &dx_viewport);
	}
	void gfx_engine::set_clear_color(v4f clear_color) {
		m_clear_color = clear_color;
	};
	void gfx_engine::set_clear_color(v1f red, v1f green, v1f blue, v1f alpha) {
		m_clear_color[0] = red;
		m_clear_color[1] = green;
		m_clear_color[2] = blue;
		m_clear_color[3] = alpha;
	};
	void gfx_engine::set_prim(primitives primitive) {
		m_prim = convert<primitives, prim>(primitive);
		m_ctxh->IASetPrimitiveTopology(convert<primitives, D3D11_PRIMITIVE_TOPOLOGY>(primitive));
	}
	void gfx_engine::set_swap_delay(v1ui swap_delay) {
		m_swap_delay = swap_delay;
	}
	// --==<core_methods>==--
	void gfx_engine::update()
	{
		HRESULT h_result;
		if ((h_result = m_swap_chain->Present(m_swap_delay, 0u)) != S_OK) { throw(run_error("something went wrong")); return; }
		m_ctxh->ClearRenderTargetView(m_draw_target, &m_clear_color[0]);
	}
	// --==</core_methods>==--
}
#endif
#endif	// NW_GAPI