// AsyncSelectClient.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"


SOCKET g_sockClient;
BOOL CALLBACK DlgProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.

	WSADATA wData;

	WSAStartup(0x0202,&wData);

	DialogBox(hInstance,MAKEINTRESOURCE(IDD_CHAT_DIALOG),NULL,DlgProc);
	WSACleanup();
	return 0;
}



BOOL CALLBACK DlgProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	char ErrorStr[255] = "";
	char szBuf[SZBUF_MAX] = "";
	char ChatStr[2*SZBUF_MAX] = "";

	switch (uMsg)
	{
		case WM_INITDIALOG:
			{
				g_sockClient = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
				
				if(INVALID_SOCKET == g_sockClient)
				{
					sprintf(ErrorStr,"socket Error:%d", WSAGetLastError());
					MessageBox(NULL,ErrorStr,"Error",MB_OK);
					//exit(0);
				}
				
				SOCKADDR_IN sockAddr;
				sockAddr.sin_family = AF_INET;
				sockAddr.sin_addr.s_addr = inet_addr(CLIENT_IP_STR);
				sockAddr.sin_port = htons(PORT_NUM);
				
				if(SOCKET_ERROR == connect(g_sockClient,(sockaddr *)&sockAddr,sizeof(sockAddr)))
				{
					sprintf(ErrorStr,"connect Error:%d", WSAGetLastError());
					MessageBox(NULL,ErrorStr,"Error",MB_OK);
					exit(0);
				}
				WSAAsyncSelect(g_sockClient,hWnd,WM_ZXCSOCKET,FD_READ | FD_CLOSE);
			}
			break;
		case WM_COMMAND:
			{
				if (ID_SEND_BUTTON == LOWORD(wParam))
				{
					
					GetWindowText(GetDlgItem(hWnd,IDC_CHAT_EDIT),ChatStr,2*SZBUF_MAX);
					GetWindowText(GetDlgItem(hWnd,IDC_INPUT_EDIT),szBuf,SZBUF_MAX);
					if(SOCKET_ERROR == send(g_sockClient,szBuf,strlen(szBuf)+1,0))
					{
						sprintf(ErrorStr,"send Error:%d", WSAGetLastError());
						MessageBox(NULL,ErrorStr,"Error",MB_OK);
						
					}
					strcat(ChatStr,"自己：");
					strcat(ChatStr,szBuf);
					strcat(ChatStr,"\r\n");

					SetWindowText(GetDlgItem(hWnd,IDC_CHAT_EDIT),ChatStr);

				}
			}
			break;
		case WM_ZXCSOCKET:
			{

				if(0 == WSAGETSELECTERROR(lParam))
				{
					if(FD_READ == WSAGETSELECTEVENT(lParam))
					{
						GetWindowText(GetDlgItem(hWnd,IDC_CHAT_EDIT),ChatStr,2*SZBUF_MAX);

						if(SOCKET_ERROR == recv(g_sockClient,szBuf,SZBUF_MAX,0))
						{
							sprintf(ErrorStr,"recv Error:%d", WSAGetLastError());
							MessageBox(NULL,ErrorStr,"Error",MB_OK);
							
						}
						strcat(ChatStr,"对方：");
						strcat(ChatStr,szBuf);
						strcat(ChatStr,"\r\n");
						
						SetWindowText(GetDlgItem(hWnd,IDC_CHAT_EDIT),ChatStr);
					}
				}
			}
			break;
		case WM_CLOSE:
			{
				EndDialog(hWnd,WM_CLOSE);
			}
			break;
		default:
			return FALSE;
			break;
	}
	return TRUE;
}