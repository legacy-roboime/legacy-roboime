#include "Simulation.h"

#include "NxVehicle.h"
#include "NxAllVehicles.h"
#include "Stream.h"
#include "cooking.h"

class MyContactReport : public NxUserContactReport
{
public:
	virtual void  onContactNotify(NxContactPair& pair, NxU32 events)
	{
		NxI32 robotIndex = -1;
		NxAllVehicles::handlePair(pair, events);
		
	}

}	static robotContactReportObj;

static NxUserContactReport * robotContactReport = &robotContactReportObj;

/**
* 
*/
void Simulation::createRobotWithDesc(int indexRobot)
{
	//Veiculo descricao
	NxActor* robotActor = Simulation::getActorRobot(0,indexRobot);
	NxShape*const* robotShapes = robotActor->getShapes();
	NxU32 nShapes = robotActor->getNbShapes();

	NxVehicleDesc vehicleDesc;
	NxConvexShapeDesc robotShape[1];
	if(robotShapes)
	{
		static NxConvexMeshDesc convexMesh;
		robotShapes[0]->isConvexMesh()->getConvexMesh().saveToDesc(convexMesh);

		MemoryWriteBuffer buf;
		bool status = CookConvexMesh(convexMesh, buf);
		if(status)
		{
			robotShape[0].meshData = gPhysicsSDK->createConvexMesh(MemoryReadBuffer(buf.data));
			vehicleDesc.robotShapes.pushBack(&robotShape[0]);
		}
	}

	vehicleDesc.position				= NxVec3(robotActor->getGlobalPosition());
	vehicleDesc.position.z				+= 35;
	vehicleDesc.mass					= robotActor->getMass();
	//vehicleDesc.motorForce				= 70000;
	//vehicleDesc.maxVelocity				= 300.f;
	//vehicleDesc.cameraDistance			= 8.0f;
	vehicleDesc.centerOfMass.set(robotActor->getCMassLocalPosition());
	//vehicleDesc.differentialRatio = 3.42f;
	//vehicleDesc.transmissionEfficiency
	vehicleDesc.bodyActor = robotActor;

	//Motor descricao
	//NxVehicleMotorDesc motorsDesc[4];
	//for(NxU32 i=0;i<4;i++)
	//{
		//motorsDesc[i].setToCorvette();
		//vehicleDesc.motorsDesc.push_back(&motorsDesc[i]);
	//}

	//Roda descricao
	NxWheelDesc wheelDesc[4];
	for(NxU32 i=0;i<4;i++)
	{
		//Para exportar modelo da roda do 3ds Max
		//	NxWhee
		//wheelDesc[i]
		//robot1Shapes[0]->isConvexMesh()->getConvexMesh().saveToDesc(convexMesh);
		//NxWheelShape* wheelShape = (NxWheelShape*)wheel;
		//NxTriangleMeshDesc meshDesc = *((NxTriangleMeshDesc*)(mesh->userData));
		//robot1Shapes[0]->isWheel()->

		//wheelDesc[i].wheelApproximation = 10;
		wheelDesc[i].wheelFlags |= NX_WF_BUILD_LOWER_HALF;
		wheelDesc[i].wheelRadius = 20;
		//wheelDesc[i].wheelWidth = 100;
		wheelDesc[i].wheelSuspension = 0;
		wheelDesc[i].springRestitution = 0;
		wheelDesc[i].springDamping = 0;
		wheelDesc[i].springBias = 0.0f;
		wheelDesc[i].maxBrakeForce = 100;
		wheelDesc[i].frictionToFront = 0.1f;
		wheelDesc[i].frictionToSide = 0;
		wheelDesc[i].wheelFlags |= NX_WF_USE_WHEELSHAPE;
		vehicleDesc.robotWheels.pushBack(&wheelDesc[i]);
	}

	NxReal robotRadius = 90;
	NxReal angle1 = 33./180.;
	NxReal angle2 = 45./180.;
	wheelDesc[0].position.set(	robotRadius*NxMath::cos( NxPi*angle1 ),		robotRadius*NxMath::sin( NxPi*angle1 ),		0);
	wheelDesc[1].position.set(	-robotRadius*NxMath::cos( NxPi*angle1 ),	robotRadius*NxMath::sin( NxPi*angle1 ),		0);
	wheelDesc[2].position.set(	-robotRadius*NxMath::cos( NxPi*angle2 ),	-robotRadius*NxMath::sin( NxPi*angle2 ),	0);
	wheelDesc[3].position.set(	robotRadius*NxMath::cos( NxPi*angle2 ),		-robotRadius*NxMath::sin( NxPi*angle2 ),	0);
	NxU32 flags = NX_WF_BUILD_LOWER_HALF;
	wheelDesc[0].wheelFlags |= NX_WF_ACCELERATED | /*NX_WF_STEERABLE_INPUT |*/ flags;
	wheelDesc[1].wheelFlags |= NX_WF_ACCELERATED | /*NX_WF_STEERABLE_INPUT |*/ flags;
	wheelDesc[2].wheelFlags |= NX_WF_ACCELERATED | /*NX_WF_AFFECTED_BY_HANDBRAKE |*/ flags;
	wheelDesc[3].wheelFlags |= NX_WF_ACCELERATED | /*NX_WF_AFFECTED_BY_HANDBRAKE |*/ flags;

	//Driblador descricao. O driblador funcionará como uma roda.
	NxWheelDesc dribblerDesc;
	dribblerDesc.wheelApproximation = 10;
	dribblerDesc.wheelFlags |= NX_WF_BUILD_LOWER_HALF;
	dribblerDesc.wheelRadius = 10;
	dribblerDesc.wheelWidth = 50;
	dribblerDesc.wheelSuspension = 0;
	dribblerDesc.springRestitution = 0;
	dribblerDesc.springDamping = 0;
	dribblerDesc.springBias = 0.0f;
	dribblerDesc.maxBrakeForce = 100;
	dribblerDesc.frictionToFront = 0.1f;
	dribblerDesc.frictionToSide = 0;
	dribblerDesc.wheelFlags |= NX_WF_USE_WHEELSHAPE;
	vehicleDesc.robotWheels.pushBack(&dribblerDesc);
	dribblerDesc.position.set(	0,		robotRadius+10,		30);
	dribblerDesc.wheelFlags |= NX_WF_ACCELERATED | /*NX_WF_STEERABLE_INPUT |*/ flags;

	//Criar veiculo
	NxVehicle* vehicle = NxVehicle::createVehicle(gScenes[0], &vehicleDesc);

	//Mudar pose do robo
	//NxQuat q;
	//q.fromAngleAxis(180.0f, NxVec3(0.0f, 1.0f, 0.0f));
	//vehicle->getActor()->setGlobalOrientationQuat(q);

	//Release no actor importado do 3ds Max
	//gScenes[0]->releaseActor(*robotActor);
}