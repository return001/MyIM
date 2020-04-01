#include "StdAfx.h"
#include "List.h"



int CreateList(LINKER **pHead,NEWNODE pfn,void *pVoid,	SOCKET nSock)
{
	if(NULL != *pHead || NULL == pHead)
	{
		return -1;
	}

	if(NULL != pfn)
	{
		(*pHead) = pfn();

		(*pHead)->pLast = NULL;
		(*pHead)->pNext = NULL;

		(*pHead)->pTable->pfnInput((*pHead),pVoid,nSock);
	}
	return 0;
}

// int InsertNode(LINKER **pHead, LINKER *pNode)//前插
// {
// 	if(NULL == *pHead && NULL != pHead)
// 	{
// 		return ERROR_PHEAD;
// 	}
// 
// 	if(NULL == pNode)
// 	{
// 		return ERROR_PNODE;
// 	}
// 
// 	LINKER *pNew = pNode->pTable->pfnCreate();
// 	pNew->pTable->pfnInput(pNew);
// 
// 	if(NULL == pNode->pLast)
// 	{
// 		pNew->pNext = pNode;
// 		pNode->pLast = pNew;
// 		*pHead = pNew;
// 	}
// 	else
// 	{
// 		pNew->pLast = pNode->pLast;
// 		pNew->pNext = pNode;
// 		pNode->pLast->pNext = pNew;
// 		pNode->pLast = pNew;
// 	}
// 
// 	return 0;
// }

// int InsertNodeB(LINKER *pNode)//后插
// {
// 	if(NULL == pNode)
// 	{
// 		return ERROR_PNODE;
// 	}
// 
// 	LINKER *pNew = pNode->pTable->pfnCreate();
// 	pNew->pTable->pfnInput(pNew);
// 
// 	if(NULL == pNode->pNext)
// 	{
// 		pNew->pLast = pNode;
// 		pNode->pNext = pNew;
// 	}
// 	else
// 	{
// 		pNew->pLast = pNode;
// 		pNew->pNext = pNode->pNext;
// 		pNode->pNext->pLast = pNew;
// 		pNode->pNext = pNew;
// 	}
// 
// 	return 0;
// }

int AddNode(LINKER *pHead,void *pVoid,SOCKET nSock,NEWNODE pfn)
{
	if(NULL == pHead)
	{
		return ERROR_PHEAD;
	}

	LINKER *pNew = pfn();
	
	LINKER *pTemp = pHead;
	while(NULL != pTemp->pNext)
	{
		pTemp = pTemp->pNext;
	}

	pTemp->pNext = pNew;
	pNew->pLast = pTemp;
	pNew->pNext = NULL;

	pNew->pTable->pfnInput(pNew,pVoid,nSock);


	return 0;
}

LINKER *FindNode(LINKER *pHead,char *IdStr)
{
	LINKER *pTemp = pHead;

	while (NULL != pTemp)
	{
		if(0 == strcmp(IdStr,pTemp->IdStr))
		{
			return pTemp;
		}
		pTemp = pTemp->pNext;
	}
	return pTemp;
}

int DeleteNode(LINKER **pHead,char *IdStr)
{
	if(NULL == *pHead && NULL != pHead)
	{
		return ERROR_PHEAD;
	}

	LINKER *pNode = FindNode(*pHead,IdStr);

	if(NULL == pNode)
	{
		return ERROR_PNODE;
	}

	if(NULL == pNode->pLast && NULL == pNode->pNext)
	{
		*pHead = NULL;
	}
	else if(NULL != pNode->pLast && NULL == pNode->pNext)
	{
		pNode->pLast->pNext = NULL;
	}
	else if(NULL == pNode->pLast && NULL != pNode->pNext)
	{
		*pHead = pNode->pNext;
		(*pHead)->pLast = NULL;
	}
	else if(NULL != pNode->pLast && NULL != pNode->pNext)
	{
		pNode->pLast->pNext = pNode->pNext;
		pNode->pNext->pLast = pNode->pLast;
	}

	delete pNode;

	return 0;
}

int ClearList(LINKER **pHead)
{
	if(NULL == *pHead && NULL != pHead)
	{
		return ERROR_PHEAD;
	}

	LINKER *pTemp = *pHead;
	while(NULL != pTemp)
	{
		*pHead = pTemp->pNext;
		delete pTemp;
		pTemp = *pHead;
	}

	return 0;
}

int ModifyNode(LINKER *pNode,void *pVoid,SOCKET nSock)
{
	if(NULL == pNode)
	{
		return ERROR_PNODE;
	}

	pNode->pTable->pfnInput(pNode,pVoid,nSock);

	return 0;
}

// int ShowList(LINKER *pHead)
// {
// 	if(NULL == pHead)
// 	{
// 		return ERROR_PHEAD;
// 	}
// 
// 	LINKER *pTemp = pHead;
// 	while(NULL != pTemp)
// 	{
// 		pTemp->pTable->pfnOutput(pTemp);
// 		pTemp = pTemp->pNext;
// 	}
// 
// 	return 0;
// }

int CheckEvent(const void *pVoid)     //校验事件的函数
{
	char EventStr[5] = "";
	char *pCh = (char *)pVoid;
	
	int i = 0;
	
	for(i = 0;i < 4;i++)
	{
		EventStr[i] = pCh[i];
	}
	
	EventStr[i] = '\0';
	
	return atoi(EventStr);
}

