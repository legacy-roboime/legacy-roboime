
#include "NxScene1.h"
#include "Simulation.h"

NxScene1::NxScene1(void)
{
	allRobots = new NxAllRobots();
	field = new NxField();
	ball = new NxBall();
}

NxScene1::~NxScene1(void)
{
	delete allRobots;
	delete field;
	delete ball;
}