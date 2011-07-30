#include "NxBall.h"
#include "Simulation.h"

NxBall::NxBall(void)
{
}

NxBall::~NxBall(void)
{
}

void Simulation::buildModelBall(int indexScene){
	NxBall ball;
	ball.ball = Simulation::getActorBall(indexScene);
	ball.indexScene = indexScene;
	Simulation::allBalls.balls.push_back(ball);
}

void NxBall::cloneBall(int indexNewScene){
	NxBall ball;
	ball.ball = Simulation::cloneActor(this->ball, indexNewScene);
	ball.indexScene = indexNewScene;
	Simulation::allBalls.balls.push_back(ball);
}
