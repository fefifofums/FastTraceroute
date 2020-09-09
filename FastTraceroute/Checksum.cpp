#pragma

#include "pch.h"

#include "Checksum.h"

u_short ip_checksum(u_short *buffer, int size)
{
	u_long  cksum = 0;

	while (size > 1)
	{
		cksum += *buffer++;
		size -= sizeof(u_short);
	}

	if (size)
		cksum += *(u_char *)buffer;

	// add carry bits to lower u_short word
	cksum = (cksum >> 16) + (cksum & 0xffff);

	// return a bitwise complement of result
	return (u_short)(~cksum);
}
