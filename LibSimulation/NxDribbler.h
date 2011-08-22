#pragma once

#include "NxArray.h"
#include "NxShape.h"

class NxDribbler
{
private:
	
public:
	NxArray<NxShape*> dribblerShapes;
	NxDribbler(void);
	~NxDribbler(void);
};
