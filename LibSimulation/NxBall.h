#pragma once

#include "NxActor.h"

class NxBall
{
public:
	int indexScene;
	NxActor* ball; 
public:
	NxBall(void);
	~NxBall(void);

	void cloneBall(int indexNewScene);
};
