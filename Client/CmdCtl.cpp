#include "StdAfx.h"
#include "CmdCtl.h"
#include "ActionDlg.h"



COMMAND_MAP g_CmdCtlId[] = {
							{ID_SET_INFOMATOIN,ID_SET_INFOMATOIN_Proc},
							{IDF_DELETE_FRI,IDF_DELETE_FRI_Proc},
							{IDF_ADDFRI,IDF_ADDFRI_Proc},
							{IDF_SEE_INFOMATION,IDF_SEE_INFOMATION_Proc},
							{ID_SEND_MSG_BUTTON,ID_SEND_MSG_BUTTON_Proc},
							{ID_BGP_P1,ID_BGP_P1_Proc},
							{ID_BGP_P2,ID_BGP_P2_Proc},
							{ID_BGP_P3,ID_BGP_P3_Proc},
							{IDC_EXIT_LOGIN,IDC_EXIT_LOGIN_Proc},
							{ID_BGP_P0,ID_BGP_P0_Proc},
							{0,NULL}
};




int ID_SET_INFOMATOIN_Proc(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp)
{

	DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_REGISTER_DIALOG),hWnd,GET_WNDPROC_ADRR(SetMyInfo));
	return 0;
}//==========================================================================End

int IDF_DELETE_FRI_Proc(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp)
{
	char SendStr[SZBUF_MAX] = "";
	char MyIdStr[12] = "";
	char FriIdStr[12] = "";//得到listctl控件里的好友ID

	GetWindowText(hWnd,MyIdStr,12);

	MY_FRI_ID_PACK *pMyFriId = new MY_FRI_ID_PACK;

	pMyFriId->nEvent = CLI_DELETE_FRI;
	strcpy(pMyFriId->UserId,MyIdStr);
	strcpy(pMyFriId->BeAdderId,FriIdStr);

	sprintf(SendStr,"%-4d%-12s%-12s",pMyFriId->UserId,pMyFriId->BeAdderId);

	if(SOCKET_ERROR == send(g_sockClient,SendStr,strlen(SendStr)+1,0))
	{
		sprintf(MyIdStr,"CLI_DELETE_FRI Error:%d",WSAGetLastError());
		MessageBox(NULL,MyIdStr,MyIdStr,MB_OK);
	}

	return 0;
}//==========================================================================End

int IDF_ADDFRI_Proc(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp)
{
	DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_ADDFRI_DIALOG),hWnd,GET_WNDPROC_ADRR(AddFri));

	return 0;
}//==========================================================================End

int IDF_SEE_INFOMATION_Proc(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp)
{
	//调试用
	//DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_FRIINFO_DIALOG),NULL,GET_WNDPROC_ADRR(FriInfo));

	char SendStr[SZBUF_MAX] = "";
	char MyIdStr[12] = "";
	char FriIdStr[12] = "";//得到listctl控件里的好友ID
	
	GetWindowText(hWnd,MyIdStr,12);
	
	MY_FRI_ID_PACK *pMyFriId = new MY_FRI_ID_PACK;
	
	pMyFriId->nEvent = CLI_SEE_FRI_INFOMATION;
	strcpy(pMyFriId->UserId,MyIdStr);
	strcpy(pMyFriId->BeAdderId,FriIdStr);
	
	sprintf(SendStr,"%-4d%-12s%-12s",pMyFriId->UserId,pMyFriId->BeAdderId);
	
	if(SOCKET_ERROR == send(g_sockClient,SendStr,strlen(SendStr)+1,0))
	{
		sprintf(MyIdStr,"CLI_ADDFRI_ASK Error:%d",WSAGetLastError());
		MessageBox(NULL,MyIdStr,MyIdStr,MB_OK);
	}
	return 0;
}//==========================================================================End

