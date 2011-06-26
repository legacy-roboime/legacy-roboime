#include "Simulation.h"
#include "NxRobot.h"

#include "NxAllRobots.h"
#include "Stream.h"
#include "cooking.h"

/////////////////////////////////////////////////////////CLASS MyContactReport/////////////////////////////////////
/////////////////////////////////////////////////////////CLASS MyContactReport/////////////////////////////////////
/////////////////////////////////////////////////////////CLASS MyContactReport/////////////////////////////////////
class MyContactReport : public NxUserContactReport
{
public:
	virtual void  onContactNotify(NxContactPair& pair, NxU32 events)
	{
		NxI32 robotIndex = -1;
		NxAllRobots::handlePair(pair, events);
		
	}

}	static robotContactReportObj;

static NxUserContactReport * robotContactReport = &robotContactReportObj;

/////////////////////////////////////////////////////////CLASS ROBOT/////////////////////////////////////
/////////////////////////////////////////////////////////CLASS ROBOT/////////////////////////////////////
/////////////////////////////////////////////////////////CLASS ROBOT/////////////////////////////////////

/**
* 
*/
void Simulation::createRobotWithDesc(int indexRobot, int indexScene)
{
	//Veiculo descricao
	//Body Descricao
	NxActor* robotActor = Simulation::getActorRobot(indexScene, indexRobot);
	NxShape*const* robotShapes = robotActor->getShapes();
	//NxBounds3 bodyBounds;
	//robotShapes[0]->getWorldBounds(bodyBounds);

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
	vehicleDesc.mass					= 3;//robotActor->getMass();
	//vehicleDesc.motorForce				= 70000;
	//vehicleDesc.maxVelocity				= 300.f;
	//vehicleDesc.cameraDistance			= 8.0f;
	vehicleDesc.centerOfMass.set(NxVec3(0,0,0));//robotActor->getCMassLocalPosition());
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

	//Roda (Wheel) descricao
	int numberWheels = getNumberWheels(indexScene, indexRobot);
	NxWheelDesc* wheelDesc = new NxWheelDesc[numberWheels];
	for(NxU32 i=0;i<numberWheels;i++)
	{
		NxActor* actorWheel = getActorWheel(indexScene,indexRobot,i);
		NxShape*const* wheelShapes = actorWheel->getShapes();
		//NxBounds3 wheelBounds;
		//wheelShapes[0]->getWorldBounds(wheelBounds);

		//Para exportar modelo da roda do 3ds Max
		//	NxWhee
		//wheelDesc[i]
		//robot1Shapes[0]->isConvexMesh()->getConvexMesh().saveToDesc(convexMesh);
		//NxWheelShape* wheelShape = (NxWheelShape*)wheel;
		//NxTriangleMeshDesc meshDesc = *((NxTriangleMeshDesc*)(mesh->userData));
		//robot1Shapes[0]->isWheel()->

		//wheelDesc[i].wheelApproximation = 10;
		NxMat33 mat33 = robotActor->getGlobalOrientation();

		wheelDesc[i].wheelOrientation = actorWheel->getGlobalOrientation();//NxMat33(wheelOrientation.getColumn(2),wheelOrientation.getColumn(0),wheelOrientation.getColumn(1));
		wheelDesc[i].position.set(actorWheel->getGlobalPosition()-robotActor->getGlobalPosition());
		//wheelDesc[i].position.z = 0;
		wheelDesc[i].id = i;
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
		wheelDesc[i].inverseWheelMass = 0.1; //TODO: CONFIGURAR PARÂMETRO
		wheelDesc[i].wheelFlags |= NX_WF_USE_WHEELSHAPE;

		//Angulo das Rodas (Omni)
		NxVec3 wheelPosRel = actorWheel->getGlobalPosition() - robotActor->getGlobalPosition();
		wheelDesc[i].angWheelRelRobot = NxMath::atan2( wheelPosRel.y, wheelPosRel.x );

		vehicleDesc.robotWheels.pushBack(&wheelDesc[i]);
		Simulation::gScenes[indexScene]->releaseActor(*actorWheel);

		NxU32 flags = NX_WF_BUILD_LOWER_HALF;
		wheelDesc[i].wheelFlags |= NX_WF_ACCELERATED | /*NX_WF_STEERABLE_INPUT |*/ flags;
	}

	//Orientacao das rodas (robo de 4 rodas)
	/*float angle1 = NxPi * 45. / 180.;
	float angle2 = NxPi * 33. / 180.;
	NxMat33 mat1 = NxMat33(NxVec3(1,0,0),NxVec3(0,1,0),NxVec3(0,0,1));
	NxMat33 mat2 = NxMat33(NxVec3(1,0,0),NxVec3(0,1,0),NxVec3(0,0,1));
	mat1.rotX(NxPi*0.5);
	mat2.rotY(NxPi + angle1);
	wheelDesc[0].wheelOrientation = mat1*mat2;

	mat1 = NxMat33(NxVec3(1,0,0),NxVec3(0,1,0),NxVec3(0,0,1));
	mat2 = NxMat33(NxVec3(1,0,0),NxVec3(0,1,0),NxVec3(0,0,1));
	mat1.rotX(NxPi*0.5);
	mat2.rotY(-angle1);
	wheelDesc[1].wheelOrientation = mat1*mat2;

	mat1 = NxMat33(NxVec3(1,0,0),NxVec3(0,1,0),NxVec3(0,0,1));
	mat2 = NxMat33(NxVec3(1,0,0),NxVec3(0,1,0),NxVec3(0,0,1));
	mat1.rotX(NxPi*0.5);
	mat2.rotY(2*NxPi - angle);
	wheelDesc[2].wheelOrientation = mat1*mat2;

	mat1 = NxMat33(NxVec3(1,0,0),NxVec3(0,1,0),NxVec3(0,0,1));
	mat2 = NxMat33(NxVec3(1,0,0),NxVec3(0,1,0),NxVec3(0,0,1));
	mat1.rotX(NxPi*0.5);
	mat2.rotY(3*NxPi*0.25);
	wheelDesc[3].wheelOrientation = mat1*mat2;*/

	//TODO: Incluir Driblador descricao.
	//NxActor* actorDribbler = getActorDribbler(indexScene, indexRobot);
	//actorDribbler->setMaxAngularVelocity(100);

	//TODO: Incluir Chutador descricao.
	//NxActor* kickerActor = getActorKicker(indexScene, indexRobot);
	//kickerActor->setMaxAngularVelocity(100);

	//Criar robot, vehicle base
	NxRobot* robot = (NxRobot*)NxRobot::createVehicle(gScenes[indexScene], &vehicleDesc);
	//NxRobot* robot = (NxRobot*)NxRobot::createVehicle(gScenes[indexScene], &vehicleDesc);
	//robot->initDefault();
	robot->setId(indexRobot);

	//Mudar pose do robo
	//NxQuat q;
	//q.fromAngleAxis(180.0f, NxVec3(0.0f, 1.0f, 0.0f));
	//vehicle->getActor()->setGlobalOrientationQuat(q);

	//Release no actor importado do 3ds Max
	//gScenes[0]->releaseActor(*robotActor);
}

NxRobot::NxRobot():NxVehicle()
{
	idTeam = 1;
	robotRadius = 90;
	angleRelativeWheel1 = NxPi * 33./180.;//NxPi*33./180.;
	angleRelativeWheel2 = NxPi * 33./180.;//NxPi*33./180.;
	angleRelativeWheel3 = NxPi * 45./180.;//NxPi*45./180.;
	angleRelativeWheel4 = NxPi * 45./180.;//NxPi*45./180.;
}

int NxRobot::getId()
{
	return id;
}

void NxRobot::setId(int id)
{
	this->id = id;
}

int NxRobot::getIdTeam()
{
	return idTeam;
}

void NxRobot::setIdTeam(int idTeam)
{
	this->idTeam = idTeam;
}