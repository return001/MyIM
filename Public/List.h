#ifndef __LIST_H__
#define __LIST_H__

struct LINKER;
typedef int (*PFN_IO)(LINKER *pNode,void *pVoid,SOCKET nSock);
typedef LINKER *(*NEWNODE)();

struct PFN_TABLE
{
	PFN_IO pfnInput;

	NEWNODE pfnCreate;
};


#define DECLARE_PHEAD(NodeName) extern LINKER *g_##NodeName##pHead;
#define INIT_PHEAD(NodeName) LINKER *g_##NodeName##pHead = NULL;
#define USE_PHEAD(NodeName) g_##NodeName##pHead

#define DECLARE_PHEADS(NodeName) extern LINKER *(g_##NodeName##pHead[65]);
#define INIT_PHEADS(NodeName) LINKER *(g_##NodeName##pHead[65]) = {NULL};


#define DECLARE_PFN_TABLE(NodeName) extern PFN_TABLE g_##NodeName##FunTable;
#define INIT_PFN_TABLE(NodeName,pfnInput,pfnCreate) PFN_TABLE g_##NodeName##FunTable = {pfnInput,pfnCreate};
#define CALL_NEWNODE(NodeName) g_##NodeName##FunTable.pfnCreate


struct LINKER
{
	LINKER *pLast;
	LINKER *pNext;

	char IdStr[12];
	PFN_TABLE *pTable;

};



#define DECLEAR_NEWNODE(NodeName) LINKER *Create##NodeName();
#define IMPLEMENT_NEWNODE(NodeName)\
LINKER *Create##NodeName()\
{\
	LINKER *pNew = (LINKER *)new NodeName;\
	pNew->pTable = &g_##NodeName##FunTable;\
	return pNew;\
}

#define GET_CREATE_ADDR(NodeName) Create##NodeName

#define ERROR_PNODE -1
#define ERROR_PHEAD -2

int CreateList(LINKER **pHead,NEWNODE pfn,void *pVoid,SOCKET nSock);
// int InsertNode(LINKER **pHead,LINKER *pNode);//前插
// int InsertNodeB(LINKER *pNode);//后插

LINKER *FindNode(LINKER *pHead,char *IdStr);
int AddNode(LINKER *pHead,void *pVoid,SOCKET nSock,NEWNODE pfn);
int DeleteNode(LINKER **pHead,char *pVoid);
int ClearList(LINKER **pHead);
int ModifyNode(LINKER *pNode,void *pVoid,SOCKET nSock);
/*int ShowList(LINKER *pHead);*/

int CheckEvent(const void *pVoid);   //校验事件的函数


#endif