#pragma once

#include "ou_thread.h"
#include <string>
#include <iostream>
#include <windows.h>          // For ::Sleep()

using namespace std;
using namespace openutils;

class SimpleThread :
	public Thread
{
private:
	int argc;
	char** argv;
	void (*function) (int, char**);
	void (*function1) (void);
public:
	SimpleThread(void);
	SimpleThread(void (*function1) (void)); //SimulateRun
	SimpleThread(void (*function) (int, char**)); //MainLoop
	SimpleThread(void (*function) (int, char**), int argc, char** argv); //MainLoop
	~SimpleThread(void);
	void run();
};
