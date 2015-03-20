#include "stdafx.h"
#include <stdio.h>

HINSTANCE g_hInst=NULL;
HANDLE g_hStdOut=NULL;
BOOL g_bCheckCut = FALSE;


void OnInitMenuPopup(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	CHAR szText[260] = {0};
	sprintf(szText, "OnInitMenuPopup: HANDLE=%p\n", (HMENU)wParam);
	WriteConsole(g_hStdOut, szText, strlen(szText), NULL, NULL);
	HMENU hMenu = (HMENU)wParam;
	if(TRUE == g_bCheckCut)
	{
		CheckMenuItem(hMenu, 1003,
			MF_CHECKED | MF_BYCOMMAND);
	}
	else
	{
		CheckMenuItem(hMenu, 1003,
			MF_BYCOMMAND);

	}
}

void OnCommand(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam) 
{
	UINT nID = LOWORD(wParam);
	CHAR szText[260] = {0};
	sprintf(szText, "id: %d\n", nID);
	WriteConsole(g_hStdOut, szText, strlen(szText), NULL, NULL);
	switch(nID)
	{
	case 1002:
		PostQuitMessage(0);
		break;
	case 1003:
		g_bCheckCut = !g_bCheckCut;
		break;
	}
	
}

void OnCreate(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	//创建主菜单
	HMENU hMainMenu = CreateMenu();
	//创建子菜单
	HMENU hFileMenu = CreatePopupMenu();
	//增加菜单项
	AppendMenu(hFileMenu, MF_STRING, 1001, "新建(&N)");
	AppendMenu(hFileMenu, MF_SEPARATOR, 0, NULL);		//添加分割线
	AppendMenu(hFileMenu, MF_STRING, 1002, "退出(&E)");
	
	AppendMenu(hMainMenu, MF_STRING| MF_POPUP, (UINT)hFileMenu, "文件(&F)");


	HMENU hEditMenu = CreatePopupMenu();
	AppendMenu(hEditMenu, MF_STRING, 1003, "剪切(&T)");
	AppendMenu(hEditMenu, MF_STRING, 1004, "拷贝(&C)");
	AppendMenu(hEditMenu, MF_STRING, 1005, "粘贴(&P)");
	AppendMenu(hMainMenu, MF_STRING| MF_POPUP, (UINT)hEditMenu, "编辑(&E)");

	
	HMENU hHelpMenu = CreatePopupMenu();
	AppendMenu(hHelpMenu, MF_STRING, 1006, "帮助(&H)");
	AppendMenu(hHelpMenu, MF_STRING, 1007, "关于(&A)");
	AppendMenu(hMainMenu, MF_STRING| MF_POPUP, (UINT)hHelpMenu, "帮助(&H)");
	SetMenu(hWnd, hMainMenu);
}


LRESULT CALLBACK WndProc(HWND hWnd,
						 UINT nMsg,
						 WPARAM wParam,
						 LPARAM lParam)
{
	switch(nMsg)
	{
	case WM_COMMAND:
		OnCommand(hWnd, nMsg, wParam, lParam);
		break;
	case WM_CREATE:
		OnCreate(hWnd, nMsg, wParam, lParam);
		break;
	case WM_INITMENUPOPUP:
		OnInitMenuPopup(hWnd, nMsg, wParam, lParam);

	case WM_DESTROY:
		KillTimer(hWnd, 1000);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, nMsg, wParam, lParam);
}


BOOL RegisterWnd(LPSTR pszClassName)
{
	WNDCLASSEX wce = {0};
	wce.cbSize			= sizeof(wce);
	wce.cbClsExtra		= 0;
	wce.cbWndExtra		= 0;
	wce.hbrBackground	= HBRUSH(COLOR_WINDOW);
	wce.hCursor			= NULL;
	wce.hIcon			= NULL;
	wce.hIconSm			= NULL;
	wce.hInstance		= g_hInst;
	wce.lpfnWndProc		= WndProc;
	wce.lpszMenuName	= NULL;
	wce.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wce.lpszClassName	= pszClassName;
	ATOM nAtom = RegisterClassEx(&wce);
	if(0 == nAtom)
	{
		return FALSE;
	}
	return TRUE;
}

HWND CreateWnd(LPSTR pszClassName)
{
	HWND hWnd = CreateWindowEx(0,
							pszClassName,
							"MyWnd",
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
	NewConsole();
 	g_hInst = hInstance;
	RegisterWnd("MYWND");
	HWND hWnd = CreateWnd("MYWND");
	DisplayWnd(hWnd);
	Message();
	return 0;
}



