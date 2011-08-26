#include "NxRobot.h"
#include "Simulation.h"
#include "NxAllRobots.h"
#include "Stream.h"
#include "cooking.h"

NxRobot::NxRobot() : NxVehicle()
{
	idTeam = 1;
	bodyRadius = 87.5;
	wheelsRadius = 80.6;
}

void NxRobot::handleContactPair(NxContactPair& pair, NxU32 robotIndex)
{
	NxContactStreamIterator i(pair.stream);

	while(i.goNextPair())
	{
		NxShape * s = i.getShape(robotIndex); //umas das partes do robo (o robo eh um unico actor com as MESHs: rodas, driblador, corpo)
		NxShape * s1 = i.getShape(1-robotIndex); //corpo que o robo esta colidindo

		while(i.goNextPatch())
		{
			const NxVec3& contactNormal = i.getPatchNormal();

			while(i.goNextPoint())
			{
				//user can also call getPoint() and getSeparation() here

				const NxVec3& contactPoint = i.getPoint();

				//add forces:

				/*//assuming front wheel drive we need to apply a force at the wheels.
				if (s->is(NX_SHAPE_CAPSULE) && s->userData != NULL) {
					//assuming only the wheels of the car are capsules, otherwise we need more checks.
					//this branch can't be pulled out of loops because we have to do a full iteration through the stream

					NxQuat local2global = s->getActor().getGlobalOrientationQuat();
					NxWheel* w = (NxWheel*)s->userData;
					if (!w->getWheelFlag(NX_WF_USE_WHEELSHAPE))
					{
						NxWheel1 * wheel = static_cast<NxWheel1*>(w);
						wheel->contactInfo.otherActor = pair.actors[1-robotIndex];
						wheel->contactInfo.contactPosition = contactPoint;

						wheel->contactInfo.contactPositionLocal = contactPoint;
						wheel->contactInfo.contactPositionLocal -= this->getActor()->getGlobalPosition();
						local2global.inverseRotate(wheel->contactInfo.contactPositionLocal);

						wheel->contactInfo.contactNormal = contactNormal;
						if (wheel->contactInfo.otherActor->isDynamic()) 
						{
							NxVec3 globalV = s->getActor().getLocalPointVelocity(wheel->getWheelPos());
							globalV -= wheel->contactInfo.otherActor->getLinearVelocity();
							local2global.inverseRotate(globalV);
							wheel->contactInfo.relativeVelocity = globalV.x;
							//printf("%2.3f (%2.3f %2.3f %2.3f)\n", wheel->contactInfo.relativeVelocity,
							//	globalV.x, globalV.y, globalV.z);
						} 
						else 
						{
							NxVec3 vel = s->getActor().getLocalPointVelocity(wheel->getWheelPos());
							local2global.inverseRotate(vel);
							wheel->contactInfo.relativeVelocity = vel.x;
							wheel->contactInfo.relativeVelocitySide = vel.z;
						}
						NX_ASSERT(wheel->hasGroundContact());
						//printf(" Wheel %x is touching\n", wheel);
					}
				}*/
				const char* name = s->getName();
				if(name){
					const char* name1 = s1->getName();
					if(name1){
						char* dribblerName = new char[10]; //"Driblador\0"
						dribblerName[9] = 0;
						memcpy(dribblerName, name, strlen(dribblerName));

						//char* kickerName = new char[9]; //"Chutador\0"
						//kickerName[8] = 0;
						//memcpy(kickerName, name, strlen(kickerName));

						char* ballName = new char[5]; //"Bola\0"
						ballName[4] = 0;
						memcpy(ballName, name1, strlen(ballName));

						if(strcmp(dribblerName, "Driblador")==0 && strcmp(ballName, "Bola")==0){
							//NxActor& ball = s1->getActor();
							//ball.addTorque(NxVec3(0,1000,0), NX_IMPULSE);
							//Simulation::flagDribblerContact[
						}
						//else if(strcmp(kickerName, "Chutador")==0 && strcmp(ballName, "Bola")==0){
						//	NxActor& ball = s1->getActor();
						//	ball.addForce(NxVec3(100,0,0), NX_IMPULSE);
						//}

						delete dribblerName;
						//delete kickerName;
						delete ballName;
					}
				}
			}
		}		
	}
	//printf("----\n");
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

void Simulation::buildModelRobot(int indexRobot, int indexScene, int indexTeam)
{
	//Veiculo descricao
	//Body Descricao
	NxActor* robotActor = Simulation::getActorRobot(indexScene, indexRobot);
	//NxBounds3 bodyBounds;
	//robotShapes[0]->getWorldBounds(bodyBounds);
	NxVehicleDesc vehicleDesc;

	vehicleDesc.position				= NxVec3(robotActor->getGlobalPosition());
	vehicleDesc.mass					= 5.;//robotActor->getMass(); //PLUGIN TAH COM PROBLEMA XML ERRADO
	//vehicleDesc.motorForce				= 70000;
	//vehicleDesc.maxVelocity				= 300.f;
	//vehicleDesc.cameraDistance			= 8.0f;
	vehicleDesc.centerOfMass.set(NxVec3(0,0,0));//robotActor->getCMassLocalPosition());
	//vehicleDesc.differentialRatio = 3.42f;
	//vehicleDesc.transmissionEfficiency
	vehicleDesc.actor = robotActor;
	vehicleDesc.actor->setMaxAngularVelocity(6.2);
	vehicleDesc.actor->setMassSpaceInertiaTensor(vehicleDesc.actor->getMassSpaceInertiaTensor()*10.);
	vehicleDesc.actor->setCMassOffsetLocalPose( NxMat34( NxMat33(NxVec3(1,0,0),NxVec3(0,1,0),NxVec3(0,0,1)), NxVec3(0,0,0) ) );
	NxMat34 teste = vehicleDesc.actor->getCMassLocalPose();

	//Motor descricao
	//NxVehicleMotorDesc motorsDesc[4];
	//for(NxU32 i=0;i<4;i++)
	//{
		//motorsDesc[i].setToCorvette();
		//vehicleDesc.motorsDesc.push_back(&motorsDesc[i]);
	//}

	//Roda (Wheel) descricao
	int numberWheels = Simulation::getNumberWheels(indexScene, indexRobot);
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
		wheelDesc[i].wheelRadius = 27.6;
		//wheelDesc[i].wheelWidth = 100;
		wheelDesc[i].wheelSuspension = 0;
		wheelDesc[i].springRestitution = 0;
		wheelDesc[i].springDamping = 0;
		wheelDesc[i].springBias = 0.0f;
		wheelDesc[i].maxBrakeForce = 100;
		wheelDesc[i].frictionToFront = 0.1f;//0.1f;	//TODO: CONFIGURAR PARÂMETRO
		wheelDesc[i].frictionToSide = 0;//0.02f;	//TODO: CONFIGURAR PARÂMETRO
		wheelDesc[i].inverseWheelMass = 0.1;		//TODO: CONFIGURAR PARÂMETRO

		//Angulo das Rodas (Omni)
		NxVec3 wheelPosRel = actorWheel->getGlobalPosition() - robotActor->getGlobalPosition();
		wheelDesc[i].angWheelRelRobot = NxMath::atan2( wheelPosRel.y, wheelPosRel.x );

		vehicleDesc.robotWheels.pushBack(&wheelDesc[i]);
		Simulation::gScenes[indexScene]->releaseActor(*actorWheel);

		//NxU32 flags = NX_WF_BUILD_LOWER_HALF;
		wheelDesc[i].wheelFlags = NX_WF_ACCELERATED | NX_WF_AFFECTED_BY_HANDBRAKE | NX_WF_USE_WHEELSHAPE | NX_WF_BUILD_LOWER_HALF;// |/*NX_WF_STEERABLE_INPUT |*/ flags;
	}

	//Criar robot, vehicle base
	NxRobot* robot = (NxRobot*)NxRobot::createVehicle(Simulation::gScenes[indexScene], &vehicleDesc);
	if(robot){
		robot->setId(indexRobot);
		robot->setIdTeam(indexTeam);
		robot->indexScene = indexScene;

		//Dribbler and Kicker
		for(int i=0; i<robotActor->getNbShapes(); i++){
			NxShape*const* robotShapes = robotActor->getShapes();
			const char* shapeName = robotShapes[i]->getName();
			if(shapeName){
				char* dribblerName = new char[10];//"Driblador\0"
				dribblerName[9] = 0;
				memcpy(dribblerName, shapeName, strlen(dribblerName));
				
				char* kickerName = new char[9];//"Chutador\0"
				kickerName[8] = 0;
				memcpy(kickerName, shapeName, strlen(kickerName));
				
				if(strcmp(dribblerName, "Driblador") == 0){
					robot->dribbler.dribblerShapes.push_back(robotShapes[i]);
				}
				else if(strcmp(kickerName, "Chutador") == 0){
					robot->kicker.kickerShapeDesc = Simulation::copyShapeDesc(robotShapes[i]);
					robotActor->releaseShape(*(robotShapes[i]));
				}
			}
		}

		//Initial Pose
		robot->setInitialPose(robotActor->getGlobalPose());

		//Mudar pose do robo
		//NxQuat q;
		//q.
		//q.fromAngleAxis(180.0f, NxVec3(0.0f, 1.0f, 0.0f));
		//robot->getActor()->setGlobalPose(pose);

		//Release no actor importado do 3ds Max
		//gScenes[0]->releaseActor(*robotActor);
	}
}

