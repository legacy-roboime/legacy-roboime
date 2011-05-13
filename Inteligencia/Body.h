#pragma once
#include "Component.h"

class Body : Component {
	friend class Robot;

private:
	//fields:
	double _height, _radius;

public:
	Body(void);
	Body(double height, double radius);
	~Body(void);

};