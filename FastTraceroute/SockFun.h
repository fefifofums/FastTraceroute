#pragma once

#include "pch.h"


void initWinSock();
void createSock(SOCKET * imcpSock);
void setTTL(SOCKET * icmpSock, char ttl);
void sendICMP(SOCKET * icmpSock, u_char send_buff[MAX_ICMP_SIZE], sockaddr_in RecvAddr);