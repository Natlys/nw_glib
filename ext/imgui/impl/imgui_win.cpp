#include <nw_pch.hpp>
#include "imgui_win.h"
#if (defined NW_PLATFORM_WINDOWS)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// Using XInput library for gamepad (with recent Windows SDK this may leads to executables which won't run on Windows 7)
#ifndef IMGUI_IMPL_WIN32_DISABLE_GAMEPAD
#include <XInput.h>
#else
#define IMGUI_IMPL_WIN32_DISABLE_LINKING_XINPUT
#endif
#if defined(_MSC_VER) && !defined(IMGUI_IMPL_WIN32_DISABLE_LINKING_XINPUT)
#pragma comment(lib, "xinput")
//#pragma comment(lib, "Xinput9_1_0")
#endif

namespace GUI
{
    // Win32 Data
    static HWND s_pCurrWnd = NULL;
    static INT64 s_nTime = 0;
    static INT64 s_nTicksPerSecond = 0;
    static ImGuiMouseCursor s_nLastCursor = ImGuiMouseCursor_COUNT;
    static bool s_bHasGamepad = false;
    static bool s_bWantUpdateGamepad = true;
    static bool s_bWantUpdateMonitors = true;

    // --==<forward_declarations>==--
    static void Win32InitPlatformInterface();
    static void Win32ShutdownPlatformInterface();
    static void Win32UpdateMonitors();
    static void Win32UpdateMousePos();
    static bool Win32UpdateMouseCursor();
    static void Win32UpdateGamepads();
    // --==</forward_declarations>==--

