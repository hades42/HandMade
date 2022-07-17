#include <windows.h>

#define internal static
#define local_persist static
#define global_variable static

global_variable HBITMAP BitmapHandle;
global_variable BITMAPINFO BitmapInfo;
global_variable void *BitmapMemory;
global_variable HDC BitmapDeviceContext;

global_variable bool Running;

internal void Win32ResizeDIBSection(int Width, int Height)
{
    if(BitmapHandle){
        DeleteObject(BitmapHandle);
    } 

    if(!BitmapDeviceContext){
        BitmapDeviceContext = CreateCompatibleDC(0);
    }

    BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
    BitmapInfo.bmiHeader.biWidth = Width;
    BitmapInfo.bmiHeader.biHeight = Height;
    BitmapInfo.bmiHeader.biPlanes = 1;
    BitmapInfo.bmiHeader.biBitCount = 32;
    BitmapInfo.bmiHeader.biCompression = BI_RGB;

    BitmapHandle = CreateDIBSection(BitmapDeviceContext, &BitmapInfo,
                                    DIB_RGB_COLORS, &BitmapMemory, 0, 0);
}

internal void Win32UpdateWindow(HDC DeviceContext, int X, int Y, int Width, int Height)
{
    StretchDIBits(DeviceContext, X, Y, Width, Height, X, Y, Width, Height,
                  BitmapMemory, &BitmapInfo, DIB_RGB_COLORS, SRCCOPY);
}

// This function is responsible for handling Window (basically, record every activity that we did with the Window)
LRESULT CALLBACK MainWindowCallback(
    HWND Window,
    UINT Message,
    WPARAM WParam,
    LPARAM LParam)
{
    LRESULT Result = 0;

    switch (Message)
    {
    case WM_SIZE:
    {
        RECT ClientRect;
        GetClientRect(Window, &ClientRect);
        int Width = ClientRect.right - ClientRect.left;
        int Height = ClientRect.bottom - ClientRect.top;
        Win32ResizeDIBSection(Width, Height);
        break;
    }

    case WM_DESTROY:
    {
        // TODO: Handle this with an error - recreate window
        Running = false;
        break;
    }

    case WM_CLOSE:
    {
        // TODO: Handle this with a message to the user?
        Running = false;
        break;
    }

    case WM_ACTIVATEAPP:
    {
        OutputDebugStringA("WM_ACTIVATEAPP\n");
        break;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT Paint;
        HDC DeviceContent = BeginPaint(Window, &Paint);
        int X = Paint.rcPaint.left;
        int Y = Paint.rcPaint.top;
        int Width = Paint.rcPaint.right - Paint.rcPaint.left;
        int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
        Win32UpdateWindow(DeviceContent, X, Y, Width, Height);
        EndPaint(Window, &Paint);
        break;
    }

    default:
    {
        // OutputDebugStringA("default");
        Result = DefWindowProc(Window, Message, WParam, LParam);
        break;
    }
    }

    return (Result);
}

int CALLBACK WinMain(
    HINSTANCE Instance,
    HINSTANCE PrevInstance,
    LPSTR CommandLine,
    int ShowCode)
{
    WNDCLASS WindowClass = {};
    WindowClass.lpfnWndProc = MainWindowCallback;
    WindowClass.hInstance = Instance;
    WindowClass.lpszClassName = "HandmadeHeroWindowClass";

    if (RegisterClassA(&WindowClass))
    {

        HWND WindowHandle =
            CreateWindowExA(
                0,
                WindowClass.lpszClassName,
                "Handmade Hero",
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                0,
                0,
                Instance,
                0);

        if (WindowHandle)
        {
            Running = true;
            // Todo: Logging
            while (Running)
            {
                MSG Message;
                BOOL MessageResult = GetMessageA(&Message, 0, 0, 0);
                if (MessageResult > 0)
                {
                    TranslateMessage(&Message);
                    DispatchMessageA(&Message);
                }
                else
                {
                    break;
                }
            }
        }
    }
    else
    {
        // Todo: Logging
    }
    return 0;
};