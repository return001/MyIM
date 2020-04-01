#include "StdAfx.h"
#include "ProcEvent.h"


int g_NumFriend;

BEGIN_EVENT_MAP(Service)
BODY_EVENTMAP(CLI_REGISTER,RegisterProc,NULL)
BODY_EVENTMAP(CLI_LOGIN,LoginProc,NULL)
BODY_EVENTMAP(CLI_ADDFRI_ASK,AddFriAskProc,NULL)
BODY_EVENTMAP(CLI_ADD_AGREE,AddFriAgreeProc,NULL)
BODY_EVENTMAP(CLI_ADD_REFUSE,AddFriRefuseProc,NULL)
BODY_EVENTMAP(CLI_CHAT_DATA,ChatDataProc,NULL)
BODY_EVENTMAP(CLI_PICTURE_DATA,PictrueProc,NULL)
BODY_EVENTMAP(CLI_SEE_FRI_INFOMATION,Ask_InfomationProc,NULL)
BODY_EVENTMAP(CLI_DELETE_FRI,Delete_FriProc,NULL)
BODY_EVENTMAP(CLI_EXIT,ExitProc,NULL)
BODY_EVENTMAP(CLI_MODIFY,Modify_InfoProc,NULL)
END_EVENTMAP


IMPLEMENT_EVENTPROC(Service)



//定义用户存储链表
INIT_PHEAD(User)
IMPLEMENT_NEWNODE(SER_USER_NODE)
INIT_PFN_TABLE(SER_USER_NODE,UserInput,GET_CREATE_ADDR(SER_USER_NODE))




INIT_PHEADS(Friend)
IMPLEMENT_NEWNODE(USER_ID)
INIT_PFN_TABLE(USER_ID,FriendsInput,GET_CREATE_ADDR(USER_ID))

int RegisterProc(void *pVoid,SOCKET nSock)
{
	
	if(NULL == pVoid)
	{
		return -2;
	}

	if (NULL == USE_PHEAD(User))
	{
		CreateList(&USE_PHEAD(User),CALL_NEWNODE(SER_USER_NODE),pVoid,nSock);
	}
	else
	{
		AddNode(USE_PHEAD(User),pVoid,nSock,CALL_NEWNODE(SER_USER_NODE));
	}

	LINKER *pTemp = USE_PHEAD(User);

	while(NULL != pTemp->pNext)
	{
		pTemp = pTemp->pNext;
	}


	((SER_USER_NODE *)pTemp)->FriendListHead = NULL;


	char SendStr[SZBUF_MAX] = "";
	USER_ID_PACK *pRegister = new USER_ID_PACK;

	pRegister->nEvent = SER_SEND_USER_ID;
	strcpy(pRegister->IdStr,pTemp->IdStr);

	sprintf(SendStr,"%-4d%-12s",pRegister->nEvent,pRegister->IdStr);

	if(SOCKET_ERROR == send(((SER_USER_NODE *)pTemp)->uSock,SendStr,strlen(SendStr)+1,0))
	{
		cout<<"Send Error:"<<WSAGetLastError()<<endl;
	}

	cout<<((SER_USER_NODE *)pTemp)->linker.IdStr<<":注册成功"<<endl;
	
	//调试用的语句
	cout<<"头结点ID:"<<USE_PHEAD(User)->IdStr<<endl;
	/////////////////////////////////////////


	delete pRegister;
	return 0;
	
}//============================================End

