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
	UDPServer* udpServer;
	int port;
	string address;

	UDPServerThread(void);
	UDPServerThread(UDPServer* udpServer);
	~UDPServerThread(void);
	UDPServerThread(const char* nm);
	UDPServerThread(const char* nm, int port, string address);
	void run();
	string getLastReceivedString();
};