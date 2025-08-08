/*=============================================================================
* HK_ClockWidget.h
===============================================================================
* Author: Henry King
* Version: 1.2
* Release Date: 8/1/2025
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

//Menu ID constants
#define IDM_CLOSE_APP 1001
#define IDM_ABOUT 1002
#define IDM_MILITARY_TIME 1003

/*=============================================================================
* Function Prototypes
=============================================================================*/
HFONT* ConstructFont(wchar_t* typeface);
void DestroyFont(HFONT* lpFont);

//Define a pointer (indivated by *) to a font handle.
HFONT* myFont;

int PASCAL WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevious, LPWSTR pCmdLine, int nCmdShow);
LRESULT WINAPI WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
