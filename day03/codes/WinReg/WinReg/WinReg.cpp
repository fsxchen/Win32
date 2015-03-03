// WinReg.cpp : Defines the entry point for the application.
//

#include <windows.h>
#include <stdio.h>

HINSTANCE g_hInst = NULL;
//定义消息处理函数
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

HWND CreateButton()
{
	HWND hWnd = CreateWindow(
						"EDIT",
						"Button",
						WS_OVERLAPPEDWINDOW,
						0,
						0,
						500,
						600,
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
	while(GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

BOOL RegisterWnd(LPSTR pazClassName)
{
	WNDCLASSEX wce		= {0};
	wce.cbSize			= sizeof(wce);
	wce.style			= CS_VREDRAW | CS_HREDRAW;
	wce.lpfnWndProc		= WndProc;
	wce.cbClsExtra		= 100;		//
	wce.cbWndExtra		= 100;
	wce.hCursor			= NULL;
	wce.hIcon			= NULL;
	wce.hbrBackground	= HBRUSH(COLOR_BTNFACE+1);
	wce.lpszClassName	= pazClassName;
	wce.hIconSm			= NULL;
	wce.hInstance		= g_hInst;
	
	ATOM nAtom = RegisterClassEx(&wce);
	if(0 == nAtom) {
		return FALSE;
	}
	return TRUE;
}

HWND CreateWnd(LPSTR pszClassName) {
	HWND hWnd = CreateWindow(
				pszClassName,
				"MyWindow",
				WS_OVERLAPPEDWINDOW,
				0,
				0,
				400,
				500,
				NULL,
				NULL,
				g_hInst,
				NULL);
	
	return hWnd;
}

void SetExtra(HWND hWnd) {
	SetClassLong(hWnd, 0, 100);
	SetWindowLong(hWnd, 0, 200);
}

void GetExtra(HWND hWnd) {
	//获取CLASS附加数据
	DWORD nClass = GetClassLong(hWnd, 0);
	DWORD nWnd = GetWindowLong(hWnd, 0);
	//显示
	CHAR szText[260] = {0};
	sprintf(szText, "CLS:%s WND:%d",
		nClass, nWnd);
	MessageBox(NULL, szText, "Extra", MB_OK);
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{

	g_hInst = hInstance;
	//HWND hWndBtn = CreateButton();
	//DisplayWnd(hWndBtn);
	RegisterWnd("MyWindow");
	//HWND hWnd = CreateWnd("MyWindow");
	
	HWND hWnd1 = CreateWnd("MyWindow");
	HWND hWnd2 = CreateWnd("MyWindow");
	
	SetExtra(hWnd1);
	GetExtra(hWnd1);
	GetExtra(hWnd2);
	DisplayWnd(hWnd1);


	
	Message();
	return 0;
}
