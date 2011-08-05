#pragma once

#include "NxActor.h"

class NxKicker
{
private:
	
public:
	NxActor* kicker;
	NxMat34 initialPose;
	NxKicker(void);
	~NxKicker(void);
};
