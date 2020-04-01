#include "StdAfx.h"
#include "Register.h"
#include "CliEventProc.h"


IMPLEMENT_WNDPROC(RegisterDlg)


BEGIN_MSGMAP(RegisterDlg)
BODY_MSGMAP(WM_INITDIALOG,OnRInitMsg)
BODY_MSGMAP(WM_COMMAND,OnRCommand)
BODY_MSGMAP(WM_CLOSE,OnRCloseMsg)
BODY_MSGMAP(WM_PAINT,OnRPaintMsg)
BODY_MSGMAP(WM_CTLCOLORSTATIC,OnRCTLCOLORSTATICMsg)
BODY_MSGMAP(WM_DRAWITEM,OnRDRAWITEMMsg)
END_MSGMAP


LRESULT OnRInitMsg(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	char PicStr[10] = "";

	HWND combo1 = GetDlgItem(hWnd,IDC_COMBO_HEAD);

// 	HWND combo1 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("COMBOBOX"), NULL, WS_CHILD | WS_VISIBLE |CBS_DROPDOWN ,
// 		185, 110, 160, 30, hWnd, (HMENU)9, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	SendMessage(combo1, WM_SETFONT, (WPARAM)GetStockObject(17), 0);
	SendMessage(combo1, CB_ADDSTRING, NULL, (LPARAM)TEXT("头像1"));
	SendMessage(combo1, CB_ADDSTRING, NULL, (LPARAM)TEXT("头像2"));
	SendMessage(combo1, CB_ADDSTRING, NULL, (LPARAM)TEXT("头像3"));
	SendMessage(combo1, CB_SETCURSEL, 0, NULL);//自动选择第一项

	return TRUE;
}//=======================================================================End

LRESULT OnRCommand(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	char Str[SZBUF_MAX] = "";
	char SendStr[SZBUF_MAX] = "";
	switch (LOWORD(wParam))
	{
		case ID_SUBMIT_BUTTON:
			{
				REGISTER_PACK *pRegister = new REGISTER_PACK;
				pRegister->nEvent = CLI_REGISTER;
				if(0 == GetWindowText(GetDlgItem(hWnd,IDC_RNAME_EDIT),pRegister->uName,20))
				{
					MessageBox(hWnd,"名字不能为空","Error",MB_OK|MB_ICONWARNING);
					return 1;
				}

				if(0 == GetWindowText(GetDlgItem(hWnd,IDC_RPWD_EDIT),pRegister->uPwd,17))
				{
					MessageBox(hWnd,"密码不能为空","Error",MB_OK|MB_ICONWARNING);
					return 2;
				}

				if(0 == GetWindowText(FindWindowEx(hWnd,NULL,TEXT("COMBOBOX"),NULL),pRegister->PicStr,10))
				{
					MessageBox(hWnd,"头像不能为空","Error",MB_OK|MB_ICONWARNING);
					return 3;
				}

				if(0 != strcmp("头像1",pRegister->PicStr) && 0 != strcmp("头像2",pRegister->PicStr) && 0 != strcmp("头像3",pRegister->PicStr))
				{
					MessageBox(hWnd,"头像格式错误","Error",MB_OK|MB_ICONWARNING);
					return 4;
				}

				GetWindowText(GetDlgItem(hWnd,IDC_RAGE_EDIT),Str,4);
				GetWindowText(GetDlgItem(hWnd,IDC_RHRO_EDIT),pRegister->uHro,10);

				//前4字节为事件标识，20字节昵称，17字节密码，10字节图片，10字节星座，4字节年龄
				sprintf(SendStr,"%-4d%-20s%-17s%-10s%-10s%-4s",pRegister->nEvent,pRegister->uName,pRegister->uPwd,pRegister->uHro,Str);
				if(SOCKET_ERROR == send(g_sockClient,SendStr,strlen(SendStr)+1,0))
				{
					sprintf(Str,"注册错误:%d",WSAGetLastError());
					MessageBox(hWnd,Str,"Error",MB_OK);
				}
				else
				{
					MessageBox(hWnd,"注册完成","End",MB_OK);
					EndDialog(hWnd,WM_CLOSE);
				}

				delete pRegister;
	
			}
			break;
		default:
			break;
	}
	return TRUE;
}//=======================================================================End

LRESULT OnRPaintMsg(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd,&ps);

	
	
	char *pStr = MAKEINTRESOURCE(IDB_BITMAP7);

	SetBgToWnd(hWnd,hdc,pStr);
	EndPaint(hWnd,&ps);
	return TRUE;
}


LRESULT OnRCloseMsg(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	EndDialog(hWnd,WM_CLOSE);
	return TRUE;
}//=======================================================================End



LRESULT OnRCTLCOLORSTATICMsg(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	SetTextColor((HDC) wParam, RGB(0,255,0)); 
	SetBkMode((HDC)wParam, TRANSPARENT);
	return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));
}

LRESULT OnRDRAWITEMMsg(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	ControlMap(IDB_BUTTON_BITMAP,ID_SUBMIT_BUTTON,"提交",lParam);

	
	return TRUE;
}