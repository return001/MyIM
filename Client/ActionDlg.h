#ifndef __ACTIONDLG_H__
#define __ACTIONDLG_H__
#include "MsgProc.h"


//设置自己的个人信息对话处理框

DECLARE_MSGPROC(SetMyInfo)

DECLARE_MSGMAP(SetMyInfo)


LRESULT OnSInitMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnSCommandMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnSCloseMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnSPaintMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnSDRAWITEMMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnSCTLCOLORSTATICMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam);

///////////////////////////////////////////////////////////////////////////////////////

//查看好友信息的处理框
extern char g_RecvStr[SZBUF_MAX];

DECLARE_MSGMAP(FriInfo)

DECLARE_WNDPROC(FriInfo)

LRESULT OnShowInfoInitMsgProc(HWND hWnd,WPARAM wParam ,LPARAM lParam);
LRESULT OnShowInfoCommandMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnShowInfoCloseMsgProc(HWND hWnd,WPARAM wParam ,LPARAM lParam);
LRESULT OnShowInfoPaintMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnShowInfoCTLCOLORSTATICMsgProc(HWND hWnd,WPARAM wParam,LPARAM);
LRESULT OnShowInfoDRAWITEMMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam);


////////////////////////////////////////////////////////////////////////////
//添加好友的处理框

DECLARE_MSGMAP(AddFri)
DECLARE_WNDPROC(AddFri)


LRESULT OnAddInitMsgProc(HWND hWnd,WPARAM wParam ,LPARAM lParam);
LRESULT OnAddCommandMsgProc(HWND hWnd,WPARAM wParam ,LPARAM lParam);
LRESULT OnAddCloseMsgProc(HWND hWnd,WPARAM wParam ,LPARAM lParam);
LRESULT OnAddPaintMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnAddCTLCOLORSTATICMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnAddDRAWITEMMsgProc(HWND hWnd,WPARAM wParam,LPARAM lParam);


#endif