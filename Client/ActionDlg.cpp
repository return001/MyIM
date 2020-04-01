#include "StdAfx.h"
#include "AddBgpToWnd.h"
#include "ActionDlg.h"


////////////////////////////////////////////////////////////////////
//设置自己的个人信息对话处理框


IMPLEMENT_WNDPROC(SetMyInfo)

BEGIN_MSGMAP(SetMyInfo)
BODY_MSGMAP(WM_INITDIALOG,OnSInitMsgProc)
BODY_MSGMAP(WM_COMMAND,OnSCommandMsgProc)
BODY_MSGMAP(WM_CLOSE,OnSCloseMsgProc)
BODY_MSGMAP(WM_DRAWITEM,OnSDRAWITEMMsgProc)
BODY_MSGMAP(WM_PAINT,OnSPaintMsgProc)
BODY_MSGMAP(WM_CTLCOLORSTATIC,OnSCTLCOLORSTATICMsgProc)
END_MSGMAP



LRESULT OnSPaintMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT ps;
	
	HDC hdc = BeginPaint(hWnd,&ps);

	char *Str = MAKEINTRESOURCE(IDB_BITMAP7);
	SetBgToWnd(hWnd,hdc,Str);

	EndPaint(hWnd,&ps);
	return TRUE;
}

LRESULT OnSCTLCOLORSTATICMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	SetTextColor((HDC) wParam, RGB(125,0,0)); 
	SetBkMode((HDC)wParam, TRANSPARENT);
	return (BOOL)((HBRUSH)GetStockObject(HOLLOW_BRUSH));
}

LRESULT OnSDRAWITEMMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	ControlMap(IDB_BUTTON_BITMAP,ID_SUBMIT_BUTTON,"确认",lParam);
	return TRUE;
}
LRESULT OnSInitMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	SetWindowText(hWnd,"修改信息框");
	return TRUE;
}//==============================================================End

LRESULT OnSCommandMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	char Str[SZBUF_MAX] = "";
	char SendStr[SZBUF_MAX] = "";
	switch (LOWORD(wParam))
	{
	case ID_SUBMIT_BUTTON:
		{
			MODIFY_PACK *pModifyer = new MODIFY_PACK;
			pModifyer->nEvent = CLI_MODIFY;
			GetWindowText(GetDlgItem(hWnd,IDC_RNAME_EDIT),pModifyer->uName,20);
			GetWindowText(GetDlgItem(hWnd,IDC_RPWD_EDIT),pModifyer->uPwd,17);
			GetWindowText(GetDlgItem(hWnd,IDC_RAGE_EDIT),Str,4);
			GetWindowText(GetDlgItem(hWnd,IDC_RHRO_EDIT),pModifyer->uHro,10);
			GetWindowText(GetParent(hWnd),pModifyer->SourId,12);
			
			
			
			//前4字节为事件标识，12字节ID，20字节昵称，17字节密码，10字节星座，4字节年龄
			sprintf(SendStr,"%-4d%-12s%-20s%-17s%-10s%-4s",pModifyer->nEvent,pModifyer->SourId,pModifyer->uName,pModifyer->uPwd,pModifyer->uHro,Str);
			if(SOCKET_ERROR == send(g_sockClient,SendStr,strlen(SendStr)+1,0))
			{
				sprintf(Str,"修改错误:%d",WSAGetLastError());
				MessageBox(NULL,Str,"Error",MB_OK);
			}
			else
			{
				MessageBox(hWnd,"修改完成，下次登录使用新密码","End",MB_OK);
				EndDialog(hWnd,WM_CLOSE);
			}
			
		}
		break;
	default:
		break;
	}
	return TRUE;
}//==============================================================End

LRESULT OnSCloseMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	EndDialog(hWnd,WM_CLOSE);
	return TRUE;
}//==============================================================End



///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//查看好友信息的处理框


BEGIN_MSGMAP(FriInfo)
BODY_MSGMAP(WM_INITDIALOG,OnShowInfoInitMsgProc)
BODY_MSGMAP(WM_COMMAND,OnShowInfoCommandMsgProc)
BODY_MSGMAP(WM_CLOSE,OnShowInfoCloseMsgProc)
BODY_MSGMAP(WM_PAINT,OnShowInfoPaintMsgProc)
BODY_MSGMAP(WM_CTLCOLORSTATIC,OnShowInfoCTLCOLORSTATICMsgProc)
BODY_MSGMAP(WM_DRAWITEM,OnShowInfoDRAWITEMMsgProc)
END_MSGMAP


IMPLEMENT_WNDPROC(FriInfo)


LRESULT OnShowInfoDRAWITEMMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	ControlMap(IDB_HEAD_BITMAP1,IDC_HEAD_BUTTON,"",lParam);

	return TRUE;
}

LRESULT OnShowInfoPaintMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT ps;
	
	HDC hdc = BeginPaint(hWnd,&ps);
	
	char *Str = MAKEINTRESOURCE(IDB_BITMAP7);
	SetBgToWnd(hWnd,hdc,Str);
	
	EndPaint(hWnd,&ps);
	return TRUE;
}


LRESULT OnShowInfoCTLCOLORSTATICMsgProc(HWND hWnd,WPARAM wParam,LPARAM)
{
	SetTextColor((HDC) wParam, RGB(125,0,0)); 
	SetBkMode((HDC)wParam, TRANSPARENT);
	return (BOOL)((HBRUSH)GetStockObject(HOLLOW_BRUSH));
}


