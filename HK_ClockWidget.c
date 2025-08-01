/*=============================================================================
* HK_ClockWidget.c
===============================================================================
* Author: Henry King
* Version: Beta 2.0
* Release Date: 7/31/2025
=============================================================================*/

#include "HK_ClockWidget.h"

//Define a constant for the menu item ID
#define IDM_CLOSE_APP 1001

/*=============================================================================
*   ConstructFont [returns: HFONT* (pointer to HFONT)]
*       Routine Description: Construct a font handle
*		timwking1	01-Aug 2025
*
*	***Add more parameters to this function if you need them,
*		for this example I just pass the typeface name as a wide string***
*
*       wchar_t* typeface		Typeface name
*
=============================================================================*/
HFONT* ConstructFont(wchar_t* typeface)
{

	//malloc is a function that allocates memory and returns a pointer to it...

	//allocate enough memory on the heap for an HFONT and store it in a new pointer named "result"
	HFONT* result = malloc(sizeof(HFONT));

	if(!result)
	{
		//malloc will give you a NULL pointer if it fails (out of memory, etc.)
		//so if result is NULL, the malloc failed...
		//In this case, we just return a NULL pointer and the font will not be constructed

		//alloc fail
		return NULL;
	}

	//We call CreateFontW on HFONT result:
	*result = CreateFontW
			(
				60,                              //Height in logical units (approx. point size)
				0,                               //Width (0 for default)
				0,                               //Escapement
				0,                               //Orientation
				FW_NORMAL,                       //Weight (normal, not bold)
				FALSE,                           //Italic
				FALSE,                           //Underline
				FALSE,                           //Strikeout
				DEFAULT_CHARSET,                 //Character set
				OUT_DEFAULT_PRECIS,              //Output precision
				CLIP_DEFAULT_PRECIS,             //Clipping percision
				DEFAULT_QUALITY,                 //Quality
				DEFAULT_PITCH | FF_DONTCARE,     //Pitch and family
				typeface                         //Font name
			);

	//Return the pointer to the HFONT we just created
	return result;
}

/*=============================================================================
*   DestroyFont [returns: nothing (void)]
*       Routine Description: Destroy a font handle
*		timwking1	01-Aug 2025
*
*		HFONT* lpFont			pointer to HFONT we are freeing from the heap
*
=============================================================================*/
void DestroyFont(HFONT* lpFont)
{
	//Check if lpFont is a valid pointer before freeing it
	//Not checking this can lead to undefined behavior
	if(lpFont)
	{
		//Free the memory we malloced earlier when we created the HFONT
		free(lpFont);
	}
}

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
		WS_POPUP,               //dwStyle
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

	//Define a pointer (indicated by *) to a font handle
	HFONT* myFont;
	//set it equal to ConstructFont which allocates memory and creates the HFONT
	myFont = ConstructFont(L"Arial");

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
		case WM_CONTEXTMENU:
		{
			//Create a popup menu
			HMENU hMenu = CreatePopupMenu();
			if (hMenu)
			{
				//Add "Close" menu item
				AppendMenuW(hMenu, MF_STRING, IDM_CLOSE_APP, L"Close");
				
				//Get the cursor position from lParam (screen coordinates)
				int x = GET_X_LPARAM(lParam);
				int y = GET_Y_LPARAM(lParam);
				
				//Display the menu at the cursor position
				TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON, x, y, 0, hwnd, NULL);
				
				//Destroy the menu to free resources
				DestroyMenu(hMenu);
			}
			break;
		}
		case WM_COMMAND:
		{
			//Handle menu item selection
			switch (LOWORD(wParam))
			{
				case IDM_CLOSE_APP:
					//Post WM_CLOSE to close the application
					PostMessage(hwnd, WM_CLOSE, 0, 0);
					break;
			}
			break;
		}
		case WM_LBUTTONDOWN:
		{
			//Initiate window dragging by simulating a title bar click
			SendMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, lParam);
			break;
		}
		case WM_DESTROY:
		{
			//Stops the timer
			KillTimer(hwnd, 1);
			//Free any resources allocated for the window here

			//Because CreateFont uses malloc, we have to free it
			DestroyFont(myFont);

			PostQuitMessage(0);
			return 0;
		}
		case WM_PAINT:
		{
			hdc = BeginPaint(hwnd, &ps);
			//Fill the window background with a default gray color
			FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
			
			//Define a buffer for the time string
			wchar_t timeText[25];
			wchar_t dateText[50]; //Larger buffer to accommodate for longer format
			SYSTEMTIME st;
			GetLocalTime(&st);
			
			//Format the time as "hh:mm:ss tt" (e.g., "12:00:00 PM")
			GetTimeFormatW(LOCALE_USER_DEFAULT, 0, &st, L"hh:mm:ss tt", timeText, sizeof(timeText)/sizeof(wchar_t));
			
			//Format the date as "Day, Month Date, Year" (e.g., "Thursday, July 31, 2025")
			GetDateFormatW(LOCALE_USER_DEFAULT, 0, &st, L"dddd, MMMM dd, yyyy", dateText, sizeof(dateText)/sizeof(wchar_t));
			
			//Define the text rectangle based on the client area
			RECT timeRect = {0, 0, clientRect.right, 120};
			RECT dateRect = {0, 50, clientRect.right, 120};
			
			//Select the pointer to the font we constructed (*myFont) into the hdc
			SelectObject(hdc, *myFont);

			//Draw the time centered in the rectangle
			DrawTextW(hdc, timeText, -1, &timeRect, DT_CENTER);
			DrawTextW(hdc, dateText, -1, &dateRect, DT_CENTER);
			
			EndPaint(hwnd, &ps);
			break;
		}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}