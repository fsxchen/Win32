#include "windows.h"
#include <stdlib.h>


int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR pszCmdLine,
	int nShowCmd
	)
{
	CHAR     m_Volume[256];//卷标名  
	CHAR     m_FileSysName[256];  
	DWORD   m_SerialNum;//序列号  
	DWORD   m_FileNameLength;  
	DWORD   m_FileSysFlag;  
	GetVolumeInformation("c:\\",  
	    m_Volume,  
	    256,  
	    &m_SerialNum,  
	    &m_FileNameLength,  
	    &m_FileSysFlag,  
	    m_FileSysName,  
	    256);
	// CString Serial;
	// Serial.Format("%lx",m_SerialNum);
	// SetDlgItemText(IDC_EDIT_User,Serial);
	MessageBox(NULL,
		m_Volume,
		"Frist Win32",
		MB_OK);
	return 0;
}