int LoginProc(void *pVoid,SOCKET nSock)
{
	if(NULL == pVoid)
	{
		return -2;
	}

	char SendStr[SZBUF_MAX] = "";
	LOGIN_PACK *pLogin = (LOGIN_PACK *)pVoid;
	EVENT_TIP_PACK *pEvent = new EVENT_TIP_PACK;

	pLogin->IdStr[11] = '\0';
	pLogin->PwdStr[16] = '\0';

	//调试用的语句
	cout<<pLogin->IdStr<<endl;
	cout<<pLogin->PwdStr<<endl;
	//////////////////////////////////////////////////////////////////////////

	LINKER *pFNode = FindNode(USE_PHEAD(User),pLogin->IdStr);

	//调试用的语句
	cout<<"头结点ID:"<<USE_PHEAD(User)->IdStr<<endl;
	/////////////////////////////////////////


	if(NULL == pFNode)
	{
		pEvent->nEvent = SER_NOTFINDID_ERROR;
		strcpy(pEvent->nExvent,"未注册此用户");
		sprintf(SendStr,"%-4d%-20s",pEvent->nEvent,pEvent->nExvent);
		send(nSock,SendStr,strlen(SendStr)+1,0);
		return -1;
	}

	if(0 != strcmp(((SER_USER_NODE *)pFNode)->uPwd,pLogin->PwdStr))
	{

		pEvent->nEvent = SER_USERPWD_ERROR;
		strcpy(pEvent->nExvent,"密码错误");
		sprintf(SendStr,"%-4d%-20s",pEvent->nEvent,pEvent->nExvent);
		send(nSock,SendStr,strlen(SendStr)+1,0);
		return -2;
	}

	USER_FRIEND_BASIC_PACK *SendFriInfo = new USER_FRIEND_BASIC_PACK;
	USER_ID *pFriend = ((SER_USER_NODE *)pFNode)->FriendListHead;
	SER_USER_NODE *pUser = NULL;

	((SER_USER_NODE *)pFNode)->uState = LINE;
	((SER_USER_NODE *)pFNode)->uSock = nSock;


	pEvent->nEvent = SER_LOGIN_SUCCESS;
	strcpy(pEvent->nExvent,"登录成功");
	sprintf(SendStr,"%-4d%-20s",pEvent->nEvent,pEvent->nExvent);

	if(SOCKET_ERROR == send(nSock,SendStr,strlen(SendStr)+1,0))
	{
		cout<<"SER_LOGIN_SUCCESS Error:"<<WSAGetLastError()<<endl;
		return -2;
	}

	
	SendFriInfo->nEvent = SER_SEND_FRIEND_LIST;
	while (NULL != pFriend)
	{
		pUser = (SER_USER_NODE *)FindNode(USE_PHEAD(User),pFriend->linker.IdStr);

		strcpy(SendFriInfo->FName,pUser->uName);
		strcpy(SendFriInfo->IdStr,pUser->linker.IdStr);
		strcpy(SendFriInfo->PicStr,pUser->PicStr);
		SendFriInfo->FState = pUser->uState;


		//前4字节为事件标示，然后，12字节的Id,20字节为昵称，10字节的图片，4字节的状态。
		sprintf(SendStr,"%-4d%-12s%-20s%-10s%-4d",SendFriInfo->nEvent,SendFriInfo->IdStr,SendFriInfo->FName,SendFriInfo->PicStr,SendFriInfo->FState);    
		send(nSock,SendStr,strlen(SendStr)+1,0);

		sprintf(SendStr,"%-4d%-12s",SER_USER_LOGIN,pLogin->IdStr);
		send(pUser->uSock,SendStr,strlen(SendStr)+1,0);

		pFriend = (USER_ID *)pFriend->linker.pNext;

	}

	cout<<pLogin->IdStr<<":登录成功"<<endl;
	delete SendFriInfo;
	delete pEvent;

	return 0;	
}//================================================End

