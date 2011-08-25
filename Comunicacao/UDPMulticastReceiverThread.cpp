#include "UDPMulticastReceiverThread.h"

UDPMulticastReceiverThread::UDPMulticastReceiverThread(void) : Thread()
{
	Thread::setName("UDPMulticastReceiverThread");
	this->udpMulticastReceiver = new UDPMulticastReceiver();
}

UDPMulticastReceiverThread::UDPMulticastReceiverThread(UDPMulticastReceiver* udpMulticastReceiver)
{
	Thread::setName("UDPMulticastReceiverThread");
	this->udpMulticastReceiver = udpMulticastReceiver;
}

UDPMulticastReceiverThread::~UDPMulticastReceiverThread(void)
{
}

void UDPMulticastReceiverThread::run()
{
	try {
		//wait("UDPMulticastReceiverMutex");
		udpMulticastReceiver->receive();
		//release("UDPMulticastReceiverMutex");
	}catch(ThreadException ex) {
		cout << ex.getMessage().c_str() << endl;
	}		
}