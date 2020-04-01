#ifndef __RICHEDIT_H__
#define __RICHEDIT_H__

#include  <richedit.h>
#include <richole.h>
#include <AFXRES.H>
#include "resource.h"
#include <commctrl.h>
#include <commdlg.h>
BOOL SetDefaultCharFormat(CHARFORMAT &cf,HWND hMsg);
BOOL SetSelectionCharFormat(CHARFORMAT &cf,HWND hMsg);
DWORD GetDefaultCharFormat(CHARFORMAT &cf,HWND hMsg);

DWORD GetSelectionCharFormat(CHARFORMAT &cf,HWND hMsg);


void InitMsgSetting(HWND hMsg);
void InitContentSetting(HWND hContent);

#endif