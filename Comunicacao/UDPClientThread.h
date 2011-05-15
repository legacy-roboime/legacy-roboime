#pragma once

#include <string>
#include <iostream>
using namespace std;

#include "UDPClient.h"

#include "ou_thread.h"
using namespace openutils;


class UDPClientThread : public Thread
{
private:
public:
	UDPClient* udpClient;
	int port;
	string address;

	UDPClientThread(void);
	UDPClientThread(UDPClient* udpClient);
	~UDPClientThread(void);
	UDPClientThread(const char* nm);
	UDPClientThread(const char* nm, int port, string address);
	void run();
	string getLastReceivedString();
};