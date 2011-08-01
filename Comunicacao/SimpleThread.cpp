#include "SimpleThread.h"

SimpleThread::SimpleThread(void): Thread()
{
	function = NULL;
	function1 = NULL;
}

SimpleThread::SimpleThread(void (*function1) (void)): Thread(){
	function = NULL;
	this->function1 =  function1;
}

SimpleThread::SimpleThread(void (*function) (int, char**)): Thread(){
	this->function =  function;
	function1 = NULL;
}

SimpleThread::SimpleThread(void (*function) (int, char**), int argc, char** argv): Thread(){
	this->function =  function;
	this->argc = argc;
	this->argv = argv;
	function1 = NULL;
}

SimpleThread::~SimpleThread(void)
{
}

void SimpleThread::run(){
	try {
		//wait("UDPMulticastReceiverMutex");
		if(this->function)
			this->function(argc,argv);
		else if(this->function1){
			Sleep(7000);
			this->function1();
		}
		//release("UDPMulticastReceiverMutex");
	}catch(ThreadException ex) {
		cout << ex.getMessage().c_str() << endl;
	}	
}
