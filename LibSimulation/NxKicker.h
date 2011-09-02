#pragma once

#include "NxShapeDesc.h"

class NxRobot;

class NxKicker
{
private:
public:
	NxShapeDesc* kickerShapeDesc;
	//float calcTorqueFromSpeed(); 	//TODO: implementar o controlador
	void controlKicker( float kickerSpeed, NxRobot* robot );
	NxKicker(void);
	~NxKicker(void);
};
