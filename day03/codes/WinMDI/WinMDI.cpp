// WinMDI.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

HWND g_hMDIClient = NULL;

LRESULT CALLBACK MainProc(HWND hWnd,
						  UINT nMsg,
						  WPARAM wParam,
						  LPARAM lParam) 
{
	return DefFrameProc(hWnd, g_hMDIClient, nMsg,
		wParam, lParam);
}




int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.


	return 0;
}



