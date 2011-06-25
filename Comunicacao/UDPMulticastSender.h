/*
 *   C++ sockets on Unix and Windows
 *   Copyright (C) 2002
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

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
