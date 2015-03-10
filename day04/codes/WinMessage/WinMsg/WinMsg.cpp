// WinMsg.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <stdio.h>
HINSTANCE g_hInst	= NULL;
HWND g_hButton		= NULL;


#define WM_FRISTMSG WM_USER+1
#define WM_SECONDMSG WM_USER+2

void OnCreade(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	LPCREATESTRUCT pCreateStruct = LPCREATESTRUCT(lParam);
	//MessageBox(NULL, pCreateStruct->lpszName,
	//	"OnCreate", MB_OK);

	g_hButton = CreateWindowEx(0, "BUTTON", "BUTTON", WS_CHILD | WS_VISIBLE,
			0, 0, 100, 100,
			hWnd, NULL, g_hInst, NULL);

	SendMessage(hWnd, WM_FRISTMSG, 0, 0);
}

void OnSize(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	int nWidth = LOWORD(lParam);
	int nHeight = HIWORD(lParam);
	CHAR szText[260] = {0};
	sprintf(szText, "WIDTH:%d, HEIGHT:%d", nWidth, nHeight);
	//MessageBox(NULL, szText, "OnSize", MB_OK);
	int nX = (nWidth - 100)/2;
	int nY = (nHeight - 100 ) /2;

	MoveWindow(g_hButton, nX, nY, 100 , 100, TRUE);

}

BOOL OnSysCommand(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	switch(wParam) {
	case SC_CLOSE:
		if(IDOK == MessageBox(
			NULL, "是否将文件存盘？", "提示", 
			MB_OK | MB_OKCANCEL | MB_ICONWARNING)) {
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd,
						 UINT nMsg,
						 WPARAM wParam,
						 LPARAM lParam)
{
	switch(nMsg) {
	case WM_CREATE:
		OnCreade(hWnd, nMsg, wParam, lParam);
		break;
	case WM_SIZE:
		OnSize(hWnd, nMsg, wParam, lParam);
		break;
	case WM_SYSCOMMAND:
		if (!OnSysCommand(hWnd, nMsg, wParam, lParam))
			return 0;
		break;
	case WM_DESTROY:   //窗口销毁的时候的消息
		//PostQuitMessage(0);		//发送WM_QUIT的消息
		PostMessage(hWnd, WM_QUIT, 0, 0);
		return 0;
	case WM_FRISTMSG:
		MessageBox(NULL, "FIRSTMSG", "FFFFFFF", MB_OK);
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
	//while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
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



