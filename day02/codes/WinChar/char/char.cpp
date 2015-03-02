// char.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include "string.h"

#define _UNICODE

#include "tchar.h"
#include <windows.h>
// #ifndef _UNICODE
// 	typedef char TCHAR
// 	#define __T(x)	x
// #else
// 	typedef wchar_t TCHAR
// 	#define __T(x)  L##x
// #endif
// UNICODE
//  wchar_t * pszText = L"我是程序员";
// MUTIBYTE
//  char * pszText = "我是程序员";


void PrintUnicode() {
	HANDLE hOut = 
		GetStdHandle(STD_OUTPUT_HANDLE);
	wchar_t * pszText = L"我不是程序员！";
	//WriteConsole(hOut);	//其实是WriteConsoleA/WriteConsoleW
	WriteConsoleW(hOut, pszText, wcslen(pszText), NULL, NULL);

	wchar_t szText[2] = {0};
	for (BYTE nHigh = 0x48; nHigh < 0x9F; nHigh++) {
		for (BYTE nLow= 0; nLow < 0xFF; nLow++) {
			szText[0] = MAKEWORD(nLow, nHigh);
			WriteConsoleW(hOut, szText, wcslen(szText), NULL, NULL);
		}
	}
	
}

void tchar( )
{
	TCHAR * pszText = __T("我是程序员") ;
#ifndef _UNICODE
	int nLen = strlen(pszText);
#else
	int nLen = wcslen(pszText);
#endif
	printf("%d\n", nLen);
}


void C_wchar( )
{
	wchar_t cText = 'A';
	wchar_t * pszText = L"ABCD";
	int nLen = wcslen( pszText );
	printf( "%d %s\n", nLen, pszText );
	wprintf( L"%s\n", pszText );

	wchar_t * pwszChs = L"我是程序员";
	nLen = wcslen( pwszChs );
	wprintf( L"W: %d %s\n", nLen, pwszChs );
	
	char * pszChs = "我是程序员";
	nLen = strlen( pszChs );
	printf( "M %d %s\n", nLen, pszChs );
}

void CoadPage( int nCodePage )
{
	SetConsoleOutputCP( nCodePage );
	char cText = 0;
	for( int nIndex=0; nIndex<256; nIndex++ )
	{
		printf( "%c ", cText );
		cText++;
	}
}

void ASCII( )
{
	char cText = 0;
	for( int nIndex=0; nIndex<256; nIndex++ )
	{
		printf( "%c ", cText );
		cText++;
	}
}

void c_char( )
{
	char * pszText = "Hello World!\n";
	int nLen = strlen( pszText );
	printf( "%d, %s", nLen, pszText );
}

int main(int argc, char* argv[])
{
	//c_char( );
	//ASCII( );
	//printf( "\n-------------------\n" );
	//CoadPage( 437 );
	//CoadPage( 936 );
	//C_wchar();
	PrintUnicode();
	return 0;
}


