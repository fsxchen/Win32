// WinMouse.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <stdio.h>
HINSTANCE g_hInst=NULL;
HANDLE g_hStdOut=NULL;

UINT g_nTimerID1 = 0;


void PrintLog(LPSTR pszLog)
{
	WriteConsole(g_hStdOut, pszLog, strlen(pszLog), NULL, NULL);
}

void OnCreate(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	SetTimer(hWnd, 1000, 3 * 1000, NULL);
	SetTimer(hWnd, 1001, 2 * 1000, NULL);
	//使用窗口处理函数
	g_nTimerID1 = SetTimer(hWnd, 0, 5 * 1000, NULL);
}

void OnTimer(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	
	switch(wParam)
	{
	case 1000:
		{
		CHAR szText[] = "1000: Hello Timer\n";
		WriteConsole(g_hStdOut, szText, strlen(szText), NULL, NULL);
		}
		break;
	case 1001:
		CHAR sz1Text[] = "1001: Hello Timer\n";
		WriteConsole(g_hStdOut, sz1Text, strlen(sz1Text), NULL, NULL);
		break;
	if (wParam == g_nTimerID1)
	{

		CHAR sz1Text[] = "XXXX: Hello Timer\n";
		WriteConsole(g_hStdOut, sz1Text, strlen(sz1Text), NULL, NULL);
		break;
	}
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
	case WM_TIMER:
		OnTimer(hWnd, nMsg, wParam, lParam);
		break;
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



