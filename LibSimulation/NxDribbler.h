#pragma once

#include "NxArray.h"
#include "NxShape.h"

class NxDribbler
{
private:
public:
	float speedToExecute;
	NxArray<NxShape*> dribblerShapes;
	void controlDribbler( float dribblerSpeed );
	NxDribbler(void);
	~NxDribbler(void);
};
