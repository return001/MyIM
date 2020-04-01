#include "StdAfx.h"
#include "Login.h"
#include "CliEventProc.h"
#include "CmdCtl.h"
#include "RichEdit.h"
#include "ToolBar.h"
#include "AddFriToList.h"
#include "MainWnd.h"




SOCKET g_sockClient;

int g_BgPictrue;
HWND g_hToolBar;
HWND g_listview1;

IMPLEMENT_WNDPROC(MainDlg)


BEGIN_MSGMAP(MainDlg)
BODY_MSGMAP(WM_INITDIALOG,OnMInitMsg)
BODY_MSGMAP(WM_COMMAND,OnMCommand)
BODY_MSGMAP(WM_LBUTTONDOWN,OnMLButtonDownMsg)
BODY_MSGMAP(WM_PAINT,OnMPaintMsg)
BODY_MSGMAP(WM_CLOSE,OnMCloseMsg)
BODY_MSGMAP(WM_MAIN_SOCKET,OnMSocketMsg)
BODY_MSGMAP(WM_DRAWITEM,OnMDRAWITEMMsg)
END_MSGMAP

LRESULT OnMDRAWITEMMsg(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	ControlMap(IDB_BUTTON_BITMAP,ID_SEND_MSG_BUTTON,"发送",lParam);

	return TRUE;
}

LRESULT OnMInitMsg(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	int nW,nH,nX,nY;
	char szMsg[1024] = {0};
	static CHARFORMAT cf = {0};
	char ErrorStr[255] = "";
	char szBuf[SZBUF_MAX] = "";
	InitCommonControls();



	nW = GetSystemMetrics(SM_CXSCREEN)/2;
	nH = GetSystemMetrics(SM_CYSCREEN)/2;
	RECT rt;
	GetClientRect(hWnd,&rt);
	nX = nW - (rt.right - rt.left)/2;
	nY = nH - (rt.bottom - rt.top)/2;
	MoveWindow(hWnd,nX,nY,rt.right - rt.left,rt.bottom - rt.top,TRUE);


	HWND hREdit = CreateWindowEx(WS_EX_WINDOWEDGE , "RichEdit20A", NULL,WS_CHILD | WS_CLIPCHILDREN | ES_WANTRETURN | ES_MULTILINE | WS_VISIBLE | ES_LEFT|ES_NOHIDESEL|WS_VSCROLL,
				0 ,0,(rt.right-rt.left)-250, (rt.bottom - rt.top)/2, hWnd, (HMENU)123, GetModuleHandle(NULL), NULL);

	InitMsgSetting(hREdit);

	//ToolBar
	RECT rtToolBar = {0,275,rt.right-250,325};
	g_hToolBar = CreateSimpleToolbar(hWnd,rtToolBar);

	
	//内容框
	HWND g_hContent = CreateWindowEx(WS_EX_WINDOWEDGE , "RichEdit20A", NULL,WS_CHILD | WS_CLIPCHILDREN | ES_WANTRETURN | ES_MULTILINE | WS_VISIBLE | ES_LEFT|ES_NOHIDESEL|WS_VSCROLL|ES_READONLY,
		0 , (rt.bottom/5)*3+5 ,(rt.right-rt.left)-250, (rt.bottom - rt.top)/4, hWnd, (HMENU)IDC_CONTENT, GetModuleHandle(NULL), NULL);
	InitContentSetting(g_hContent);


	//建立list ctl好友列表
	g_listview1 = CreateWindowEx(WS_EX_STATICEDGE, TEXT("SysListView32"), NULL, WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL, 
		rt.right - 220, 0,220, 400, hWnd, (HMENU)IDC_LISTCTL, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
	ListView_SetExtendedListViewStyle(g_listview1, LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);//设置listview扩展风格
	SendMessage(g_listview1, WM_SETFONT, (WPARAM)GetStockObject(17), 0);
	
	CreateFriendList(hWnd);
	//AddFriendItem(hWnd,NULL,1);


	//套接字的建立
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
		//exit(0);
	}
	DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_LOGIN_DIALOG),hWnd,GET_WNDPROC_ADRR(LoginDlg));
	WSAAsyncSelect(g_sockClient,hWnd,WM_MAIN_SOCKET,FD_READ | FD_CLOSE);


	return TRUE;
}//================================================================End

LRESULT OnMCommand(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	CtlIdProc(hWnd,wParam,lParam,&g_BgPictrue);
	return TRUE;
}//================================================================End


LRESULT OnMLButtonDownMsg(HWND hWnd,WPARAM wParam,LPARAM lParam)
{


	return TRUE;
}//================================================================End



LRESULT OnMPaintMsg(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT ps;

	HDC hdc = BeginPaint(hWnd,&ps);

	char *pStr = NULL;

	switch (g_BgPictrue)
	{
		case 0:
			{
				pStr = MAKEINTRESOURCE(IDB_BITMAP8);
			}
			break;
		case 1:
			{
				pStr = MAKEINTRESOURCE(IDB_BITMAP11);
			}
			break;
		case 2:
			{
				pStr = MAKEINTRESOURCE(IDB_BITMAP12);
			}
			break;
		case 3:
			{
				pStr = MAKEINTRESOURCE(IDB_BITMAP13);

			}
			break;
		default:
			{
				pStr = MAKEINTRESOURCE(IDB_BITMAP8);
			}	
			break;
	}
	
	
	SetBgToWnd(hWnd,hdc,pStr);

	pStr = MAKEINTRESOURCE(IDB_BITMAP2);
	
	SetBgToWnd(g_hToolBar,hdc,pStr);

	EndPaint(hWnd,&ps);
	return TRUE;
}

LRESULT OnMCloseMsg(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	char SendStr[SZBUF_MAX] = "";
	USER_ID_PACK *pUser = new USER_ID_PACK;
	
	pUser->nEvent = CLI_EXIT;
	GetWindowText(hWnd,pUser->IdStr,12);
	
	sprintf(SendStr,"%-4d%-12s",pUser->nEvent,pUser->IdStr);
	
	if(SOCKET_ERROR == send(g_sockClient,SendStr,strlen(SendStr)+1,0))
	{
		
	}
	
	delete pUser;
	closesocket(g_sockClient);
	EndDialog(hWnd,WM_CLOSE);
	return TRUE;
}//================================================================End

LRESULT OnMSocketMsg(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	char ErrorStr[255] = "";
	char szBuf[SZBUF_MAX] = "";
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
}//================================================================End



