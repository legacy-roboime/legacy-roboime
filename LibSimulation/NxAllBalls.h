#pragma once
#include "NxBall.h"

class NxAllBalls
{
public:
	NxArray<NxBall> balls;
public:
	NxAllBalls(void);
	~NxAllBalls(void);
	NxBall getBallByScene(int indexScene);
};
