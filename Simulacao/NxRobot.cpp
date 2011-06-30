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

NxRobot::NxRobot():NxVehicle()
{
	idTeam = 1;
	bodyRadius = 90;
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

/////////////////////////////////////////////////////////CLASS SIMULATION/////////////////////////////////////
/////////////////////////////////////////////////////////CLASS SIMULATION/////////////////////////////////////
/////////////////////////////////////////////////////////CLASS SIMULATION/////////////////////////////////////

/**
* 
*/
void Simulation::buildModelRobotWithDesc(int indexRobot, int indexScene)
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
		//NxActor* wheelModel = Simulation::getActorWheel(indexScene,indexRobot,i);
		//NxActorDesc wheelActorDesc;
		//wheelModel->saveToDesc(wheelActorDesc);
		//Simulation::gScenes[0]->releaseActor(*wheelModel);
		NxActor* actorWheel = Simulation::getActorWheel(indexScene,indexRobot,i);//wheelModel;//Simulation::gScenes[0]->createActor(wheelActorDesc);
		//NxShape*const* wheelShapes = actorWheel->getShapes();
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

		wheelDesc[i].wheelOrientation = actorWheel->getGlobalOrientation();
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
	NxActor* actorDribbler = getActorDribbler(indexScene, indexRobot);
	actorDribbler->setMaxAngularVelocity(100);

	//TODO: Incluir Chutador descricao.
	NxActor* kickerActor = getActorKicker(indexScene, indexRobot);
	kickerActor->setMaxAngularVelocity(100);

	//Criar robot, vehicle base
	NxRobot* robot = (NxRobot*)NxRobot::createVehicle(gScenes[indexScene], &vehicleDesc);
	robot->setId(indexRobot);
	robot->bodyRadius = 90;
	robot->dribbler.dribbler = actorDribbler;
	robot->kicker.kicker = kickerActor;

	//Joints
	robot->joints = Simulation::getJoints(indexScene, indexRobot);

	//Mudar pose do robo
	//NxQuat q;
	//q.
	//q.fromAngleAxis(180.0f, NxVec3(0.0f, 1.0f, 0.0f));
	//robot->getActor()->setGlobalPose(pose);

	//Release no actor importado do 3ds Max
	//gScenes[0]->releaseActor(*robotActor);
}

