#pragma once
#include "Component.h"

class Kicker : Component {
	friend class Robot;

private:
	//fields:
	double _force;

public:
	Kicker(void);
	Kicker(double force);
	~Kicker(void);

};