int AddFriAskProc(void *pVoid,SOCKET nSock)
{
	if(NULL == pVoid)
	{
		return -2;
	}

	char SendStr[SZBUF_MAX] = "";
	MY_FRI_ID_PACK *pAddFri = (MY_FRI_ID_PACK *)pVoid;
	USER_ID_PACK *pUserId = new USER_ID_PACK;
	EVENT_TIP_PACK *pEvent = new EVENT_TIP_PACK;

	pAddFri->UserId[11] = '\0';
	pAddFri->BeAdderId[11] = '\0';


	//调试语句
	cout<<pAddFri->UserId<<endl;
	cout<<pAddFri->BeAdderId<<endl;
	//////////////////////////////////////////////////////////////////////////


	LINKER *pAddUser = FindNode(USE_PHEAD(User),pAddFri->UserId);

	LINKER *pBeAddUser = FindNode(USE_PHEAD(User),pAddFri->BeAdderId);

	if(NULL == pBeAddUser)
	{
		pEvent->nEvent = SER_NOTFIND_ID;
		strcpy(pEvent->nExvent,"查无此人");
		sprintf(SendStr,"%-4d%-20s",pEvent->nEvent,pEvent->nExvent);
		send(nSock,SendStr,strlen(SendStr)+1,0);
		return -1;
	}
	else
	{
		if(NULL != FindNode((LINKER *)(((SER_USER_NODE *)pAddUser)->FriendListHead),pAddFri->BeAdderId))
		{
			pEvent->nEvent = SER_ADD_YET;
			strcpy(pEvent->nExvent,"已经添加过好友");
			sprintf(SendStr,"%-4d%-20s",pEvent->nEvent,pEvent->nExvent);
			send(nSock,SendStr,strlen(SendStr)+1,0);
			return -1;
		}
		else
		{
			if(OFF_LINE == ((SER_USER_NODE *)pAddUser)->uState)
			{
				pEvent->nEvent = SER_ADD_ERROR;
				strcpy(pEvent->nExvent,"用户离线，添加失败");
				sprintf(SendStr,"%-4d%-20s",pEvent->nEvent,pEvent->nExvent);
				send(nSock,SendStr,strlen(SendStr)+1,0);
				return -1;
			}
			else
			{
				pUserId->nEvent = SER_ADD_ASK;
				strcpy(pUserId->IdStr,pAddFri->UserId);
				sprintf(SendStr,"%-4d%-12s",pUserId->nEvent,pUserId->IdStr);

				if(SOCKET_ERROR == send(((SER_USER_NODE *)pBeAddUser)->uSock,SendStr,strlen(SendStr)+1,0))
				{
					cout<<"SER_ADD_ASK Error:"<<WSAGetLastError()<<endl;
				}
			}
		}
	}

	delete pUserId;
	delete pEvent;
	return 0;
	
}//============================================End

