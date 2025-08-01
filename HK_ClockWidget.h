/*=============================================================================
* HK_ClockWidget.h
===============================================================================
* Author: Henry King
* Version: 1.1
* Release Date: 7/31/2025
=============================================================================*/

#include <windows.h> //The Win32 API
#include <windowsx.h> //Windows Macros

/*=============================================================================
* Preprocessor Directives
=============================================================================*/
#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 120

/*=============================================================================
* Function Prototypes
=============================================================================*/
HFONT* ConstructFont(wchar_t* typeface);
void DestroyFont(HFONT* lpFont);
int PASCAL WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevious, LPWSTR pCmdLine, int nCmdShow);
LRESULT WINAPI WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
