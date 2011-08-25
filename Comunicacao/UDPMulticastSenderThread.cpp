#include "UDPMulticastSenderThread.h"

UDPMulticastSenderThread::UDPMulticastSenderThread(void) : Thread()
{
	Thread::setName("UDPMulticastSenderThread");
	this->udpMulticastSender = new UDPMulticastSender();
}

UDPMulticastSenderThread::UDPMulticastSenderThread(UDPMulticastSender* udpMulticastSender)
{
	Thread::setName("UDPMulticastSenderThread");
	this->udpMulticastSender = udpMulticastSender;
}

UDPMulticastSenderThread::~UDPMulticastSenderThread(void)
{
}

void UDPMulticastSenderThread::run()
{
	try {
		//wait("UDPMulticastSenderMutex");
		udpMulticastSender->send();
		//release("UDPMulticastSenderMutex");
	}catch(ThreadException ex) {
		cout << ex.getMessage().c_str() << endl;
	}		
}
