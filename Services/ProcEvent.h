#ifndef __PROC_EVENT_H__
#define __PROC_EVENT_H__
#include "../Public/Protocol.h"





DECLARE_PHEAD(User)
DECLARE_PFN_TABLE(SER_USER_NODE)
DECLEAR_NEWNODE(SER_USER_NODE)



DECLARE_PHEADS(Friend)
DECLARE_PFN_TABLE(USER_ID)
DECLEAR_NEWNODE(USER_ID)


DECLARE_EVENT_MAP(Service)
DECLARE_EVENTPROC(Service)

int RegisterProc(void *pVoid,SOCKET nSock);
int LoginProc(void *pVoid,SOCKET nSock);
int AddFriAskProc(void *pVoid,SOCKET nSock);
int AddFriAgreeProc(void *pVoid,SOCKET nSock);
int AddFriRefuseProc(void *pVoid,SOCKET nSock);
int ChatDataProc(void *pVoid,SOCKET nSock);
int PictrueProc(void *pVoid,SOCKET nSock);
int Ask_InfomationProc(void *pVoid,SOCKET nSock);
int Delete_FriProc(void *pVoid,SOCKET nSock);
int ExitProc(void *pVoid,SOCKET nSock);
int Modify_InfoProc(void *pVoid,SOCKET nSock);


int UserInput(LINKER *pNode,void *pVoid,SOCKET nSock);
int FriendsInput(LINKER *pNode,void *pVoid,SOCKET nSock);
int AddIdStr(char *Str);







#endif