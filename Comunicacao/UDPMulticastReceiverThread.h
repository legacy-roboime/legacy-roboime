#pragma once

#include "UDPMulticastReceiver.h"

#include "ou_thread.h"
#include <string>
#include <iostream>

using namespace std;
using namespace openutils;

class UDPMulticastReceiverThread : public Thread
{
private:
	UDPMulticastReceiver* udpMulticastReceiver;
public:
	UDPMulticastReceiverThread(void);
	UDPMulticastReceiverThread(UDPMulticastReceiver* udpMulticastReceiver);
	~UDPMulticastReceiverThread(void);
	void run();
};
