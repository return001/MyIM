// Client.cpp : Defines the entry point for the application.
//


#include "stdafx.h"
#include "MainWnd.h"


#pragma  comment (lib,"comctl32.lib")

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.

	WSADATA wData;
	
	WSAStartup(0x0202,&wData);
	

	HMODULE g_hDll = LoadLibrary("RICHED20.DLL");
	if (NULL == g_hDll)
	{
		MessageBox(NULL,"Error","Error",MB_OK);
		return 1;
	}
	//AfxInitRichEdit();
	DialogBox(hInstance,MAKEINTRESOURCE(IDD_CHAT_DLG),NULL,MainDlgProc);
	WSACleanup();

	FreeLibrary(g_hDll);
	return 0;
}



