#pragma once
#include "NxVehicle.h"
#include "NxKicker.h"
#include "NxDribbler.h"

class NxRobot : public NxVehicle
{
private: 
	int id;
	int idTeam; //0 (Yellow Team) - 1 (Blue Team)
	NxKicker kicker;
	NxDribbler dribbler;
public:
	float bodyRadius;
public:
	NxRobot();

	//getters and setters
	int getId();
	void setId(int id);
	int getIdTeam();
	void setIdTeam(int idTeam);
};