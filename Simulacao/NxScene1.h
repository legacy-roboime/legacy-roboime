#pragma once
#include <NxScene.h>
//#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include "NxPhysics.h"
//#include "NxAllRobots.h"
//#include "NxField.h"
//#include "NxBall.h"
#include <NxArray.h>

using namespace std;

class NxScene1 : public NxScene
{
public:
	//int indexScene;
	//NxAllRobots allRobots;
	//NxField field;
	//NxArray<NxBall> balls;
public:
	friend class NxScene;

	NxScene1(void);
	~NxScene1(void);
	//void initNxScene1();
	//NxActor* getActorWheel(int robotNumber, int wheelNumber);
};
