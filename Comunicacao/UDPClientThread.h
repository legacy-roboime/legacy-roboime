#pragma once
#include "udpclient.h"

class UDPClientThread :
	public UDPClient
{
public:
	UDPClientThread(void);
	~UDPClientThread(void);
};
