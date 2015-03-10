// WinPaint.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "stdio.h"
HINSTANCE g_hInst = NULL;
HANDLE g_hStdOut = NULL;


LRESULT CALLBACK WndProc(HWND hWnd,
						 UINT nMsg,
						 WPARAM wParam,
						 LPARAM lParam)
{
	switch(nMsg)
	{
//	case WM_KEYDOWN:
//	{
//		CHAR szText[] = "WM_KEYDOWN\n";
//		sprintf(szText, "WM_CHAR: %c\n", wParam);
//		WriteConsole(g_hStdOut, szText, strlen(szText), NULL, NULL);
//	}
//	break;
	case WM_KEYDOWN:
	{
		switch(wParam){
		case VK_LEFT:
		{
			CHAR szText[] = "WM_KEYDOWN\n";
			sprintf(szText, "WM_CHAR: %c\n", wParam);
			WriteConsole(g_hStdOut, szText, strlen(szText), NULL, NULL);
		}break;
		case VK_UP:
			break;
		case VK_RIGHT:
			break;
		case VK_DOWN:
			break;
		}
		}
		break;
	case WM_KEYUP:
		{
		CHAR szText[] = "WM_KEYUP\n";
		WriteConsole(g_hStdOut, szText, strlen(szText), NULL, NULL);
	}
		break;
	case WM_SYSKEYDOWN:
		{
		CHAR szText[] = "WM_SYSKEYDOWN\n";
		WriteConsole(g_hStdOut, szText, strlen(szText), NULL, NULL);
	}
		break;
	case WM_SYSKEYUP:
		{
		CHAR szText[] = "WM_SYSKEYUP\n";
		WriteConsole(g_hStdOut, szText, strlen(szText), NULL, NULL);
	}
		break;
	case WM_CHAR:
		{
		CHAR szText[] = "WM_CHAR\n";
		WriteConsole(g_hStdOut, szText, strlen(szText), NULL, NULL);
	}
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

void NewConsole()
{
	AllocConsole();
	g_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CHAR *szText = "Debug Message.......:\n";
	WriteConsole(g_hStdOut, szText, strlen(szText), NULL, NULL);
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



