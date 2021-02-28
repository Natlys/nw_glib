#ifndef NWG_GUI_DX_H
#define NWG_GUI_DX_H
#include <nwg_core.hpp>

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ImDrawData;
namespace GUI
{
	NWG_API bool Dx11Init(ID3D11Device* device, ID3D11DeviceContext* device_context);
	NWG_API void Dx11Shutdown();
	NWG_API void Dx11NewFrame();
	NWG_API void Dx11RenderDrawData(ImDrawData* draw_data);
	// use if you want to reset your rendering device without losing dear imgui state.
	NWG_API void Dx11InvalidateDeviceObjects();
	NWG_API bool Dx11CreateDeviceObjects();
}

#endif	// NWG_GUI_DX_H