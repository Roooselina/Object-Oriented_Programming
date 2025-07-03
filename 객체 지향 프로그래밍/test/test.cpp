#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <gdiplus.h>
using namespace Gdiplus;

// Console window handle
static HWND hWnd;
// Program instance handle
static HINSTANCE hInst;

// Function to render a PNG image on the console
void Render(int x, int y)
{
    HDC hDC;
    static HDC hBackDC;
    HBITMAP hBackBitmap;
    RECT WindowRect;

    // Get the console window handle
    hWnd = GetConsoleWindow();
    if (hWnd == NULL) {
        printf("Failed to get console window handle.\n");
        return;
    }

    // Get the device context of the console window
    hDC = GetDC(hWnd);
    if (hDC == NULL) {
        printf("Failed to get device context.\n");
        return;
    }

    // Get the console window's client area
    GetClientRect(hWnd, &WindowRect);

    // Create a compatible DC for double buffering
    if (hBackDC == NULL) {
        hBackDC = CreateCompatibleDC(hDC);
        hBackBitmap = CreateCompatibleBitmap(hDC, WindowRect.right, WindowRect.bottom);
        SelectObject(hBackDC, hBackBitmap);
    }

    // Fill the back buffer with a solid color (e.g., white)
    FillRect(hBackDC, &WindowRect, (HBRUSH)(COLOR_WINDOW + 1));

    // Initialize GDI+
    ULONG_PTR gdiplusToken;
    GdiplusStartupInput gdiplusStartupInput;
    if (GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL) != Ok) {
        printf("Failed to initialize GDI+.\n");
        ReleaseDC(hWnd, hDC);
        return;
    }

    // Load the PNG image
    Gdiplus::Image image(L"C:\\Users\\kuroc\\Documents\\OOP lab files\\TestPNG.png");
    if (image.GetLastStatus() != Gdiplus::Ok) {
        printf("Failed to load PNG image.\n");
        GdiplusShutdown(gdiplusToken);
        ReleaseDC(hWnd, hDC);
        return;
    }

    // Use GDI+ to draw the image on the back buffer
    Graphics graphics(hBackDC);
    graphics.DrawImage(&image, x, y, image.GetWidth(), image.GetHeight());

    // Copy the back buffer to the actual device context to avoid flickering
    BitBlt(hDC, 0, 0, WindowRect.right, WindowRect.bottom, hBackDC, 0, 0, SRCCOPY);

    // Cleanup
    GdiplusShutdown(gdiplusToken);
    ReleaseDC(hWnd, hDC);
}

int main()
{
    // Example usage of the Render function
    int x = 50; // X coordinate to render the image
    int y = 50; // Y coordinate to render the image

    // Render the image at the specified coordinates
    Render(x, y);

    // Wait for a key press before exiting
    printf("Press any key to exit...\n");
    _getch();

    return 0;
}