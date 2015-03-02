// WinChar.cpp : Defines the entry point for the application.
//

/*

int
WINAPI
MessageBoxExA(
    HWND hWnd ,
    LPCSTR lpText,
    LPCSTR lpCaption,
    UINT uType,
    WORD wLanguageId);
WINUSERAPI
int
WINAPI
MessageBoxExW(
    HWND hWnd ,
    LPCWSTR lpText,
    LPCWSTR lpCaption,
    UINT uType,
    WORD wLanguageId);
#ifdef UNICODE
#define MessageBoxEx  MessageBoxExW
#else
#define MessageBoxEx  MessageBoxExA
#endif // !UNICODE

*/


#include "stdafx.h"
#include "stdlib.h"

void MyMessageBox() {
	MessageBox(NULL, TEXT("Hello Wide"), TEXT("WIDE"), MB_OK);
}

void Wide2Multi() {
	WCHAR *pwszText = L"Wide2Multi";
	//计算转换后字符串长度
	int nLen = WideCharToMultiByte(
				CP_ACP,
				0,
				pwszText,
				wcslen(pwszText),
				NULL,
				0, 
				NULL,
				NULL);
	//分配内存
	char * pszText = (char *)malloc(nLen);
	WideCharToMultiByte(
				CP_ACP,
				0,
				pwszText,
				wcslen(pwszText),
				pszText,
				nLen, 
				NULL,
				NULL);
	MessageBoxA(NULL, pszText, "CHAR", MB_OK);
	free(pszText);
}

void Multi2Wide()
{
	CHAR * pszText = "Multi2Wide";
	//获取转换后需要的BUFF的长度
	int nLen = MultiByteToWideChar(CP_ACP, 
						0,
						pszText,
						strlen(pszText),
						NULL,
						0
						);
	//分配BUFF的空间
	WCHAR *pwszText =  (WCHAR *)malloc(nLen * sizeof(WCHAR));
	//进行转换
	MultiByteToWideChar(CP_ACP, 
						0,
						pszText,
						strlen(pszText),
						pwszText,
						nLen
						);

	MessageBoxW(NULL, pwszText, L"WIDE", MB_OK);
	free(pwszText);

}
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	Multi2Wide();
	Wide2Multi();
	
	return 0;
}



