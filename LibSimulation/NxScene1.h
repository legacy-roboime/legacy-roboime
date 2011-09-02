#pragma once
#include <NxScene.h>
//#include <stdio.h>
//#include <string.h>
//#include <sstream>
//#include <iostream>
//#include "NxPhysics.h"
#include "NxAllRobots.h"
#include "NxField.h"
#include "NxBall.h"
//#include <NxArray.h>

//using namespace std;

class NxScene1
{
public:
	int indexScene;
	NxScene* scene;
	NxAllRobots* allRobots;
	NxField* field;
	NxBall* ball;
public:
	friend class NxScene;

	NxScene1(void);
	~NxScene1(void);
};
