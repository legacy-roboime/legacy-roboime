#pragma once

#include "NxActor.h"

class NxDribbler
{
private:
	
public:
	NxActor* dribbler;
	NxMat34 initialPose;
	NxDribbler(void);
	~NxDribbler(void);
};