int ID_SEND_MSG_BUTTON_Proc(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp)
{
	char ChatStr[SZBUF_MAX] = "";
	char szBuf[SZBUF_MAX] = "";
	char ErrorStr[255] = "";

	USER_SEND_DATA_PACK *pSendData = new USER_SEND_DATA_PACK;

	GetWindowText(hWnd,szBuf,12);
	pSendData->nEvent = CLI_CHAT_DATA;
	strcpy(pSendData->SourId,szBuf);
	//strcpy(pSendData->DesId,从控件 中获取要发送好友Id);


	GetWindowText(GetDlgItem(hWnd,IDC_CHAT_EDIT),ChatStr,2*SZBUF_MAX);

	//将聊天文本框聊天数据中的表情转化为表情映射中的内容（字符串）
	//fun todo


	GetWindowText(GetDlgItem(hWnd,IDC_INPUT_EDIT),szBuf,SZBUF_MAX);
	
	//将输入文本框聊天数据中的表情转化为表情映射中的内容（字符串）
	//fun todo

	strcpy(pSendData->DataType.szBuf,szBuf);
	sprintf(szBuf,"%-4d%-12s%-12s%s",pSendData->nEvent,pSendData->SourId,pSendData->DesId,pSendData->DataType.szBuf);
	
	if(0 == strcmp("",szBuf))
	{
		MessageBox(NULL,"消息不能为空","Error",MB_OK);
		return 1;
	}

	if(SOCKET_ERROR == send(g_sockClient,szBuf,strlen(szBuf)+1,0))
	{
		sprintf(ErrorStr,"send Error:%d", WSAGetLastError());
		MessageBox(NULL,ErrorStr,"Error",MB_OK);		
	}

	strcat(ChatStr,"自己：");
	strcat(ChatStr,szBuf);
	strcat(ChatStr,"\r\n");
	
	SetWindowText(GetDlgItem(hWnd,IDC_INPUT_EDIT),"");
	SetWindowText(GetDlgItem(hWnd,IDC_CHAT_EDIT),ChatStr);

	return 0;
}//==========================================================================End


int ID_BGP_P0_Proc(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp)
{
	RECT rt;
	GetWindowRect(hWnd,&rt);
	
	*pBgp = 0;
	UpdateWindow(hWnd);	
	InvalidateRect(hWnd,&rt,TRUE);

	return 0;
}

int ID_BGP_P1_Proc(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp)
{
	//设置窗口背景图片

	RECT rt;
	GetWindowRect(hWnd,&rt);

	*pBgp = 1;
	UpdateWindow(hWnd);	
	InvalidateRect(hWnd,&rt,TRUE);


	return 0;
}//==========================================================================End

int ID_BGP_P2_Proc(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp)
{
	RECT rt;
	GetWindowRect(hWnd,&rt);

	*pBgp = 2;
	UpdateWindow(hWnd);
	InvalidateRect(hWnd,&rt,TRUE);

	return 0;
}//==========================================================================End

int ID_BGP_P3_Proc(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp)
{
	RECT rt;
	GetWindowRect(hWnd,&rt);

	*pBgp = 3;
	UpdateWindow(hWnd);
	InvalidateRect(hWnd,&rt,TRUE);

	return 0;
}//==========================================================================End

int IDC_EXIT_LOGIN_Proc(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp)
{
	char SendStr[SZBUF_MAX] = "";
	USER_ID_PACK *pUser = new USER_ID_PACK;

	pUser->nEvent = CLI_EXIT;
	GetWindowText(hWnd,pUser->IdStr,12);

	sprintf(SendStr,"%-4d%-12s",pUser->nEvent,pUser->IdStr);

	if(SOCKET_ERROR == send(g_sockClient,SendStr,strlen(SendStr)+1,0))
	{
		return -1;
	}

	delete pUser;
	closesocket(g_sockClient);
	EndDialog(hWnd,WM_CLOSE);
	return 0;
}


int CtlIdProc(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp)
{
	COMMAND_MAP *pTemp = g_CmdCtlId;

	UINT CtlId = LOWORD(wParam);


	int i = 0;
	for (i = 0;NULL != pTemp[i].pFun;i++)
	{
		if(CtlId == pTemp[i].CtlId)
		{
			pTemp[i].pFun(hWnd,wParam,lParam,pBgp);
			break;
		}
	}

	if(NULL == pTemp[i].pFun)
	{
		return 2;
	}

	return 0;
}



