#include <nwg_pch.hpp>
#include "nwg_imgui.h"
#if (defined NW_OS && defined NW_GAPI)
#include "imgui_core.hpp"
#include <lib/nwg_load_core.h>
#include <lib/nwg_load_wgl.h>
#include <lib/nwg_load_txr.h>
#include <lib/nwg_load_smp.h>
#include <lib/nwg_load_fmbuf.h>
#include <lib/nwg_load_buf.h>
#include <lib/nwg_load_layt.h>
#include <lib/nwg_load_shd.h>
#include <lib/nwg_load_mtl.h>
namespace NW
{
    // data
    imgui_io* s_imgui_io = NULL;
    imgui_platform_io* s_platform_io = NULL;
    imgui_style* s_imgui_style = NULL;
    bit s_is_dockspace_enabled = TRUE;
    // getters
    // setters
    extern NW_API void imgui_set_mouse_enabled(bit enable);
    extern NW_API void imgui_set_dockspace_enabled(bit enable);
    // core_functions
    extern NW_API bit imgui_init(window_handle window, device_handle device, context_handle context);
    extern NW_API void imgui_quit();
    extern NW_API void imgui_begin_frame();
    extern NW_API void imgui_end_frame();
}
namespace NW
{
    extern bit drawer_init(device_handle device, context_handle context);
    extern void drawer_quit();
    extern void drawer_update(imgui_draw_data* draw_data);
    // getters
    // setters
    extern void drawer_set_wnd_size(imgui_viewport* viewport, ImVec2 size);
    // core_methods
    extern void drawer_create_wnd(imgui_viewport* viewport);
    extern void drawer_delete_wnd(imgui_viewport* viewport);
    extern void drawer_update_wnd(imgui_viewport* viewport, ptr draw_arg);
    extern void drawer_swap_buffers(imgui_viewport* viewport, ptr draw_arg);
}
namespace NW
{
    extern bit platform_init(window_handle window);
    extern void platform_quit();
    extern void platform_update();
    // getters
    extern ImVec2 platform_get_wnd_coord(imgui_viewport* viewport);
    extern ImVec2 platform_get_wnd_size(imgui_viewport* viewport);
    extern bit platform_get_wnd_focus(imgui_viewport* viewport);
    extern bit platform_get_wnd_minimized(imgui_viewport* viewport);
    // setters
    extern void platform_set_wnd_coord(imgui_viewport* viewport, ImVec2 coord);
    extern void platform_set_wnd_size(imgui_viewport* viewport, ImVec2 size);
    extern void platform_set_wnd_focus(imgui_viewport* viewport);
    extern void platform_set_wnd_title(imgui_viewport* viewport, cstr title);
    extern void platform_set_wnd_alpha(imgui_viewport* viewport, f32 alpha);
    // core_methods
    extern void platform_create_wnd(imgui_viewport* viewport);
    extern void platform_delete_wnd(imgui_viewport* viewport);
    extern void platform_show_wnd(imgui_viewport* viewport);
    extern void platform_update_wnd(imgui_viewport* viewport);
}
#if (defined NW_GAPI)
#if (NW_GAPI & NW_GAPI_OGL)
namespace NW
{
    // types
    struct ogl_viewport_data
    {
    };
    struct ogl_context_state
    {
    };
    // data
    static device_handle s_device = NULL;
    static context_handle s_context = NULL;
    static GLuint s_txr_font = 0;
    static GLuint s_shd_prog = 0, s_shd_vtx = 0, s_shd_pxl = 0;
    static GLint s_unf_loc_txr = 0, s_unf_loc_proj = 0;
    static GLuint s_atb_loc_vtx_crd = 0, s_atb_loc_txr_crd = 0, s_atb_loc_vtx_clr = 0;
    static GLuint s_vbuf = 0, s_ibuf = 0;
    static const GLchar* vtx_src_with_ver[2] = { "#version 130",
"uniform mat4 ProjMtx;\n"
"in vec2 Position;\n"
"in vec2 UV;\n"
"in vec4 Color;\n"
"out vec2 Frag_UV;\n"
"out vec4 Frag_Color;\n"
"void main()\n"
"{\n"
"    Frag_UV = UV;\n"
"    Frag_Color = Color;\n"
"    gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
"}\n" };
    const GLchar* pxl_src_with_ver[2] = { "#version 130",
"uniform sampler2D Texture;\n"
"in vec2 Frag_UV;\n"
"in vec4 Frag_Color;\n"
"out vec4 Out_Color;\n"
"void main()\n"
"{\n"
"    Out_Color = Frag_Color * texture(Texture, Frag_UV.st);\n"
"}\n" };
    // functions
    extern void drawer_update_state(imgui_draw_data* draw_data, si32 fmbuf_size_x, si32 fmbuf_size_y, GLuint varr);
}
namespace NW
{
    bit drawer_init(device_handle device, context_handle context)
    {
        if (s_device != nullptr || s_context != nullptr) { return false; }
        s_device = device; s_context = context;
        // setup back-end capabilities flags
        {
            s_imgui_io->BackendRendererName = "nwg_open_gl";
            s_imgui_io->BackendFlags |= ImGuiBackendFlags_RendererHasViewports;
            if (s_imgui_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                // set 1 of 5 platform_io functions;
                //s_platform_io->Renderer_CreateWindow = drawer_create_wnd;
                //s_platform_io->Renderer_DestroyWindow = drawer_delete_wnd;
                s_platform_io->Renderer_RenderWindow = drawer_update_wnd;
                //s_platform_io->Renderer_SetWindowSize = drawer_set_wnd_size;
                //s_platform_io->Renderer_SwapBuffers = drawer_swap_buffers;
            }
        }
        // create graphics resources
        {
            // save open_gl state
            GLint last_txr; glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_txr);
            GLint last_vbuf; glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_vbuf);
            GLint last_varr; glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_varr);
            // vertex shader
            s_shd_vtx = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(s_shd_vtx, 2, vtx_src_with_ver, NULL);
            glCompileShader(s_shd_vtx);
            // pixel shader
            s_shd_pxl = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(s_shd_pxl, 2, pxl_src_with_ver, NULL);
            glCompileShader(s_shd_pxl);
            // shader program
            s_shd_prog = glCreateProgram();
            glAttachShader(s_shd_prog, s_shd_vtx);
            glAttachShader(s_shd_prog, s_shd_pxl);
            glLinkProgram(s_shd_prog);
            // get program attribute and uniform locations
            s_unf_loc_txr = glGetUniformLocation(s_shd_prog, "Texture");
            s_unf_loc_proj = glGetUniformLocation(s_shd_prog, "ProjMtx");
            s_atb_loc_vtx_crd = static_cast<GLuint>(glGetAttribLocation(s_shd_prog, "Position"));
            s_atb_loc_txr_crd = static_cast<GLuint>(glGetAttribLocation(s_shd_prog, "UV"));
            s_atb_loc_vtx_clr = static_cast<GLuint>(glGetAttribLocation(s_shd_prog, "Color"));
            // create buffers
            glGenBuffers(1, &s_vbuf);
            glGenBuffers(1, &s_ibuf);
            // build texture atlas
            imgui_io& io = GUI::GetIO();
            ubyte* pxl_data = NULL;
            si32 size_x = 0, size_y = 0;
            // load as rgba 32-bit (75% of the memory is wasted, but default font is so small)
            // because it is more likely to be compatible with user's existing shaders.
            // if your ImTextureId represent a higher-level concept than just a gl texture id,
            // consider calling GetTexDataAsAlpha8() instead to save on gpu memory.
            io.Fonts->GetTexDataAsRGBA32(&pxl_data, &size_x, &size_y);
            // save open_gl state
            // upload texture to graphics system
            glGenTextures(1, &s_txr_font);
            glBindTexture(GL_TEXTURE_2D, s_txr_font);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size_x, size_y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pxl_data);
            // set this font to gui state
            io.Fonts->TexID = reinterpret_cast<imgui_txr_id>(static_cast<intptr_t>(s_txr_font));
            // restore modified open_gl state
            glBindTexture(GL_TEXTURE_2D, last_txr);
            glBindBuffer(GL_ARRAY_BUFFER, last_vbuf);
            glBindVertexArray(last_varr);
        }

        return true;
    }
    void drawer_quit()
    {
        if (s_device == nullptr || s_context == nullptr) { return; }
        s_device = nullptr; s_context = nullptr;
        {
            if (s_vbuf != 0) { glDeleteBuffers(1, &s_vbuf); s_vbuf = 0; }
            if (s_ibuf != 0) { glDeleteBuffers(1, &s_ibuf); s_ibuf = 0; }
            if (s_shd_prog != 0 && s_shd_vtx != 0) { glDetachShader(s_shd_prog, s_shd_vtx); }
            if (s_shd_prog != 0 && s_shd_pxl != 0) { glDetachShader(s_shd_prog, s_shd_pxl); }
            if (s_shd_vtx != 0) { glDeleteShader(s_shd_vtx); s_shd_vtx = 0; }
            if (s_shd_pxl != 0) { glDeleteShader(s_shd_pxl); s_shd_pxl = 0; }
            if (s_shd_prog != 0) { glDeleteProgram(s_shd_prog); s_shd_prog = 0; }
            if (s_txr_font != 0) {
                glDeleteTextures(1, &s_txr_font);
                s_imgui_io->Fonts->TexID = 0;
                s_txr_font = 0;
            }
        }
    }
    void drawer_update(imgui_draw_data* draw_data)
    {
        // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
        si32 fmbuf_size_x = static_cast<si32>(draw_data->DisplaySize.x * draw_data->FramebufferScale.x);
        si32 fmbuf_size_y = static_cast<si32>(draw_data->DisplaySize.y * draw_data->FramebufferScale.y);
        if (fmbuf_size_x <= 0 || fmbuf_size_y <= 0) { return; }

        // backup gl state
        GLenum last_active_txr; glGetIntegerv(GL_ACTIVE_TEXTURE, (GLint*)&last_active_txr);
        GLuint last_shd_prog; glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)&last_shd_prog);
        GLuint last_bound_txr; glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint*)&last_bound_txr);
        GLuint last_sampler; glGetIntegerv(GL_SAMPLER_BINDING, (GLint*)&last_sampler);
        GLuint last_varr; glGetIntegerv(GL_ARRAY_BUFFER_BINDING, (GLint*)&last_varr);
        GLuint nLastVtxArr; glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint*)&nLastVtxArr);
        GLint nLastPolyMode[2]; glGetIntegerv(GL_POLYGON_MODE, nLastPolyMode);
        GLint last_viewport[4]; glGetIntegerv(GL_VIEWPORT, last_viewport);
        GLint last_scissor_box[4]; glGetIntegerv(GL_SCISSOR_BOX, last_scissor_box);
        GLenum last_blend_src_rgb; glGetIntegerv(GL_BLEND_SRC_RGB, (GLint*)&last_blend_src_rgb);
        GLenum last_blend_dst_rgb; glGetIntegerv(GL_BLEND_DST_RGB, (GLint*)&last_blend_dst_rgb);
        GLenum last_blend_src_aplha; glGetIntegerv(GL_BLEND_SRC_ALPHA, (GLint*)&last_blend_src_aplha);
        GLenum last_blend_dst_alpha; glGetIntegerv(GL_BLEND_DST_ALPHA, (GLint*)&last_blend_dst_alpha);
        GLenum last_blend_eq_rgb; glGetIntegerv(GL_BLEND_EQUATION_RGB, (GLint*)&last_blend_eq_rgb);
        GLenum last_blend_eq_alpha; glGetIntegerv(GL_BLEND_EQUATION_ALPHA, (GLint*)&last_blend_eq_alpha);
        GLboolean last_blend = glIsEnabled(GL_BLEND);
        GLboolean last_culling = glIsEnabled(GL_CULL_FACE);
        GLboolean last_depth_test = glIsEnabled(GL_DEPTH_TEST);
        GLboolean last_scissor_test = glIsEnabled(GL_SCISSOR_TEST);

        // setup desired open_gl state
        // recreate the vao every time (this is to easily allow multiple open_gl contexts
        // to be rendered to vao that are not shared among open_gl contexts;
        // the renderer would actually work without any vao bound,
        // but then our VertexAttrib calls would overwrite the default one currently bound
        GLuint varr = 0;
        glGenVertexArrays(1, &varr);
        drawer_update_state(draw_data, fmbuf_size_x, fmbuf_size_y, varr);
        // will project scissor/clipping rectangles into framebuffer space
        // (0,0) unless using multi-viewports
        ImVec2 clip_off = draw_data->DisplayPos;
        // (1,1) unless using retina display which are often (2,2)
        ImVec2 clip_scale = draw_data->FramebufferScale;
        // render command lists
        glActiveTexture(GL_TEXTURE0);
        for (ui16 icmd = 0; icmd < draw_data->CmdListsCount; icmd++) {
            const imgui_draw_list* cmd_list = draw_data->CmdLists[icmd];

            // upload vertex/index buffers
            glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)cmd_list->VtxBuffer.Size * (int)sizeof(ImDrawVert),
                (const GLvoid*)cmd_list->VtxBuffer.Data, GL_STREAM_DRAW);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)cmd_list->IdxBuffer.Size * (int)sizeof(ImDrawIdx),
                (const GLvoid*)cmd_list->IdxBuffer.Data, GL_STREAM_DRAW);

            for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++) {
                const imgui_draw_cmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
                if (pcmd->UserCallback != NULL) {
                    // user callback, registered via imgui_draw_list::AddCallback()
                    // (ImDrawCallback_ResetRenderState is a special callback value
                    // used by the user to request the renderer to reset render state.)
                    if (pcmd->UserCallback == ImDrawCallback_ResetRenderState) {
                        drawer_update_state(draw_data, fmbuf_size_x, fmbuf_size_y, varr);
                    }
                    else { pcmd->UserCallback(cmd_list, pcmd); }
                }
                else {
                    // project scissor/clipping rectangles into framebuffer space
                    ImVec4 clip_rect;
                    clip_rect.x = (pcmd->ClipRect.x - clip_off.x) * clip_scale.x;
                    clip_rect.y = (pcmd->ClipRect.y - clip_off.y) * clip_scale.y;
                    clip_rect.z = (pcmd->ClipRect.z - clip_off.x) * clip_scale.x;
                    clip_rect.w = (pcmd->ClipRect.w - clip_off.y) * clip_scale.y;
                    if (clip_rect.x < fmbuf_size_x && clip_rect.y < fmbuf_size_y
                        && clip_rect.z >= 0.0f && clip_rect.w >= 0.0f) {
                        // apply scissor/clipping rectangle
                        glScissor(static_cast<GLint>(clip_rect.x), static_cast<GLint>(fmbuf_size_y - clip_rect.w), static_cast<GLint>(clip_rect.z - clip_rect.x), static_cast<GLint>(clip_rect.w - clip_rect.y));
                        // bind texture, draw
                        glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(reinterpret_cast<intptr_t>(pcmd->TextureId)));
                        glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount,
                            sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT,
                            (void*)(intptr_t)(pcmd->IdxOffset * sizeof(ImDrawIdx)));
                    }
                }
            }
        }
        // destroy the temporary vao
        glDeleteVertexArrays(1, &varr);
        // restore modified gl state
        glUseProgram(last_shd_prog);
        glBindTexture(GL_TEXTURE_2D, last_bound_txr);
