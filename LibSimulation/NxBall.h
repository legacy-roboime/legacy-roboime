#pragma once

#include "NxActor.h"

class NxBall
{
public:
	int indexScene;
	NxActor* ball; 
	NxMat34 initialPose;
public:
	NxBall(void);
	~NxBall(void);

	void cloneBall(int indexNewScene);
	void resetToInitialPose();
	void putToSleep();
};
