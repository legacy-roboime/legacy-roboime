#pragma once
#include "Component.h"

class Motor : Component {
	friend class Robot;

private:
	//fields:
	double _torque;

public:
	Motor(void);
	Motor(double torque);
	~Motor(void);

};