#ifdef GL_SAMPLER_BINDING
        glBindSampler(0, last_sampler);
#endif
        glActiveTexture(last_bound_txr);
#ifndef IMGUI_IMPL_OPENGL_ES2
        glBindVertexArray(nLastVtxArr);
#endif
        glBindBuffer(GL_ARRAY_BUFFER, last_varr);
        glBlendEquationSeparate(last_blend_eq_rgb, last_blend_eq_alpha);
        glBlendFuncSeparate(last_blend_src_rgb, last_blend_dst_rgb, last_blend_src_aplha, last_blend_dst_alpha);
        if (last_blend) glEnable(GL_BLEND); else glDisable(GL_BLEND);
        if (last_culling) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
        if (last_depth_test) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
        if (last_scissor_test) glEnable(GL_SCISSOR_TEST); else glDisable(GL_SCISSOR_TEST);
#ifdef GL_POLYGON_MODE
        glPolygonMode(GL_FRONT_AND_BACK, (GLenum)nLastPolyMode[0]);
#endif
        glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]);
        glScissor(last_scissor_box[0], last_scissor_box[1], (GLsizei)last_scissor_box[2], (GLsizei)last_scissor_box[3]);
    }
    void drawer_update_state(imgui_draw_data* draw_data, si32 fmbuf_size_x, si32 fmbuf_size_y, GLuint varr)
    {
        // setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled, polygon fill
        glEnable(GL_BLEND);
        glBlendEquation(GL_FUNC_ADD);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_SCISSOR_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // support for gl 4.5 rarely used glClipControl(GL_UPPER_LEFT)
        bit clip_lower_left = true;
        // setup viewport, orthographic projection matrix
        // our visible imgui space lies from draw_data->DisplayPos (top left)
        // to draw_data->DisplayPos+data_data->DisplaySize (bottom right).
        // DisplayPos is (0,0) for single viewport apps.
        glViewport(0, 0, static_cast<GLsizei>(fmbuf_size_x), static_cast<GLsizei>(fmbuf_size_y));
        f32 lft = draw_data->DisplayPos.x;
        f32 rht = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
        f32 top = draw_data->DisplayPos.y;
        f32 bot = draw_data->DisplayPos.y + draw_data->DisplaySize.y;
        if (!clip_lower_left) { f32 tmp = top; top = bot; bot = tmp; } // swap top and bottom if origin is upper left
        const m4f32 projection = {
            { +2.0f / (rht - lft),           +0.0f,                       +0.0f,          +0.0f },
            { +0.0f,                         +2.0f / (top - bot),         +0.0f,          +0.0f },
            { +0.0f,                         +0.0f,                       -1.0f,          +0.0f },
            { (rht + lft) / (lft - rht),    (top + bot) / (bot - top),    +0.0f,          +1.0f },
        };
        glUseProgram(s_shd_prog);
        glUniform1i(s_unf_loc_txr, 0);
        glUniformMatrix4fv(s_unf_loc_proj, 1, GL_FALSE, &projection[0][0]);
        glBindSampler(0, 0); // we use combined texture/sampler state. Applications using gl 3.3 may set that otherwise.
        (void)varr;
        glBindVertexArray(varr);
        // bind vertex/index buffers and setup attributes for ImDrawVert
        glBindBuffer(GL_ARRAY_BUFFER, s_vbuf);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_ibuf);
        glEnableVertexAttribArray(s_atb_loc_vtx_crd);
        glEnableVertexAttribArray(s_atb_loc_txr_crd);
        glEnableVertexAttribArray(s_atb_loc_vtx_clr);
        glVertexAttribPointer(s_atb_loc_vtx_crd, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, pos));
        glVertexAttribPointer(s_atb_loc_txr_crd, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, uv));
        glVertexAttribPointer(s_atb_loc_vtx_clr, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, col));
    }
}
namespace NW
{
    void drawer_update_wnd(imgui_viewport* viewport, ptr draw_arg)
    {
        if (!(viewport->Flags & imgui_viewportFlags_NoRendererClear)) {
            ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
        }
        drawer_update(viewport->DrawData);
    }
    void drawer_swap_buffers(imgui_viewport* viewport, ptr draw_arg)
    {
        ogl_viewport_data* data = reinterpret_cast<ogl_viewport_data*>(viewport->RendererUserData);
        ::SwapBuffers(s_device);
    }
}
#endif
#if (NW_GAPI & NW_GAPI_DX)
namespace NW
{
    // types
    struct vsbuf_m16f { f32 mdl_view_proj[4][4]; };
    struct dx_viewport_data
    {
    public:
        IDXGISwapChain* SwapChain;
        ID3D11RenderTargetView* RTView;
    public:
        dx_viewport_data() { SwapChain = NULL; RTView = NULL; }
        ~dx_viewport_data() { IM_ASSERT(SwapChain == NULL && RTView == NULL); }
    };
    struct dx_context_state
    {
        UINT                        ScissorRectsCount, ViewportsCount;
        D3D11_RECT                  ScissorRects[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
        D3D11_VIEWPORT              Viewports[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
        ID3D11RasterizerState* RS;
        ID3D11BlendState* BlendState;
        FLOAT                       BlendFactor[4];
        UINT                        SampleMask;
        UINT                        StencilRef;
        ID3D11DepthStencilState* DepthStencilState;
        ID3D11ShaderResourceView* PSShaderResource;
        ID3D11SamplerState* PSSampler;
        ID3D11PixelShader* PS;
        ID3D11VertexShader* VS;
        ID3D11GeometryShader* GS;
        UINT                        PSInstancesCount, VSInstancesCount, GSInstancesCount;
        ID3D11ClassInstance* PSInstances[256], * VSInstances[256], * GSInstances[256];   // 256 is max according to PSSetShader documentation
        D3D11_PRIMITIVE_TOPOLOGY    PrimitiveTopology;
        ID3D11Buffer* IndexBuffer, * VertexBuffer, * VSConstantBuffer;
        UINT                        IndexBufferOffset, VertexBufferStride, VertexBufferOffset;
        DXGI_FORMAT                 IndexBufferFormat;
        ID3D11InputLayout* input_layout;
    };
    // data
    static ID3D11Device* s_device = NULL;
    static ID3D11DeviceContext* s_context = NULL;
    static IDXGIFactory* s_factory = NULL;
    static ID3D11Buffer* s_vbuf = NULL;
    static ID3D11Buffer* s_ibuf = NULL;
    static ID3D11Buffer* s_vsbuf = NULL;
    static ID3D11VertexShader* s_vshd = NULL;
    static ID3D11PixelShader* s_pshd = NULL;
    static ID3D11InputLayout* s_layout = NULL;
    static ID3D11SamplerState* s_fnt_smp = NULL;
    static ID3D11ShaderResourceView* s_fnt_view = NULL;
    static ID3D11RasterizerState* s_rst_state = NULL;
    static ID3D11BlendState* s_blend_state = NULL;
    static ID3D11DepthStencilState* s_dpt_stc_state = NULL;
    static si32 s_vtx_size = 5000, s_idx_size = 10000;
    static cstr vshd_src_code =
        "cbuffer vertexBuffer : register(b0) \
            {\
              float4x4 ProjectionMatrix; \
            };\
            struct VS_INPUT\
            {\
              float2 pos : POSITION;\
              float4 col : COLOR0;\
              float2 uv  : TEXCOORD0;\
            };\
            \
            struct PS_INPUT\
            {\
              float4 pos : SV_POSITION;\
              float4 col : COLOR0;\
              float2 uv  : TEXCOORD0;\
            };\
            \
            PS_INPUT main(VS_INPUT input)\
            {\
              PS_INPUT output;\
              output.pos = mul( ProjectionMatrix, float4(input.pos.xy, 0.f, 1.f));\
              output.col = input.col;\
              output.uv  = input.uv;\
              return output;\
            }";
    static cstr pshd_src_code =
        "struct PS_INPUT\
            {\
            float4 pos : SV_POSITION;\
            float4 col : COLOR0;\
            float2 uv  : TEXCOORD0;\
            };\
            sampler sampler0;\
            Texture2D texture0;\
            \
            float4 main(PS_INPUT input) : SV_Target\
            {\
            float4 out_col = input.col * texture0.Sample(sampler0, input.uv); \
            return out_col; \
            }";
    // functions
    extern void drawer_update_state(imgui_draw_data* draw_data, context_handle context);
}
namespace NW
{
    bit drawer_init(device_handle device, context_handle context)
    {
        if (s_device != nullptr || s_context != nullptr) { return false; }
        s_device = device; s_context = context;
        // setup backend capabilities flags
        {
            s_imgui_io->BackendRendererName = "nwg_directx";
            s_imgui_io->BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;  // we can honor the imgui_draw_cmd::VtxOffset field, allowing for large meshes;
            s_imgui_io->BackendFlags |= ImGuiBackendFlags_RendererHasViewports;  // we can create multi-viewports on the renderer side (optional);
            if (s_imgui_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                // set 5 of 5 functions of imgui platform interface;
                imgui_platform_io& platform_io = GUI::GetPlatformIO();
                platform_io.Renderer_CreateWindow = drawer_create_wnd;
                platform_io.Renderer_DestroyWindow = drawer_delete_wnd;
                platform_io.Renderer_RenderWindow = drawer_update_wnd;
                platform_io.Renderer_SetWindowSize = drawer_set_wnd_size;
                platform_io.Renderer_SwapBuffers = drawer_swap_buffers;
            }
        }
        // get factory from device
        {
            IDXGIDevice* dxgi_device = NULL;
            IDXGIAdapter* dxgi_adapter = NULL;
            IDXGIFactory* dxgi_factory = NULL;

            if (device->QueryInterface(IID_PPV_ARGS(&dxgi_device)) == S_OK) {
                if (dxgi_device->GetParent(IID_PPV_ARGS(&dxgi_adapter)) == S_OK) {
                    if (dxgi_adapter->GetParent(IID_PPV_ARGS(&dxgi_factory)) == S_OK) {
                        s_device = device;
                        s_context = context;
                        s_factory = dxgi_factory;
                    }
                }
            }
            if (dxgi_device != nullptr) { dxgi_device->Release(); }
            if (dxgi_adapter != nullptr) { dxgi_adapter->Release(); }
            s_device->AddRef();
            s_context->AddRef();
        }
        // create graphics resources
        {
            // create vertex shader
            {
                ID3DBlob* vshd_bin_code;
                if (FAILED(D3DCompile(
                    vshd_src_code,
                    strlen(vshd_src_code),
                    NULL, NULL, NULL,
                    "main", "vs_4_0",
                    0u, 0u,
                    &vshd_bin_code, NULL))) {
                    return false;
                }
                if (s_device->CreateVertexShader(vshd_bin_code->GetBufferPointer(), vshd_bin_code->GetBufferSize(), NULL, &s_vshd) != S_OK)
                {
                    vshd_bin_code->Release();
                    return false;
                }
                // create the input layout
                D3D11_INPUT_ELEMENT_DESC local_layout[] = {
                    { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT,   0, (UINT)IM_OFFSETOF(ImDrawVert, pos), D3D11_INPUT_PER_VERTEX_DATA, 0 },
                    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,   0, (UINT)IM_OFFSETOF(ImDrawVert, uv),  D3D11_INPUT_PER_VERTEX_DATA, 0 },
                    { "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, (UINT)IM_OFFSETOF(ImDrawVert, col), D3D11_INPUT_PER_VERTEX_DATA, 0 },
                };
                if (s_device->CreateInputLayout(local_layout, 3, vshd_bin_code->GetBufferPointer(), vshd_bin_code->GetBufferSize(), &s_layout) != S_OK)
                {
                    vshd_bin_code->Release();
                    return false;
                }
                vshd_bin_code->Release();
                // create the constant buffer
                {
                    D3D11_BUFFER_DESC desc;
                    desc.ByteWidth = sizeof(vsbuf_m16f);
                    desc.Usage = D3D11_USAGE_DYNAMIC;
                    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
                    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
                    desc.MiscFlags = 0;
                    s_device->CreateBuffer(&desc, NULL, &s_vsbuf);
                }
            }
            // create pixel shader
            {
                ID3DBlob* pshd_bin_code;
                if (FAILED(D3DCompile(
                    pshd_src_code, strlen(pshd_src_code),
                    NULL, NULL, NULL,
                    "main", "ps_4_0",
                    0u, 0u, &pshd_bin_code, NULL))) {
                    return false;
                }
                if (s_device->CreatePixelShader(pshd_bin_code->GetBufferPointer(), pshd_bin_code->GetBufferSize(), NULL, &s_pshd) != S_OK) {
                    pshd_bin_code->Release();
                    return false;
                }
                pshd_bin_code->Release();
            }
            // create blending setup
            {
                D3D11_BLEND_DESC desc;
                ZeroMemory(&desc, sizeof(desc));
                desc.AlphaToCoverageEnable = false;
                desc.RenderTarget[0].BlendEnable = true;
                desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
                desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
                desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
                desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
                desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
                desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
                desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
                s_device->CreateBlendState(&desc, &s_blend_state);
            }
            // create rasterizer state
            {
                D3D11_RASTERIZER_DESC desc;
                ZeroMemory(&desc, sizeof(desc));
                desc.FillMode = D3D11_FILL_SOLID;
                desc.CullMode = D3D11_CULL_NONE;
                desc.ScissorEnable = true;
                desc.DepthClipEnable = true;
                s_device->CreateRasterizerState(&desc, &s_rst_state);
            }
            // create depth-stencil State
            {
                D3D11_DEPTH_STENCIL_DESC desc;
                ZeroMemory(&desc, sizeof(desc));
                desc.DepthEnable = false;
                desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
                desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
                desc.StencilEnable = false;
                desc.FrontFace.StencilFailOp = desc.FrontFace.StencilDepthFailOp = desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
                desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
                desc.BackFace = desc.FrontFace;
                s_device->CreateDepthStencilState(&desc, &s_dpt_stc_state);
            }
            // create font texture
            {
                imgui_io& io = GUI::GetIO();
                unsigned char* pixels;
                int width, height;
                io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
                // create texture and it's view
                {
                    D3D11_TEXTURE2D_DESC desc;
                    ZeroMemory(&desc, sizeof(desc));
                    desc.Width = width;
                    desc.Height = height;
                    desc.MipLevels = 1;
                    desc.ArraySize = 1;
                    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                    desc.SampleDesc.Count = 1;
                    desc.Usage = D3D11_USAGE_DEFAULT;
                    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
                    desc.CPUAccessFlags = 0;

                    ID3D11Texture2D* txr = NULL;
                    D3D11_SUBRESOURCE_DATA sub_rsc;
                    sub_rsc.pSysMem = pixels;
                    sub_rsc.SysMemPitch = desc.Width * 4;
                    sub_rsc.SysMemSlicePitch = 0;
                    s_device->CreateTexture2D(&desc, &sub_rsc, &txr);

                    D3D11_SHADER_RESOURCE_VIEW_DESC view_desc;
                    ZeroMemory(&view_desc, sizeof(view_desc));
                    view_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                    view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
                    view_desc.Texture2D.MipLevels = desc.MipLevels;
                    view_desc.Texture2D.MostDetailedMip = 0;
                    s_device->CreateShaderResourceView(txr, &view_desc, &s_fnt_view);
                    txr->Release();
                }
                // store our identifier
                io.Fonts->TexID = (imgui_txr_id)s_fnt_view;
                // create texture sampler
                {
                    D3D11_SAMPLER_DESC desc;
                    ZeroMemory(&desc, sizeof(desc));
                    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
                    desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
                    desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
                    desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
                    desc.MipLODBias = 0.f;
                    desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
                    desc.MinLOD = 0.f;
                    desc.MaxLOD = 0.f;
                    s_device->CreateSamplerState(&desc, &s_fnt_smp);
                }
            }
        }

        return true;
    }
    void drawer_quit()
    {
        if (s_device == nullptr || s_context == nullptr) { return; }
        s_device = nullptr; s_context = nullptr;
        {
            if (s_fnt_smp) { s_fnt_smp->Release(); s_fnt_smp = NULL; }
            if (s_fnt_view) { s_fnt_view->Release(); s_fnt_view = NULL; GUI::GetIO().Fonts->TexID = NULL; } // we copied s_fnt_viewto io.Fonts->TexID so let's clear that as well.
            if (s_ibuf) { s_ibuf->Release(); s_ibuf = NULL; }
            if (s_vbuf) { s_vbuf->Release(); s_vbuf = NULL; }

            if (s_blend_state) { s_blend_state->Release(); s_blend_state = NULL; }
            if (s_dpt_stc_state) { s_dpt_stc_state->Release(); s_dpt_stc_state = NULL; }
            if (s_rst_state) { s_rst_state->Release(); s_rst_state = NULL; }
            if (s_pshd) { s_pshd->Release(); s_pshd = NULL; }
            if (s_vsbuf) { s_vsbuf->Release(); s_vsbuf = NULL; }
            if (s_layout) { s_layout->Release(); s_layout = NULL; }
            if (s_vshd) { s_vshd->Release(); s_vshd = NULL; }
        }
        if (s_factory != nullptr) { s_factory->Release(); s_factory = nullptr; }
        if (s_device != nullptr) { s_device->Release(); s_device = nullptr; }
        if (s_context != nullptr) { s_context->Release(); s_context = nullptr; }
    }
    void drawer_update(imgui_draw_data* draw_data)
    {
        // avoid rendering when minimized
        if (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f) { return; }

        ID3D11DeviceContext* context = s_context;

        // Create and grow vertex/index buffers if needed
        if (!s_vbuf || s_vtx_size < draw_data->TotalVtxCount)
        {
            if (s_vbuf) { s_vbuf->Release(); s_vbuf = NULL; }
            s_vtx_size = draw_data->TotalVtxCount + 5000;
            D3D11_BUFFER_DESC desc;
            memset(&desc, 0, sizeof(D3D11_BUFFER_DESC));
            desc.Usage = D3D11_USAGE_DYNAMIC;
            desc.ByteWidth = s_vtx_size * sizeof(ImDrawVert);
            desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
            desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            desc.MiscFlags = 0;
            if (s_device->CreateBuffer(&desc, NULL, &s_vbuf) < 0) { return; }
        }
        if (!s_ibuf || s_idx_size < draw_data->TotalIdxCount)
        {
            if (s_ibuf) { s_ibuf->Release(); s_ibuf = NULL; }
            s_idx_size = draw_data->TotalIdxCount + 10000;
            D3D11_BUFFER_DESC desc;
            memset(&desc, 0, sizeof(D3D11_BUFFER_DESC));
            desc.Usage = D3D11_USAGE_DYNAMIC;
            desc.ByteWidth = s_idx_size * sizeof(ImDrawIdx);
            desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
            desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            if (s_device->CreateBuffer(&desc, NULL, &s_ibuf) < 0) { return; }
        }

        // Upload vertex/index data into a single contiguous GPU buffer
        D3D11_MAPPED_SUBRESOURCE vtx_resource, idx_resource;
        if (context->Map(s_vbuf, 0, D3D11_MAP_WRITE_DISCARD, 0, &vtx_resource) != S_OK) { return; }
        if (context->Map(s_ibuf, 0, D3D11_MAP_WRITE_DISCARD, 0, &idx_resource) != S_OK) { return; }
        ImDrawVert* vtx_dst = (ImDrawVert*)vtx_resource.pData;
        ImDrawIdx* idx_dst = (ImDrawIdx*)idx_resource.pData;
        for (int n = 0; n < draw_data->CmdListsCount; n++) {
            const imgui_draw_list* cmd_list = draw_data->CmdLists[n];
            memcpy(vtx_dst, cmd_list->VtxBuffer.Data, cmd_list->VtxBuffer.Size * sizeof(ImDrawVert));
            memcpy(idx_dst, cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx));
            vtx_dst += cmd_list->VtxBuffer.Size;
            idx_dst += cmd_list->IdxBuffer.Size;
        }
        context->Unmap(s_vbuf, 0);
        context->Unmap(s_ibuf, 0);

