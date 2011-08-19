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
	ball.ball->setMaxAngularVelocity(0.0001);
	//0.031
	ball.ball->setMass(0.000001); //PLUGIN TAH COM PROBLEMA XML ERRADO 
	ball.initialPose = ball.ball->getGlobalPose();
	ball.indexScene = indexScene;
	Simulation::allBalls.balls.push_back(ball);
}

void NxBall::cloneBall(int indexNewScene){
	NxBall ball;
	ball.ball = Simulation::cloneActor(this->ball, indexNewScene);
	ball.indexScene = indexNewScene;
	Simulation::allBalls.balls.push_back(ball);
}

void NxBall::resetToInitialPose(){
	this->ball->setGlobalPose(this->initialPose);
}

void NxBall::putToSleep(){
	this->ball->putToSleep();
	this->ball->setLinearVelocity(NxVec3(0,0,0));
	this->ball->setAngularVelocity(NxVec3(0,0,0));
}