    // --==<functions>==--
    bool Win32Init(HWND pWnd) {
        if (!QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&s_nTicksPerSecond))) { return false; }
        if (!QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&s_nTime))) { return false; }
        // setup back-end capabilities flags
        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // we can honor GetMouseCursor() values (optional)
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;          // we can honor io.WantSetMousePos requests (optional, rarely used)
        io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;    // we can create multi-viewports on the Platform side (optional)
        io.BackendFlags |= ImGuiBackendFlags_HasMouseHoveredViewport; // we can set io.MouseHoveredViewport correctly (optional, not easy)
        io.BackendPlatformName = "imgui_win";

        // our mouse update function expect PlatformHandle to be filled for the main viewport
        s_pCurrWnd = pWnd;
        ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        main_viewport->PlatformHandle = main_viewport->PlatformHandleRaw = pWnd;
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) { Win32InitPlatformInterface(); }
        // keyboard mapping.
        // imgui will use those indices to peek into the io.KeysDown[] array that we will update during the application lifetime.
        io.KeyMap[ImGuiKey_Tab] = VK_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = VK_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = VK_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = VK_UP;
        io.KeyMap[ImGuiKey_DownArrow] = VK_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = VK_PRIOR;
        io.KeyMap[ImGuiKey_PageDown] = VK_NEXT;
        io.KeyMap[ImGuiKey_Home] = VK_HOME;
        io.KeyMap[ImGuiKey_End] = VK_END;
        io.KeyMap[ImGuiKey_Insert] = VK_INSERT;
        io.KeyMap[ImGuiKey_Delete] = VK_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = VK_BACK;
        io.KeyMap[ImGuiKey_Space] = VK_SPACE;
        io.KeyMap[ImGuiKey_Enter] = VK_RETURN;
        io.KeyMap[ImGuiKey_Escape] = VK_ESCAPE;
        io.KeyMap[ImGuiKey_KeyPadEnter] = VK_RETURN;
        io.KeyMap[ImGuiKey_A] = 'A';
        io.KeyMap[ImGuiKey_C] = 'C';
        io.KeyMap[ImGuiKey_V] = 'V';
        io.KeyMap[ImGuiKey_X] = 'X';
        io.KeyMap[ImGuiKey_Y] = 'Y';
        io.KeyMap[ImGuiKey_Z] = 'Z';

        return true;
    }
    void Win32Shutdown()
    {
        Win32ShutdownPlatformInterface();
        s_pCurrWnd = nullptr;
    }
    void Win32NewFrame()
    {
        ImGuiIO& io = ImGui::GetIO();
        IM_ASSERT(io.Fonts->IsBuilt() && "Font atlas not built!"
            "It is generally built by the renderer back-end."
            "Missing call to renderer _NewFrame() function? e.g."
            "OGLNewFrame().");

        // setup display size (every frame to accommodate for window resizing)
        RECT rect;
        GetClientRect(s_pCurrWnd, &rect);
        io.DisplaySize = ImVec2((float)(rect.right - rect.left), (float)(rect.bottom - rect.top));
        if (s_bWantUpdateMonitors) { Win32UpdateMonitors(); }

        // setup time step
        INT64 current_time;
        QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&current_time));
        io.DeltaTime = (float)(current_time - s_nTime) / s_nTicksPerSecond;
        s_nTime = current_time;

        // read keyboard modifiers inputs
        io.KeyCtrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
        io.KeyShift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
        io.KeyAlt = (GetKeyState(VK_MENU) & 0x8000) != 0;
        io.KeySuper = false;
        // io.KeysDown[], io.MousePos, io.MouseDown[], io.MouseWheel: filled by the WndProc handler below.
        // update os mouse position
        Win32UpdateMousePos();
        // update os mouse cursor with the cursor requested by imgui
        ImGuiMouseCursor mouse_cursor = io.MouseDrawCursor ? ImGuiMouseCursor_None : ImGui::GetMouseCursor();
        if (s_nLastCursor != mouse_cursor) {
            s_nLastCursor = mouse_cursor;
            Win32UpdateMouseCursor();
        }
        // update game controllers (if enabled and available)
        Win32UpdateGamepads();
    }

    static bool Win32UpdateMouseCursor()
    {
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange) { return false; }

        ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
        if (imgui_cursor == ImGuiMouseCursor_None || io.MouseDrawCursor) {
            // hide os mouse cursor if imgui is drawing it or if it wants no cursor
            SetCursor(NULL);
        }
        else {
            // show os mouse cursor
            LPTSTR win32_cursor = IDC_ARROW;
            switch (imgui_cursor) {
            case ImGuiMouseCursor_Arrow:        win32_cursor = IDC_ARROW; break;
            case ImGuiMouseCursor_TextInput:    win32_cursor = IDC_IBEAM; break;
            case ImGuiMouseCursor_ResizeAll:    win32_cursor = IDC_SIZEALL; break;
            case ImGuiMouseCursor_ResizeEW:     win32_cursor = IDC_SIZEWE; break;
            case ImGuiMouseCursor_ResizeNS:     win32_cursor = IDC_SIZENS; break;
            case ImGuiMouseCursor_ResizeNESW:   win32_cursor = IDC_SIZENESW; break;
            case ImGuiMouseCursor_ResizeNWSE:   win32_cursor = IDC_SIZENWSE; break;
            case ImGuiMouseCursor_Hand:         win32_cursor = IDC_HAND; break;
            case ImGuiMouseCursor_NotAllowed:   win32_cursor = IDC_NO; break;
            }
            SetCursor(LoadCursor(NULL, win32_cursor));
        }
        return true;
    }
    // this code supports multi-viewports (multiple os windows mapped into different dear imgui viewports)
    // because of that, it is a little more complicated than your typical single-viewport binding code!
    static void Win32UpdateMousePos()
    {
        ImGuiIO& io = ImGui::GetIO();
        // set os mouse position if requested (rarely used, only when ImGuiConfigFlags_NavEnableSetMousePos is enabled by user)
        // (when multi-viewports are enabled, all imgui positions are same as os positions)
        if (io.WantSetMousePos) {
            POINT pos = { (int)io.MousePos.x, (int)io.MousePos.y };
            if ((io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) == 0) { ClientToScreen(s_pCurrWnd, &pos); }
            SetCursorPos(pos.x, pos.y);
        }

        io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
        io.MouseHoveredViewport = 0;
        // set imgui mouse position
        POINT mouse_screen_pos;
        if (!GetCursorPos(&mouse_screen_pos)) { return; }
        if (HWND focused_hwnd = GetForegroundWindow()) {
            if (IsChild(focused_hwnd, s_pCurrWnd)) { focused_hwnd = s_pCurrWnd; }
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                // Multi-viewport mode: mouse position in OS absolute coordinates (io.MousePos is (0,0) when the mouse is on the upper-left of the primary monitor)
                // This is the position you can get with GetCursorPos(). In theory adding viewport->Pos is also the reverse operation of doing ScreenToClient().
                if (ImGui::FindViewportByPlatformHandle((void*)focused_hwnd) != NULL)
                    io.MousePos = ImVec2((float)mouse_screen_pos.x, (float)mouse_screen_pos.y);
            }
            else {
                // single viewport mode: mouse position in client window coordinates (io.MousePos is (0,0) when the mouse is on the upper-left corner of the app window.)
                // this is the position you can get with GetCursorPos() + ScreenToClient() or from WM_MOUSEMOVE.
                if (focused_hwnd == s_pCurrWnd) {
                    POINT mouse_client_pos = mouse_screen_pos;
                    ScreenToClient(focused_hwnd, &mouse_client_pos);
                    io.MousePos = ImVec2((float)mouse_client_pos.x, (float)mouse_client_pos.y);
                }
            }
        }
        // (optional) when using multiple viewports: set io.MouseHoveredViewport to the viewport the os mouse cursor is hovering;
        // important: this information is not easy to provide and many high-level windowing library won't be able to provide it correctly, because
        // - this is _ignoring_ viewports with the ImGuiViewportFlags_NoInputs flag (pass-through windows);
        // - this is _regardless_ of whether another viewport is focused or being dragged from;
        // if ImGuiBackendFlags_HasMouseHoveredViewport is not set by the back-end, imgui will ignore this field and infer the information by relying on the
        // rectangles and last focused time of every viewports it knows about;
        // it will be unaware of foreign windows that may be sitting between or over your windows.
        if (HWND hovered_hwnd = WindowFromPoint(mouse_screen_pos)) {
            if (ImGuiViewport* viewport = ImGui::FindViewportByPlatformHandle(static_cast<void*>(hovered_hwnd))) {
                if ((viewport->Flags & ImGuiViewportFlags_NoInputs) == 0) {
                    // FIXME: we still get our NoInputs window with WM_NCHITTEST/HTTRANSPARENT code when decorated?
                    io.MouseHoveredViewport = viewport->ID;
                }
            }
        }
    }
    // gamepad navigation mapping
    static void Win32UpdateGamepads()
    {
#ifndef IMGUI_IMPL_WIN32_DISABLE_GAMEPAD
        ImGuiIO& io = ImGui::GetIO();
        memset(io.NavInputs, 0, sizeof(io.NavInputs));
        if ((io.ConfigFlags & ImGuiConfigFlags_NavEnableGamepad) == 0)
            return;
        // calling XInputGetState() every frame on disconnected gamepads is unfortunately too slow.
        // instead we refresh gamepad availability by calling XInputGetCapabilities() _only_ after receiving WM_DEVICECHANGE.
        if (s_bWantUpdateGamepad) {
            XINPUT_CAPABILITIES caps;
            s_bHasGamepad = (XInputGetCapabilities(0, XINPUT_FLAG_GAMEPAD, &caps) == ERROR_SUCCESS);
            s_bWantUpdateGamepad = false;
        }
        XINPUT_STATE xinput_state;
        io.BackendFlags &= ~ImGuiBackendFlags_HasGamepad;
        if (s_bHasGamepad && XInputGetState(0, &xinput_state) == ERROR_SUCCESS) {
            const XINPUT_GAMEPAD& gamepad = xinput_state.Gamepad;
            io.BackendFlags |= ImGuiBackendFlags_HasGamepad;

#           define MAP_BUTTON(NAV_NO, BUTTON_ENUM)     { io.NavInputs[NAV_NO] = (gamepad.wButtons & BUTTON_ENUM) ? 1.0f : 0.0f; }
#           define MAP_ANALOG(NAV_NO, VALUE, V0, V1)   { float vn = (float)(VALUE - V0) / (float)(V1 - V0); if (vn > 1.0f) vn = 1.0f; if (vn > 0.0f && io.NavInputs[NAV_NO] < vn) io.NavInputs[NAV_NO] = vn; }
            MAP_BUTTON(ImGuiNavInput_Activate, XINPUT_GAMEPAD_A);              // Cross / A
            MAP_BUTTON(ImGuiNavInput_Cancel, XINPUT_GAMEPAD_B);              // Circle / B
            MAP_BUTTON(ImGuiNavInput_Menu, XINPUT_GAMEPAD_X);              // Square / X
            MAP_BUTTON(ImGuiNavInput_Input, XINPUT_GAMEPAD_Y);              // Triangle / Y
            MAP_BUTTON(ImGuiNavInput_DpadLeft, XINPUT_GAMEPAD_DPAD_LEFT);      // D-Pad Left
            MAP_BUTTON(ImGuiNavInput_DpadRight, XINPUT_GAMEPAD_DPAD_RIGHT);     // D-Pad Right
            MAP_BUTTON(ImGuiNavInput_DpadUp, XINPUT_GAMEPAD_DPAD_UP);        // D-Pad Up
            MAP_BUTTON(ImGuiNavInput_DpadDown, XINPUT_GAMEPAD_DPAD_DOWN);      // D-Pad Down
            MAP_BUTTON(ImGuiNavInput_FocusPrev, XINPUT_GAMEPAD_LEFT_SHOULDER);  // L1 / LB
            MAP_BUTTON(ImGuiNavInput_FocusNext, XINPUT_GAMEPAD_RIGHT_SHOULDER); // R1 / RB
            MAP_BUTTON(ImGuiNavInput_TweakSlow, XINPUT_GAMEPAD_LEFT_SHOULDER);  // L1 / LB
            MAP_BUTTON(ImGuiNavInput_TweakFast, XINPUT_GAMEPAD_RIGHT_SHOULDER); // R1 / RB
            MAP_ANALOG(ImGuiNavInput_LStickLeft, gamepad.sThumbLX, -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, -32768);
            MAP_ANALOG(ImGuiNavInput_LStickRight, gamepad.sThumbLX, +XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, +32767);
            MAP_ANALOG(ImGuiNavInput_LStickUp, gamepad.sThumbLY, +XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, +32767);
            MAP_ANALOG(ImGuiNavInput_LStickDown, gamepad.sThumbLY, -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, -32767);
#undef MAP_BUTTON
#undef MAP_ANALOG
        }
#endif // #ifndef IMGUI_IMPL_WIN32_DISABLE_GAMEPAD
    }

    static BOOL CALLBACK Win32UpdateMonitorsEnumFunc(HMONITOR monitor, HDC, LPRECT, LPARAM)
    {
        MONITORINFO info = { 0 };
        info.cbSize = sizeof(MONITORINFO);
        if (!GetMonitorInfo(monitor, &info)) { return TRUE; }
        ImGuiPlatformMonitor imgui_monitor;
        imgui_monitor.MainPos = ImVec2((float)info.rcMonitor.left, (float)info.rcMonitor.top);
        imgui_monitor.MainSize = ImVec2((float)(info.rcMonitor.right - info.rcMonitor.left), (float)(info.rcMonitor.bottom - info.rcMonitor.top));
        imgui_monitor.WorkPos = ImVec2((float)info.rcWork.left, (float)info.rcWork.top);
        imgui_monitor.WorkSize = ImVec2((float)(info.rcWork.right - info.rcWork.left), (float)(info.rcWork.bottom - info.rcWork.top));
        imgui_monitor.DpiScale = Win32GetDpiScaleForMonitor(monitor);
        ImGuiPlatformIO& io = ImGui::GetPlatformIO();
        if (info.dwFlags & MONITORINFOF_PRIMARY) { io.Monitors.push_front(imgui_monitor); }
        else { io.Monitors.push_back(imgui_monitor); }
        return TRUE;
    }
    
    static void Win32UpdateMonitors()
    {
        ImGui::GetPlatformIO().Monitors.resize(0);
        EnumDisplayMonitors(NULL, NULL, Win32UpdateMonitorsEnumFunc, NULL);
        s_bWantUpdateMonitors = false;
    }
    // allow compilation with old windows sdk. mingw doesn't have default _WIN32_WINNT/WINVER versions.
