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
	UDPClient* udpClient;
public:
	UDPClientThread(void);
	UDPClientThread(UDPClient* udpClient);
	~UDPClientThread(void);
	UDPClientThread(const char* nm);
	UDPClientThread(const char* nm, int port, string address);
	void run();
	string getLastReceivedString();
	void setSendString(string sendString);
};