/*
Windows:  When you compile this program on Windows, make sure you add
wsock32.lib to the library module list (Project->Setting->Link under
VC++).
*/
#pragma once

#include "PracticalSocket.h" // For UDPSocket and SocketException
#include <iostream>          // For cout and cerr
#include <sstream> 
#include <stdio.h>

class UDPClient
{
protected:
	static const int ECHOMAX = 512;//255;   // Longest string to echo

	unsigned short echoServPort;			// Server port
	string servAddress;						// server address
	char* echoString;						// string to echo (send)
	int echoStringLen;						// Length of string to echo

	char echoBuffer[ECHOMAX + 1];			// Buffer for echo string (received), Buffer for echoed string + \0
	int respStringLen;						// Size of received message
	string response;

    //string sourceAddress;					// Address of datagram source
    //unsigned short sourcePort;			// Port of datagram source
public:
	//static const int numRobots = 10;
	//static const int numInfo = 4;
	//static const int sizeDataBaseVision = 1;
	//int ptrDataBaseVision;
	//float ballRadius;
	//struct DataBaseVision dataBaseVision[sizeDataBaseVision];

	UDPClient(void);
	~UDPClient(void);
	UDPClient(string servAddress, char* echoString, unsigned short echoServPort);
	void func1();
	virtual void parsing();					//Parse the received string
};