#ifndef WM_MOUSEHWHEEL
#define WM_MOUSEHWHEEL 0x020E
#endif
#ifndef DBT_DEVNODES_CHANGED
#define DBT_DEVNODES_CHANGED 0x0007
#endif
// Win32 message handler (process Win32 mouse/keyboard inputs, etc.)
// call from your application's message handler.
// when implementing your own back-end, you can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if Dear ImGui wants to use your inputs;
// --when io.WantCaptureMouse is true, do not dispatch mouse input data to your main application;
// --when io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application;
// generally you may always pass all inputs to Dear ImGui, and hide them from your application based on those two flags;
// ps: in this Win32 handler, we use the capture api (GetCapture/SetCapture/ReleaseCapture) to be able to read mouse coordinates when dragging mouse outside of our window bounds.
// ps: we treat DBLCLK messages as regular mouse down messages, so this code will work on windows classes that have the CS_DBLCLKS flag set. our own example app code doesn't set this flag.
#if 0
// copy this line into your .cpp file to forward declare the function.
    extern IMGUI_IMPL_API LRESULT Win32WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif
    IMGUI_IMPL_API LRESULT Win32WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        if (ImGui::GetCurrentContext() == NULL)
            return 0;

        ImGuiIO& io = ImGui::GetIO();
        switch (msg)
        {
        case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
        case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
        case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
        case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK:
        {
            int button = 0;
            if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONDBLCLK) { button = 0; }
            if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONDBLCLK) { button = 1; }
            if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONDBLCLK) { button = 2; }
            if (msg == WM_XBUTTONDOWN || msg == WM_XBUTTONDBLCLK) { button = (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) ? 3 : 4; }
            if (!ImGui::IsAnyMouseDown() && GetCapture() == NULL) { SetCapture(hwnd); }
            io.MouseDown[button] = true;
            return 0;
        }
        case WM_LBUTTONUP: case WM_RBUTTONUP: case WM_MBUTTONUP: case WM_XBUTTONUP: {
            int button = 0;
            if (msg == WM_LBUTTONUP) { button = 0; }
            if (msg == WM_RBUTTONUP) { button = 1; }
            if (msg == WM_MBUTTONUP) { button = 2; }
            if (msg == WM_XBUTTONUP) { button = (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) ? 3 : 4; }
            io.MouseDown[button] = false;
            if (!ImGui::IsAnyMouseDown() && GetCapture() == hwnd) { ReleaseCapture(); }
            return 0;
        }
        case WM_MOUSEWHEEL: io.MouseWheel += (float)GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA;
            return 0;
        case WM_MOUSEHWHEEL: io.MouseWheelH += (float)GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA;
            return 0;
        case WM_KEYDOWN: case WM_SYSKEYDOWN:
            if (wParam < 256) { io.KeysDown[wParam] = true; }
            return 0;
        case WM_KEYUP: case WM_SYSKEYUP:
            if (wParam < 256) { io.KeysDown[wParam] = false; }
            return 0;
        case WM_CHAR:
            // you can also use ToAscii()+GetKeyboardState() to retrieve characters.
            if (wParam > 0 && wParam < 0x10000) { io.AddInputCharacterUTF16((unsigned short)wParam); }
            return 0;
        case WM_SETCURSOR:
            if (LOWORD(lParam) == HTCLIENT && Win32UpdateMouseCursor()) { return 1; }
            return 0;
        case WM_DEVICECHANGE:
            if (static_cast<UINT>(wParam) == DBT_DEVNODES_CHANGED) { s_bWantUpdateGamepad = true; }
            return 0;
        case WM_DISPLAYCHANGE: { s_bWantUpdateMonitors = true; }
            return 0;
        }
        return 0;
    }
    //--------------------------------------------------------------------------------------------------------
    // dpi-related helpers (optional)
    //--------------------------------------------------------------------------------------------------------
    // --use to enable DPI awareness without having to create an application manifest.
    // --your own app may already do this via a manifest or explicit calls. This is mostly useful for our examples/ apps.
    // --in theory we could call simple functions from Windows SDK such as SetProcessDPIAware(), SetProcessDpiAwareness(), etc.
    //   but most of the functions provided by Microsoft require Windows 8.1/10+ SDK at compile time and Windows 8/10+ at runtime,
    //   neither we want to require the user to have. So we dynamically select and load those functions to avoid dependencies.
    //---------------------------------------------------------------------------------------------------------
    // this is the scheme successfully used by glfw (from which we borrowed some of the code) and other apps aiming to be highly portable.
    // Win32EnableDpiAwareness() is just a helper called by main.cpp, we don't call it automatically.
    // if you are trying to implement your own back-end for your own engine, you may ignore that noise.
    //---------------------------------------------------------------------------------------------------------
    // implement some of the functions and types normally declared in recent windows sdk.
