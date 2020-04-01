#include "StdAfx.h"
#include "Register.h"
#include "CliEventProc.h"
#include "AddBgpToWnd.h"
#include "Login.h"




IMPLEMENT_WNDPROC(LoginDlg)


BEGIN_MSGMAP(LoginDlg)
BODY_MSGMAP(WM_INITDIALOG,OnLInitMsg)
BODY_MSGMAP(WM_COMMAND,OnLCommand)
BODY_MSGMAP(WM_CLOSE,OnLCloseMsg)
BODY_MSGMAP(WM_LOGIN_SOCKET,OnLSockMsg)
BODY_MSGMAP(WM_PAINT,OnLPaintMsg)
BODY_MSGMAP(WM_CTLCOLORSTATIC,OnLCTLCOLORSTATICMsg)
BODY_MSGMAP(WM_DRAWITEM,OnLDRAWITEMMsg)
END_MSGMAP


LRESULT OnLInitMsg(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	WSAAsyncSelect(g_sockClient,hWnd,WM_LOGIN_SOCKET,FD_READ | FD_CLOSE);



	return TRUE;
}//=======================================================================End

LRESULT OnLCommand(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	switch(LOWORD(wParam))
	{
		case ID_LOGIN_BUTTON:
			{
				char SendStr[SZBUF_MAX] = "";
				char Str[255] = "";
				
				LOGIN_PACK *pLogin = new LOGIN_PACK;
				
				pLogin->nEvent = CLI_LOGIN;

				if(0 == GetWindowText(GetDlgItem(hWnd,IDC_IDSTR_EDIT),pLogin->IdStr,12))
				{
					MessageBox(hWnd,"ID²»ÄÜÎª¿Õ","Error",MB_OK|MB_ICONWARNING);
					return 1;
				}

				if(0 == GetWindowText(GetDlgItem(hWnd,IDC_PWD_EDIT),pLogin->PwdStr,17))
				{
					MessageBox(hWnd,"ÃÜÂë²»ÄÜÎª¿Õ","Error",MB_OK|MB_ICONWARNING);
					return 2;
				}

				

				HWND hWndPa = GetParent(hWnd);
				SetWindowText(hWndPa,pLogin->IdStr);
				
				sprintf(SendStr,"%-4d%-12s%-17s",pLogin->nEvent,pLogin->IdStr,pLogin->PwdStr);
				//EndDialog(hWnd,WM_CLOSE);
				if(SOCKET_ERROR == send(g_sockClient,SendStr,strlen(SendStr)+1,0))
				{
					sprintf(Str,"µÇÂ¼´íÎó:%d",WSAGetLastError());
					MessageBox(hWnd,Str,Str,MB_OK);
					break;
				}
				delete pLogin;
			}
			break;
		case ID_REGISTER_BUTTON:
			{
				DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_REGISTER_DIALOG),hWnd,GET_WNDPROC_ADRR(RegisterDlg));
			}
			break;
		default:
			break;
	}
	return TRUE;
}//=======================================================================End

LRESULT OnLCloseMsg(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	EndDialog(hWnd,WM_CLOSE);
	PostQuitMessage(0);
	closesocket(g_sockClient);
	exit(0);
	return TRUE;
}//=======================================================================End

LRESULT OnLSockMsg(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	char szBuf[SZBUF_MAX] = "";
	char ErrorStr[255] = "";
	if(0 == WSAGETSELECTERROR(lParam))
	{
		if(FD_READ == WSAGETSELECTEVENT(lParam))
		{
			
			if(SOCKET_ERROR == recv(g_sockClient,szBuf,SZBUF_MAX,0))
			{
				sprintf(ErrorStr,"recv Error:%d", WSAGetLastError());
				MessageBox(NULL,ErrorStr,"Error",MB_OK);
				
			}
			CALL_CLI_EVENTPROC(Client,szBuf,hWnd);
		}
	}
	return TRUE;
}

LRESULT OnLPaintMsg(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd,&ps);
	char *Str = MAKEINTRESOURCE(IDB_BITMAP6);
	SetBgToWnd(hWnd,hdc,Str);
	EndPaint(hWnd,&ps);
	return TRUE;
}

LRESULT OnLCTLCOLORSTATICMsg(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	SetTextColor((HDC) wParam, RGB(125,0,0)); 
	SetBkMode((HDC)wParam, TRANSPARENT);
	return (BOOL)((HBRUSH)GetStockObject(HOLLOW_BRUSH));
}

LRESULT OnLDRAWITEMMsg(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	ControlMap(IDB_BUTTON_BITMAP,ID_LOGIN_BUTTON,"µÇÂ¼",lParam);
	ControlMap(IDB_BUTTON_BITMAP,ID_REGISTER_BUTTON,"×¢²á",lParam);

	return TRUE;
}