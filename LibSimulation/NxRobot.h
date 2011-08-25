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
	float wheelsRadius;
public:
	NxRobot();

	void handleContactPair(NxContactPair& pair, NxU32 robotIndex);

	void cloneRobot(int indexNewScene, int indexNewRobot, NxVec3 newPosition, int indexNewTeam);
	void setGlobalPosition(NxVec3 position);
	void setGlobalOrientation(NxMat33 orientation);
	void putToSleep();
	void resetToInitialPose();

	//getters and setters
	int getId();
	void setId(int id);
	int getIdTeam();
	void setIdTeam(int idTeam);
};