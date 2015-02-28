#include <windows.h>

int WINAPI WinMain( HINSTANCE hInstance,
			HINSTANCE hPrevInstance,
			LPSTR pszCmdLine,
			int nShowCmd) 
{

	MessageBox(NULL,
		"Hello World",
		"HELLO",
		MB_OK | MB_OKCANCEL);
	return 0;
}