#include <windows.h>

int WINAPI WinMain( HINSTANCE hInstance,
			HINSTANCE hPrevInstance,
			LPSTR pszCmdLine,
			int nShowCmd) 
{

	MessageBox(NULL,
		pszCmdLine,
		"Frist Win32",
		MB_OK);
	return 0;
}