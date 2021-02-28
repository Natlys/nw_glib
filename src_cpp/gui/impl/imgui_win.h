#ifndef NWG_GUI_WIN_H
#define NWG_GUI_WIN_H

#include <nwg_core.hpp>

namespace GUI
{
	NWG_API bool Win32Init(HWND pWindow);
	NWG_API void Win32Shutdown();
	NWG_API void Win32NewFrame();

	// --disable gamepad support or linking with xinput.lib
	//#define IMGUI_IMPL_WIN32_DISABLE_GAMEPAD
	//#define IMGUI_IMPL_WIN32_DISABLE_LINKING_XINPUT

	// --win32 message handler your application need to call.
	// --intentionally commented out in a '#if 0' block to avoid dragging dependencies on <windows.h> from this helper.
	// --you should COPY the line below into your .cpp code to forward declare the function and then you can call it.
	extern NWG_API LRESULT Win32MsgProc(HWND hWnd, UINT unMsg, WPARAM wParam, LPARAM lParam);
	/// --dpi-related helpers (optional)
	/// --use to enable dpi awareness without having to create an application manifest.
	/// --your own app may already do this via a manifest or explicit calls;
	/// --this is mostly useful for our examples/ apps.
	/// --in theory we could call simple functions from Windows sdr such as SetProcessDPIAware(), SetProcessDpiAwareness(), etc.
	/// but most of the functions provided by microsoft require windows 8.1/10+ sdk at compile time and windows 8/10+ at runtime,
	/// neither we want to require the user to have;
	/// -we dynamically select and load those functions to avoid dependencies.
	NWG_API void Win32EnableDpiAwareness();
	NWG_API float Win32GetDpiScaleForHwnd(HWND pWindow);
	NWG_API float Win32GetDpiScaleForMonitor(HMONITOR pMonitor);
}

#endif	// NWG_GUI_WIN_H