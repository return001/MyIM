#ifndef __REGISTER_H__
#define __REGISTER_H__
#include "MsgProc.h"
#include "resource.h"

DECLARE_MSGPROC(RegisterDlg)
DECLARE_MSGMAP(RegisterDlg)


LRESULT OnRInitMsg(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnRCommand(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnRCloseMsg(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnRPaintMsg(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnRCTLCOLORSTATICMsg(HWND hWnd,WPARAM wParam,LPARAM lParam);
LRESULT OnRDRAWITEMMsg(HWND hWnd,WPARAM wParam,LPARAM lParam);

#endif 