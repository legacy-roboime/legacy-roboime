#pragma once

#include "UDPMulticastSender.h"

#include "ou_thread.h"
#include <string>
#include <iostream>

using namespace std;
using namespace openutils;

class UDPMulticastSenderThread : public Thread
{
private:
	UDPMulticastSender* udpMulticastSender;
public:
	UDPMulticastSenderThread(void);
	UDPMulticastSenderThread(UDPMulticastSender* udpMulticastSender);
	~UDPMulticastSenderThread(void);
	void run();
};
