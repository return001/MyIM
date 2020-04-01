// OverLappedServices.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{
	WSADATA data;
	WSAStartup(0x0202, &data);

	WSAOVERLAPPED Overlapped;
	WSABUF DataBuf;
	SOCKET aSock[64];
	WSAEVENT aEvent[64];
	int nCount = 0;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == sListen)
	{
		cout << "ListenSock error!" << endl;
		return -1;
	}

	SOCKADDR_IN addrlisten;
	addrlisten.sin_family = AF_INET;
	addrlisten.sin_addr.s_addr = INADDR_ANY;
	addrlisten.sin_port = htons(5050);

	if (SOCKET_ERROR == bind(sListen, (sockaddr *)&addrlisten, sizeof(addrlisten)))
	{
		cout << "bind error!" << endl;
		return -1;
	}

	if (SOCKET_ERROR == listen(sListen, 3))
	{
		cout << "listen error!" << endl;
		return -1;
	}

	aSock[nCount] = sListen;
	aEvent[nCount] = WSACreateEvent();

	ZeroMemory(&Overlapped, sizeof(Overlapped));
	Overlapped.hEvent = aEvent[nCount];
	nCount++;
	DWORD dwRecv = 0;
	char szBuf[4096] = "";

	
	SOCKET sClient = socket(AF_INET, SOCK_STREAM, 0);
	aSock[nCount] = sClient;
	WSAEVENT Event = WSACreateEvent();
	aEvent[nCount] = Event;
	AcceptEx(sListen, sClient, szBuf, 0, 0, sizeof(SOCKADDR_IN) + 16, &dwRecv, &Overlapped);
	nCount++;

	int nIndex = 0;
	dwRecv = 0;
	DWORD dwFlag = 0;
	while (TRUE)
	{
		nIndex = WSAWaitForMultipleEvents(nCount, aEvent, FALSE, WSA_INFINITE, FALSE);

		WSAResetEvent(aEvent[nIndex - WSA_WAIT_EVENT_0]);

		WSAGetOverlappedResult(aSock[nIndex - WSA_WAIT_EVENT_0], &Overlapped, &dwRecv, FALSE, &dwFlag);

		
		if (0 == (nIndex - WSA_WAIT_EVENT_0))
		{
			//accept
			DataBuf.len = 4096;
			DataBuf.buf = szBuf;

			ZeroMemory(&Overlapped, sizeof(Overlapped));
			Overlapped.hEvent = Event;

			WSARecv(sClient, &DataBuf, 1, &dwRecv, &dwFlag, &Overlapped, NULL);

			//post accept
			ZeroMemory(&Overlapped, sizeof(Overlapped));
			Overlapped.hEvent = aEvent[nIndex - WSA_WAIT_EVENT_0];

			sClient = socket(AF_INET, SOCK_STREAM, 0);
			aSock[nCount] = sClient;
			Event = WSACreateEvent();
			aEvent[nCount] = Event;
			AcceptEx(sListen, sClient, szBuf, 0, 0, sizeof(SOCKADDR_IN) + 16, &dwRecv, &Overlapped);
			nCount++;
		}
		else
		{
			if (0 == dwRecv)
			{
				//TODO: error
				continue;
			}

			cout << szBuf << endl;

			DataBuf.len = 4096;
			DataBuf.buf = szBuf;

			ZeroMemory(&Overlapped, sizeof(Overlapped));
			Overlapped.hEvent = aEvent[nIndex - WSA_WAIT_EVENT_0];
		
			WSARecv(aSock[nIndex - WSA_WAIT_EVENT_0], &DataBuf, 1, &dwRecv, &dwFlag, &Overlapped, NULL);
		}

	}

	WSACleanup();
	return 0;
}
