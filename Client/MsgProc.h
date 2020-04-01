#ifndef __MSGPROC_H__
#define __MSGPROC_H__
#include "resource.h"

typedef LRESULT (*MSG_FUN)(HWND hWnd,WPARAM wParam,LPARAM lParam);

struct MSGMAP
{
	UINT uMsg;

	MSG_FUN pMsgFun;
};

extern SOCKET g_sockClient;

#define DECLARE_MSGMAP(WndName) extern MSGMAP g_##WndName##MsgMap[];

#define BEGIN_MSGMAP(WndName) MSGMAP g_##WndName##MsgMap[] = {

#define BODY_MSGMAP(msg,Msgfun) {msg,&Msgfun},

#define END_MSGMAP {WM_NULL,NULL}};


#define DECLARE_MSGPROC(WndName) BOOL CALLBACK WndName##Proc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

#define DECLARE_WNDPROC(WndName) BOOL CALLBACK WndName##Proc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

#define IMPLEMENT_WNDPROC(WndName)  BOOL CALLBACK WndName##Proc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)\
{\
	MSGMAP *pTemp = g_##WndName##MsgMap;\
	\
	while(NULL != pTemp->pMsgFun)\
{\
	if(uMsg == pTemp->uMsg)\
{\
	return pTemp->pMsgFun(hWnd,wParam,lParam);\
}\
	pTemp++;\
}\
	\
	return FALSE;\
}

#define GET_WNDPROC_ADRR(WndName) WndName##Proc

#endif