#pragma once

#include "pch.h"

#include "Checksum.h"
#include "pakcets.h"
#include "SockFun.h"





int main(int argc, char** argv)
{
	initWinSock();

	// Create ICMP socket
	SOCKET icmpSock = INVALID_SOCKET;
	createSock(&icmpSock);


	u_char send_buff[MAX_ICMP_SIZE];
	ICMPHeader *icmp = (ICMPHeader *)send_buff;
	icmp->type = ICMP_ECHO_REQUEST;
	icmp->code = 0;
	icmp->id = GetCurrentProcessId();
	icmp->seq = 1;
	icmp->checksum = 0;

	int packet_size = sizeof(ICMPHeader);
	
	icmp->checksum = ip_checksum((u_short *)send_buff, packet_size);

	char ttl = 8;

		
	setTTL(&icmpSock, ttl);

	sockaddr_in RecvAddr; 
	RecvAddr.sin_family = AF_INET;
	RecvAddr.sin_port = htons(27015);
	RecvAddr.sin_addr.s_addr = inet_addr("98.137.11.163");

	sendICMP(&icmpSock, send_buff, RecvAddr);
	

	WSACleanup();


	return 0;
}