void Simulation::cloneRobot(int indexRobot, int indexScene, int indexRobotSource, NxVec3 newPosition)
{
	NxRobot* nxRobotSource = NxAllRobots::getRobotById(indexRobotSource);
	//Body
	NxActor* robotActor = Simulation::cloneActor(nxRobotSource->getActor());
	NxShape*const* robotShapes = robotActor->getShapes();
	//NxBounds3 bodyBounds;
	//robotShapes[0]->getWorldBounds(bodyBounds);

	NxVehicleDesc vehicleDesc;
	for(int i=0; i<nxRobotSource->getActor()->getNbShapes()-nxRobotSource->getNbWheels(); i++)
	{
		NxConvexShapeDesc convexShapeDesc;
		nxRobotSource->getActor()->getShapes()[i]->isConvexMesh()->saveToDesc(convexShapeDesc);
		vehicleDesc.robotShapes.push_back(&convexShapeDesc);
	}

	vehicleDesc.position				= NxVec3(robotActor->getGlobalPosition());
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

	//Roda (Wheel) descricao
	int numberWheels = nxRobotSource->getNbWheels();
	NxWheelDesc* wheelDesc = new NxWheelDesc[numberWheels];
	for(NxU32 i=0;i<numberWheels;i++)
	{
		//NxActor* wheelModel = Simulation::getActorWheel(indexScene,indexRobot,i);
		//NxActorDesc wheelActorDesc;
		//wheelModel->saveToDesc(wheelActorDesc);
		//Simulation::gScenes[0]->releaseActor(*wheelModel);
		
		//NxShape*const* wheelShapes = actorWheel->getShapes();
		//NxBounds3 wheelBounds;
		//wheelShapes[0]->getWorldBounds(wheelBounds);

		const NxWheel* wheel = nxRobotSource->getWheel(i);
		NxWheelShape* wheelShape = ((NxWheel2*)wheel)->getWheelShape();
		//wheelDesc[i].wheelApproximation = 10;
		wheelDesc[i].wheelOrientation = wheelShape->getGlobalOrientation();
		wheelDesc[i].position.set(wheelShape->getGlobalPosition()-robotActor->getGlobalPosition());
		//wheelDesc[i].position.z = 0;
		wheelDesc[i].id = i;
		wheelDesc[i].wheelFlags = ((NxWheel*)wheel)->getWheelFlags();
		wheelDesc[i].wheelRadius = wheel->getRadius();
		//wheelDesc[i].wheelWidth = 100;
		wheelDesc[i].wheelSuspension = wheelShape->getSuspensionTravel();
		wheelDesc[i].springRestitution = 0;
		wheelDesc[i].springDamping = 0;
		wheelDesc[i].springBias = 0.0f;
		wheelDesc[i].maxBrakeForce = 100;
		wheelDesc[i].frictionToFront = 0.1f;
		wheelDesc[i].frictionToSide = 0;
		wheelDesc[i].inverseWheelMass = wheelShape->getInverseWheelMass(); //TODO: CONFIGURAR PARÂMETRO

		//Angulo das Rodas (Omni)
		wheelDesc[i].angWheelRelRobot = ((NxWheel2*)wheel)->angWheelRelRobot;
		
		vehicleDesc.robotWheels.pushBack(&wheelDesc[i]);
	}

	//TODO: Incluir Driblador descricao.
	NxActor* actorDribbler = cloneActor(nxRobotSource->dribbler.dribbler);
	actorDribbler->setMaxAngularVelocity(100);

	//TODO: Incluir Chutador descricao.
	NxActor* kickerActor = cloneActor(nxRobotSource->kicker.kicker);
	kickerActor->setMaxAngularVelocity(100);

	//Criar robot, vehicle base
	NxRobot* robot = (NxRobot*)NxRobot::createVehicle(gScenes[indexScene], &vehicleDesc);
	//NxRobot* robot = (NxRobot*)NxRobot::createVehicle(gScenes[indexScene], &vehicleDesc);
	robot->setId(indexRobot);
	robot->setIdTeam(nxRobotSource->getIdTeam());
	robot->bodyRadius = nxRobotSource->bodyRadius;
	robot->kicker.kicker = kickerActor;
	robot->dribbler.dribbler = actorDribbler;

	//Joints
	for(int i=0; i<nxRobotSource->joints.size(); i++)
	{	
		NxActor* actor1;
		NxActor* actor2;
		robot->joints.push_back(cloneJoint(nxRobotSource->joints[i]));
		robot->joints[i]->getActors(&actor1, &actor2);
		const char* name1 = actor1->getName();
		const char* name2 = actor2->getName();
		const char* bodyName = robot->getActor()->getName();
		const char* dribblerName = robot->dribbler.dribbler->getName();
		const char* kickerName = robot->kicker.kicker->getName();

		if( strcmp( name1, bodyName )==0 ){
			actor1 = robot->getActor();
		}
		else if( strcmp( name2, bodyName )==0 ) {
			actor2 = robot->getActor();
		}
		else if( strcmp( name1, dribblerName )==0 ){
			actor1 = robot->dribbler.dribbler;
		}
		else if( strcmp( name2, dribblerName )==0 ){
			actor2 = robot->dribbler.dribbler;
		}
		else if( strcmp( name1, kickerName )==0 ){
			actor1 = robot->kicker.kicker;
		}
		else if( strcmp( name2, kickerName )==0 ){
			actor2 = robot->kicker.kicker;
		}
	}

	//Transladando os componentes do robo
	robot->kicker.kicker->setGlobalPosition(robot->kicker.kicker->getGlobalPosition() - robot->getActor()->getGlobalPosition() + newPosition);
	robot->dribbler.dribbler->setGlobalPosition(robot->dribbler.dribbler->getGlobalPosition() - robot->getActor()->getGlobalPosition() + newPosition);
	robot->getActor()->setGlobalPosition(newPosition);
}

NxActor* Simulation::cloneActor(NxActor* actorSource)
{
	NxActorDesc actorDesc;
	actorSource->saveToDesc(actorDesc);

	//// Create body
	NxBodyDesc bodyDesc;
	actorSource->saveBodyToDesc(bodyDesc);
	actorDesc.body = &bodyDesc;

	for(int i=0; i<actorSource->getNbShapes(); i++)
	{
		NxShapeType type = (actorSource->getShapes())[i]->getType();
		if(type==NxShapeType::NX_SHAPE_BOX){
			NxBoxShapeDesc boxDesc;
			(actorSource->getShapes())[i]->isBox()->saveToDesc(boxDesc);
			actorDesc.shapes.push_back(&boxDesc);
		}
		else if(type==NxShapeType::NX_SHAPE_CONVEX){
			NxConvexShapeDesc convexShapeDesc;
			//static NxConvexMeshDesc convexMeshDesc;
			(actorSource->getShapes())[i]->isConvexMesh()->saveToDesc(convexShapeDesc);
					
			//MemoryWriteBuffer buf;
			//bool status = CookConvexMesh(convexMeshDesc, buf);
			//if(status){
			//	convexShapeDesc.meshData = gPhysicsSDK->createConvexMesh(MemoryReadBuffer(buf.data);
				actorDesc.shapes.push_back(&convexShapeDesc);
			//}
		}
	}

	return gScenes[gCurrentScene]->createActor(actorDesc);
}

NxJoint* Simulation::cloneJoint(NxJoint* jointSource){
	NxJoint* joint;
	
	NxJointType type = jointSource->getType();
	if(type==NxJointType::NX_JOINT_REVOLUTE){
		
	}
	else if(type==NxJointType::NX_JOINT_D6){
		NxD6JointDesc d6JointDesc;
		jointSource->isD6Joint()->saveToDesc(d6JointDesc);
		joint = gScenes[gCurrentScene]->createJoint(d6JointDesc);
	}
	
	return joint;
}