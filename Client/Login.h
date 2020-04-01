#ifndef __LOGIN_H__
#define __LOGIN_H__
#include "MsgProc.h"


DECLARE_MSGPROC(LoginDlg)
DECLARE_MSGMAP(LoginDlg)


LRESULT OnLInitMsg(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnLCommand(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnLCloseMsg(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnLSockMsg(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnLPaintMsg(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnLCTLCOLORSTATICMsg(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnLDRAWITEMMsg(HWND hWnd,WPARAM wParam,LPARAM lParam);

#endif