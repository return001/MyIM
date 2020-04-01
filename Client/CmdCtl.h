#ifndef __CMDCTL_H__
#define __CMDCTL_H__
#include "MsgProc.h"


typedef int (*PCMD_FUN)(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp);

struct COMMAND_MAP
{
	UINT CtlId;
	PCMD_FUN pFun;
};


extern COMMAND_MAP g_CmdCtlId[];

int CtlIdProc(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp);

int ID_SET_INFOMATOIN_Proc(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp);
int IDF_DELETE_FRI_Proc(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp);
int IDF_ADDFRI_Proc(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp);
int IDF_SEE_INFOMATION_Proc(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp);
int ID_SEND_MSG_BUTTON_Proc(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp);
int ID_BGP_P1_Proc(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp);
int ID_BGP_P2_Proc(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp);
int ID_BGP_P3_Proc(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp);
int IDC_EXIT_LOGIN_Proc(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp);
int ID_BGP_P0_Proc(HWND hWnd,WPARAM wParam,LPARAM lParam,int *pBgp);

#endif