#include <windows.h>

int CALLBACK WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    MessageBox(0, (LPCTSTR)"This is a new setup", (LPCTSTR)"This is the caption", MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2);
    return 0;
};