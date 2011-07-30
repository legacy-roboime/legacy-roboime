#pragma once
#include "NxVehicle.h"
#include "NxKicker.h"
#include "NxDribbler.h"

class NxRobot : public NxVehicle
{
private: 
	int id;
	int idTeam; //0 (Yellow Team) - 1 (Blue Team)
public:
	int indexScene;
	NxKicker kicker;
	NxDribbler dribbler;
	NxArray<NxJoint*> joints;
	float bodyRadius;
public:
	NxRobot();

	void cloneRobot(int indexNewScene, int indexNewRobot, NxVec3 newPosition, int indexNewTeam);
	NxJoint* cloneJointRobot(NxJoint* jointSource, int indexDestScene);

	//getters and setters
	int getId();
	void setId(int id);
	int getIdTeam();
	void setIdTeam(int idTeam);
};