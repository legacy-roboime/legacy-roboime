#pragma once

#include "NxShapeDesc.h"

class NxKicker
{
private:
public:
	float speedToExecute;
	NxShapeDesc* kickerShapeDesc;
	//float calcTorqueFromSpeed(); 	//TODO: implementar o controlador
	NxKicker(void);
	~NxKicker(void);
};
