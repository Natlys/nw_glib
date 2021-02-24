#ifndef IMGUI_DX_H
#define IMGUI_DX_H
#include <nw_pch.hpp>
#include "../imgui_core.hpp"

struct ID3D11Device;
struct ID3D11DeviceContext;

namespace GUI
{
	IMGUI_IMPL_API bool Dx11Init(ID3D11Device* device, ID3D11DeviceContext* device_context);
	IMGUI_IMPL_API void Dx11Shutdown();
	IMGUI_IMPL_API void Dx11NewFrame();
	IMGUI_IMPL_API void Dx11RenderDrawData(ImDrawData* draw_data);

	// Use if you want to reset your rendering device without losing Dear ImGui state.
	IMGUI_IMPL_API void Dx11InvalidateDeviceObjects();
	IMGUI_IMPL_API bool Dx11CreateDeviceObjects();
}

#endif IMGUI_DX_H