int AddFriAgreeProc(void *pVoid,SOCKET nSock)
{
	char SendStr[SZBUF_MAX] = "";
	if(NULL == pVoid)
	{
		return -2;
	}

	MY_FRI_ID_PACK *pUFnode = (MY_FRI_ID_PACK *)pVoid;
	pUFnode->UserId[11] = '\0';
	pUFnode->BeAdderId[11] = '\0';

	LINKER *pAddUser = FindNode(USE_PHEAD(User),pUFnode->UserId);
	LINKER *pFripHead = (LINKER *)(((SER_USER_NODE *)pAddUser)->FriendListHead);




	if(NULL == pFripHead)
	{
		CreateList(&pFripHead,CALL_NEWNODE(USER_ID),pUFnode->BeAdderId,0);
	}
	else
	{
		AddNode(pFripHead,pUFnode->BeAdderId,0,CALL_NEWNODE(USER_ID));
	}

	//调试语句
	if(NULL == pFripHead)
	{
		cout<<((SER_USER_NODE *)pAddUser)->linker.IdStr<<":好友链表为空"<<endl;
	}
	//////////////////////////////////////////////////////////////////////////



	LINKER *pBeAddUser = FindNode(USE_PHEAD(User),pUFnode->BeAdderId);
	pFripHead = (LINKER *)(((SER_USER_NODE *)pBeAddUser)->FriendListHead);
	

	if(NULL == pFripHead)
	{
		CreateList(&pFripHead,CALL_NEWNODE(USER_ID),pVoid,0);
	}
	else
	{
		AddNode(pFripHead,pVoid,0,CALL_NEWNODE(USER_ID));
	}

	//调试语句
	if(NULL == pFripHead)
	{
		cout<<((SER_USER_NODE *)pBeAddUser)->linker.IdStr<<":好友链表为空"<<endl;
	}
	//////////////////////////////////////////////////////////////////////////


	USER_FRIEND_BASIC_PACK *pFriBasic = new USER_FRIEND_BASIC_PACK;

	//向被添加者发送添加者的基本信息

	SER_USER_NODE *pNode = (SER_USER_NODE *)pAddUser;

	pFriBasic->nEvent = SER_ASK_AGREE;
	pFriBasic->FState = pNode->uState;
	strcpy(pFriBasic->FName,pNode->uName);
	strcpy(pFriBasic->IdStr,pNode->linker.IdStr);
	strcpy(pFriBasic->PicStr,pNode->PicStr);



	//前4字节为事件标示，然后，12字节的Id,20字节为昵称，10字节的图片信息，4字节的状态。
	sprintf(SendStr,"%-4d%-12s%-20s%-10s%-4d",pFriBasic->nEvent,pFriBasic->IdStr,pFriBasic->FName,pFriBasic->PicStr,pFriBasic->FState);
	send(((SER_USER_NODE *)pBeAddUser)->uSock,SendStr,strlen(SendStr)+1,0);


	//向添加者发送被添加者的基本信息
	pNode = (SER_USER_NODE *)pBeAddUser;
	
	pFriBasic->nEvent = SER_ASK_AGREE;
	pFriBasic->FState = pNode->uState;
	strcpy(pFriBasic->FName,pNode->uName);
	strcpy(pFriBasic->IdStr,pNode->linker.IdStr);
	strcpy(pFriBasic->PicStr,pNode->PicStr);
	
	
	//前4字节为事件标示，然后，12字节的Id,20字节为昵称，10字节的图片信息，4字节的状态。
	sprintf(SendStr,"%-4d%-12s%-20s%-10s%-4d",pFriBasic->nEvent,pFriBasic->IdStr,pFriBasic->FName,pFriBasic->PicStr,pFriBasic->FState);
	send(((SER_USER_NODE *)pAddUser)->uSock,SendStr,strlen(SendStr)+1,0);


	return 0;	
}//============================================End

int AddFriRefuseProc(void *pVoid,SOCKET nSock)
{
	char SendStr[SZBUF_MAX] = "";

	MY_FRI_ID_PACK *pRefuser = (MY_FRI_ID_PACK *)pVoid;

	pRefuser->UserId[11] = '\0';

	pRefuser->BeAdderId[11] = '\0';

	sprintf(SendStr,"%-4d%-12s",SER_ASK_REFUSE,pRefuser->BeAdderId);

	if(SOCKET_ERROR == send(((SER_USER_NODE *)FindNode(USE_PHEAD(User),pRefuser->UserId))->uSock,SendStr,strlen(SendStr),0))
	{
		cout<<"SER_ASK_REFUSE Error:"<<WSAGetLastError()<<endl;
	}

	return 0;
}//============================================End

int ChatDataProc(void *pVoid,SOCKET nSock)
{
	char SendStr[SZBUF_MAX] = "";
	USER_SEND_DATA_PACK *pChatData = (USER_SEND_DATA_PACK *)pVoid;
	SER_SEND_DATA_PACK *pSendData = new SER_SEND_DATA_PACK;

	pChatData->SourId[11] = '\0';
	pChatData->DesId[11] = '\0';
	pSendData->nEvent = SER_SEND_DATA;

	SER_USER_NODE *pNode = (SER_USER_NODE *)FindNode(USE_PHEAD(User),pChatData->DesId);

	strcpy(pSendData->SourId,pChatData->SourId);
	strcpy(pSendData->DataType.szBuf,pChatData->DataType.szBuf);

	sprintf(SendStr,"%-4d%-12s%s",pSendData->nEvent,pSendData->SourId,pSendData->DataType.szBuf);

	if(SOCKET_ERROR == send(pNode->uSock,SendStr,strlen(SendStr)+1,0))
	{
		cout<<"SER_SEND_DATA Error:"<<WSAGetLastError()<<endl;
	}

	return 0;
	
}//============================================End

