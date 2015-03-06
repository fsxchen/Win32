// WinMDI.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

HWND g_hMDIClient = NULL;
HINSTANCE g_hInst = NULL;

//�����ڵĴ��ڴ�����
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


//�Ӵ��ڵĴ��ڴ�����
LRESULT CALLBACK ChildProc(HWND hWnd,
						  UINT nMsg,
						  WPARAM wParam,
						  LPARAM lParam) 
{
	return DefMDIChildProc(hWnd, nMsg,
		wParam, lParam);
}

//����ע�ắ��

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

//����������

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


//����MDIClient����
//����MDI�ͻ�ȥ�������һ��ϵͳ��ע�ᴰ��

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

//�����Ӵ��ں���
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



//��ʾ����
void DisplayWnd(HWND hWnd) 
{
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
}


//��Ϣѭ��
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
	
	//ע��������
	RegisterWnd("MainWnd", MainProc, COLOR_BTNFACE + 1);

	//ע���Ӵ���
	RegisterWnd("ChildWnd", ChildProc, COLOR_WINDOW);

	//����������
	HWND hMain = CreateMainWnd("MainWnd");
	
	//����MDICLIENT����
	g_hMDIClient = CreateMDIClient(hMain);

	//����MDI�Ӵ���
	HWND hChild1 = CreateChildWnd("ChildWnd", g_hMDIClient);
	MoveWindow(hChild1, 100 , 100, 200, 200, TRUE);

	DisplayWnd(hMain);
	Message();
	return 0;
}



