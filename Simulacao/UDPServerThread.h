#pragma once

#include "UDPServer.h"
#include <string>
#include <iostream>
using namespace std;

#include "ou_thread.h"
using namespace openutils;

// a child class of Thread
// prints out object name up to a counter times in the
// run() function
class UDPServerThread : public Thread
{
private:
public:
	UDPServerThread(void);
	~UDPServerThread(void);
	UDPServerThread(const char* nm);
	void run();
	//void startUDPServerThread();
	//void stopUDPServerThread();
};
