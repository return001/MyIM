#include "stdafx.h"
#include "RichEdit.h"


void InitMsgSetting(HWND hMsg)
{
	unsigned mask = SendMessage(hMsg, EM_GETEVENTMASK, (WPARAM)0, (LPARAM)0);
	//设置响应事件信息
	SendMessage(hMsg, EM_SETEVENTMASK, (WPARAM)0, (LPARAM)(mask | ENM_LINK | ENM_MOUSEEVENTS | ENM_SCROLLEVENTS | ENM_KEYEVENTS | EN_REQUESTRESIZE));
	SendMessage(hMsg, EM_AUTOURLDETECT, true, (LPARAM)0);
	int iTotalTextLength = GetWindowTextLength(hMsg);
	int iStartPos = iTotalTextLength - 100;
	int iEndPos;
	
	CHARFORMAT cf = { 0 };
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_COLOR | CFM_UNDERLINE | CFM_BOLD;
	iEndPos = GetWindowTextLength(hMsg);
	
	SendMessage(hMsg, EM_SETSEL, (WPARAM)(int)iStartPos, (LPARAM)(int)iEndPos);
	SendMessage(hMsg, EM_SETCHARFORMAT, (WPARAM)(UINT)SCF_SELECTION, (LPARAM)&cf);
	SendMessage(hMsg, EM_HIDESELECTION, (WPARAM)(BOOL)TRUE, (LPARAM)(BOOL)FALSE);
	SendMessage(hMsg, EM_LINESCROLL, (WPARAM)(int)0, (LPARAM)(int)1);
}


void InitContentSetting(HWND hContent)
{
	CHARFORMAT cf = { 0 };
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_BOLD;
	SendMessage(hContent, EM_SETCHARFORMAT, (WPARAM)(UINT)SCF_ALL, (LPARAM)(CHARFORMAT *)&cf);
}


BOOL SetDefaultCharFormat(CHARFORMAT &cf,HWND hMsg)
{
	cf.cbSize = sizeof(CHARFORMAT);
	return (BOOL)SendMessage(hMsg, EM_SETCHARFORMAT, 0, (LPARAM)&cf);
}

BOOL SetSelectionCharFormat(CHARFORMAT &cf,HWND hMsg)
{
	cf.cbSize = sizeof(CHARFORMAT);
	return (BOOL)SendMessage(hMsg, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}


DWORD GetDefaultCharFormat(CHARFORMAT &cf,HWND hMsg)
{
	cf.cbSize = sizeof(CHARFORMAT);
	return (DWORD)SendMessage(hMsg, EM_GETCHARFORMAT, 0, (LPARAM)&cf);
}

DWORD GetSelectionCharFormat(CHARFORMAT &cf,HWND hMsg)
{
	cf.cbSize = sizeof(CHARFORMAT);
	return (DWORD)SendMessage(hMsg, EM_GETCHARFORMAT, 1, (LPARAM)&cf);
}