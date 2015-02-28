// char.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include <string.h>
#include <windows.h>



void ASCII() {
	char cText = 0;
	for(int nIndex = 0; nIndex < 256; nIndex ++) {
		printf("%c ", cText);
		cText++;
	}	
}

void CodePage(int nCodePage) {
	SetConsoleOutputCP(nCodePage);
	ASCII();
}


void c_char() {
	char * pszText = "Hello World!\n";
	int nLen = strlen(pszText);
	printf("%d, %s", nLen, pszText);
}

void C_wchat() {
	wchar_t cText = 'A';
	wchar_t * pszText = L"ABCD";
	wchar_t * pszChs = L"我是程序员";
	int nLen = wcslen(pszText);
	//printf("%d %s\n", nLen, pszText);
	//wprintf(L"%s\n", pszText);
	nLen = wcslen(pszChs);
	wprintf(L"什么情况：%d %s\n", nLen, pszChs);

	printf("++++++++++++++++++++++++++\n");
	char * pChs = "我是程序员";
	nLen = strlen(pChs);
	printf("M %d %s\n", nLen, pChs);

}

int main(int argc, char* argv[])
{
//	c_char();
//	printf("Hello World!\n");
	
//	ASCII();
//	printf("=====================================================\n");
//	CodePage(437);
//	printf("=====================================================\n");
//	CodePage(936);
	C_wchat();
	return 0;
}

