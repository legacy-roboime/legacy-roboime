#pragma once

#include "PracticalSocket.h"  // For UDPSocket and SocketException
#include <iostream>           // For cout and cerr
#include <cstdlib>            // For atoi()
#include <string.h>

#define NOMINMAX

#ifdef WIN32
#include <windows.h>          // For ::Sleep()
//void sleep(unsigned int seconds) {::Sleep(seconds * 1000);}
#else
#include <unistd.h>           // For sleep()
#endif

using namespace std;

class UDPMulticastReceiver
{
private:
	static const int ECHOMAX = 2048;//512 // Longest string to echo
	string multiAddress;			      // multicast address
	unsigned short port;				  // port
	unsigned char multicastTTL;			  // Default TTL
	char receiveBuffer[ECHOMAX];		  // received message
	int bufLen;							  // lenght of message to send 
public:
	UDPMulticastReceiver(void);
	UDPMulticastReceiver(string address, unsigned short port);
	~UDPMulticastReceiver(void);
	void receive();
	virtual void buildSendMessage();
	char* getReceiveBuffer();
	int getBufLen();
	void setBufLen(int bufLen);
};