        // setup orthographic projection matrix into our constant buffer
        // our visible imgui space lies from draw_data->DisplayPos (top left) to
        // draw_data->DisplayPos+data_data->DisplaySize (bottom right). DisplayPos is (0,0) for single viewport apps.
        {
            D3D11_MAPPED_SUBRESOURCE mapped_resource;
            if (context->Map(s_vsbuf, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource) != S_OK) { return; }
            vsbuf_m16f* constant_buffer = (vsbuf_m16f*)mapped_resource.pData;
            f32 L = draw_data->DisplayPos.x;
            f32 R = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
            f32 T = draw_data->DisplayPos.y;
            f32 B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;
            f32 mdl_view_proj[4][4] = {
                { 2.0f / (R - L),   0.0f,           0.0f,       0.0f },
                { 0.0f,         2.0f / (T - B),     0.0f,       0.0f },
                { 0.0f,         0.0f,           0.5f,       0.0f },
                { (R + L) / (L - R),  (T + B) / (B - T),    0.5f,       1.0f },
            };
            memcpy(&constant_buffer->mdl_view_proj, mdl_view_proj, sizeof(mdl_view_proj));
            context->Unmap(s_vsbuf, 0);
        }

        // backup DX state that will be modified to restore it afterwards (unfortunately this is very ugly looking and verbose. Close your eyes!)
        dx_context_state old;
        old.ScissorRectsCount = old.ViewportsCount = D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
        // rasterizer
        context->RSGetScissorRects(&old.ScissorRectsCount, old.ScissorRects);
        context->RSGetViewports(&old.ViewportsCount, old.Viewports);
        context->RSGetState(&old.RS);
        // output_manager
        context->OMGetBlendState(&old.BlendState, old.BlendFactor, &old.SampleMask);
        context->OMGetDepthStencilState(&old.DepthStencilState, &old.StencilRef);
        // shaders
        old.PSInstancesCount = old.VSInstancesCount = old.GSInstancesCount = 256;
        context->PSGetShaderResources(0, 1, &old.PSShaderResource);
        context->PSGetSamplers(0, 1, &old.PSSampler);
        context->PSGetShader(&old.PS, old.PSInstances, &old.PSInstancesCount);
        context->VSGetShader(&old.VS, old.VSInstances, &old.VSInstancesCount);
        context->VSGetConstantBuffers(0, 1, &old.VSConstantBuffer);
        context->GSGetShader(&old.GS, old.GSInstances, &old.GSInstancesCount);
        // input_assembler
        context->IAGetPrimitiveTopology(&old.PrimitiveTopology);
        context->IAGetIndexBuffer(&old.IndexBuffer, &old.IndexBufferFormat, &old.IndexBufferOffset);
        context->IAGetVertexBuffers(0, 1, &old.VertexBuffer, &old.VertexBufferStride, &old.VertexBufferOffset);
        context->IAGetInputLayout(&old.input_layout);
        // setup desired dx state
        drawer_update_state(draw_data, context);
        // render command lists
        // because we merged all buffers into a single one, we maintain our own offset into them)
        si32 global_idx_offset = 0;
        si32 global_vtx_offset = 0;
        ImVec2 clip_off = draw_data->DisplayPos;
        for (int n = 0; n < draw_data->CmdListsCount; n++) {
            const imgui_draw_list* cmd_list = draw_data->CmdLists[n];
            for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++) {
                const imgui_draw_cmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
                if (pcmd->UserCallback != NULL) {
                    // user callback, registered via imgui_draw_list::AddCallback()
                    // (ImDrawCallback_ResetRenderState is a special callback value used by the user to request the renderer to reset render state.)
                    if (pcmd->UserCallback == ImDrawCallback_ResetRenderState) { drawer_update_state(draw_data, context); }
                    else { pcmd->UserCallback(cmd_list, pcmd); }
                }
                else {
                    // apply scissor/clipping rectangle
                    const D3D11_RECT r = { (LONG)(pcmd->ClipRect.x - clip_off.x), (LONG)(pcmd->ClipRect.y - clip_off.y), (LONG)(pcmd->ClipRect.z - clip_off.x), (LONG)(pcmd->ClipRect.w - clip_off.y) };
                    context->RSSetScissorRects(1, &r);
                    // bind texture, draw
                    ID3D11ShaderResourceView* txr_srv = (ID3D11ShaderResourceView*)pcmd->TextureId;
                    context->PSSetShaderResources(0, 1, &txr_srv);
                    context->DrawIndexed(pcmd->ElemCount, pcmd->IdxOffset + global_idx_offset, pcmd->VtxOffset + global_vtx_offset);
                }
            }
            global_idx_offset += cmd_list->IdxBuffer.Size;
            global_vtx_offset += cmd_list->VtxBuffer.Size;
        }
        // restore modified dx state
        // rasterizer_state
        context->RSSetScissorRects(old.ScissorRectsCount, old.ScissorRects);
        context->RSSetViewports(old.ViewportsCount, old.Viewports);
        context->RSSetState(old.RS); if (old.RS) old.RS->Release();
        // output_manager
        context->OMSetBlendState(old.BlendState, old.BlendFactor, old.SampleMask); if (old.BlendState) old.BlendState->Release();
        context->OMSetDepthStencilState(old.DepthStencilState, old.StencilRef); if (old.DepthStencilState) old.DepthStencilState->Release();
        // shaders
        context->PSSetShaderResources(0, 1, &old.PSShaderResource); if (old.PSShaderResource) old.PSShaderResource->Release();
        context->PSSetSamplers(0, 1, &old.PSSampler); if (old.PSSampler) old.PSSampler->Release();
        context->PSSetShader(old.PS, old.PSInstances, old.PSInstancesCount); if (old.PS) old.PS->Release();
        for (UINT i = 0; i < old.PSInstancesCount; i++) if (old.PSInstances[i]) old.PSInstances[i]->Release();
        context->VSSetShader(old.VS, old.VSInstances, old.VSInstancesCount); if (old.VS) old.VS->Release();
        context->VSSetConstantBuffers(0, 1, &old.VSConstantBuffer); if (old.VSConstantBuffer) old.VSConstantBuffer->Release();
        context->GSSetShader(old.GS, old.GSInstances, old.GSInstancesCount); if (old.GS) old.GS->Release();
        for (UINT i = 0; i < old.VSInstancesCount; i++) if (old.VSInstances[i]) old.VSInstances[i]->Release();
        // input_assembler
        context->IASetPrimitiveTopology(old.PrimitiveTopology);
        context->IASetIndexBuffer(old.IndexBuffer, old.IndexBufferFormat, old.IndexBufferOffset); if (old.IndexBuffer) old.IndexBuffer->Release();
        context->IASetVertexBuffers(0, 1, &old.VertexBuffer, &old.VertexBufferStride, &old.VertexBufferOffset); if (old.VertexBuffer) old.VertexBuffer->Release();
        context->IASetInputLayout(old.input_layout); if (old.input_layout) old.input_layout->Release();
    }
    void drawer_update_state(imgui_draw_data* draw_data, context_handle context)
    {
        // setup viewport
        {
            D3D11_VIEWPORT vp;
            memset(&vp, 0, sizeof(D3D11_VIEWPORT));
            vp.Width = draw_data->DisplaySize.x;
            vp.Height = draw_data->DisplaySize.y;
            vp.MinDepth = 0.0f;
            vp.MaxDepth = 1.0f;
            vp.TopLeftX = vp.TopLeftY = 0;
            context->RSSetViewports(1, &vp);
        }

        // setup shader and vertex buffers
        {
            UINT stride_size = sizeof(ImDrawVert);
            UINT offset_size = 0;
            context->IASetInputLayout(s_layout);
            context->IASetVertexBuffers(0, 1, &s_vbuf, &stride_size, &offset_size);
            context->IASetIndexBuffer(s_ibuf, sizeof(ImDrawIdx) == 2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT, 0);
            context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            context->VSSetShader(s_vshd, NULL, 0);
            context->VSSetConstantBuffers(0, 1, &s_vsbuf);
            context->PSSetShader(s_pshd, NULL, 0);
            context->PSSetSamplers(0, 1, &s_fnt_smp);
            // in theory we should backup and restore this as well.. very infrequently used..
            context->GSSetShader(NULL, NULL, 0);
            context->HSSetShader(NULL, NULL, 0);
            context->DSSetShader(NULL, NULL, 0);
            context->CSSetShader(NULL, NULL, 0);
            // setup blend state
            f32 blend_factor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
            context->OMSetBlendState(s_blend_state, blend_factor, 0xffffffff);
            context->OMSetDepthStencilState(s_dpt_stc_state, 0);
            context->RSSetState(s_rst_state);
        }
    }
}
namespace NW
{
    void drawer_create_wnd(imgui_viewport* viewport)
    {
        dx_viewport_data* data = IM_NEW(dx_viewport_data)();
        viewport->RendererUserData = data;
        // platformHandleRaw should always be a HWND, whereas PlatformHandle might be a higher-level handle (e.g. GLFWWindow*, SDL_Window*).
        // Some back-end will leave PlatformHandleRaw NULL, in which case we assume PlatformHandle will contain the HWND.
        HWND hwnd = viewport->PlatformHandleRaw ? (HWND)viewport->PlatformHandleRaw : (HWND)viewport->PlatformHandle;
        IM_ASSERT(hwnd != 0);
        // create swap chain
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferDesc.Width = (UINT)viewport->Size.x;
        sd.BufferDesc.Height = (UINT)viewport->Size.y;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.BufferCount = 1;
        sd.OutputWindow = hwnd;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        sd.Flags = 0;

        IM_ASSERT(data->SwapChain == NULL && data->RTView == NULL);
        s_factory->CreateSwapChain(s_device, &sd, &data->SwapChain);

        // create the render target
        if (data->SwapChain) {
            ID3D11Texture2D* pBackBuffer;
            data->SwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
            s_device->CreateRenderTargetView(pBackBuffer, NULL, &data->RTView);
            pBackBuffer->Release();
        }
    }
    void drawer_delete_wnd(imgui_viewport* viewport)
    {
        // the main viewport (owned by the application) will always have RendererUserData == NULL;
        // since we didn't create the data for it.
        if (dx_viewport_data* data = (dx_viewport_data*)viewport->RendererUserData) {
            if (data->SwapChain) { data->SwapChain->Release(); }
            data->SwapChain = NULL;
            if (data->RTView) { data->RTView->Release(); }
            data->RTView = NULL;
            IM_DELETE(data);
        }
        viewport->RendererUserData = NULL;
    }
    void drawer_update_wnd(imgui_viewport* viewport, ptr)
    {
        dx_viewport_data* data = (dx_viewport_data*)viewport->RendererUserData;
        ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
        s_context->OMSetRenderTargets(1, &data->RTView, NULL);
        if (!(viewport->Flags & imgui_viewportFlags_NoRendererClear)) {
            s_context->ClearRenderTargetView(data->RTView, (float*)&clear_color);
        }
        drawer_update(viewport->DrawData);
    }
    void drawer_set_wnd_size(imgui_viewport* viewport, ImVec2 size)
    {
        dx_viewport_data* data = (dx_viewport_data*)viewport->RendererUserData;
        if (data->RTView)
        {
            data->RTView->Release();
            data->RTView = NULL;
        }
        if (data->SwapChain)
        {
            ID3D11Texture2D* pBackBuffer = NULL;
            data->SwapChain->ResizeBuffers(0, (UINT)size.x, (UINT)size.y, DXGI_FORMAT_UNKNOWN, 0);
            data->SwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
            if (pBackBuffer == NULL) { fprintf(stderr, "Dx11SetWindowSize() failed creating buffers.\n"); return; }
            s_device->CreateRenderTargetView(pBackBuffer, NULL, &data->RTView);
            pBackBuffer->Release();
        }
    }
    void drawer_swap_buffers(imgui_viewport* viewport, ptr draw_arg)
    {
        dx_viewport_data* data = reinterpret_cast<dx_viewport_data*>(viewport->RendererUserData);
        data->SwapChain->Present(0u, 0u);
        // present without vsync
    }
}
#endif
#endif  // NW_API
#if (defined NW_OS)
#if (NW_OS & NW_OS_WIN)
namespace NW
{
    // types
    struct win_viewport_data
    {
    public:
        HWND    Hwnd;
        bool    HwndOwned;
        DWORD   DwStyle;
        DWORD   DwExStyle;
    public:
        win_viewport_data() { Hwnd = nullptr; HwndOwned = false;  DwStyle = DwExStyle = 0; }
        ~win_viewport_data() { IM_ASSERT(Hwnd == nullptr); }
    };
    // data
    static window_handle s_wnd = nullptr;
    static WNDCLASSEX s_wnd_class = { 0 };
    static imgui_mouse_cursor s_last_crs = imgui_mouse_cursor_COUNT;
    static si64 s_time = 0;
    static si64 s_ticks_per_sec = 0;
    static bit s_update_monitors = true;}
