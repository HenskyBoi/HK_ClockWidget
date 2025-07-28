/*=============================================================================
*       hellowin.h
*       timwking1
*       28-Jul 2025
*
*       Unicode Hello World in the Windows API
*
=============================================================================*/

#include <windows.h>            //The Win32 API

/*=============================================================================
*   Preprocessor Directives
=============================================================================*/
#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

/*=============================================================================
*   Function prototypes
=============================================================================*/
int PASCAL WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevious, LPWSTR pCmdLine, int nCmdShow);
LRESULT WINAPI WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);