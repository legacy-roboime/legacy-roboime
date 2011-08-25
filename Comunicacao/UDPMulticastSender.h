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

class UDPMulticastSender
{
private:
	static const int ECHOMAX = 2048;//512 // Longest string to echo
	string servAddress;					  // multicast address
	unsigned short port;				  // port
	unsigned char multicastTTL;			  // Default TTL
	char sendBuffer[ECHOMAX];			  // message to send
	int bufLen;							  // lenght of message to send 
public:
	UDPMulticastSender(void);
	~UDPMulticastSender(void);
	void send();
	virtual void buildSendMessage();
	char* getSendBuffer();
	int getBufLen();
	void setBufLen(int bufLen);
};
