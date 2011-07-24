#pragma once

#include "ou_thread.h"
#include <string>
#include <iostream>

using namespace std;
using namespace openutils;

class SimpleThread :
	public Thread
{
private:
	int argc;
	char** argv;
	void (*function) (int, char**);
public:
	SimpleThread(void);
	SimpleThread(void (*function) (int, char**));
	SimpleThread(void (*function) (int, char**), int argc, char** argv);
	~SimpleThread(void);
	void run();
};
