#include "UDPMulticastReceiver.h"

UDPMulticastReceiver::UDPMulticastReceiver(void){
	multicastTTL = 1;
	multiAddress = "224.5.23.2";
	port = 10002;
	bufLen=ECHOMAX;
}

UDPMulticastReceiver::UDPMulticastReceiver(string address, unsigned short port){
	multicastTTL = 1;
	multiAddress = address;
	this->port = port;
	bufLen=ECHOMAX;
}

UDPMulticastReceiver::~UDPMulticastReceiver(void){
}

void UDPMulticastReceiver::receive(){
	try {
		UDPSocket sock;

		sock.joinGroup(multiAddress);

		for (;;) {
 			buildReceiveMessage();

			int bytesRcvd = sock.recvFrom(receiveBuffer, bufLen, multiAddress, port);
		}
	} catch (SocketException &e) {
		cerr << e.what() << endl;
		exit(1);
	}
}

void UDPMulticastReceiver::buildReceiveMessage(){}

int UDPMulticastReceiver::getBufLen(){
	return bufLen;
}

void UDPMulticastReceiver::setBufLen(int bufLen)
{
	this->bufLen = bufLen;
}

char* UDPMulticastReceiver::getReceiveBuffer(){
	return receiveBuffer;
}