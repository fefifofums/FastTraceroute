#pragma

#include "pch.h"

#include "Checksum.h"
#include "pakcets.h"
#include "SockFun.h"

void initWinSock()
{
	WSADATA wsaData;
	DWORD wVersionRequested;
	wVersionRequested = MAKEWORD(2, 2);

	if (WSAStartup(wVersionRequested, &wsaData) != 0) {
		printf("WSAStartup error %d\n", WSAGetLastError());
		WSACleanup();
		exit(-1);
	}

}

void createSock(SOCKET * icmpSock)
{
	
	*icmpSock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	SOCKET * sockAddr = &(*icmpSock);
	int sockResult;

	if (*icmpSock == INVALID_SOCKET)
	{
		printf("Unable to create a raw socket: error %d\n", WSAGetLastError());

		//Attempt to close socket
		sockResult = closesocket(*icmpSock);

		if (sockResult == SOCKET_ERROR)
		{
			printf("closesocket failed with error = %d\n", WSAGetLastError());
			WSACleanup();
		}

		exit(-1);
	}
}

void setTTL(SOCKET * icmpSock, char ttl)
{
	int sockResult;

	if (setsockopt(*icmpSock, IPPROTO_IP, IP_TTL, (const char *)&ttl, sizeof(ttl)) == SOCKET_ERROR)
	{
		printf("setsockopt failed with %d\n", WSAGetLastError());
		sockResult = closesocket(*icmpSock);
		if (sockResult == SOCKET_ERROR)
		{
			printf("closesocket failed with error = %d\n", WSAGetLastError());
			WSACleanup();
		}

		exit(-1);
	}
}

void sendICMP(SOCKET * icmpSock, u_char send_buff[MAX_ICMP_SIZE], sockaddr_in RecvAddr)
{
	int result = sendto(*icmpSock, (const char *)send_buff, sizeof(ICMPHeader), 0, (SOCKADDR *)& RecvAddr, sizeof(RecvAddr));
	if (result == SOCKET_ERROR) {
		wprintf(L"closesocket failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		exit(-1);
	}
}