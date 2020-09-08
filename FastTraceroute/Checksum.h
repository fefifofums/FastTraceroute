#pragma once
#include "pch.h"

class Checksum
{

public:
	u_short ip_checksum(u_short *buffer, int size);
};

