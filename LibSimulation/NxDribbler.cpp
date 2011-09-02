#include "NxDribbler.h"

NxDribbler::NxDribbler(void)
{
	speedToExecute = 0;
}

NxDribbler::~NxDribbler(void)
{
}

void NxDribbler::controlDribbler( float dribblerSpeed )
{
	this->speedToExecute = dribblerSpeed;
}