int PictrueProc(void *pVoid,SOCKET nSock)
{
	return 0;
	
}//============================================End

int Ask_InfomationProc(void *pVoid,SOCKET nSock)
{
	char SendStr[SZBUF_MAX] = "";
	MY_FRI_ID_PACK *pSeeInfoer = (MY_FRI_ID_PACK *)pVoid;

	pSeeInfoer->UserId[11] = '\0';
	pSeeInfoer->BeAdderId[11] = '\0';

	SER_USER_NODE *pBeUser = (SER_USER_NODE *)FindNode(USE_PHEAD(User),pSeeInfoer->BeAdderId);

	sprintf(SendStr,"%-4d%-12s%-20s%-4d%-10s%-4d",SER_SEND_USER_INFORMATION,pBeUser->linker.IdStr,pBeUser->uName,pBeUser->uState,pBeUser->uHoro,pBeUser->uAge);

	if(SOCKET_ERROR == send(nSock,SendStr,strlen(SendStr)+1,0))
	{
		cout<<"SER_SEND_USER_INFORMATION Error:"<<WSAGetLastError()<<endl;
	}
	return 0;
	
}//============================================End

int Delete_FriProc(void *pVoid,SOCKET nSock)
{
	MY_FRI_ID_PACK *pMyFriId = (MY_FRI_ID_PACK *)pVoid;

	pMyFriId->BeAdderId[11] = '\0';
	pMyFriId->UserId[11] = '\0';

	SER_USER_NODE *pNode = (SER_USER_NODE *)FindNode(USE_PHEAD(User),pMyFriId->UserId);
	LINKER *pHead = ((LINKER *)(pNode->FriendListHead));
	DeleteNode(&pHead,pMyFriId->BeAdderId);


	pNode = (SER_USER_NODE *)FindNode(USE_PHEAD(User),pMyFriId->BeAdderId);
	pHead = ((LINKER *)(pNode->FriendListHead));
	DeleteNode(&pHead,pMyFriId->UserId);
	return 0;
}//============================================End

int ExitProc(void *pVoid,SOCKET nSock)
{
	USER_ID_PACK *pUser = (USER_ID_PACK *)pVoid;
	USER_ID_PACK *pSendPack = new USER_ID_PACK;
	char SendStr[SZBUF_MAX] = "";

	pSendPack->nEvent = SER_USER_EXIT;
	pUser->IdStr[11] = '\0';
	strcpy(pSendPack->IdStr,pUser->IdStr);
	cout<<pUser->IdStr<<endl;



	LINKER *pNode = FindNode(USE_PHEAD(User),pUser->IdStr);
	
	//调试用的语句
	cout<<"头结点ID:"<<USE_PHEAD(User)->IdStr<<endl;
	/////////////////////////////////////////


	if(NULL == pNode)
	{
		cout<<pUser->IdStr<<"退出错误"<<endl;
	}
	((SER_USER_NODE *)pNode)->uState = OFF_LINE;

	LINKER *pTemp = (LINKER *)((SER_USER_NODE *)pNode)->FriendListHead;

	cout<<pUser->IdStr<<":退出"<<endl;


	SER_USER_NODE *pUNode = NULL;

	while(NULL != pTemp)
	{
		pUNode = (SER_USER_NODE *)FindNode(USE_PHEAD(User),pTemp->IdStr);
		
		sprintf(SendStr,"%-4d%-12s",pSendPack->nEvent,pSendPack->IdStr);

		if(SOCKET_ERROR == send(pUNode->uSock,SendStr,strlen(SendStr)+1,0))
		{
			//error todo
		}

		pTemp = pTemp->pNext;
	}

	return 0;
	
}//============================================End

