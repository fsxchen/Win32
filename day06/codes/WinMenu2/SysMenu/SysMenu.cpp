// SysMenu.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <stdio.h>

HINSTANCE g_hInst = NULL;
HANDLE g_hStdOut = NULL;

void OnCreate(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	HMENU hSysMenu = GetSystemMenu(hWnd, FALSE);
	//删除菜单项
	RemoveMenu(hSysMenu, 0, MF_BYPOSITION);
	RemoveMenu(hSysMenu, 0, MF_BYPOSITION);
	RemoveMenu(hSysMenu, 0, MF_BYPOSITION);
	RemoveMenu(hSysMenu, 0, MF_BYPOSITION);
	//增加菜单项
	InsertMenu(hSysMenu, 0, MF_BYPOSITION|MF_STRING, 1001, "测试1");
	InsertMenu(hSysMenu, 1, MF_BYPOSITION|MF_STRING, 1002, "测试2");
}

void OnSysCommand(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	CHAR szText[256] = {0};
	sprintf(szText, "OnSysCommand: WPARAM:%08X, LPARAM=%08X\n", wParam, lParam);
	WriteConsole(g_hStdOut, szText, strlen(szText), NULL, NULL);
	int nID = LOWORD(wParam);
	switch(nID)
	{
	case 1001:
		MessageBox(NULL, "Hello 1001", "SysMenu", MB_OK);
		break;
	case 1002:
		MessageBox(NULL, "Hello 1002", "SysMenu", MB_OK);
		break;
	}

}

LRESULT CALLBACK WndProc(HWND hWnd,
						 UINT nMsg,
						 WPARAM wParam,
						 LPARAM lParam)
{
	switch(nMsg)
	{
	case WM_CREATE:
		OnCreate(hWnd, nMsg, wParam, lParam);
		break;
	case WM_SYSCOMMAND:
		OnSysCommand(hWnd, nMsg, wParam, lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
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


void NewConsole()
{
AllocConsole();
g_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	NewConsole();
	g_hInst = hInstance;
	RegisterWnd("MYWND");
	HWND hWnd = CreateWnd("MYWND");
	DisplayWnd(hWnd);
	Message();

	return 0;
}