LRESULT OnShowInfoInitMsgProc(HWND hWnd,WPARAM wParam ,LPARAM lParam)
{
	SER_FRIEND_INFOMATION_PACK *pFriInfo = (SER_FRIEND_INFOMATION_PACK *)g_RecvStr;
	
	pFriInfo->IdStr[11] = '\0';
	((char *)(pFriInfo->uAge))[3] = '\0';
	pFriInfo->uHoro[9] = '\0';
	pFriInfo->uName[19] = '\0';
	pFriInfo->PicStr[9] = '\0';
	((char *)(pFriInfo->uState))[3] = '\0';
	
	if (LINE == atoi((char *)pFriInfo->uState))
	{
		SetWindowText(GetDlgItem(hWnd,IDC_STATEINFO_EDIT),"在线");
	}
	else
	{
		SetWindowText(GetDlgItem(hWnd,IDC_STATEINFO_EDIT),"离线");
	}
	
	SetWindowText(GetDlgItem(hWnd,IDC_SEXINFO_EDIT),pFriInfo->uHoro);
	SetWindowText(GetDlgItem(hWnd,IDC_AGEINFO_EDIT),(char *)(pFriInfo->uAge));
	SetWindowText(GetDlgItem(hWnd,IDC_NAMEINFO_EDIT2),pFriInfo->uName);
	SetWindowText(GetDlgItem(hWnd,IDC_IDINFO_STATIC),pFriInfo->IdStr);
	return TRUE;
}//==================================================================End

LRESULT OnShowInfoCommandMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	return TRUE;
}//==================================================================End

LRESULT OnShowInfoCloseMsgProc(HWND hWnd,WPARAM wParam ,LPARAM lParam)
{
	EndDialog(hWnd,WM_CLOSE);
	return TRUE;
}//==================================================================End




////////////////////////////////////////////////////////////////////////////
//添加好友的处理框

BEGIN_MSGMAP(AddFri)
BODY_MSGMAP(WM_INITDIALOG,OnAddInitMsgProc)
BODY_MSGMAP(WM_COMMAND,OnAddCommandMsgProc)
BODY_MSGMAP(WM_CLOSE,OnAddCloseMsgProc)
BODY_MSGMAP(WM_DRAWITEM,OnAddDRAWITEMMsgProc)
BODY_MSGMAP(WM_CTLCOLORSTATIC,OnAddCTLCOLORSTATICMsgProc)
BODY_MSGMAP(WM_PAINT,OnAddPaintMsgProc)
END_MSGMAP

IMPLEMENT_WNDPROC(AddFri)


LRESULT OnAddPaintMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT ps;
	
	HDC hdc = BeginPaint(hWnd,&ps);
	
	char *Str = MAKEINTRESOURCE(IDB_BITMAP6);
	SetBgToWnd(hWnd,hdc,Str);
	
	EndPaint(hWnd,&ps);
	return TRUE;
}//===============================================End

LRESULT OnAddCTLCOLORSTATICMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	SetTextColor((HDC) wParam, RGB(125,0,0)); 
	SetBkMode((HDC)wParam, TRANSPARENT);
	return (BOOL)((HBRUSH)GetStockObject(HOLLOW_BRUSH));

}//=========================================================End
LRESULT OnAddDRAWITEMMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	ControlMap(IDB_BUTTON_BITMAP,ID_ADDFRI_BUTTON,"确认",lParam);

	return TRUE;
}//=================================================eND

LRESULT OnAddInitMsgProc(HWND hWnd,WPARAM wParam ,LPARAM lParam)
{
	return TRUE;
}//==================================================================End

LRESULT OnAddCommandMsgProc(HWND hWnd,WPARAM wParam ,LPARAM lParam)
{
	switch(LOWORD(wParam))
	{
		case ID_ADDFRI_BUTTON:
		{
			char IdStr[255] = "";
			char SendStr[SZBUF_MAX] = "";
			
			MY_FRI_ID_PACK *pMyFriId = new MY_FRI_ID_PACK;
			pMyFriId->nEvent = CLI_ADDFRI_ASK;
			GetWindowText(GetParent(hWnd),pMyFriId->UserId,12);

			if(11 != GetWindowText(GetDlgItem(hWnd,IDC_ADDFRI_ID_EDIT),pMyFriId->BeAdderId,255))
			{
				return 2;
			}

			sprintf(SendStr,"%-4d%-12s%-12s",pMyFriId->nEvent,pMyFriId->UserId,pMyFriId->BeAdderId);
			if(SOCKET_ERROR == send(g_sockClient,SendStr,strlen(SendStr)+1,0))
			{
				//ERROR TODO
				sprintf(IdStr,"CLI_ADDFRI_ASK Error:%d",WSAGetLastError());
				MessageBox(NULL,IdStr,IdStr,MB_OK);
				//return -2;
			}
			
			delete pMyFriId;
			EndDialog(hWnd,WM_CLOSE);
		}
		break;
	default:
		break;
	}
	return TRUE;
}//========================================================================End

LRESULT OnAddCloseMsgProc(HWND hWnd,WPARAM wParam ,LPARAM lParam)
{
	EndDialog(hWnd,WM_CLOSE);
	return TRUE;
}//========================================================================End


