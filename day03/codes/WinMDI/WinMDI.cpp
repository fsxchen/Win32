// WinMDI.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

HWND g_hMDIClient = NULL;
HINSTANCE g_hInst = NULL;

//主窗口的窗口处理函数
LRESULT CALLBACK MainProc(HWND hWnd,
						  UINT nMsg,
						  WPARAM wParam,
						  LPARAM lParam) 
{
	switch(nMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefFrameProc(hWnd, g_hMDIClient, nMsg,
		wParam, lParam);
}


//子窗口的窗口处理函数
LRESULT CALLBACK ChildProc(HWND hWnd,
						  UINT nMsg,
						  WPARAM wParam,
						  LPARAM lParam) 
{
	return DefMDIChildProc(hWnd, nMsg,
		wParam, lParam);
}

//窗口注册函数

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

//创建主窗口

HWND CreateMainWnd(LPSTR pszClassName) {
	HWND hWnd = CreateWindowEx(
		0,
		pszClassName,
		"MainWindow",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		g_hInst,
		NULL)
		;
	return hWnd;
}


//创建MDIClient窗口
//创建MDI客户去，这个是一个系统的注册窗口

HWND CreateMDIClient(HWND hParent) {
	CLIENTCREATESTRUCT cs = {0};
	cs.idFirstChild = 1000;

	HWND hWnd = CreateWindowEx(
		0,
		"MDICLIENT",
		"MainWindow",
		WS_CHILD | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		hParent,
		NULL,
		g_hInst,
		&cs)
		;
	return hWnd;
}

//创建子窗口函数
HWND CreateChildWnd(LPSTR pszClassName, HWND hParent) {
	HWND hWnd = CreateWindowEx(
		WS_EX_MDICHILD,
		pszClassName,
		"MainWindow",
		WS_CHILD | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		hParent,
		NULL,
		g_hInst,
		NULL)
		;
	return hWnd;
}



//显示窗口
void DisplayWnd(HWND hWnd) 
{
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
}


//消息循环
void Message()
{
	MSG msg = {0};
	while(GetMessage(&msg, NULL, 0, 0))
	{
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
	
	//注册主窗口
	RegisterWnd("MainWnd", MainProc, COLOR_BTNFACE + 1);

	//注册子窗口
	RegisterWnd("ChildWnd", ChildProc, COLOR_WINDOW);

	//创建主窗口
	HWND hMain = CreateMainWnd("MainWnd");
	
	//创建MDICLIENT窗口
	g_hMDIClient = CreateMDIClient(hMain);

	//创建MDI子窗口
	HWND hChild1 = CreateChildWnd("ChildWnd", g_hMDIClient);
	MoveWindow(hChild1, 100 , 100, 200, 200, TRUE);

	DisplayWnd(hMain);
	Message();
	return 0;
}



