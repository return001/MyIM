#include "StdAfx.h"
#include "CliEventProc.h"
#include "ActionDlg.h"
#include "AddFriToList.h"

IMPLEMENT_CLI_EVENTPROC(Client)

BEGIN_EVENT_MAP(Client)
BODY_EVENTMAP(SER_SEND_USER_ID,NULL,RegisteBackProc)
BODY_EVENTMAP(SER_NOTFINDID_ERROR,NULL,NotFindIdErrorProc)
BODY_EVENTMAP(SER_USERPWD_ERROR,NULL,PwdErrorProc)
BODY_EVENTMAP(SER_SEND_FRIEND_LIST,NULL,LoginBackFriListProc)
BODY_EVENTMAP(SER_LOGIN_SUCCESS,NULL,LoginSuccessProc)
BODY_EVENTMAP(SER_SEND_USER_INFORMATION,NULL,SER_SEND_USER_INFORMATION_Proc)
BODY_EVENTMAP(SER_ADD_YET,NULL,SER_ADD_YET_Proc)
BODY_EVENTMAP(SER_ASK_AGREE,NULL,SER_ASK_AGREE_Proc)
BODY_EVENTMAP(SER_ASK_REFUSE,NULL,SER_ASK_REFUSE_Proc)
BODY_EVENTMAP(SER_SEND_DATA,NULL,SER_SEND_DATA_Proc)
BODY_EVENTMAP(SER_CHANGE_FINISH,NULL,SER_CHANGE_FINISH_Proc)
BODY_EVENTMAP(SER_BE_DELETED,NULL,SER_BE_DELETED_Proc)
BODY_EVENTMAP(SER_USER_EXIT,NULL,SER_USER_EXIT_Proc)
BODY_EVENTMAP(SER_ADD_ERROR,NULL,SER_ADD_ERROR_Proc)
BODY_EVENTMAP(SER_SEND_PICTURE,NULL,SER_SEND_PICTURE_Proc)
BODY_EVENTMAP(SER_OPER_ERROR,NULL,SER_OPER_ERROR_Proc)
BODY_EVENTMAP(SER_ADD_ASK,NULL,SER_ADD_ASK_Proc)
BODY_EVENTMAP(SER_NOTFIND_ID,NULL,SER_NOTFIND_ID_Proc)
END_EVENTMAP




//===============================================================

IMPLEMENT_NEWNODE(FRIEND_NODE)
INIT_PFN_TABLE(FRIEND_NODE,FriInput,GET_CREATE_ADDR(FRIEND_NODE))

INIT_PHEAD(Friend)

//================================================

char g_RecvStr[SZBUF_MAX];
int g_Count = 1;



//==============================================

int RegisteBackProc(void *pVoid,HWND hWnd)
{
	USER_ID_PACK *pUser =(USER_ID_PACK *)pVoid;

	char Str[255] = "";
	sprintf(Str,"注册成功你的ID为:%s",pUser->IdStr);
	HWND hWndPa = GetParent(hWnd);
	SetWindowText(hWndPa,pUser->IdStr);
	MessageBox(hWnd,Str,"ID",MB_OK);
	return 0;
}//=============================================End

int LoginBackFriListProc(void *pVoid,HWND hWnd)
{

	if(NULL == USE_PHEAD(Friend))
	{
		 CreateList(&USE_PHEAD(Friend),CALL_NEWNODE(FRIEND_NODE),pVoid,0);
	}
	else
	{
		AddNode(USE_PHEAD(Friend),pVoid,0,CALL_NEWNODE(FRIEND_NODE));
	}

	AddFriendItem(hWnd,pVoid,g_Count);
	g_Count++;
	return 0;
}//=============================================End

int NotFindIdErrorProc(void *pVoid,HWND hWnd)
{
	MessageBox(hWnd,((EVENT_TIP_PACK *)pVoid)->nExvent,"ID Error",MB_OK);
	return 0;
}//=============================================End




