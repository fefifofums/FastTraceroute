#pragma once

#include "pch.h"

#include "Checksum.h"
#include "pakcets.h"



int main(int argc, char** argv)
{
	// Create ICMP socket
	SOCKET icmpSock = INVALID_SOCKET;
	icmpSock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

	int sockResult;

	if (icmpSock == INVALID_SOCKET)
	{
		printf("Unable to create a raw socket: error %d\n", WSAGetLastError());

		//Attempt to close socket
		sockResult = closesocket(icmpSock);

		if (sockResult == SOCKET_ERROR)
		{
			printf("closesocket failed with error = %d\n", WSAGetLastError());
			WSACleanup();
		}
		
		exit(-1);
	}
	return 0;
}