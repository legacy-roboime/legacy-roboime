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

struct DataBaseVision{
	float ballX;
	float ballY;
	float ballSpeedX;
	float ballSpeedY;
	float robots[10][4];
};

class UDPServer
{
private:
	static const int ECHOMAX = 512;//255;     // Longest string to echo
	static unsigned short echoServPort;     // local port
	static char echoBuffer[ECHOMAX];         // Buffer for echo string
    static int recvMsgSize;                  // Size of received message
    static string sourceAddress;             // Address of datagram source
    static unsigned short sourcePort;        // Port of datagram source
public:
	static const int numRobots = 10;
	static const int numInfo = 4;
	static const int sizeDataBaseVision = 1;
	static int ptrDataBaseVision;
	static float ballRadius;
	static struct DataBaseVision dataBaseVision[sizeDataBaseVision];

	UDPServer(void);
	UDPServer(unsigned short port, string address);
	~UDPServer(void);
	static void func1();
};
