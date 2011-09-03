#include "NxKicker.h"
#include "Simulation.h"

NxKicker::NxKicker(void)
{
}

NxKicker::~NxKicker(void)
{
	delete kickerShapeDesc;
}

void NxKicker::controlKicker( float kickerSpeed, NxRobot* robot )
{
	//TODO: implementar o controlador
	if(robot && kickerSpeed>0){
		NxBall* ball = Simulation::gScenes[robot->indexScene]->ball;
		NxShape* const* ballShapes = ball->ball->getShapes();

		NxBoxShapeDesc* kickerShapeDesc = (NxBoxShapeDesc*)this->kickerShapeDesc;
		
		NxBox box = NxBox(kickerShapeDesc->localPose.t + robot->getActor()->getGlobalPosition(), kickerShapeDesc->dimensions,  robot->getActor()->getGlobalOrientation() * kickerShapeDesc->localPose.M);
		
		NxSphere sphere = NxSphere(ball->ball->getGlobalPosition(), ballShapes[0]->isSphere()->getRadius());
		
		NxReal angle = robot->getAngle2DFromVehicle();
		NxVec3 dir = NxVec3(-cos(angle), -sin(angle), 0); // A orientacao do chutador tah invertida 180 graus em relacao a do robo

		float min_dist;

		NxVec3 normal;

		NxUtilLib* gUtilLib = NxGetUtilLib();
		if(gUtilLib->NxSweepBoxSphere(box, sphere, dir, 50, min_dist, normal)){
			ball->ball->addForce(NxVec3(kickerSpeed*cos(angle)*150., kickerSpeed*sin(angle)*150., 0), NX_IMPULSE); //TODO: VERIFICAR A FORÇA OU IMPULSO
		}
	}
}
