// selectServices.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define SERVICE_IP_STR ("172.16.36.199")
#define CLIENT_IP_STR ("172.16.36.199")
#define SZBUF_MAX (4096)
#define PORT_NUM (5000)
#define LISTEN_NUM (3)
#define WM_ZXCSOCKET (WM_USER + 2)
#define PROC_SOCK_NUM (64)


int main(int argc, char* argv[])
{ 
	int nError = 0;
	SOCKET nSocks[PROC_SOCK_NUM] = {0};
	fd_set PendSocks;
	int nNum = 0;
	int nRe = 0;
	char szBuf[SZBUF_MAX] = "";

	WSADATA wData;

	WSAStartup(0x0202,&wData);

	SOCKET sockListen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	if(INVALID_SOCKET == sockListen)
	{
		nError = WSAGetLastError();
		cout<<"socket Error:"<<nError<<endl;
		return -1;
	}

	SOCKADDR_IN sockAddr;
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(SERVICE_IP_STR);
	sockAddr.sin_port = htons(PORT_NUM);

	if(SOCKET_ERROR == bind(sockListen,(sockaddr *)&sockAddr,sizeof(sockAddr)))
	{
		nError = WSAGetLastError();
		cout<<"bind error"<<nError<<endl;
		return -2;
	}

	if(SOCKET_ERROR == listen(sockListen,LISTEN_NUM))
	{
		nError = WSAGetLastError();
		cout<<"listen Error"<<endl;
		return -3;
	}

	nSocks[nNum] = sockListen;
	nNum++;

	while(TRUE)
	{
		FD_ZERO(&PendSocks);

		for(int i = 0;i < nNum;i++)
		{
			FD_SET(nSocks[i],&PendSocks);
		}

		nRe = select(0,&PendSocks,NULL,NULL,NULL);

		if(nRe > 0)
		{
			for (int j = 0;j < nNum;j++)
			{
				if(FD_ISSET(nSocks[j],&PendSocks))
				{
					if(0 == j)
					{
						nSocks[nNum] = accept(sockListen,NULL,NULL);

						if(INVALID_SOCKET == nSocks[nNum])

						{
							nError = WSAGetLastError();
							cout<<"nSock Error"<<nError<<endl;
						}
						nNum++;
					}
					else
					{
						if(SOCKET_ERROR == recv(nSocks[j],szBuf,SZBUF_MAX,0))
						{
							nError = WSAGetLastError();
							cout<<"recv Error"<<nError<<endl;
							break;
						}
						cout<<szBuf<<endl;
						send(nSocks[j],szBuf,strlen(szBuf)+1,0);
					}
					break;
				}
			}
		}

	}

	WSACleanup();
	return 0;
}
