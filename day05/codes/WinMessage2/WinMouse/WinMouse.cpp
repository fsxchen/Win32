// WinMouse.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <stdio.h>
HINSTANCE g_hInst=NULL;
HANDLE g_hStdOut=NULL;

int g_nXPos = 0;
int g_nYPos = 0;

int g_nX1Rect = 0;
int g_nY1Rect = 0;
int g_nX2Rect = 0;
int g_nY2Rect = 0;


void PrintLog(LPSTR pszLog)
{
	WriteConsole(g_hStdOut, pszLog, strlen(pszLog), NULL, NULL);
}

void OnPaint(HWND hWnd,UINT nMsg,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT ps = {0};
	HDC hDC = BeginPaint(hWnd, &ps);
	CHAR szText[] = "Hello Mouse";
	TextOut(hDC, g_nXPos, g_nYPos, szText, strlen(szText));
	Rectangle(hDC, g_nX1Rect, g_nY1Rect, g_nX2Rect, g_nY2Rect);
	EndPaint(hWnd, &ps);
}

LRESULT CALLBACK WndProc(HWND hWnd,
						 UINT nMsg,
						 WPARAM wParam,
						 LPARAM lParam)
{
	switch(nMsg)
	{
	case WM_PAINT:
		OnPaint(hWnd, nMsg, wParam, lParam);
		break;
	case WM_LBUTTONDBLCLK:
		PrintLog("WM_LBUTTONDBLCLK");
		break;
	case WM_MOUSEWHEEL:
		{
			short nDetla = HIWORD(wParam);
			int nX		= LOWORD(lParam);
			int nY		= HIWORD(lParam);
			CHAR szText[260] = {0};
			sprintf(szText, "WM_MOUSEWHELL: Detla=%d, X=%d, Y=%d\n",
				nDetla, nX, nY);
			PrintLog(szText);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			PrintLog("WM_LBUTTONDOWN\n");
			g_nX1Rect = LOWORD(lParam);
			g_nY1Rect = HIWORD(lParam);
		
		}
		break;
	case WM_LBUTTONUP:
		{
			PrintLog("WM_LBUTTONUP\n");
			g_nX2Rect = LOWORD(lParam);
			g_nY2Rect = HIWORD(lParam);
		}
		break;
	case WM_RBUTTONDOWN:
		PrintLog("WM_RBUTTONDOWN\n");
		break;
	case WM_RBUTTONUP:
		PrintLog("WM_RBUTTONU\n");
		break;
	case WM_MOUSEMOVE:
		{
		
		int nX = LOWORD(lParam);
		int nY = HIWORD(lParam);
		POINT ptScreen = {0};
		ptScreen.x = nX;
		ptScreen.y = nY;
		ClientToScreen(hWnd, &ptScreen);

		CHAR szText[260] = {0};
		sprintf(szText, "WM_MOUSEMOVE: X=%d (%d), Y=%d (%d)\n", nX, ptScreen.x, nY, ptScreen.y);
		PrintLog(szText);
		if(wParam & MK_CONTROL) {
			PrintLog("WM_MOUSEVE: MK_CONTROL");
		}
		if(wParam & MK_LBUTTON) {
			PrintLog("WM_MOUSEVE: MK_CONTROL");
		}
		g_nXPos = LOWORD(lParam);
		g_nYPos = HIWORD(lParam);
		InvalidateRect(hWnd, NULL,TRUE);
		}
		break;
	case WM_DESTROY:
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



