#ifndef __MAINWND_H__
#define __MAINWND_H__
#include "MsgProc.h"
#include "resource.h"


DECLARE_MSGPROC(MainDlg)
DECLARE_MSGMAP(MainDlg)




LRESULT OnMInitMsg(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnMCommand(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnMLButtonDownMsg(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnMPaintMsg(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnMSocketMsg(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnMCloseMsg(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnMDRAWITEMMsg(HWND hWnd,WPARAM wParam,LPARAM lParam);




#endif