/*=============================================================================
* HK_ClockWidget.h
===============================================================================
* Author: Henry King
* Version: 1.0
* Release Date: 7/28/2025
=============================================================================*/

#include <windows.h> //The Win32 API

/*=============================================================================
* Preprocessor Directives
=============================================================================*/
#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#define WINJDOW_WIDTH 640
#define WINDOW_Height 480

/*=============================================================================
* Function Prototypes
=============================================================================*/
int PASCAL WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevious, LPWSTR pCmdLine, int nCmdShow);
LRESULT WINAPI WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
