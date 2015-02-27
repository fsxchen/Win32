#include "windows.h"

//2.窗口处理函数

HINSTANCE g_hInst = NULL;

LRESULT CALLBACK WndProc(HWND hWnd, 
	UINT nMsg, 
	WPARAM wParam,
	LPARAM lParam)
{
	//判断消息ID
	switch (nMsg) {
		case WM_DESTROY:		//窗口销毁消息
			PostQuitMessage(0);	//发送退出消息
			return 0;
	}
	//调用缺省的消息处理程序
	return DefWindowProc(hWnd, nMsg,
		wParam, lParam);
}


//3 注册窗口类型

BOOL MyRegister(LPSTR pszClassName) {
	WNDCLASS wc 		= {0};
	ATOM nAtom 			= 0;
	wc.style 			= CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc 		= WndProc;
	wc.cbClsExtra 		= 0;
	wc.cbWndExtra 		= 0;
	wc.hInstance 		= g_hInst;
	wc.hIcon			= LoadIcon(g_hInst, MAKEINTRESOURCE(100));
	wc.hCursor			= NULL;
	wc.hbrBackground	= (HBRUSH) (COLOR_BTNFACE);
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= pszClassName;

	nAtom = RegisterClass(&wc);

	if ( 0 == nAtom) {
		MessageBox(NULL, "Register Failed", "Error", MB_OK | MB_ICONWARNING);
		return FALSE;
	} else {
		MessageBox(NULL, "Register Successed", "Successed", MB_OK);
	}
	return TRUE;
}

//4.窗口的创建
HWND MyCreate(LPSTR pszClassName) {
	HWND hWnd = NULL;
	hWnd = CreateWindow(pszClassName,
				"Hello Window",
				WS_OVERLAPPEDWINDOW,
				100,
				100,
				300,
				500,
				NULL,
				NULL,
				g_hInst,
				NULL);
	if(hWnd == NULL) {
		MessageBox(NULL, "CreateWnd Failed", "Error", MB_OK | MB_ICONWARNING);
		return NULL;
	}
	MessageBox(NULL, "CreateWnd Successed", "Successed", MB_OK);

	return hWnd;
}


//5 显示窗口

void DisplayWnd(HWND hWnd)
{
	//显示
	ShowWindow(hWnd, SW_SHOW);
	//刷新
	UpdateWindow(hWnd);
}

//6.消息处理
void Message() {
	MSG msg = {0};
	//循环获取消息
	while(GetMessage(&msg, NULL, 0, 0)) {
		DispatchMessage(&msg);
	}
}

//1.入口函数
int WINAPI WinMain(HINSTANCE hInstance,
				HINSTANCE hPrevInstance,
				LPSTR pszCmdLine,
				int nShowCmd)
{
	HWND hWnd = NULL;
	g_hInst = hInstance;
	MyRegister("MyWnd");
	hWnd = MyCreate("MyWnd");
	DisplayWnd(hWnd);

	Message();
	return 0;
}