int LoginSuccessProc(void *pVoid,HWND hWnd)
{

	EndDialog(hWnd,WM_CLOSE);
	return 0;
}


int PwdErrorProc(void *pVoid,HWND hWnd)
{
	MessageBox(hWnd,((EVENT_TIP_PACK *)pVoid)->nExvent,"PassWord Error",MB_OK);
	return 0;
}

int SER_SEND_USER_INFORMATION_Proc(void *pVoid,HWND hWnd)
{

	strcpy(g_RecvStr,(char *)pVoid);
	DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_FRIINFO_DIALOG),NULL,GET_WNDPROC_ADRR(FriInfo));
	return 0;
}

int SER_ADD_YET_Proc(void *pVoid,HWND hWnd)
{

	MessageBox(hWnd,((EVENT_TIP_PACK *)pVoid)->nExvent,"提示框",MB_OK);
	return 0;
}//===================================================End

int SER_SEND_PICTURE_Proc(void *pVoid,HWND hWnd)
{

	return 0;
}//===================================================End


int SER_ASK_AGREE_Proc(void *pVoid,HWND hWnd)
{
	USER_FRIEND_BASIC_PACK *pFriNode = (USER_FRIEND_BASIC_PACK *)pVoid;

	pFriNode->IdStr[11] = '\0';
	pFriNode->FName[19] = '\0';
	pFriNode->PicStr[9] = '\0';
	//((char *)(pFriNode->FState))[3] = '\0';


	
	if(NULL == USE_PHEAD(Friend))
	{
		CreateList(&USE_PHEAD(Friend),CALL_NEWNODE(FRIEND_NODE),pVoid,0);
	}
	else
	{
		AddNode(USE_PHEAD(Friend),pVoid,0,CALL_NEWNODE(FRIEND_NODE));
	}
	
	//在控件里添加好友
	AddFriendItem(hWnd,pVoid,g_Count);
	g_Count++;
	return 0;
}//===================================================End

int SER_ASK_REFUSE_Proc(void *pVoid,HWND hWnd)
{
	char Refuser[255] = "";

	USER_ID_PACK *pUser = (USER_ID_PACK *)pVoid;

	sprintf(Refuser,"对方拒绝：%-12s",pUser->IdStr);

	MessageBox(hWnd,Refuser,Refuser,MB_OK);

	return 0;
}//===================================================End

int SER_SEND_DATA_Proc(void *pVoid,HWND hWnd)
{
	char ChatStr[SZBUF_MAX] = "";
	char szBuf[SZBUF_MAX] = "";
	SER_SEND_DATA_PACK *pUserData = (SER_SEND_DATA_PACK *)pVoid;

	pUserData->SourId[11] = '\0';

	FRIEND_NODE *pNode = (FRIEND_NODE *)FindNode(USE_PHEAD(Friend),pUserData->SourId);

	if(CHOOSE == pNode->IsBeChoose)
	{
		GetWindowText(GetDlgItem(hWnd,IDC_CHAT_EDIT),ChatStr,SZBUF_MAX);


		strcpy(szBuf,pUserData->SourId);
		strcat(szBuf,": ");
		strcat(szBuf,pUserData->DataType.szBuf);
		strcat(ChatStr,szBuf);
		strcat(ChatStr,"\r\n");

		if((SZBUF_MAX-3) <= strlen(ChatStr))
		{
			SetWindowText(GetDlgItem(hWnd,IDC_CHAT_EDIT),szBuf);

		}
		else
		{
			SetWindowText(GetDlgItem(hWnd,IDC_CHAT_EDIT),ChatStr);
		}
	}
	else
	{
		FILE *hFile = fopen(pNode->FileName,"a+");

		fwrite(pUserData->DataType.szBuf,strlen(pUserData->DataType.szBuf)+1,1,hFile);

		fclose(hFile);
	}

	return 0;
}//===================================================End