#if !defined(_versionhelpers_H_INCLUDED_) && !defined(_INC_VERSIONHELPERS)
    static BOOL IsWindowsVersionOrGreater(WORD major, WORD minor, WORD sp)
    {
        OSVERSIONINFOEXW osvi = { sizeof(osvi), major, minor, 0, 0, { 0 }, sp, 0, 0, 0, 0 };
        DWORD mask = VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR;
        ULONGLONG cond = VerSetConditionMask(0, VER_MAJORVERSION, VER_GREATER_EQUAL);
        cond = VerSetConditionMask(cond, VER_MINORVERSION, VER_GREATER_EQUAL);
        cond = VerSetConditionMask(cond, VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL);
        return VerifyVersionInfoW(&osvi, mask, cond);
    }
#define IsWindows8Point1OrGreater()  IsWindowsVersionOrGreater(HIBYTE(0x0602), LOBYTE(0x0602), 0) // _WIN32_WINNT_WINBLUE
#endif

#ifndef DPI_ENUMS_DECLARED
    typedef enum { PROCESS_DPI_UNAWARE = 0, PROCESS_SYSTEM_DPI_AWARE = 1, PROCESS_PER_MONITOR_DPI_AWARE = 2 } PROCESS_DPI_AWARENESS;
    typedef enum { MDT_EFFECTIVE_DPI = 0, MDT_ANGULAR_DPI = 1, MDT_RAW_DPI = 2, MDT_DEFAULT = MDT_EFFECTIVE_DPI } MONITOR_DPI_TYPE;