void NxRobot::cloneRobot(int indexNewScene, int indexNewRobot, NxVec3 newPosition, int indexNewTeam)
{
	NxRobot* nxRobotSource = Simulation::allRobots.getRobotByIdScene(this->getId(), this->indexScene);

	NxActor* robotActor = Simulation::cloneActor(nxRobotSource->getActor(),indexNewScene);
	//NxBounds3 bodyBounds;
	//robotShapes[0]->getWorldBounds(bodyBounds);
	
	NxVehicleDesc vehicleDesc;
	
	vehicleDesc.position				= NxVec3(robotActor->getGlobalPosition());
	vehicleDesc.mass					= robotActor->getMass();
	//vehicleDesc.motorForce				= 70000;
	//vehicleDesc.maxVelocity				= 300.f;
	//vehicleDesc.cameraDistance			= 8.0f;
	vehicleDesc.centerOfMass.set(robotActor->getCMassLocalPosition());
	//vehicleDesc.differentialRatio = 3.42f;
	//vehicleDesc.transmissionEfficiency
	vehicleDesc.actor = robotActor;

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
		//NxActor* wheelModel = Simulation::getActorWheel(indexSourceScene,indexNewRobot,i);
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
		wheelDesc[i].frictionToFront = 0.1f;//0.1f;
		wheelDesc[i].frictionToSide = 0;//0.02f;//
		wheelDesc[i].inverseWheelMass = wheelShape->getInverseWheelMass(); //TODO: CONFIGURAR PARÂMETRO

		//Angulo das Rodas (Omni)
		wheelDesc[i].angWheelRelRobot = ((NxWheel2*)wheel)->angWheelRelRobot;
		
		vehicleDesc.robotWheels.pushBack(&wheelDesc[i]);
	}

	//Criar robot, vehicle base
	NxRobot* robot = (NxRobot*)NxRobot::createVehicle(Simulation::gScenes[indexNewScene], &vehicleDesc);
	//NxRobot* robot = (NxRobot*)NxRobot::createVehicle(gScenes[indexSourceScene], &vehicleDesc);
	robot->setId(indexNewRobot);
	robot->setIdTeam(indexNewTeam);
	robot->indexScene = indexNewScene;
	robot->bodyRadius = nxRobotSource->bodyRadius;

	//Dribbler and Kicker
	NxShape*const* robotShapes = robotActor->getShapes();
	for(int i=0; i<robotActor->getNbShapes(); i++){
		const char* shapeName = robotShapes[i]->getName();
		if(shapeName){
			char* dribblerName = new char[10];//"Driblador\0"
			dribblerName[9] = 0;
			memcpy(dribblerName, shapeName, strlen(dribblerName));

			char* kickerName = new char[9];//"Chutador\0"
			kickerName[8] = 0;
			memcpy(kickerName, shapeName, strlen(kickerName));

			if(strcmp(dribblerName, "Driblador") == 0){
				robot->dribbler.dribblerShapes.push_back(robotShapes[i]);
			}
		}
	}
	robot->kicker.kickerShapeDesc = new NxBoxShapeDesc();
	NxShapeDesc* shapeDesc = nxRobotSource->kicker.kickerShapeDesc;
	robot->kicker.kickerShapeDesc->localPose = shapeDesc->localPose;
	((NxBoxShapeDesc*)(robot->kicker.kickerShapeDesc))->dimensions = ((NxBoxShapeDesc*)shapeDesc)->dimensions;

	//Initial Pose
	robot->setInitialPose(robotActor->getGlobalPose());

	//Transladando o robo
	robot->getActor()->setGlobalPosition(newPosition);

	//Criando e Zerando matrizes para controle
	int diff = robot->getId() - Simulation::lastWheelSpeeds[indexNewScene].size();
	if(diff>=0){
		for(int i=0; i<diff+1; i++){
			NxReal* wheels;
			int nbWheels = robot->getNbWheels();
			wheels = new NxReal[nbWheels];
			for(int j=0; j<nbWheels; j++)
			{
				wheels[j]=0;
			}
			Simulation::lastWheelSpeeds[indexNewScene].push_back(wheels);
			Simulation::lastDesiredWheelSpeeds[indexNewScene].push_back(wheels);
			Simulation::lastWheelTorques[indexNewScene].push_back(wheels);
		}
	}
	else{
		NxReal* wheels;
		int nbWheels = robot->getNbWheels();
		wheels = new NxReal[nbWheels];
		for(int j=0; j<nbWheels; j++)
		{
			wheels[j]=0;
		}
		Simulation::lastWheelSpeeds[indexNewScene][robot->getId()] = wheels;
		Simulation::lastDesiredWheelSpeeds[indexNewScene][robot->getId()] = wheels;
		Simulation::lastWheelTorques[indexNewScene][robot->getId()] = wheels;
	}
}

void NxRobot::setGlobalPosition(NxVec3 position){
	//get relative distances from body
	//NxVec3 bodyPos = this->getBodyPos();
	//NxVec3 dribblerPos = this->dribbler.dribbler->getGlobalPosition();
	//NxVec3 kickerPos = this->kicker.kicker->getGlobalPosition();

	this->getActor()->setGlobalPosition(position);
}

void NxRobot::setGlobalOrientation(NxMat33 orientation){
	this->getActor()->setGlobalOrientation(orientation);
}

void NxRobot::putToSleep(){
	//for(int i=0; i<this->getNbWheels(); i++){
	//	((NxWheel2*)(this->getWheel(i)))->getWheelShape()->setMo
	//}
	this->getActor()->putToSleep();
	this->getActor()->setLinearVelocity(NxVec3(0,0,0));
	this->getActor()->setAngularVelocity(NxVec3(0,0,0));
}

void NxRobot::resetToInitialPose(){
	this->getActor()->setGlobalPose(this->getInitialPose());
}