int SER_CHANGE_FINISH_Proc(void *pVoid,HWND hWnd)
{
	MessageBox(hWnd,((EVENT_TIP_PACK *)pVoid)->nExvent,"修改完成",MB_OK);

	return 0;
}//===================================================End

int SER_BE_DELETED_Proc(void *pVoid,HWND hWnd)
{
	USER_ID_PACK *pUser = (USER_ID_PACK *)pVoid;

	pUser->IdStr[11] = '\0';

	DeleteNode(&(USE_PHEAD(Friend)),pUser->IdStr);

	//在控件里删除好友

	return 0;
}//===================================================End

int SER_USER_EXIT_Proc(void *pVoid,HWND hWnd)
{
	USER_ID_PACK *pUser = (USER_ID_PACK *)pVoid;

	pUser->IdStr[11] = '\0';

	FRIEND_NODE *pNode = (FRIEND_NODE *)FindNode(USE_PHEAD(Friend),pUser->IdStr);

	pNode->FState = OFF_LINE;

	//在控件里设置离线
	return 0;
}//===================================================End

int SER_ADD_ERROR_Proc(void *pVoid,HWND hWnd)
{
	return 0;
}//===================================================End

int SER_OPER_ERROR_Proc(void *pVoid,HWND hWnd)
{
	return 0;
}//===================================================End


int SER_ADD_ASK_Proc(void *pVoid,HWND hWnd)
{
	char Str[255] = "";
	char SendStr[SZBUF_MAX] = "";
	USER_ID_PACK *pFriId = (USER_ID_PACK *)pVoid;
	MY_FRI_ID_PACK *pMyFriId =  new MY_FRI_ID_PACK;

	pFriId->IdStr[11] = '\0';
	strcpy(pMyFriId->UserId,pFriId->IdStr);

	GetWindowText(hWnd,pMyFriId->BeAdderId,12);

	sprintf(Str,"ID为：%s用户添加你为好友",pFriId->IdStr);


	if(IDOK == MessageBox(hWnd,Str,"请求添加好友",MB_OKCANCEL))
	{
		pMyFriId->nEvent = CLI_ADD_AGREE;
	}
	else
	{
		pMyFriId->nEvent = CLI_ADD_REFUSE;
	}

	sprintf(SendStr,"%-4d%-12s%-12s",pMyFriId->nEvent,pMyFriId->UserId,pMyFriId->BeAdderId);

	if(SOCKET_ERROR == send(g_sockClient,SendStr,strlen(SendStr)+1,0))
	{
		return -1;
	}

	delete pMyFriId;
	return 0;
}

int SER_NOTFIND_ID_Proc(void *pVoid,HWND hWnd)
{
	EVENT_TIP_PACK *pEvent = (EVENT_TIP_PACK *)pVoid;

	MessageBox(hWnd,pEvent->nExvent,pEvent->nExvent,MB_OK);

	return 0;
}

int FriInput(LINKER *pNode,void *pVoid,SOCKET nSock)
{
	USER_FRIEND_BASIC_PACK *pFriend = (USER_FRIEND_BASIC_PACK *)pVoid;
	FRIEND_NODE *pFriNode = (FRIEND_NODE *)pNode;
	
	pFriend->FName[19] = '\0';
	pFriend->IdStr[11] = '\0';
	pFriend->PicStr[9] = '\0';
	//((char *)pFriend->FState)[3] = '\0';

	strcpy(pFriNode->FName,pFriend->FName);
	strcpy(pFriNode->FileName,pFriend->IdStr);
	strcpy(pFriNode->PicStr,pFriend->PicStr);
	strcat(pFriNode->FileName,".txt");
	pFriNode->IsBeChoose = NO_CHOOSE;
	strcpy(pFriNode->linker.IdStr,pFriend->IdStr);
	pFriNode->FState = atoi((char *)(&pFriend->FState));
	
	return 0;
}