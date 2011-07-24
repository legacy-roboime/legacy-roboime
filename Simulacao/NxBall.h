#pragma once

#include "NxActor.h"

class NxBall
{
private:
	NxArray<NxActor*> balls; 
public:
	NxBall(void);
	~NxBall(void);
};
