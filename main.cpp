#include <windows.h>

#include "nano_window.hpp"

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) {
    MSG msg;
    HWND hwnd;
    WNDCLASSW wc;

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.lpszClassName = L"Window";
    wc.hInstance = hThisInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpszMenuName = NULL;
    wc.lpfnWndProc = WindowProcedure;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassW(&wc);
    hwnd = CreateWindowW(wc.lpszClassName, L"Nano Calc", WS_OVERLAPPED | WS_SYSMENU, 100, 100, 800, 600, NULL, NULL,
                         hThisInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    NanoWindow nano(hwnd);
    switch (message) {
        case WM_CREATE:
            nano.onCreate();
            break;
        case WM_COMMAND:
            nano.executeEvent(LOWORD(wParam), HIWORD(wParam));
            break;
        case WM_HSCROLL:
            nano.onHTrack();
            break;
        case WM_VSCROLL:
            nano.onVTrack();
            break;
        case WM_PAINT:
            nano.paint();
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProcW(hwnd, message, wParam, lParam);
}
