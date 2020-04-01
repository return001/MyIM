#ifndef __CLI_EVENTPROC_H__
#define __CLI_EVENTPROC_H__
#include "../Public/Protocol.h"
#include "MsgProc.h"

DECLARE_EVENT_MAP(Client)
DECLARE_CLI_EVENTPROC(Client)

DECLARE_PHEAD(Friend)

DECLARE_PFN_TABLE(FRIEND_NODE)
DECLEAR_NEWNODE(FRIEND_NODE)


int RegisteBackProc(void *pVoid,HWND hWnd);
int LoginBackFriListProc(void *pVoid,HWND hWnd);
int NotFindIdErrorProc(void *pVoid,HWND hWnd);
int LoginSuccessProc(void *pVoid,HWND hWnd);
int PwdErrorProc(void *pVoid,HWND hWnd);
int SER_ADD_YET_Proc(void *pVoid,HWND hWnd);
int SER_SEND_PICTURE_Proc(void *pVoid,HWND hWnd);
int SER_SEND_USER_INFORMATION_Proc(void *pVoid,HWND hWnd);
int SER_ASK_AGREE_Proc(void *pVoid,HWND hWnd);
int SER_ASK_REFUSE_Proc(void *pVoid,HWND hWnd);
int SER_SEND_DATA_Proc(void *pVoid,HWND hWnd);
int SER_CHANGE_FINISH_Proc(void *pVoid,HWND hWnd);
int SER_BE_DELETED_Proc(void *pVoid,HWND hWnd);
int SER_USER_EXIT_Proc(void *pVoid,HWND hWnd);
int SER_ADD_ERROR_Proc(void *pVoid,HWND hWnd);
int SER_OPER_ERROR_Proc(void *pVoid,HWND hWnd);
int SER_ADD_ASK_Proc(void *pVoid,HWND hWnd);
int SER_NOTFIND_ID_Proc(void *pVoid,HWND hWnd);

int FriInput(LINKER *pNode,void *pVoid,SOCKET nSock);







#endif