namespace NW
{
    BOOL __stdcall win_update_monitors_enum(HMONITOR monitor, HDC device, LPRECT rect, LPARAM lparam)
    {
        MONITORINFO info = { 0 };
        info.cbSize = sizeof(MONITORINFO);
        if (!GetMonitorInfo(monitor, &info)) { return TRUE; }
        ImGuiPlatformMonitor imgui_monitor;
        imgui_monitor.MainPos = ImVec2(static_cast<f32>(info.rcMonitor.left), static_cast<f32>(info.rcMonitor.top));
        imgui_monitor.MainSize = ImVec2(static_cast<f32>(info.rcMonitor.right - info.rcMonitor.left), static_cast<f32>(info.rcMonitor.bottom - info.rcMonitor.top));
        imgui_monitor.WorkPos = ImVec2(static_cast<f32>(info.rcWork.left), static_cast<f32>(info.rcWork.top));
        imgui_monitor.WorkSize = ImVec2(static_cast<f32>(info.rcWork.right - info.rcWork.left), static_cast<f32>(info.rcWork.bottom - info.rcWork.top));
        imgui_platform_io* platform_io = &GUI::GetPlatformIO();
        if (info.dwFlags & MONITORINFOF_PRIMARY) { platform_io->Monitors.push_front(imgui_monitor); }
        else { platform_io->Monitors.push_back(imgui_monitor); }
        return TRUE;
    }
    LRESULT __stdcall win_event_proc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
    {
        if (imgui_event_proc(wnd, msg, wparam, lparam)) { return true; }

        if (imgui_viewport* viewport = GUI::FindViewportByPlatformHandle((ptr)wnd)) {
            switch (msg) {
            case WM_CLOSE: { viewport->PlatformRequestClose = true; } return 0;
            case WM_MOVE: { viewport->PlatformRequestMove = true; } break;
            case WM_SIZE: { viewport->PlatformRequestResize = true; } break;
            case WM_MOUSEACTIVATE: if (viewport->Flags & imgui_viewportFlags_NoFocusOnClick) { return MA_NOACTIVATE; } break;
            case WM_NCHITTEST:
                // let mouse pass-through the window; this will allow the back-end to set io.MouseHoveredViewport properly (which is optional);
                // the imgui_viewportFlags_NoInputs flag is set while dragging a viewport, as want to detect the window behind the one we are dragging;
                // if you cannot easily access those viewport flags from your windowing/event code: you may manually synchronize its state e.g. in
                // your main loop after calling UpdateWindows(). Iterate all viewports/platform windows and pass the flag to your windowing system.
                if (viewport->Flags & imgui_viewportFlags_NoInputs) { return HTTRANSPARENT; }
                break;
            }
        }
        return DefWindowProc(wnd, msg, wparam, lparam);
    }
    void win_get_viewport_flags_style(imgui_viewportFlags flags, DWORD* out_style, DWORD* out_ex_style)
    {
        if (flags & imgui_viewportFlags_NoDecoration) { *out_style = WS_POPUP; }
        else { *out_style = WS_OVERLAPPEDWINDOW; }

        if (flags & imgui_viewportFlags_NoTaskBarIcon) { *out_ex_style = WS_EX_TOOLWINDOW; }
        else { *out_ex_style = WS_EX_APPWINDOW; }

        if (flags & imgui_viewportFlags_TopMost) { *out_ex_style |= WS_EX_TOPMOST; }
    }
    void win_update_monitors()
    {
        s_platform_io->Monitors.resize(0);
        ::EnumDisplayMonitors(NULL, NULL, win_update_monitors_enum, NULL);
        s_update_monitors = false;
    }
    bit win_update_mouse_coord()
    {
        // set os mouse position if requested (rarely used, only when ImGuiConfigFlags_NavEnableSetMousePos is enabled by user)
        // (when multi-viewports are enabled, all imgui positions are same as os positions)
        if (s_imgui_io->WantSetMousePos) {
            POINT pos = { static_cast<si32>(s_imgui_io->MousePos.x), static_cast<int>(s_imgui_io->MousePos.y) };
            if ((s_imgui_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) == 0) { ::ClientToScreen(s_wnd, &pos); }
            ::SetCursorPos(pos.x, pos.y);
        }

        s_imgui_io->MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
        s_imgui_io->MouseHoveredViewport = 0;
        // set imgui mouse position
        POINT mouse_screen_pos;
        if (!::GetCursorPos(&mouse_screen_pos)) { return false; }
        if (HWND focused_hwnd = ::GetForegroundWindow()) {
            if (::IsChild(focused_hwnd, s_wnd)) { focused_hwnd = s_wnd; }
            if (s_imgui_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                // Multi-viewport mode: mouse position in OS absolute coordinates (io.MousePos is (0,0) when the mouse is on the upper-left of the primary monitor)
                // This is the position you can get with GetCursorPos(). In theory adding viewport->Pos is also the reverse operation of doing ScreenToClient().
                if (GUI::FindViewportByPlatformHandle(static_cast<ptr>(focused_hwnd)) != NULL)
                    s_imgui_io->MousePos = ImVec2(static_cast<f32>(mouse_screen_pos.x), static_cast<f32>(mouse_screen_pos.y));
            }
            else {
                // single viewport mode: mouse position in client window coordinates (io.MousePos is (0,0) when the mouse is on the upper-left corner of the app window.)
                // this is the position you can get with GetCursorPos() + ScreenToClient() or from WM_MOUSEMOVE.
                if (focused_hwnd == s_wnd) {
                    POINT mouse_client_pos = mouse_screen_pos;
                    ::ScreenToClient(focused_hwnd, &mouse_client_pos);
                    s_imgui_io->MousePos = ImVec2(static_cast<f32>(mouse_client_pos.x), static_cast<f32>(mouse_client_pos.y));
                }
            }
        }
        // (optional) when using multiple viewports: set io.MouseHoveredViewport to the viewport the os mouse cursor is hovering;
        // important: this information is not easy to provide and many high-level windowing library won't be able to provide it correctly, because
        // - this is _ignoring_ viewports with the imgui_viewportFlags_NoInputs flag (pass-through windows);
        // - this is _regardless_ of whether another viewport is focused or being dragged from;
        // if ImGuiBackendFlags_HasMouseHoveredViewport is not set by the back-end, imgui will ignore this field and infer the information by relying on the
        // rectangles and last focused time of every viewports it knows about;
        // it will be unaware of foreign windows that may be sitting between or over your windows.
        if (HWND hovered_hwnd = ::WindowFromPoint(mouse_screen_pos)) {
            if (imgui_viewport* viewport = GUI::FindViewportByPlatformHandle(static_cast<ptr>(hovered_hwnd))) {
                if ((viewport->Flags & imgui_viewportFlags_NoInputs) == 0) {
                    // FIXME: we still get our NoInputs window with WM_NCHITTEST/HTTRANSPARENT code when decorated?
                    s_imgui_io->MouseHoveredViewport = viewport->ID;
                }
            }
        }
        return true;
    }
    bit win_update_mouse_cursor()
    {
        if (s_imgui_io->ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange) { return false; }

        imgui_mouse_cursor imgui_cursor = GUI::GetMouseCursor();
        if (imgui_cursor == imgui_mouse_cursor_None || s_imgui_io->MouseDrawCursor) {
            // hide operation_system mouse cursor if imgui is drawing it or if it wants no cursor
            ::SetCursor(NULL);
        }
        else {
            // show operation_system mouse cursor
            LPTSTR win32_cursor = IDC_ARROW;
            switch (imgui_cursor) {
            case imgui_mouse_cursor_Arrow:        win32_cursor = IDC_ARROW; break;
            case imgui_mouse_cursor_TextInput:    win32_cursor = IDC_IBEAM; break;
            case imgui_mouse_cursor_ResizeAll:    win32_cursor = IDC_SIZEALL; break;
            case imgui_mouse_cursor_ResizeEW:     win32_cursor = IDC_SIZEWE; break;
            case imgui_mouse_cursor_ResizeNS:     win32_cursor = IDC_SIZENS; break;
            case imgui_mouse_cursor_ResizeNESW:   win32_cursor = IDC_SIZENESW; break;
            case imgui_mouse_cursor_ResizeNWSE:   win32_cursor = IDC_SIZENWSE; break;
            case imgui_mouse_cursor_Hand:         win32_cursor = IDC_HAND; break;
            case imgui_mouse_cursor_NotAllowed:   win32_cursor = IDC_NO; break;
            }
            ::SetCursor(LoadCursor(NULL, win32_cursor));
        }
        return true;
    }
}
namespace NW
{
    bit platform_init(window_handle window)
    {
        if (s_wnd != nullptr) { return false; }
        s_wnd = window;

        if (!::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&s_ticks_per_sec))) { return false; }
        if (!::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&s_time))) { return false; }
        
        imgui_viewport* main_viewport = GUI::GetMainViewport();
        main_viewport->PlatformHandle = main_viewport->PlatformHandleRaw = window;
        // setup back-end capabilities flags
        {
            s_imgui_io->BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // we can honor GetMouseCursor() values (optional)
            s_imgui_io->BackendFlags |= ImGuiBackendFlags_HasSetMousePos;          // we can honor io.WantSetMousePos requests (optional, rarely used)
            s_imgui_io->BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;    // we can create multi-viewports on the Platform side (optional)
            s_imgui_io->BackendFlags |= ImGuiBackendFlags_HasMouseHoveredViewport; // we can set io.MouseHoveredViewport correctly (optional, not easy)
            s_imgui_io->BackendPlatformName = "nwg_windows";
            // our mouse update function expect platform handle to be filled for the main viewport
        }
        // keyboard mapping.
        // imgui will use those indices to peek into the io.KeysDown[] array that we will update during the application lifetime.
        {
            s_imgui_io->KeyMap[ImGuiKey_Tab] = VK_TAB;
            s_imgui_io->KeyMap[ImGuiKey_LeftArrow] = VK_LEFT;
            s_imgui_io->KeyMap[ImGuiKey_RightArrow] = VK_RIGHT;
            s_imgui_io->KeyMap[ImGuiKey_UpArrow] = VK_UP;
            s_imgui_io->KeyMap[ImGuiKey_DownArrow] = VK_DOWN;
            s_imgui_io->KeyMap[ImGuiKey_PageUp] = VK_PRIOR;
            s_imgui_io->KeyMap[ImGuiKey_PageDown] = VK_NEXT;
            s_imgui_io->KeyMap[ImGuiKey_Home] = VK_HOME;
            s_imgui_io->KeyMap[ImGuiKey_End] = VK_END;
            s_imgui_io->KeyMap[ImGuiKey_Insert] = VK_INSERT;
            s_imgui_io->KeyMap[ImGuiKey_Delete] = VK_DELETE;
            s_imgui_io->KeyMap[ImGuiKey_Backspace] = VK_BACK;
            s_imgui_io->KeyMap[ImGuiKey_Space] = VK_SPACE;
            s_imgui_io->KeyMap[ImGuiKey_Enter] = VK_RETURN;
            s_imgui_io->KeyMap[ImGuiKey_Escape] = VK_ESCAPE;
            s_imgui_io->KeyMap[ImGuiKey_KeyPadEnter] = VK_RETURN;
            s_imgui_io->KeyMap[ImGuiKey_A] = 'A';
            s_imgui_io->KeyMap[ImGuiKey_C] = 'C';
            s_imgui_io->KeyMap[ImGuiKey_V] = 'V';
            s_imgui_io->KeyMap[ImGuiKey_X] = 'X';
            s_imgui_io->KeyMap[ImGuiKey_Y] = 'Y';
            s_imgui_io->KeyMap[ImGuiKey_Z] = 'Z';
        }
        // register window class;
        {
            s_wnd_class.cbSize = sizeof(WNDCLASSEX);
            s_wnd_class.style = CS_HREDRAW | CS_VREDRAW;
            s_wnd_class.lpfnWndProc = win_event_proc;
            s_wnd_class.cbClsExtra = 0;
            s_wnd_class.cbWndExtra = 0;
            s_wnd_class.hInstance = ::GetModuleHandle(NULL);
            s_wnd_class.hIcon = NULL;
            s_wnd_class.hCursor = NULL;
            s_wnd_class.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND + 1);
            s_wnd_class.lpszMenuName = NULL;
            s_wnd_class.lpszClassName = _T("imgui_window");
            s_wnd_class.hIconSm = NULL;
            ::RegisterClassEx(&s_wnd_class);
            win_update_monitors();
        }
        // set 13 of 17 functions for imgui platform interface;
        if (s_imgui_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            s_platform_io->Platform_GetWindowPos = platform_get_wnd_coord;
            s_platform_io->Platform_GetWindowSize = platform_get_wnd_size;
            s_platform_io->Platform_GetWindowFocus = platform_get_wnd_focus;
            s_platform_io->Platform_GetWindowMinimized = platform_get_wnd_minimized;
            // setters
            s_platform_io->Platform_SetWindowPos = platform_set_wnd_coord;
            s_platform_io->Platform_SetWindowSize = platform_set_wnd_size;
            s_platform_io->Platform_SetWindowFocus = platform_set_wnd_focus;
            s_platform_io->Platform_SetWindowTitle = platform_set_wnd_title;
            s_platform_io->Platform_SetWindowAlpha = platform_set_wnd_alpha;
            // core_methods
            s_platform_io->Platform_CreateWindow = platform_create_wnd;
            s_platform_io->Platform_DestroyWindow = platform_delete_wnd;
            s_platform_io->Platform_UpdateWindow = platform_update_wnd;
            s_platform_io->Platform_ShowWindow = platform_show_wnd;
        }
        // --register main window handle (which is owned by the main application, not by us)
        // --this is mostly for simplicity and consistency, so that our code (e.g. mouse handling etc.)
        // --can use same logic for main and secondary viewports.
        {
            main_viewport = GUI::GetMainViewport();
            win_viewport_data* data = IM_NEW(win_viewport_data)();
            data->Hwnd = s_wnd;
            data->HwndOwned = false;
            main_viewport->PlatformUserData = data;
            main_viewport->PlatformHandle = static_cast<ptr>(s_wnd);
        }
        return true;
    }
    void platform_quit()
    {
        if (s_wnd != nullptr) { return; }
        s_wnd = nullptr;
        ::UnregisterClass(s_wnd_class.lpszClassName, s_wnd_class.hInstance);
        s_wnd_class = { 0 };
    }
    void platform_update()
    {
        IM_ASSERT(s_imgui_io->Fonts->IsBuilt() && "font atlas is not built; it is generally built by the renderer back-end;");
        // setup display size (every frame to accommodate for window resizing)
        RECT rect;
        ::GetClientRect(s_wnd, &rect);
        s_imgui_io->DisplaySize = ImVec2(static_cast<f32>(rect.right - rect.left), static_cast<f32>(rect.bottom - rect.top));
        if (s_update_monitors) { win_update_monitors(); }
        // setup delta time
        INT64 current_time;
        ::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&current_time));
        s_imgui_io->DeltaTime = static_cast<f32>(current_time - s_time) / s_ticks_per_sec;
        s_time = current_time;
        // read keyboard modifiers inputs
        s_imgui_io->KeyCtrl = (::GetKeyState(VK_CONTROL) & 0x8000) != 0;
        s_imgui_io->KeyShift = (::GetKeyState(VK_SHIFT) & 0x8000) != 0;
        s_imgui_io->KeyAlt = (::GetKeyState(VK_MENU) & 0x8000) != 0;
        s_imgui_io->KeySuper = FALSE;
        // io.KeysDown[], io.MousePos, io.MouseDown[], io.MouseWheel: filled by the window procedure handler below.
        // update os mouse position
        win_update_mouse_coord();
        // update os mouse cursor with the cursor requested by imgui
        imgui_mouse_cursor mouse_cursor = s_imgui_io->MouseDrawCursor ? imgui_mouse_cursor_None : GUI::GetMouseCursor();
        if (s_last_crs != mouse_cursor) {
            s_last_crs = mouse_cursor;
            win_update_mouse_cursor();
        }
    }
}
namespace NW
{
    // --getters
    ImVec2 platform_get_wnd_coord(imgui_viewport* viewport)
    {
        win_viewport_data* data = (win_viewport_data*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        POINT pos = { 0, 0 };
        ::ClientToScreen(data->Hwnd, &pos);
        return ImVec2((float)pos.x, (float)pos.y);
    }
    ImVec2 platform_get_wnd_size(imgui_viewport* viewport)
    {
        win_viewport_data* data = (win_viewport_data*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        RECT rect;
        ::GetClientRect(data->Hwnd, &rect);
        return ImVec2(float(rect.right - rect.left), float(rect.bottom - rect.top));
    }
    bit platform_get_wnd_focus(imgui_viewport* viewport)
    {
        win_viewport_data* data = (win_viewport_data*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        return ::GetForegroundWindow() == data->Hwnd;
    }
    bit platform_get_wnd_minimized(imgui_viewport* viewport)
    {
        win_viewport_data* data = (win_viewport_data*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        return ::IsIconic(data->Hwnd) != 0;
    }
    // --setters
    void platform_set_wnd_coord(imgui_viewport* viewport, ImVec2 pos)
    {
        win_viewport_data* data = (win_viewport_data*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        RECT rect = { (LONG)pos.x, (LONG)pos.y, (LONG)pos.x, (LONG)pos.y };
        ::AdjustWindowRectEx(&rect, data->DwStyle, FALSE, data->DwExStyle);
        ::SetWindowPos(data->Hwnd, NULL, rect.left, rect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
    }
    void platform_set_wnd_size(imgui_viewport* viewport, ImVec2 size)
    {
        win_viewport_data* data = (win_viewport_data*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        RECT rect = { 0, 0, (LONG)size.x, (LONG)size.y };
        ::AdjustWindowRectEx(&rect, data->DwStyle, FALSE, data->DwExStyle); // client to Screen
        ::SetWindowPos(
            data->Hwnd, NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top,
            SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE
        );
    }
    void platform_set_wnd_focus(imgui_viewport* viewport)
    {
        win_viewport_data* data = (win_viewport_data*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        ::BringWindowToTop(data->Hwnd);
        ::SetForegroundWindow(data->Hwnd);
        ::SetFocus(data->Hwnd);
    }
    void platform_set_wnd_title(imgui_viewport* viewport, cstr title)
    {
        // SetWindowTextA() doesn't properly handle utf-8 so we explicitely convert our string;
        win_viewport_data* data = (win_viewport_data*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        si32 n = ::MultiByteToWideChar(CP_UTF8, 0, title, -1, NULL, 0);
        ImVector<wchar_t> title_w;
        title_w.resize(n);
        ::MultiByteToWideChar(CP_UTF8, 0, title, -1, title_w.Data, n);
        ::SetWindowTextW(data->Hwnd, title_w.Data);
    }
    void platform_set_wnd_alpha(imgui_viewport* viewport, f32 alpha)
    {
        win_viewport_data* data = (win_viewport_data*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        IM_ASSERT(alpha >= 0.0f && alpha <= 1.0f);
        if (alpha < 1.0f) {
            DWORD style = ::GetWindowLongW(data->Hwnd, GWL_EXSTYLE) | WS_EX_LAYERED;
            ::SetWindowLongW(data->Hwnd, GWL_EXSTYLE, style);
            ::SetLayeredWindowAttributes(data->Hwnd, 0, (BYTE)(255 * alpha), LWA_ALPHA);
        }
        else {  // get rid of transparency
            DWORD style = ::GetWindowLongW(data->Hwnd, GWL_EXSTYLE) & ~WS_EX_LAYERED;
            ::SetWindowLongW(data->Hwnd, GWL_EXSTYLE, style);
        }
    }
    // --core_methods
    void platform_create_wnd(imgui_viewport* viewport)
    {
        win_viewport_data* data = IM_NEW(win_viewport_data)();
        viewport->PlatformUserData = data;
        // --select style and parent window
        win_get_viewport_flags_style(viewport->Flags, &data->DwStyle, &data->DwExStyle);
        HWND parent_window = NULL;
        if (viewport->ParentViewportId != 0) {
            if (imgui_viewport* parent_viewport = GUI::FindViewportByID(viewport->ParentViewportId)) {
                parent_window = (HWND)parent_viewport->PlatformHandle;
            }
        }
        // create window
        {
            RECT rect = { (LONG)viewport->Pos.x, (LONG)viewport->Pos.y, (LONG)(viewport->Pos.x + viewport->Size.x), (LONG)(viewport->Pos.y + viewport->Size.y) };
            ::AdjustWindowRectEx(&rect, data->DwStyle, FALSE, data->DwExStyle);
            data->Hwnd = ::CreateWindowEx(
                data->DwExStyle,            // extended style
                s_wnd_class.lpszClassName,  // class name
                _T("imgui_viewport"),       // window name
                data->DwStyle,              // style
                rect.left, rect.top,        // coord
                rect.right - rect.left,     // width
                rect.bottom - rect.top,     // height
                parent_window,              // parrent
                NULL,                       // menu
                s_wnd_class.hInstance,      // instance handle
                NULL                        // param
            );
            if (data->Hwnd == NULL) { throw init_error(__FILE__, __LINE__); return; }
            data->HwndOwned = true;
            viewport->PlatformRequestResize = false;
            viewport->PlatformHandle = viewport->PlatformHandleRaw = data->Hwnd;
        }
    }
    void platform_delete_wnd(imgui_viewport* viewport)
    {
        if (win_viewport_data* data = (win_viewport_data*)viewport->PlatformUserData) {
            if (GetCapture() == data->Hwnd) {
                // transfer capture so if we started 
                // dragging from a window that later disappears, we'll still receive the MOUSEUP event.
                ::ReleaseCapture();
                ::SetCapture(s_wnd);
            }
            if (data->Hwnd && data->HwndOwned) { DestroyWindow(data->Hwnd); }
            data->Hwnd = NULL;
            IM_DELETE(data);
        }
        viewport->PlatformUserData = viewport->PlatformHandle = NULL;
    }
    void platform_show_wnd(imgui_viewport* viewport)
    {
        win_viewport_data* data = (win_viewport_data*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        if (viewport->Flags & imgui_viewportFlags_NoFocusOnAppearing) { ::ShowWindow(data->Hwnd, SW_SHOWNA); }
        else { ::ShowWindow(data->Hwnd, SW_SHOW); }
    }
    void platform_update_wnd(imgui_viewport* viewport)
    {
        // (Optional) Update Win32 style if it changed _after_ creation.
        // Generally they won't change unless configuration flags are changed, but advanced uses (such as manually rewriting viewport flags) make this useful.
        win_viewport_data* data = (win_viewport_data*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        DWORD new_style;
        DWORD new_ex_style;
        win_get_viewport_flags_style(viewport->Flags, &new_style, &new_ex_style);

        // only reapply the flags that have been changed from our point of view (as other flags are being modified by Windows)
        if (data->DwStyle != new_style || data->DwExStyle != new_ex_style) {
            data->DwStyle = new_style;
            data->DwExStyle = new_ex_style;
            SetWindowLong(data->Hwnd, GWL_STYLE, data->DwStyle);
            SetWindowLong(data->Hwnd, GWL_EXSTYLE, data->DwExStyle);
            RECT rect = { (LONG)viewport->Pos.x, (LONG)viewport->Pos.y, (LONG)(viewport->Pos.x + viewport->Size.x), (LONG)(viewport->Pos.y + viewport->Size.y) };
            ::AdjustWindowRectEx(&rect, data->DwStyle, FALSE, data->DwExStyle); // Client to Screen
            ::SetWindowPos(data->Hwnd, NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
            ::ShowWindow(data->Hwnd, SW_SHOWNA); // This is necessary when we alter the style
            viewport->PlatformRequestMove = viewport->PlatformRequestResize = true;
        }
    }
}
namespace NW
{
    // win32 message handler (process Win32 mouse/keyboard inputs, etc.)
    // call from your application's message handler.
    // when implementing your own back-end, you can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if Dear ImGui wants to use your inputs;
    // --when io.WantCaptureMouse is true, do not dispatch mouse input data to your main application;
    // --when io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application;
    // generally you may always pass all inputs to Dear ImGui, and hide them from your application based on those two flags;
    // ps: in this win32 handler, we use the capture api (GetCapture/SetCapture/ReleaseCapture) to be able to read mouse coordinates when dragging mouse outside of our window bounds.
    // ps: we treat DBLCLK messages as regular mouse down messages, so this code will work on windows classes that have the CS_DBLCLKS flag set. our own example app code doesn't set this flag.
    LRESULT __stdcall imgui_event_proc(window_handle hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
    {
        if (GUI::GetCurrentContext() == NULL) { return 0; }
        switch (msg) {
        case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
        case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
        case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK: {
            si32 button = 0;
            if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONDBLCLK) { button = 0; }
            if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONDBLCLK) { button = 1; }
            if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONDBLCLK) { button = 2; }
            if (!GUI::IsAnyMouseDown() && ::GetCapture() == NULL) { ::SetCapture(hwnd); }
            s_imgui_io->MouseDown[button] = true;
            return 0;
        }
        case WM_LBUTTONUP: case WM_RBUTTONUP: case WM_MBUTTONUP: {
            si32 button = 0;
            if (msg == WM_LBUTTONUP) { button = 0; }
            if (msg == WM_RBUTTONUP) { button = 1; }
            if (msg == WM_MBUTTONUP) { button = 2; }
            s_imgui_io->MouseDown[button] = false;
            if (!GUI::IsAnyMouseDown() && ::GetCapture() == hwnd) { ::ReleaseCapture(); }
            return 0;
        }
        case WM_MOUSEWHEEL: s_imgui_io->MouseWheel += static_cast<f32>(GET_WHEEL_DELTA_WPARAM(wparam)) / static_cast<f32>(WHEEL_DELTA);
            return 0;
        case WM_MOUSEHWHEEL: s_imgui_io->MouseWheelH += static_cast<f32>(GET_WHEEL_DELTA_WPARAM(wparam)) / static_cast<f32>(WHEEL_DELTA);
            return 0;
        case WM_KEYDOWN: case WM_SYSKEYDOWN:
            if (wparam < 256) { s_imgui_io->KeysDown[wparam] = true; }
            return 0;
        case WM_KEYUP: case WM_SYSKEYUP:
            if (wparam < 256) { s_imgui_io->KeysDown[wparam] = false; }
            return 0;
        case WM_CHAR:
            // you can also use ToAscii()+GetKeyboardState() to retrieve characters.
            if (wparam > 0 && wparam < 0x10000) { s_imgui_io->AddInputCharacterUTF16(static_cast<wchar>(wparam)); }
            return 0;
        case WM_SETCURSOR:
            if (LOWORD(lparam) == HTCLIENT && win_update_mouse_cursor()) { return 1; }
            return 0;
        case WM_DISPLAYCHANGE: s_update_monitors = true;
            return 0;
        }
        return 0;
    }
}
#endif
#endif  // NW_OS
namespace NW
{
    // --setters
    void imgui_set_mouse_enabled(bit enable) {
        if (s_imgui_io == nullptr) { return; }
        if (enable == true) { s_imgui_io->ConfigFlags &= ~ImGuiConfigFlags_NoMouse; }
        if (enable == false) { s_imgui_io->ConfigFlags |= ImGuiConfigFlags_NoMouse; }
    }
    void imgui_set_dockspace_enabled(bit enable) {
        s_is_dockspace_enabled = enable;
    }
    // --==<core_methods>==--
    bit imgui_init(window_handle window, device_handle device, context_handle context)
    {
        if (s_imgui_io != nullptr || s_platform_io != nullptr) { return false; }
        
        IMGUI_CHECKVERSION();
        GUI::CreateContext();
        
        s_imgui_io = &GUI::GetIO();
        s_platform_io = &GUI::GetPlatformIO();
        s_imgui_style = &GUI::GetStyle();

        s_imgui_io->ConfigFlags |=
            ImGuiConfigFlags_NavEnableKeyboard |
            ImGuiConfigFlags_ViewportsEnable |
            ImGuiConfigFlags_DockingEnable;
        s_imgui_io->ConfigDockingWithShift = true;

        GUI::StyleColorsDark();
        if (s_imgui_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            s_imgui_style->WindowRounding = 0.0f;
            s_imgui_style->Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        if (!platform_init(window)) { return false; }
        if (!drawer_init(device, context)) { return false; }

        return true;
    }
    void imgui_quit()
    {
        if (s_imgui_io == nullptr || s_platform_io == nullptr) { return; }

        GUI::DestroyWindows();
        drawer_quit();
        platform_quit();
        GUI::DestroyContext();

        s_imgui_io = nullptr; s_platform_io = nullptr;
    }
    void imgui_begin_frame()
    {
        static bit s_enable_dockspace = true;
        static bit s_full_screen_persist = true;
        platform_update();
        GUI::NewFrame();
        // setup dockspace
        if (s_is_dockspace_enabled) {
            bit full_screen = s_full_screen_persist;
            static ImGuiDockNodeFlags dock_flags = ImGuiDockNodeFlags_None;
            ImGuiWindowFlags wnd_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

            if (full_screen) {
                imgui_viewport* viewport = GUI::GetMainViewport();
                GUI::SetNextWindowPos(viewport->Pos);
                GUI::SetNextWindowSize(viewport->Size);
                GUI::SetNextWindowViewport(viewport->ID);
                GUI::PushStyleVar(imgui_styleVar_WindowRounding, 0.0f);
                GUI::PushStyleVar(imgui_styleVar_WindowBorderSize, 0.0f);
                wnd_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
                wnd_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
            }

            GUI::PushStyleVar(imgui_styleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            GUI::Begin("dockspace", &s_enable_dockspace, wnd_flags);
            GUI::PopStyleVar();

            if (full_screen) { GUI::PopStyleVar(2); }

            f32 min_size_x = s_imgui_style->WindowMinSize.x;
            s_imgui_style->WindowMinSize.x = 100.0f;
            s_imgui_style->Alpha = 1.0f;
            if (s_imgui_io->ConfigFlags & ImGuiConfigFlags_DockingEnable) {
                ImGuiID dockspace_id = GUI::GetID("DockSpace");
                GUI::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dock_flags);
            }
            s_imgui_style->WindowMinSize.x = min_size_x;
        }
    }
    void imgui_end_frame()
    {
        if (s_is_dockspace_enabled) { GUI::End(); }
        GUI::Render();
        drawer_update(GUI::GetDrawData());
        GUI::EndFrame();
        if (s_imgui_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GUI::UpdateWindows();
            GUI::RenderWindowsDefault();
        }
    }
}
#endif  // NW_OS && NW_GAPI