#pragma once
#include "NxVehicle.h"

class NxRobot : public NxVehicle
{
private: 
	int id;
	int idTeam; //0 (Yellow Team) - 1 (Blue Team)
public:
	float robotRadius;
	float angleRelativeWheel1;
	float angleRelativeWheel2;
	float angleRelativeWheel3;
	float angleRelativeWheel4;
public:
	NxRobot();

	//getters and setters
	int getId();
	void setId(int id);
	int getIdTeam();
	void setIdTeam(int idTeam);
};