#endif
#ifndef _DPI_AWARENESS_CONTEXTS_
    DECLARE_HANDLE(DPI_AWARENESS_CONTEXT);
#define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE    (DPI_AWARENESS_CONTEXT)-3
#endif
#ifndef DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2
#define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 (DPI_AWARENESS_CONTEXT)-4
#endif
    typedef HRESULT(WINAPI* PFN_SetProcessDpiAwareness)(PROCESS_DPI_AWARENESS);                     // Shcore.lib + dll, Windows 8.1+
    typedef HRESULT(WINAPI* PFN_GetDpiForMonitor)(HMONITOR, MONITOR_DPI_TYPE, UINT*, UINT*);        // Shcore.lib + dll, Windows 8.1+
    typedef DPI_AWARENESS_CONTEXT(WINAPI* PFN_SetThreadDpiAwarenessContext)(DPI_AWARENESS_CONTEXT); // User32.lib + dll, Windows 10 v1607+ (Creators Update)

    // helper function to enable dpi awareness without setting up a manifest
    void Win32EnableDpiAwareness()
    {
        // make sure monitors will be updated with latest correct scaling
        s_bWantUpdateMonitors = true;

        // if (IsWindows10OrGreater()) // this needs a manifest to succeed; instead we try to grab the function pointer!
        {
            static HINSTANCE user32_dll = ::LoadLibraryA("user32.dll"); // reference counted per-process
            if (PFN_SetThreadDpiAwarenessContext SetThreadDpiAwarenessContextFn =
                (PFN_SetThreadDpiAwarenessContext)::GetProcAddress(user32_dll, "SetThreadDpiAwarenessContext")) {
                SetThreadDpiAwarenessContextFn(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
                return;
            }
        }
        if (IsWindows8Point1OrGreater()) {
            static HINSTANCE shcore_dll = ::LoadLibraryA("shcore.dll"); // reference counted per-process
            if (PFN_SetProcessDpiAwareness SetProcessDpiAwarenessFn =
                (PFN_SetProcessDpiAwareness)::GetProcAddress(shcore_dll, "SetProcessDpiAwareness")) {
                SetProcessDpiAwarenessFn(PROCESS_PER_MONITOR_DPI_AWARE);
                return;
            }
        }
#if _WIN32_WINNT >= 0x0600
        SetProcessDPIAware();
#endif
    }
#if defined(_MSC_VER) && !defined(NOGDI)
#pragma comment(lib, "gdi32")   // link with gdi32.lib for GetDeviceCaps()
#endif
    float Win32GetDpiScaleForMonitor(HMONITOR pMonitor)
    {
        unsigned int xdpi = 96, ydpi = 96;
        static bool bIsWindows8Point1OrGreater = IsWindows8Point1OrGreater();
        if (bIsWindows8Point1OrGreater) {
            static HINSTANCE shcore_dll = LoadLibraryA("shcore.dll"); // reference counted per-process
            if (PFN_GetDpiForMonitor GetDpiForMonitorFn = (PFN_GetDpiForMonitor)::GetProcAddress(shcore_dll, "GetDpiForMonitor")) {
                GetDpiForMonitorFn(pMonitor, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
            }
        }
#ifndef NOGDI
        else {
            const HDC dc = GetDC(NULL);
            xdpi = GetDeviceCaps(dc, LOGPIXELSX);
            ydpi = GetDeviceCaps(dc, LOGPIXELSY);
            ReleaseDC(NULL, dc);
        }
#endif
        IM_ASSERT(xdpi == ydpi); // Please contact me if you hit this assert!
        return xdpi / 96.0f;
    }
    float Win32GetDpiScaleForHwnd(HWND pWnd)
    {
        HMONITOR monitor = MonitorFromWindow(pWnd, MONITOR_DEFAULTTONEAREST);
        return Win32GetDpiScaleForMonitor(monitor);
    }
    //--------------------------------------------------------------------------------------------------------
    // ime (input method editor) basic support for e.g. asian language users
    //--------------------------------------------------------------------------------------------------------
#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_APP) // uwp doesn't have win32 functions
#define IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS
#endif
#if defined(_WIN32) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS) && !defined(IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS) && !defined(__GNUC__)
#define HAS_WIN32_IME   1
#include <imm.h>
#ifdef _MSC_VER
#pragma comment(lib, "imm32")
#endif
    static void Win32SetImeInputPos(ImGuiViewport* viewport, ImVec2 pos)
    {
        COMPOSITIONFORM cf = { CFS_FORCE_POSITION,
            { static_cast<LONG>(pos.x - viewport->Pos.x), static_cast<LONG>(pos.y - viewport->Pos.y) },{ 0, 0, 0, 0 } };
        if (HWND hwnd = (HWND)viewport->PlatformHandle) {
            if (HIMC himc = ::ImmGetContext(hwnd)) {
                ImmSetCompositionWindow(himc, &cf);
                ImmReleaseContext(hwnd, himc);
            }
        }
    }
#else
#define HAS_WIN32_IME   0
#endif
    // --==</functions>==--

//--------------------------------------------------------------------------------------------------------
// MULTI-VIEWPORT / PLATFORM INTERFACE SUPPORT
// this is an _advanced_ and _optional_ feature, allowing the back-end to create and handle multiple viewports simultaneously.
// if you are new to dear imgui or creating a new binding for dear imgui, it is recommended that you completely ignore this section first..
//--------------------------------------------------------------------------------------------------------

// helper structure we store in the void* RenderUserData field of each ImGuiViewport to easily retrieve our backend data.
    struct Win32ViewportData
    {
        HWND    Hwnd;
        bool    HwndOwned;
        DWORD   DwStyle;
        DWORD   DwExStyle;

        Win32ViewportData() { Hwnd = NULL; HwndOwned = false;  DwStyle = DwExStyle = 0; }
        ~Win32ViewportData() { IM_ASSERT(Hwnd == NULL); }
    };

    // --getters
    static ImVec2 Win32GetWindowPos(ImGuiViewport* viewport)
    {
        Win32ViewportData* data = (Win32ViewportData*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        POINT pos = { 0, 0 };
        ClientToScreen(data->Hwnd, &pos);
        return ImVec2((float)pos.x, (float)pos.y);
    }
    static void Win32SetWindowPos(ImGuiViewport* viewport, ImVec2 pos)
    {
        Win32ViewportData* data = (Win32ViewportData*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        RECT rect = { (LONG)pos.x, (LONG)pos.y, (LONG)pos.x, (LONG)pos.y };
        AdjustWindowRectEx(&rect, data->DwStyle, FALSE, data->DwExStyle);
        SetWindowPos(data->Hwnd, NULL, rect.left, rect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
    }
    static ImVec2 Win32GetWindowSize(ImGuiViewport* viewport)
    {
        Win32ViewportData* data = (Win32ViewportData*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        RECT rect;
        GetClientRect(data->Hwnd, &rect);
        return ImVec2(float(rect.right - rect.left), float(rect.bottom - rect.top));
    }
    static bool Win32GetWindowFocus(ImGuiViewport* viewport)
    {
        Win32ViewportData* data = (Win32ViewportData*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        return GetForegroundWindow() == data->Hwnd;
    }
    static bool Win32GetWindowMinimized(ImGuiViewport* viewport)
    {
        Win32ViewportData* data = (Win32ViewportData*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        return IsIconic(data->Hwnd) != 0;
    }
    static float Win32GetWindowDpiScale(ImGuiViewport* viewport)
    {
        Win32ViewportData* data = (Win32ViewportData*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        return Win32GetDpiScaleForHwnd(data->Hwnd);
    }
    // --setters
    static void Win32SetWindowSize(ImGuiViewport* viewport, ImVec2 size)
    {
        Win32ViewportData* data = (Win32ViewportData*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        RECT rect = { 0, 0, (LONG)size.x, (LONG)size.y };
        AdjustWindowRectEx(&rect, data->DwStyle, FALSE, data->DwExStyle); // client to Screen
        SetWindowPos(data->Hwnd, NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top,
            SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
    }
    static void Win32SetWindowFocus(ImGuiViewport* viewport)
    {
        Win32ViewportData* data = (Win32ViewportData*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        BringWindowToTop(data->Hwnd);
        SetForegroundWindow(data->Hwnd);
        SetFocus(data->Hwnd);
    }
    static void Win32SetWindowTitle(ImGuiViewport* viewport, const char* title)
    {
        // SetWindowTextA() doesn't properly handle utf-8 so we explicitely convert our string;
        Win32ViewportData* data = (Win32ViewportData*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        int n = MultiByteToWideChar(CP_UTF8, 0, title, -1, NULL, 0);
        ImVector<wchar_t> title_w;
        title_w.resize(n);
        MultiByteToWideChar(CP_UTF8, 0, title, -1, title_w.Data, n);
        SetWindowTextW(data->Hwnd, title_w.Data);
    }
    static void Win32SetWindowAlpha(ImGuiViewport* viewport, float alpha)
    {
        Win32ViewportData* data = (Win32ViewportData*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        IM_ASSERT(alpha >= 0.0f && alpha <= 1.0f);
        if (alpha < 1.0f) {
            DWORD style = GetWindowLongW(data->Hwnd, GWL_EXSTYLE) | WS_EX_LAYERED;
            SetWindowLongW(data->Hwnd, GWL_EXSTYLE, style);
            SetLayeredWindowAttributes(data->Hwnd, 0, (BYTE)(255 * alpha), LWA_ALPHA);
        }
        else {  // get rid of transparency
            DWORD style = GetWindowLongW(data->Hwnd, GWL_EXSTYLE) & ~WS_EX_LAYERED;
            SetWindowLongW(data->Hwnd, GWL_EXSTYLE, style);
        }
    }

    // --==<core_methods>==--
    static void Win32GetStyleFromViewportFlags(ImGuiViewportFlags flags, DWORD* out_style, DWORD* out_ex_style)
    {
        if (flags & ImGuiViewportFlags_NoDecoration) { *out_style = WS_POPUP; }
        else { *out_style = WS_OVERLAPPEDWINDOW; }

        if (flags & ImGuiViewportFlags_NoTaskBarIcon) { *out_ex_style = WS_EX_TOOLWINDOW; }
        else { *out_ex_style = WS_EX_APPWINDOW; }

        if (flags & ImGuiViewportFlags_TopMost) { *out_ex_style |= WS_EX_TOPMOST; }
    }

    static void Win32CreateWindow(ImGuiViewport* viewport)
    {
        Win32ViewportData* data = IM_NEW(Win32ViewportData)();
        viewport->PlatformUserData = data;

        // --select style and parent window
        Win32GetStyleFromViewportFlags(viewport->Flags, &data->DwStyle, &data->DwExStyle);
        HWND parent_window = NULL;
        if (viewport->ParentViewportId != 0) {
            if (ImGuiViewport* parent_viewport = ImGui::FindViewportByID(viewport->ParentViewportId)) {
                parent_window = (HWND)parent_viewport->PlatformHandle;
            }
        }

        // --create window
        RECT rect = { (LONG)viewport->Pos.x, (LONG)viewport->Pos.y, (LONG)(viewport->Pos.x + viewport->Size.x), (LONG)(viewport->Pos.y + viewport->Size.y) };
        AdjustWindowRectEx(&rect, data->DwStyle, FALSE, data->DwExStyle);
        data->Hwnd = ::CreateWindowEx(
            data->DwExStyle, _T("ImGui Platform"), _T("Untitled"), data->DwStyle,   // style, class name, window name
            rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,    // window area
            parent_window, NULL, GetModuleHandle(NULL), NULL);                    // parent window, menu, instance, param
        data->HwndOwned = true;
        viewport->PlatformRequestResize = false;
        viewport->PlatformHandle = viewport->PlatformHandleRaw = data->Hwnd;
    }
    static void Win32DestroyWindow(ImGuiViewport* viewport)
    {
        if (Win32ViewportData* data = (Win32ViewportData*)viewport->PlatformUserData)
        {
            if (GetCapture() == data->Hwnd) {
                // transfer capture so if we started dragging from a window that later disappears, we'll still receive the MOUSEUP event.
                ReleaseCapture();
                SetCapture(s_pCurrWnd);
            }
            if (data->Hwnd && data->HwndOwned) { DestroyWindow(data->Hwnd); }
            data->Hwnd = NULL;
            IM_DELETE(data);
        }
        viewport->PlatformUserData = viewport->PlatformHandle = NULL;
    }

    static void Win32ShowWindow(ImGuiViewport* viewport)
    {
        Win32ViewportData* data = (Win32ViewportData*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        if (viewport->Flags & ImGuiViewportFlags_NoFocusOnAppearing) { ShowWindow(data->Hwnd, SW_SHOWNA); }
        else { ShowWindow(data->Hwnd, SW_SHOW); }
    }
    static void Win32UpdateWindow(ImGuiViewport* viewport)
    {
        // (Optional) Update Win32 style if it changed _after_ creation.
        // Generally they won't change unless configuration flags are changed, but advanced uses (such as manually rewriting viewport flags) make this useful.
        Win32ViewportData* data = (Win32ViewportData*)viewport->PlatformUserData;
        IM_ASSERT(data->Hwnd != nullptr);
        DWORD new_style;
        DWORD new_ex_style;
        Win32GetStyleFromViewportFlags(viewport->Flags, &new_style, &new_ex_style);

        // Only reapply the flags that have been changed from our point of view (as other flags are being modified by Windows)
        if (data->DwStyle != new_style || data->DwExStyle != new_ex_style) {
            data->DwStyle = new_style;
            data->DwExStyle = new_ex_style;
            SetWindowLong(data->Hwnd, GWL_STYLE, data->DwStyle);
            SetWindowLong(data->Hwnd, GWL_EXSTYLE, data->DwExStyle);
            RECT rect = { (LONG)viewport->Pos.x, (LONG)viewport->Pos.y, (LONG)(viewport->Pos.x + viewport->Size.x), (LONG)(viewport->Pos.y + viewport->Size.y) };
            AdjustWindowRectEx(&rect, data->DwStyle, FALSE, data->DwExStyle); // Client to Screen
            SetWindowPos(data->Hwnd, NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
            ShowWindow(data->Hwnd, SW_SHOWNA); // This is necessary when we alter the style
            viewport->PlatformRequestMove = viewport->PlatformRequestResize = true;
        }
    }

    // fixme-dpi: testing dpi related ideas
    static void Win32OnChangedViewport(ImGuiViewport* viewport)
    {
        (void)viewport;
#if 0
        ImGuiStyle default_style;
        //default_style.WindowPadding = ImVec2(0, 0);
        //default_style.WindowBorderSize = 0.0f;
        //default_style.ItemSpacing.y = 3.0f;
        //default_style.FramePadding = ImVec2(0, 0);
        default_style.ScaleAllSizes(viewport->DpiScale);
        ImGuiStyle& style = ImGui::GetStyle();
        style = default_style;
#endif
    }

    static LRESULT CALLBACK Win32WndProcPlatformWindow(HWND pWindow, UINT unMsg, WPARAM wParam, LPARAM lParam)
    {
        if (Win32WndProcHandler(pWindow, unMsg, wParam, lParam)) { return true; }

        if (ImGuiViewport* viewport = ImGui::FindViewportByPlatformHandle((void*)pWindow)) {
            switch (unMsg) {
            case WM_CLOSE: { viewport->PlatformRequestClose = true; }
                return 0;
            case WM_MOVE: { viewport->PlatformRequestMove = true; }
                break;
            case WM_SIZE: { viewport->PlatformRequestResize = true; }
                break;
            case WM_MOUSEACTIVATE:
                if (viewport->Flags & ImGuiViewportFlags_NoFocusOnClick) { return MA_NOACTIVATE; }
                break;
            case WM_NCHITTEST:
                // let mouse pass-through the window; this will allow the back-end to set io.MouseHoveredViewport properly (which is optional);
                // the ImGuiViewportFlags_NoInputs flag is set while dragging a viewport, as want to detect the window behind the one we are dragging;
                // if you cannot easily access those viewport flags from your windowing/event code: you may manually synchronize its state e.g. in
                // your main loop after calling UpdatePlatformWindows(). Iterate all viewports/platform windows and pass the flag to your windowing system.
                if (viewport->Flags & ImGuiViewportFlags_NoInputs) { return HTTRANSPARENT; }
                break;
            default: break;
            }
        }
        return DefWindowProc(pWindow, unMsg, wParam, lParam);
    }

    static void Win32InitPlatformInterface()
    {
        WNDCLASSEX wcex;
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = Win32WndProcPlatformWindow;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = ::GetModuleHandle(NULL);
        wcex.hIcon = NULL;
        wcex.hCursor = NULL;
        wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND + 1);
        wcex.lpszMenuName = NULL;
        wcex.lpszClassName = _T("ImGui Platform");
        wcex.hIconSm = NULL;
        ::RegisterClassEx(&wcex);

        Win32UpdateMonitors();

        // --register platform interface (will be coupled with a renderer interface)
        ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();
        platform_io.Platform_CreateWindow = Win32CreateWindow;
        platform_io.Platform_DestroyWindow = Win32DestroyWindow;
        platform_io.Platform_ShowWindow = Win32ShowWindow;
        platform_io.Platform_SetWindowPos = Win32SetWindowPos;
        platform_io.Platform_GetWindowPos = Win32GetWindowPos;
        platform_io.Platform_SetWindowSize = Win32SetWindowSize;
        platform_io.Platform_GetWindowSize = Win32GetWindowSize;
        platform_io.Platform_SetWindowFocus = Win32SetWindowFocus;
        platform_io.Platform_GetWindowFocus = Win32GetWindowFocus;
        platform_io.Platform_GetWindowMinimized = Win32GetWindowMinimized;
        platform_io.Platform_SetWindowTitle = Win32SetWindowTitle;
        platform_io.Platform_SetWindowAlpha = Win32SetWindowAlpha;
        platform_io.Platform_UpdateWindow = Win32UpdateWindow;
        platform_io.Platform_GetWindowDpiScale = Win32GetWindowDpiScale; // FIXME-DPI
        platform_io.Platform_OnChangedViewport = Win32OnChangedViewport; // FIXME-DPI
#if HAS_WIN32_IME
        platform_io.Platform_SetImeInputPos = Win32SetImeInputPos;
#endif

        // --register main window handle (which is owned by the main application, not by us)
        // --this is mostly for simplicity and consistency, so that our code (e.g. mouse handling etc.)
        // --can use same logic for main and secondary viewports.
        ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        Win32ViewportData* data = IM_NEW(Win32ViewportData)();
        data->Hwnd = s_pCurrWnd;
        data->HwndOwned = false;
        main_viewport->PlatformUserData = data;
        main_viewport->PlatformHandle = static_cast<void*>(s_pCurrWnd);
    }
    static void Win32ShutdownPlatformInterface() { UnregisterClass(_T("ImGui Platform"), GetModuleHandle(NULL)); }
    // --==</core_functions>==--
}
#endif  // NW_PLATFORM_WINDOWS