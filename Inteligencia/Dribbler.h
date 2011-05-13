#pragma once
#include "Component.h"

class Dribbler : Component {
	friend class Robot;

private:
	//fields:
	double _force;

public:
	Dribbler(void);
	Dribbler(double force);
	~Dribbler(void);

};