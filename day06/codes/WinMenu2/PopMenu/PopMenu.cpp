// PopMenu.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

HINSTANCE g_hInst = NULL;

void OnRButtonUp(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam) {
	//创建弹出式菜单
	HMENU hPopMenu = CreatePopupMenu();
	//增加菜单项
	AppendMenu(hPopMenu, MF_STRING, 1000, "测试");
	AppendMenu(hPopMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(hPopMenu, MF_STRING, 1001, "退出");
	//菜单项显示
	POINT point = {0};
	point.x = LOWORD(lParam);
	point.y = HIWORD(lParam);

	ClientToScreen(hWnd,&point);
	TrackPopupMenu(hPopMenu, TPM_LEFTALIGN, point.x, point.y,0, hWnd, NULL);
}

void OnCommand(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam) {
	int nCmdID = LOWORD(wParam);
	switch(nCmdID) {
	case 1000:
		MessageBox(NULL, "Hello Popmenu", "HA HA", MB_OK);
		break;
	case 1001:
		PostQuitMessage(0);
		break;
	}
}

void OnContextMenu(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	//创建弹出式菜单
	HMENU hPopMenu = CreatePopupMenu();
	//增加菜单项
	AppendMenu(hPopMenu, MF_STRING, 1000, "测试");
	AppendMenu(hPopMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(hPopMenu, MF_STRING, 1001, "退出");

	int nX = LOWORD(lParam);
	int nY = HIWORD(lParam);

	TrackPopupMenu(hPopMenu, TPM_LEFTALIGN, nX, nY,0, hWnd, NULL);

	//删除菜单
	DestroyMenu(hPopMenu);
}


LRESULT CALLBACK WndProc(HWND hWnd,
						 UINT nMsg,
						 WPARAM wParam,
						 LPARAM lParam)
{
	switch(nMsg)
	{
//	case WM_RBUTTONUP:
//		OnRButtonUp(hWnd, nMsg, wParam, lParam);
//		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CONTEXTMENU:
		OnContextMenu(hWnd, nMsg, wParam, lParam);
	case WM_COMMAND:
		OnCommand(hWnd, nMsg, wParam, lParam);
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
	wce.hbrBackground	= HBRUSH(COLOR_WINDOW);
	wce.hCursor			= NULL;
	wce.hIcon			= NULL;
	wce.hIconSm			= NULL;
	wce.hInstance		= g_hInst;
	wce.lpfnWndProc		= WndProc;
	wce.lpszClassName	= pszClassName;
	wce.lpszMenuName	= NULL;
	wce.style			= CS_HREDRAW | CS_VREDRAW;

	ATOM nAtom = RegisterClassEx(&wce);
	if (0 == nAtom) {
		return FALSE;
	}
	return TRUE;
}

HWND CreateWnd(LPSTR pszClassName)
{
	HWND hWnd = CreateWindowEx(0,
					pszClassName, "MyWnd", 
					WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
					CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
					NULL, NULL, g_hInst, NULL);
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



