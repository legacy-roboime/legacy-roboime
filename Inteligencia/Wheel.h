#include "Component.h"

class Wheel : Component {
	friend class Robot;

private:
	//fields:
	double _angular_speed, _radius;

public:
	Wheel(void);
	Wheel(double radius);//Constructor
	~Wheel(void);//Destructor

};