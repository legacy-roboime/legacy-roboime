
#include "UDPClientThread.h"

UDPClientThread::UDPClientThread(void):Thread()
{
	Thread::setName("UDPClientThread");
}

UDPClientThread::UDPClientThread(UDPClient* udpClient):Thread()
{
	Thread::setName("UDPClientThread");
	this->udpClient = udpClient;
}

UDPClientThread::~UDPClientThread(void)
{
	delete udpClient;
}

UDPClientThread::UDPClientThread(const char* nm)
{
	Thread::setName(nm);
	port=9876;
	address="127.0.0.1";
}

UDPClientThread::UDPClientThread(const char* nm, int _port, string _address)
{
	Thread::setName(nm);
	port=_port;
	address=_address;
}
void UDPClientThread::run() {
	try {
		//wait("UDPClientMutex");
		udpClient->func1();
		//release("UDPClientMutex");
	}catch(ThreadException ex) {
		cout << ex.getMessage().c_str() << endl;
	}		

	Thread::sleep(1000);//16.66); //1./60. s
}
	

string UDPClientThread::getLastReceivedString()
{
	return this->udpClient->getLastReceivedString();
}