int Modify_InfoProc(void *pVoid,SOCKET nSock)
{
	char SendStr[SZBUF_MAX] = "";
	MODIFY_PACK *pModifyer = (MODIFY_PACK *)pVoid;

	pModifyer->SourId[11] = '\0';
	cout<<pModifyer->SourId<<endl;

	SER_USER_NODE *pNode = (SER_USER_NODE *)FindNode(USE_PHEAD(User),pModifyer->SourId);

	
	if(0 == ModifyNode((LINKER *)pNode,pVoid,nSock))
	{
		cout<<"用户修改资料成功"<<endl;
		sprintf(SendStr,"%-4d%-20s",SER_CHANGE_FINISH,"修改成功");
		if(SOCKET_ERROR == send(nSock,SendStr,strlen(SendStr)+1,0))
		{
			cout<<"SER_CHANGE_FINISH SendError"<<WSAGetLastError()<<endl;
		}
	}

	pNode->uState = LINE;

	return 0;
}//============================================End



int AddIdStr(char *IdStr)
{
	if(NULL == IdStr)
	{
		return -1;
	}
	
	int j = 1;
	
	int i = 0;
	for(i = 0;'\0' != IdStr[i];i++);
	
	for (j = 1;j <= i;j++)
	{
		if(IdStr[i-j] < '9')
		{
			IdStr[i-j] = IdStr[i-j]+1;
			break;
		}
		else
		{
			IdStr[i-j] = '0';
		}
		
	}
	
	
	return 0;
}//============================================End




int UserInput(LINKER *pNode,void *pVoid,SOCKET nSock)
{
	char IdStr[12];


	SER_USER_NODE *pUser = (SER_USER_NODE *)pNode;

	if(CLI_MODIFY != CheckEvent(pVoid))
	{
		REGISTER_PACK *pRegister = (REGISTER_PACK *)(pVoid);
		if(NULL == pNode->pLast)
		{
			strcpy(pUser->linker.IdStr,"00000000001");
		}
		else
		{
			strcpy(IdStr,pUser->linker.pLast->IdStr);
			AddIdStr(IdStr);
			strcpy(pUser->linker.IdStr,IdStr);
		}
		pRegister->uName[19] = '\0';
		pRegister->PicStr[9] = '\0';
		pRegister->uPwd[16] = '\0';
		pRegister->uHro[9] = '\0';
		//(((char *)pRegister->uAge))[3] = '\0';
		strcpy(pUser->uName,pRegister->uName);
		strcpy(pUser->uPwd,pRegister->uPwd);
		strcpy(pUser->uHoro,pRegister->uHro);
		strcpy(pUser->PicStr,pRegister->PicStr);
		pUser->uSock = nSock;
		pUser->uState = OFF_LINE;
		pUser->uAge = atoi((char *)&pRegister->uAge);
	}
	else
	{
		MODIFY_PACK *pModifyer = (MODIFY_PACK *)(pVoid);
		pModifyer->uName[19] = '\0';
		pModifyer->uPwd[16] = '\0';
		pModifyer->uHro[9] = '\0';
		strcpy(pUser->uName,pModifyer->uName);
		strcpy(pUser->uPwd,pModifyer->uPwd);
		strcpy(pUser->uHoro,pModifyer->uHro);
		pUser->uSock = nSock;
		pUser->uState = OFF_LINE;
		pUser->uAge = atoi((char *)&pModifyer->uAge);
	}
	return 0;
}//============================================End


int FriendsInput(LINKER *pNode,void *pVoid,SOCKET nSock)
{
	strcpy(pNode->IdStr,(char *)pVoid);
	return 0;
}//============================================End



