// WinPaint.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
HINSTANCE g_hInst = NULL;

void OnPaint(HWND hWnd, 
			 UINT nMsg,
			 WPARAM wParam,
			 LPARAM lParam)
{
	//WM_PAINT开始时，必须调用
	PAINTSTRUCT ps = {0};
	HDC hDC = BeginPaint(hWnd, &ps);
	
	CHAR szText[] = "Hello WM_PAINT";
	TextOut(hDC, 100, 100, szText, strlen(szText));
	Rectangle(hDC, 200, 200, 300, 300);

	//WM_PAINT处理后，必须调用
	EndPaint(hWnd, &ps);
}


LRESULT CALLBACK WndProc(HWND hWnd,
						 UINT nMsg,
						 WPARAM wParam,
						 LPARAM lParam)
{
	switch(nMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		OnPaint(hWnd, nMsg, wParam, lParam);
		break;
	}
	return DefWindowProc(hWnd, nMsg, wParam, lParam);
}

BOOL RegisterWnd(LPSTR pszClassName) 
{
	WNDCLASSEX wce		= {0};
	wce.cbSize			= sizeof(wce);
	wce.cbClsExtra		= 0;
	wce.cbWndExtra		= 0;
	wce.hbrBackground	= HBRUSH(COLOR_BTNFACE+1);
	wce.hCursor			= NULL;
	wce.hIcon			= NULL;
	wce.hIconSm			= NULL;
	wce.hInstance		= g_hInst;
	wce.lpfnWndProc		= WndProc;
	wce.lpszClassName	= pszClassName;
	wce.lpszMenuName	= NULL;
	wce.style			= CS_HREDRAW | CS_VREDRAW;

	ATOM nAtom = RegisterClassEx(&wce);
	if(0 == nAtom) {
		return FALSE;
	}
	return TRUE;
}

HWND CreateWnd(LPSTR pszClassName)
{
	HWND hWnd = CreateWindowEx(0,
		pszClassName, "MyWnd",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL, NULL,
		g_hInst, NULL);
	return hWnd;
}

void DisplayWnd(HWND hWnd) 
{
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
}

void Message() 
{
	MSG msg = {0};
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.

	g_hInst = hInstance;
	RegisterWnd("MYWND");
	HWND hWnd = CreateWnd("MYWND");
	DisplayWnd(hWnd);
	Message();
	return 0;
}



