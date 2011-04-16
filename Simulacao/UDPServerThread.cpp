
#include "UDPServerThread.h"

UDPServerThread::UDPServerThread(void):Thread()
{
	Thread::setName("UDPServerThread");
}

UDPServerThread::~UDPServerThread(void)
{
}

UDPServerThread::UDPServerThread(const char* nm)
{
	Thread::setName(nm);
}

void UDPServerThread::run() {
	try {
		//wait("UDPServerMutex");
		UDPServer::func1();
		//release("UDPServerMutex");
	}catch(ThreadException ex) {
		cout << ex.getMessage().c_str() << endl;
	}		
}

//void UDPServerThread::startUDPServerThread()
//{
//	try {
//		//Mutex m("UDPServerThread");
//		this->start();
//		//m.release();
//	}catch(ThreadException ex) {
//		cout << ex.getMessage().c_str()<<endl;
//		goto del;
//	}	
//del:
//	delete this;
//}
//
//void UDPServerThread::stopUDPServerThread()
//{
//	try {
//		//Mutex m("UDPServerThread");
//		this->stop();	
//		//m.release();
//	}catch(ThreadException ex) {
//		cout << ex.getMessage().c_str()<<endl;
//		goto del;
//	}	
//del:
//	delete this;
//}