#include "NxKicker.h"
#include "Simulation.h"

NxKicker::NxKicker(Simulation* simulation)
{
	this->simulation = simulation;
}

NxKicker::~NxKicker(void)
{
	if(kickerShapeDesc)
		delete kickerShapeDesc;
}

void NxKicker::controlKicker( float kickerSpeed, NxRobot* robot )
{
	//TODO: implementar o controlador
	if(robot && kickerSpeed>0){
		NxBall* ball = simulation->gScenes[robot->indexScene]->ball;
		NxShape* const* ballShapes = ball->ball->getShapes();

		const NxBoxShapeDesc* kShapeDesc = (NxBoxShapeDesc*)this->kickerShapeDesc;

		NxReal angle = robot->getAngle2DFromVehicle();
		NxVec3 dir = NxVec3(cos(angle), sin(angle), 0); 
		
		NxVec3 posRel = dir;
		posRel.z = kShapeDesc->localPose.t.z;
		qreal distance = kShapeDesc->localPose.t.x;
		posRel.x *= distance;
		posRel.y *= distance;

		NxBox box = NxBox(posRel + robot->getActor()->getGlobalPosition(), kShapeDesc->dimensions,  robot->getActor()->getGlobalOrientation());
		
		NxSphere sphere = NxSphere(ball->ball->getGlobalPosition(), ballShapes[0]->isSphere()->getRadius());

		float min_dist;

		NxVec3 normal;

		NxUtilLib* gUtilLib = NxGetUtilLib();
		if(gUtilLib->NxSweepBoxSphere(box, sphere, -dir, 24.3, min_dist, normal)){ // Nao sei pq tem q ser o vetor -dir pra da certo pela logica eh NxVec3(cos(angle), sin(angle), 0)
			ball->ball->addForce((-normal)*kickerSpeed*150., NX_IMPULSE); //TODO: VERIFICAR A FOR�A OU IMPULSO
		}
	}
}
