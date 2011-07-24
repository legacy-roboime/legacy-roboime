#include "SimpleThread.h"

SimpleThread::SimpleThread(void): Thread()
{
}

SimpleThread::SimpleThread(void (*function) (int, char**)): Thread(){
	this->function =  function;
}

SimpleThread::SimpleThread(void (*function) (int, char**), int argc, char** argv): Thread(){
	this->function =  function;
	this->argc = argc;
	this->argv = argv;
}

SimpleThread::~SimpleThread(void)
{
}

void SimpleThread::run(){
	try {
		//wait("UDPMulticastReceiverMutex");
		this->function(argc,argv);
		//release("UDPMulticastReceiverMutex");
	}catch(ThreadException ex) {
		cout << ex.getMessage().c_str() << endl;
	}	
}
