
#include "UDPServerThread.h"

UDPServerThread::UDPServerThread(void):Thread()
{
	Thread::setName("UDPServerThread");
}

UDPServerThread::UDPServerThread(UDPServer* udpServer):Thread()
{
	Thread::setName("UDPServerThread");
	this->udpServer = udpServer;
}

UDPServerThread::~UDPServerThread(void)
{
	delete udpServer;
}

UDPServerThread::UDPServerThread(const char* nm)
{
	Thread::setName(nm);
	port=9876;
	address="127.0.0.1";
}

UDPServerThread::UDPServerThread(const char* nm, int _port, string _address)
{
	Thread::setName(nm);
	port=_port;
	address=_address;
}
void UDPServerThread::run() {
	try {
		//wait("UDPServerMutex");
		udpServer->func1();
		//release("UDPServerMutex");
	}catch(ThreadException ex) {
		cout << ex.getMessage().c_str() << endl;
	}
}
	

string UDPServerThread::getLastReceivedString()
{
	return this->udpServer->getLastReceivedString();
}