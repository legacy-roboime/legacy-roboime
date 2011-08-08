#pragma once
#include "UDPServer.h"

class UDPServerSimInt : public UDPServer
{
public:
	UDPServerSimInt(void);
	~UDPServerSimInt(void);
	virtual void parsing();			//Parse the received string and define the string to send
};
