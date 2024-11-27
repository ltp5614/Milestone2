#include <windows.h>
#include <gdiplus.h>
#include <iostream>
#include "SVGDocuments.h"  // Đảm bảo rằng bạn có lớp SVGDocuments để xử lý SVG và render các phần tử

using namespace Gdiplus;

// Hàm xử lý vẽ lên cửa sổ
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_PAINT) {
        // Khởi tạo Graphics object với HDC
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        
        // Khởi tạo GDI+ Graphics
        Graphics graphics(hdc);

        graphics.Clear(Color(255, 255, 255));  // Màu trắng (RGB)
        
        // Tạo đối tượng SVGDocuments và render
        SVGDocuments svg;
        svg = svg.loadFile("sample.svg");
        svg.render(hdc); // Render vào HDC của cửa sổ
        
        EndPaint(hwnd, &ps);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}



int main() {
    // Khởi tạo GDI+
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // Định nghĩa cửa sổ
    const wchar_t* className = L"SVGWindowClass";  // Đặt tên lớp cửa sổ với Unicode
    WNDCLASSW wc = {0};  // Khởi tạo WNDCLASSW (để hỗ trợ Unicode)
    wc.lpfnWndProc = WindowProc;  // Chỉ định hàm xử lý cửa sổ
    wc.hInstance = GetModuleHandle(NULL);  // Lấy hInstance của ứng dụng
    wc.lpszClassName = className;  // Đặt tên lớp cửa sổ
    
    // Đảm bảo lớp cửa sổ được đăng ký
    if (!RegisterClassW(&wc)) {  // Dùng RegisterClassW thay vì RegisterClass
        DWORD dwError = GetLastError();  // Lấy mã lỗi nếu đăng ký thất bại
        MessageBoxW(NULL, L"Window class registration failed!", L"Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    // Tạo cửa sổ
    HWND hwnd = CreateWindowExW(0, className, L"SVG Renderer", WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
                               NULL, NULL, wc.hInstance, NULL);  // Dùng CreateWindowExW thay vì CreateWindowEx
    if (hwnd == NULL) {
        DWORD dwError = GetLastError();
        // Chuyển mã lỗi thành chuỗi để hiển thị thông báo chi tiết
        wchar_t errorMsg[256];
        swprintf(errorMsg, 256, L"CreateWindowEx failed with error code %lu", dwError);
        MessageBoxW(NULL, errorMsg, L"Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    // Hiển thị cửa sổ
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    // Main message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Dừng GDI+
    GdiplusShutdown(gdiplusToken);
    
    return 0;
}
