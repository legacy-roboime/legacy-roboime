#include "UDPMulticastSender.h"

UDPMulticastSender::UDPMulticastSender(void)
{
	multicastTTL = 1;
	servAddress = "224.5.23.2";
	//servAddress = "127.0.0.1";
	port = 10002;
	bufLen=ECHOMAX;
}

UDPMulticastSender::~UDPMulticastSender(void)
{
}

void UDPMulticastSender::send()
{
	try {
		UDPSocket sock;

		sock.setMulticastTTL(multicastTTL);

		Sleep(7000); //Wait the Simulation Start

		// Repeatedly send the string to the server
		for (;;) {
 			buildSendMessage();

			sock.sendTo(sendBuffer, bufLen, servAddress, port);
			Sleep(1000./60.); //camera 60 fps
		}
	} catch (SocketException &e) {
		cerr << e.what() << endl;
		exit(1);
	}
}

void UDPMulticastSender::buildSendMessage()
{
	printf("buildSendMessage Super classe\n");
}

int UDPMulticastSender::getBufLen()
{
	return bufLen;
}

void UDPMulticastSender::setBufLen(int bufLen)
{
	this->bufLen = bufLen;
}

char* UDPMulticastSender::getSendBuffer()
{
	return sendBuffer;
}