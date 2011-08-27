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
	//velocidade maxima permitida segundo as rule 2010 (10m/s)
	//A bola pode atingir velocidade maior pq tem o caso de esta sendo usada pelo driblador, mas a principio consideremos isso
	ball.ball->setMaxAngularVelocity(10000./21.5);
	//0.031 medido da bola do lab
	//46g a bola da rules 2010
	ball.ball->setMass(0.031); //PLUGIN TAH COM PROBLEMA XML ERRADO 
	//float teste = ball.ball->getAngularDamping();
	//ball.ball->setAngularDamping(0.5);
	//ball.ball->setCMassOffsetGlobalPosition(NxVec3(0,0,0));
	//ball.ball->setLinearDamping(0.5);
	//ball.ball->setMassSpaceInertiaTensor(ball.ball->getMassSpaceInertiaTensor()*10.);
	//ball.ball->get
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