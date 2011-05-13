#pragma once

class Pose {

public:
	Pose(void);
	Pose(double position[3], double speed[3], double accel[3]);//Constructor
	~Pose(void);//Destructor

	//fields:
	double position[3], speed[3], accel[3], orientation[3];

};