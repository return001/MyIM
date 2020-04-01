// HookWnd.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

LRESULT CALLBACK MainProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK JournalRecordProc(int code,WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK JournalPlaybackProc(int nCode,WPARAM wParam,LPARAM lParam);

struct S_SAVE_EVENTMSG 
{	
	UINT  message; 
	UINT  paramL; 
	UINT  paramH; 
	DWORD time; 
}; 

BOOL m_Santa=FALSE;
// CPtrList的作用是定义一个链表变量

CPtrList EventMsgList;
CPtrList EventMsgListpp;

HHOOK g_hk;
HHOOK g_hk1;


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.

	WNDCLASS wc = {0};

	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.hCursor = LoadCursor(hInstance,IDC_ARROW);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = MainProc;
	wc.lpszClassName = "zxc";
	wc.style = CS_HREDRAW | CS_VREDRAW;


	if(!RegisterClass(&wc))
	{
		MessageBox(NULL,"Register Error","Error",MB_OK);
		return -1;
	}

	HWND hMain = CreateWindow("zxc","zxc1",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);

	if(NULL == hMain)
	{
		MessageBox(NULL,"Create Error","Error",MB_OK);
		return -1;
	}

	ShowWindow(hMain,nCmdShow);


	MSG msg;

	while (GetMessage(&msg,NULL,0,0))
	{

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}


LRESULT CALLBACK MainProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
			{	
				
				CreateWindow("BUTTON","录制",WS_CHILD | WS_VISIBLE ,100,100,100,24,hWnd,(HMENU)123,GetModuleHandle(NULL),NULL);
				CreateWindow("BUTTON","停止并重现",WS_CHILD | WS_VISIBLE ,400,100,100,24,hWnd,(HMENU)111,GetModuleHandle(NULL),NULL);

			}
			break;
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd,&ps);
				
				EndPaint(hWnd,&ps);
			}
			break;
		case WM_CLOSE:
			{
				DestroyWindow(hWnd);
			}
			break;

		case WM_LBUTTONDOWN:
			{
				
			}
			break;
		case WM_COMMAND:
			{
				switch(LOWORD(wParam))
				{
					case 123:
						{
							g_hk1 = SetWindowsHookEx(WH_JOURNALRECORD,JournalRecordProc,GetModuleHandle(NULL),0);
						}
						break;
					case 111:
						{
							g_hk = SetWindowsHookEx(WH_JOURNALPLAYBACK,JournalPlaybackProc,GetModuleHandle(NULL),0);
						}
						break;
					default:
						break;
				}
			}
			break;
		case WM_DESTROY:
			{
				PostQuitMessage(0);
			}
			break;
		default:
			return DefWindowProc(hWnd,uMsg,wParam,lParam);
			break;

	}
	return 0;
}

LRESULT CALLBACK JournalRecordProc(int nCode,WPARAM wParam, LPARAM lParam)
{
	if(nCode<0) 
	{
		UnhookWindowsHookEx(g_hk1);
		return CallNextHookEx (NULL,nCode,wParam,lParam);
	}

	EVENTMSG *pmsg=(EVENTMSG *)lParam;
	EVENTMSG* pEventMsg = new EVENTMSG;
	
	
	switch(nCode) 
	{ 
		case HC_ACTION:
			memcpy(pEventMsg,pmsg,sizeof(EVENTMSG));
			EventMsgList.AddTail(pEventMsg);
			break;
		case HC_SYSMODALOFF:
			break;
		case HC_SYSMODALON:
			break;
 }
	return 0;
}


LRESULT CALLBACK JournalPlaybackProc(int nCode,WPARAM wParam,LPARAM lParam)
{
	static unsigned i=0;
	static BOOL bFlag = TRUE;
	EVENTMSG *pMsg;
	POSITION pos;
	DWORD PreTime,NowTime;
	
	switch(nCode) 
	{ 
		case HC_SKIP:
		{
			bFlag=TRUE;
			i++;
		}

		break;
		/////////////////////////////////////////////////////////////////////////////////////////
		case HC_GETNEXT:
		{
			if((int) i >= EventMsgList.GetCount()-2 ) 
			{ 
				i=0;
				UnhookWindowsHookEx(g_hk);
				MessageBox(NULL,_T("消息回放完毕"),0,0);
				//exit(0);
			}
	
			pos=EventMsgList.FindIndex(i);
			pMsg=(EVENTMSG *)EventMsgList.GetAt(pos);
			memcpy((LPEVENTMSG)lParam,pMsg,sizeof(EVENTMSG));
			
			
			
			
			
			//下面是返回一个时间差
			if((i)!=0 && bFlag==TRUE ) 
			{ 
				bFlag= FALSE;
				NowTime=pMsg->time;
				pos = EventMsgList.FindIndex(i-1);
				pMsg = (EVENTMSG *)EventMsgList.GetAt(pos);
				PreTime=pMsg->time;
				CTimeSpan timecha;
				return NowTime-PreTime;
			}
			else  
			return 0;
		}	

		break;		
		
	default:
		return CallNextHookEx(NULL,nCode,wParam,lParam);
}
	return 0;
}