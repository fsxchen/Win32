// WinCreate.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

HINSTANCE g_hInst = NULL;


//父窗口的处理函数
LRESULT CALLBACK WndProc(HWND hWnd,
						 UINT nMsg,
						 WPARAM wParam,
						 LPARAM lParam)

{
	switch(nMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, nMsg, wParam, lParam);
}


//子窗口的处理函数
LRESULT CALLBACK ChildProc(HWND hWnd,
						   UINT nMsg,
						   WPARAM wParam,
						   LPARAM lParam) 
{
	return DefWindowProc(hWnd, nMsg, 
		wParam, lParam);
}

//显示窗口
void DisplayWnd(HWND hWnd) {
	//ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
}


//消息处理函数
void Message() {
	MSG msg = {0};
	while( GetMessage(&msg, NULL, 0, 0)) {
		DispatchMessage(&msg);
	}
}

//创建窗口
HWND CreateWnd(LPSTR pszClassName, 
			   DWORD nStyle,
			   HWND hParent) 
{
	HWND hWnd = CreateWindowEx(
			0,
			pszClassName,
			"MyWindow",
			nStyle,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			hParent,
			NULL,
			g_hInst,
			NULL);

	return hWnd;
}

//注册窗口
BOOL RegisterWnd(LPSTR pszClassName,
				 WNDPROC proc,
				 int nBrush) 
{
	WNDCLASSEX wce = {0};
	wce.cbSize = sizeof(wce);
	wce.style = CS_HREDRAW | CS_VREDRAW;
	wce.cbClsExtra		= 0;
	wce.cbWndExtra		= 0;
	wce.lpfnWndProc		= proc;
	wce.hIcon			= NULL;
	wce.hCursor			= NULL;
	wce.hbrBackground	= HBRUSH(nBrush);
	wce.hInstance		= g_hInst;
	wce.lpszClassName	= pszClassName;
	wce.lpszMenuName	= NULL;
	wce.hIconSm			= NULL;

	ATOM nAtom = RegisterClassEx(&wce);
	if (0 == nAtom)
	{
		return FALSE;
	}
	return TRUE;
}


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{

	g_hInst = hInstance;
	//注册父窗口类
	RegisterWnd("MyWnd", WndProc, COLOR_BTNFACE+1);

	//注册子窗口类
	RegisterWnd("Child", ChildProc, COLOR_WINDOW);
	//创建父窗口
	HWND hWnd = CreateWnd("MyWnd", WS_OVERLAPPEDWINDOW, NULL);
	
	//创建子窗口
	HWND hChild1 = CreateWnd("Child", 
			WS_CHILD | WS_VISIBLE
			| WS_BORDER | WS_THICKFRAME
			| WS_CAPTION |WS_SYSMENU
			| WS_MINIMIZEBOX | WS_MAXIMIZEBOX,

			hWnd);

	HWND hChild2 = CreateWnd("Child", 
			WS_CHILD | WS_VISIBLE
			| WS_BORDER | WS_THICKFRAME | WS_POPUP
			| WS_CAPTION |WS_SYSMENU,
			hWnd);

	HWND hChild3 = CreateWnd("Child", 
			WS_CHILD | WS_VISIBLE
			| WS_BORDER | WS_THICKFRAME
			| WS_CAPTION |WS_SYSMENU,
			hWnd);

	MoveWindow(hChild1, 100, 100, 200, 200, TRUE);
	MoveWindow(hChild2, 100, 200, 200, 200, TRUE);
	MoveWindow(hChild3, 100, 300, 200, 200, TRUE);

	//显示父窗口
	DisplayWnd(hWnd);
	
	Message();
	return 0;
}



