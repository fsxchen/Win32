// WinCreate.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

HINSTANCE g_hInst = NULL;


//�����ڵĴ�����
LRESULT CALLBACK WndProc(HWND hWnd,
						 UINT nMsg,
						 WPARAM wParam,
						 LPARAM lParam)

{
	switch(nMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, nMsg, wParam, lParam);
}


//�Ӵ��ڵĴ�����
LRESULT CALLBACK ChildProc(HWND hWnd,
						   UINT nMsg,
						   WPARAM wParam,
						   LPARAM lParam) 
{
	return DefWindowProc(hWnd, nMsg, 
		wParam, lParam);
}

//��ʾ����
void DisplayWnd(HWND hWnd) {
	//ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
}


//��Ϣ������
void Message() {
	MSG msg = {0};
	while( GetMessage(&msg, NULL, 0, 0)) {
		DispatchMessage(&msg);
	}
}

//��������
HWND CreateWnd(LPSTR pszClassName, 
			   DWORD nStyle,
			   HWND hParent) 
{
	HWND hWnd = CreateWindowEx(
			0,
			pszClassName,
			"MyWindow",
			nStyle,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			hParent,
			NULL,
			g_hInst,
			NULL);

	return hWnd;
}

//ע�ᴰ��
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


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{

	g_hInst = hInstance;
	//ע�Ḹ������
	RegisterWnd("MyWnd", WndProc, COLOR_BTNFACE+1);

	//ע���Ӵ�����
	RegisterWnd("Child", ChildProc, COLOR_WINDOW);
	//����������
	HWND hWnd = CreateWnd("MyWnd", WS_OVERLAPPEDWINDOW, NULL);
	
	//�����Ӵ���
	HWND hChild = CreateWnd("Child", 
			WS_CHILD | WS_VISIBLE
			| WS_BORDER | WS_THICKFRAME,
			hWnd);

	MoveWindow(hChild, 100, 100, 200, 200, TRUE);

	//��ʾ������
	DisplayWnd(hWnd);
	
	Message();
	return 0;
}



