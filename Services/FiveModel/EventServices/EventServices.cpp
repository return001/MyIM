// EventServices.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



int main(int argc, char* argv[])
{
	int nError = 0;
	SOCKET nSocks[PROC_SOCK_NUM];
	WSAEVENT nEvents[PROC_SOCK_NUM];
	int nNum = 0;
	int Index = 0;
	int ReIndex = 0;
	WSANETWORKEVENTS NetEvents;
	char szBuf[SZBUF_MAX] = "";


	WSADATA wData;

	WSAStartup(0x0202,&wData);

	SOCKET sockListen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	if(INVALID_SOCKET == sockListen)
	{
		nError = WSAGetLastError();
		cout<<"sock Error"<<nError<<endl;
		return -1;
	}

	SOCKADDR_IN sockAddr;
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(SERVICE_IP_STR);
	sockAddr.sin_port = htons(PORT_NUM);


	if(SOCKET_ERROR == bind(sockListen,(sockaddr *)&sockAddr,sizeof(sockaddr)))
	{
		nError = WSAGetLastError();
		cout<<"bind Error"<<nError<<endl;
		return -2;
	}

	if(SOCKET_ERROR == listen(sockListen,LISTEN_NUM))
	{
		nError  = WSAGetLastError();
		cout<<"listen Error"<<nError<<endl;
		return -3;
	}

	nSocks[nNum] = sockListen;
	nEvents[nNum] = WSACreateEvent();

	if(WSA_INVALID_EVENT == nEvents[nNum])
	{
		nError = WSAGetLastError();
		cout<<"WSACreateEvent Error:"<<nError<<endl;
	}

	if (SOCKET_ERROR == WSAEventSelect(nSocks[nNum],nEvents[nNum],FD_ACCEPT))
	{
		nError = WSAGetLastError();
		cout<<"WSAEventSelect Error"<<nError<<endl;
	}

	nNum++;


	while (TRUE)
	{
		Index = WSAWaitForMultipleEvents(nNum,nEvents,FALSE,WSA_INFINITE,FALSE);

		ReIndex = Index - WSA_WAIT_EVENT_0;

		WSAEnumNetworkEvents(nSocks[ReIndex],nEvents[ReIndex],&NetEvents);

		if (NetEvents.lNetworkEvents & FD_ACCEPT)
		{
			if(0 == NetEvents.iErrorCode[FD_ACCEPT_BIT])
			{
				nSocks[nNum] = accept(nSocks[ReIndex],NULL,NULL);
				nEvents[nNum] = WSACreateEvent();
				
				if(WSA_INVALID_EVENT == nEvents[nNum])
				{
					nError = WSAGetLastError();
					cout<<"WSACreateEvent Error:"<<nError<<endl;
				}
				
				if (SOCKET_ERROR == WSAEventSelect(nSocks[nNum],nEvents[nNum],FD_CLOSE | FD_READ))
				{
					nError = WSAGetLastError();
					cout<<"WSAEventSelect Error"<<nError<<endl;
				}
				nNum++;
			}
		}
		else if (NetEvents.lNetworkEvents & FD_READ)
		{
			if(0 == NetEvents.iErrorCode[FD_READ_BIT])
			{
				if (SOCKET_ERROR == recv(nSocks[ReIndex],szBuf,SZBUF_MAX,0))
				{
					nError = WSAGetLastError();
					cout<<"recv Error"<<nError<<endl;
				}
				cout<<szBuf<<endl;
				
			}
		}
		else if (NetEvents.lNetworkEvents & FD_CLOSE)
		{
		
			WSAEventSelect(nSocks[ReIndex],nEvents[ReIndex],0);
			closesocket(nSocks[ReIndex]);
			WSACloseEvent(nEvents[ReIndex]);

			nNum--;
				
			nSocks[ReIndex] = nSocks[nNum];
			nEvents[ReIndex] = nEvents[nNum];
			if( 1 == nNum)
			{
				return 1;
			}
				

		}


	}
	WSACleanup();
	return 0;
}
