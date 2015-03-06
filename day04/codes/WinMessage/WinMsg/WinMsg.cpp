// WinMsg.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
HINSTANCE g_hInst = NULL;

LRESULT CALLBACK WndProc(HWND hWnd,
						 UINT nMsg,
						 WPARAM wParam,
						 LPARAM lParam)
{
	switch(nMsg) {
	case WM_DESTROY:   //窗口销毁的时候的消息
		PostQuitMessage(0);		//发送WM_QUIT的消息
		return 0;
	}
	//使用系统函数来处理我们未处理的消息类型
	return DefWindowProc(hWnd, nMsg, wParam, lParam);
}

BOOL RegisterWnd(LPSTR pszClassName) {
	WNDCLASSEX wce = {0};
	wce.cbSize = sizeof(wce);
	wce.cbClsExtra = 0;
	wce.cbWndExtra = 0;
	wce.hbrBackground = HBRUSH(COLOR_BTNFACE+1);
	wce.hCursor = NULL;
	wce.hIcon = NULL;
	wce.hIconSm = NULL;
	wce.hInstance = g_hInst;
	wce.lpfnWndProc = WndProc;
	wce.lpszClassName = pszClassName;
	wce.lpszMenuName = NULL;
	wce.style = CS_VREDRAW | CS_HREDRAW;

	ATOM nAtom = RegisterClassEx(&wce);
	if (0 == nAtom) {
		return FALSE;
	}

	return TRUE;
}

HWND CreateWnd(LPSTR pszClassName) {

	HWND hWnd = CreateWindowEx(0,
						pszClassName, "MyWnd",
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						NULL,
						NULL,
						g_hInst,
						NULL);
	return hWnd;
}

void DisplayWnd(HWND hWnd) {
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
}


void Message() {
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
	RegisterWnd("MyWnd");
	HWND hWnd = CreateWnd("MyWnd");
	DisplayWnd(hWnd);
	Message();

	return 0;
}



