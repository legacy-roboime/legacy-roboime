
#include "UDPClientThread.h"

UDPClientThread::UDPClientThread(void):Thread()
{
	Thread::setName("UDPClientThread");
	udpClient = new UDPClient();
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
	udpClient = new UDPClient();
}

UDPClientThread::UDPClientThread(const char* nm, int _port, string _address)
{
	Thread::setName(nm);
	udpClient = new UDPClient(_address, _port);
}
void UDPClientThread::run() {
	try {
		//wait("UDPClientMutex");
		udpClient->service();
		//release("UDPClientMutex");
	}catch(ThreadException ex) {
		cout << ex.getMessage().c_str() << endl;
	}		
}
	

string UDPClientThread::getLastReceivedString()
{
	return this->udpClient->getLastReceivedString();
}