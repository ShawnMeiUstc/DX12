#include "stdafx.h"
HWND Hwnd = nullptr;
LPCTSTR WindowName = L"SHAWNMEIAPP";
LPCTSTR WindowTitle = L"Mei Window";
int Width = 800;
int Height = 600;
bool FullScreen = false;
bool InitializeWindow(HINSTANCE hInstance, int showWind, int width, int height, bool fullScreen);
void mainloop();
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    // create the window
    if (!InitializeWindow(hInstance, nCmdShow, Width, Height, FullScreen))
    {
        MessageBox(0, L"Window Initialization - Failed",
            L"Error", MB_OK);
        return 0;
    }

    // start the main loop
    mainloop();

	return 0;
}

bool InitializeWindow(HINSTANCE hInstance, int showWind, int width, int height, bool fullScreen)
{
    if (fullScreen)
    {
        HMONITOR hmon = MonitorFromWindow(Hwnd, MONITOR_DEFAULTTONEAREST);
        MONITORINFO mInfo = { sizeof(mInfo) };
        GetMonitorInfo(hmon, &mInfo);
        width = mInfo.rcMonitor.right - mInfo.rcMonitor.left;
        height = mInfo.rcMonitor.bottom - mInfo.rcMonitor.top;
    }

    WNDCLASSEX wc;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = NULL;
    wc.cbWndExtra = NULL;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = WindowName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, L"Error registering class",
            L"Error", MB_OK | MB_ICONERROR);
        return false;
    }

    Hwnd = CreateWindowEx(NULL,
        WindowName,
        WindowTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width, height,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (!Hwnd)
    {
        MessageBox(NULL, L"Error creating window",
            L"Error", MB_OK | MB_ICONERROR);
        return false;
    }

    if (fullScreen)
    {
        SetWindowLong(Hwnd, GWL_STYLE, 0);
    }

    ShowWindow(Hwnd, showWind);
    UpdateWindow(Hwnd);

    return true;
}

void mainloop()
{
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else 
        {
            // run game code
        }
    }
}

LRESULT CALLBACK WndProc(HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (msg)
    {

    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) {
            if (MessageBox(0, L"Are you sure you want to exit?",
                L"Really?", MB_YESNO | MB_ICONQUESTION) == IDYES)
                DestroyWindow(hwnd);
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd,
        msg,
        wParam,
        lParam);
}
