/*=============================================================================
* HK_ClockWidget.c
===============================================================================
* Author: Henry King
* Version: Beta 1.0
* Release Date: 7/30/2025
=============================================================================*/

#include "HK_ClockWidget.h"

/*=============================================================================
*   wWinMain [int]
*       The entry point of a Unicode win32 application.
*
*       HINSTANCE hInstance    The instance handle of the process.
*       HINSTANCE hPrevious    Handle of previous instance (if it exists).
*       LPWSTR lpszCmdLine     Long pointer to command line string.
*       int nCmdShow           Controls how the window is to be shown.
*
=============================================================================*/
int PASCAL WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevious, LPWSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	const wchar_t* CLASS_NAME = L"MainWindow";
	static WNDCLASSEXW wc = {0};

	//Set each member of the WNDCLASSEXW struct...
	wc.cbSize = sizeof(WNDCLASSEX);                    //class struct size in bytes
	wc.style = CS_HREDRAW | CS_VREDRAW;                //class style (CS_)
	wc.lpfnWndProc = WindowProc;                       //long pointer to window procedure function
	wc.cbClsExtra = 0;                                 //extra bytes to allocate for the class
	wc.cbWndExtra = 0;                                 //extra bytes to allocate for the window instance
	wc.hInstance = hInstance;                          //instance handle
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);        //icon (IDI_)
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);          //cursor (IDC_)
	wc.hbrBackground = (HBRUSH) (COLOR_WINDOW +1);     //background brush handle
	wc.lpszMenuName = NULL;                            //resource name of class menu
	wc.lpszClassName = CLASS_NAME;                     //class name  string
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);      //small version of the icon (IDI_)

	/*
	*   The Window class only needs to be registered once.
	*   If there is a previous instance handle, we do NOT register the class again.
	*/
	if (!hPrevious)
	{
		if(!RegisterClassEx(&wc))
		{
			//This should never happen, but we inform the user and return gracefully in case it does.
			MessageBoxW(NULL, L"Window Registration Failed", L"Error", MB_ICONERROR | MB_OK);
			return -1;
		}
	}

	hwnd = CreateWindowExW
	(
		0,                      //dwExStyle
		CLASS_NAME,             //lpClassName
		L"HK_CLockWidget",      //lpWindowName (title bar text)
		WS_OVERLAPPEDWINDOW,    //dwStyle
		CW_USEDEFAULT,          //X position
		CW_USEDEFAULT,          //Y position
		WINDOW_WIDTH,           //nWidth
		WINDOW_HEIGHT,          //nHeight
		NULL,                   //hWndParent
		NULL,                   //hMenu (use this to set a menu bar)
		hInstance,              //hInstance
		NULL                    //lpParam
	);

	if (hwnd == NULL)
	{
		//Again, this should never happen suince we just created hWnd, but just in case, inform the user and return gracefully.
		MessageBoxW(NULL, L"Window Creation Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	ShowWindow(hwnd, nCmdShow);
	//Finally, now that the window is fully initialized, we can begin ticking the message loop.
	while(GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
/*=============================================================================
*   WindowProc [LRESULT]
*       The Window Procedure
*
*       HWND hwnd               The window handle this procedure belongs to
*       UINT uMsg               The value of the message we recieve
*       WPARAM wParam           Msg data - usually lighweigh (32 bits)
*       LPARAM lParam           Msg data - usually comples (32/64 bits)
*
=============================================================================*/
LRESULT WINAPI WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT clientRect;

	switch(msg)
	{
		case WM_CREATE:
		{
		//This sets a timer that triggers every 1000 milliseconds (1 second)
		SetTimer(hwnd, 1, 1000, NULL);
		break;
		}
		case WM_SIZE:
		{
			GetClientRect(hwnd, &clientRect);
			break;
		}
		case WM_TIMER:
		{
			//Invalidate the entire window to trigger a repaint (updates the window)
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case WM_DESTROY:
		{
			//Stops the timer
			KillTimer(hwnd, 1);
			//Free any resources allocated for the window here
			PostQuitMessage(0);
			return 0;
		}
		case WM_PAINT:
		{
			hdc = BeginPaint(hwnd, &ps);
			//Fill the window background with a default gray color
			FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
			
			//Define a buffer for the time string
			wchar_t text[20];
			SYSTEMTIME st;
			GetLocalTime(&st);
			//Format the time as "hh:mm:ss tt" (e.g., "12:00:00 PM")
			GetTimeFormatW(LOCALE_USER_DEFAULT, 0, &st, L"hh:mm:ss tt", text, sizeof(text)/sizeof(wchar_t));
			
			//Define the text rectangle based on the client area
			RECT textRect = {0, 0, clientRect.right, 25};
			//Draw the time centered in the rectangle
			DrawTextW(hdc, text, -1, &textRect, DT_CENTER);
			
			EndPaint(hwnd, &ps);
			break;
		}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
