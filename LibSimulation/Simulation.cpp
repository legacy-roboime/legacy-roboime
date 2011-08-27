#include "Simulation.h"
#include "SimulationView.h"

bool Simulation::gPause = false;
bool Simulation::gSave = false;
int	Simulation::gLoad = 2;//0;
bool Simulation::gClear = false;

QMutex Simulation::mutex;

NxPhysicsSDK *Simulation::gPhysicsSDK = 0;
//NxArray<NxScene1*> Simulation::gScenes = NxArray<NxScene1*>();
int Simulation::nbExistScenes = 1;
NxScene1 *Simulation::gScenes[gMaxScenes] = { 0 };
NxU32 Simulation::gBaseScene = 0;
NxVec3 Simulation::gDefaultGravity = NxVec3(0.0f, 0.0f, - 9.81f);
UserAllocator *Simulation::gMyAllocator = NULL;
ErrorStream Simulation::gErrorStream = ErrorStream();
MyUserNotify Simulation::gUserNotify = MyUserNotify();
timeval Simulation::timeLastSimulate;

std::vector<std::vector<NxReal*>> Simulation::lastWheelSpeeds = std::vector<std::vector<NxReal*>>();
std::vector<std::vector<NxReal*>> Simulation::lastDesiredWheelSpeeds = std::vector<std::vector<NxReal*>>();
std::vector<std::vector<NxReal*>> Simulation::lastWheelTorques = std::vector<std::vector<NxReal*>>();
float Simulation::timeStep = 1./60.;//15./1000.;//
NxAllRobots Simulation::allRobots = NxAllRobots();
NxAllBalls Simulation::allBalls =  NxAllBalls();
NxAllFields Simulation::allFields =  NxAllFields();
NxArray<NxUserContactReport *> Simulation::robotContactReport = NxArray<NxUserContactReport *>();
NxArray<bool> Simulation::flagDribblerContact = NxArray<bool>();

/**
* Método do PhysX
*/
/*const char* getNxSDKCreateError(const NxSDKCreateError& errorCode) 
{
switch(errorCode) 
{
case NXCE_NO_ERROR: return "NXCE_NO_ERROR";
case NXCE_PHYSX_NOT_FOUND: return "NXCE_PHYSX_NOT_FOUND";
case NXCE_WRONG_VERSION: return "NXCE_WRONG_VERSION";
case NXCE_DESCRIPTOR_INVALID: return "NXCE_DESCRIPTOR_INVALID";
case NXCE_CONNECTION_ERROR: return "NXCE_CONNECTION_ERROR";
case NXCE_RESET_ERROR: return "NXCE_RESET_ERROR";
case NXCE_IN_USE_ERROR: return "NXCE_IN_USE_ERROR";
default: return "Unknown error";
}
};*/

/**
* Método do PhysX
*/
NX_INLINE bool isProcessorBigEndian()
{
	union EndianUnion
	{
		NxU8 bytes[4];
		NxU32 dword;
	};

	volatile EndianUnion val;

	val.dword = 1;

	return val.bytes[3] != 0;

}

Simulation::Simulation(void)
{
}

Simulation::~Simulation(void)
{
	//~ dos ponteiros do PhsyX em ReleaseNX
	//delete gPhysicsSDK;
	//delete gScenes;
	//delete gMyAllocator;

	//ReleaseNx executa a liberacao de memoria

	//delete outputfile;
}

void Simulation::releaseScene(NxScene &scene)
{
	gPhysicsSDK->releaseScene(scene);
}
//==================================================================================
void Simulation::CreateCube(const NxVec3 &pos, int size, const NxVec3 *initial_velocity)
{
	if (gScenes[SimulationView::indexRenderScene])
	{
		// Create body
		NxBodyDesc BodyDesc;
		BodyDesc.angularDamping = 0.5f;
		//	BodyDesc.maxAngularVelocity	= 10.0f;
		if (initial_velocity)
		{
			BodyDesc.linearVelocity =  *initial_velocity;
		}

		NxBoxShapeDesc BoxDesc;
		BoxDesc.dimensions = NxVec3(float(size), float(size), float(size));

		NxActorDesc ActorDesc;
		ActorDesc.shapes.pushBack(&BoxDesc);
		ActorDesc.body = &BodyDesc;
		ActorDesc.density = 10.0f;
		ActorDesc.globalPose.t = pos;
		gScenes[SimulationView::indexRenderScene]->createActor(ActorDesc)->userData = (void*)size;
	}
}

//==================================================================================
void Simulation::CreateStack(int size)
{
	float CubeSize = 2.0f;
	//	float Spacing = 0.01f;
	float Spacing = 0.0001f;
	NxVec3 Pos(0.0f, CubeSize, 0.0f);
	float Offset =  - size *(CubeSize *2.0f + Spacing) *0.5f;
	while (size)
	{
		for (int i = 0; i < size; i++)
		{
			Pos.x = Offset + float(i)*(CubeSize *2.0f + Spacing);
			CreateCube(Pos, (int)CubeSize);
		}
		Offset += CubeSize;
		Pos.y += (CubeSize *2.0f + Spacing);
		size--;
	}
}

//==================================================================================
void Simulation::CreateTower(int size)
{
	float CubeSize = 2.0f;
	float Spacing = 0.01f;
	NxVec3 Pos(0.0f, CubeSize, 0.0f);
	while (size)
	{
		CreateCube(Pos, (int)CubeSize);
		Pos.y += (CubeSize *2.0f + Spacing);
		size--;
	}
}

//==================================================================================
bool Simulation::InitNx()
{
	if (!gMyAllocator)
	{
		gMyAllocator = new UserAllocator();
	}

	NXU::setErrorReport(&gUserNotify);
	NXU::setEndianMode(isProcessorBigEndian());

	// Initialize PhysicsSDK
	NxPhysicsSDKDesc desc;
	NxSDKCreateError errorCode = NXCE_NO_ERROR;
	gPhysicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, gMyAllocator, &gErrorStream, desc, &errorCode);
	if(gPhysicsSDK == NULL) 
	{
		char* errorString;
		switch(errorCode) 
		{
		case NXCE_NO_ERROR: errorString = "NXCE_NO_ERROR";
		case NXCE_PHYSX_NOT_FOUND: errorString = "NXCE_PHYSX_NOT_FOUND";
		case NXCE_WRONG_VERSION: errorString = "NXCE_WRONG_VERSION";
		case NXCE_DESCRIPTOR_INVALID: errorString = "NXCE_DESCRIPTOR_INVALID";
		case NXCE_CONNECTION_ERROR: errorString = "NXCE_CONNECTION_ERROR";
		case NXCE_RESET_ERROR: errorString = "NXCE_RESET_ERROR";
		case NXCE_IN_USE_ERROR: errorString = "NXCE_IN_USE_ERROR";
		default: errorString = "Unknown error";
		}
		printf("\nSDK create error (%d - %s).\nUnable to initialize the PhysX SDK, exiting the sample.\n\n", errorCode, errorString);
		return false;
	}
#if SAMPLES_USE_VRD
	// The settings for the VRD host and port are found in SampleCommonCode/SamplesVRDSettings.h
	if (gPhysicsSDK->getFoundationSDK().getRemoteDebugger() && !gPhysicsSDK->getFoundationSDK().getRemoteDebugger()->isConnected())
		gPhysicsSDK->getFoundationSDK().getRemoteDebugger()->connect(SAMPLES_VRD_HOST, SAMPLES_VRD_PORT, SAMPLES_VRD_EVENTMASK);
#endif

	//if (!InitCooking(gMyAllocator, &gErrorStream)) {
	//	printf("\nError: Unable to initialize the cooking library, exiting the sample.\n\n");
	//	return false;
	//}

	gPhysicsSDK->setParameter(NX_SKIN_WIDTH, 0.025f);
	//enable visualisation
	gPhysicsSDK->setParameter(NX_VISUALIZATION_SCALE, 1.0f);

	gPhysicsSDK->setParameter(NX_VISUALIZE_BODY_AXES, 1.0f);
	gPhysicsSDK->setParameter(NX_VISUALIZE_COLLISION_SHAPES, 1.0f);
	gPhysicsSDK->setParameter(NX_VISUALIZE_COLLISION_AXES, 1.0f);
	gPhysicsSDK->setParameter(NX_VISUALIZE_CONTACT_POINT, 1.0f);
	gPhysicsSDK->setParameter(NX_VISUALIZE_CONTACT_NORMAL, 1.0f);

	gPhysicsSDK->setParameter(NX_VISUALIZE_JOINT_LOCAL_AXES, 1.0f);
	gPhysicsSDK->setParameter(NX_VISUALIZE_JOINT_WORLD_AXES, 1.0f);
	gPhysicsSDK->setParameter(NX_VISUALIZE_JOINT_LIMITS, 1.0f);

	// Don't slow down jointed objects
	gPhysicsSDK->setParameter(NX_ADAPTIVE_FORCE, 0.0f);

	//Quanto coloquei esse trecho de codigo o programa ficou lento
	//for (NxU32 i = 0; i < 1; ++i) //Just one base scene
	//{
		//if (!InitBlankScene()) return false;
	//}

	return true;
}

//==================================================================================
bool Simulation::InitBlankScene()
{
	if (gPhysicsSDK)
	{
		// Create a blank scene
		NxSceneDesc sceneDesc;
		//sceneDesc.gravity = gDefaultGravity;

		gScenes[gBaseScene] = (NxScene1*)gPhysicsSDK->createScene(sceneDesc);
		if(gScenes[gBaseScene] == NULL) 
		{
			printf("\nError: Unable to create a PhysX scene, exiting the sample.\n\n");
			return false;
		}
		
		//NxMaterial *defaultMaterial = gScenes[gBaseScene]->getMaterialFromIndex(0);
		//defaultMaterial->setRestitution(0.0f);
		//defaultMaterial->setStaticFriction(0.5f);
		//defaultMaterial->setDynamicFriction(0.5f);
		
		//// Create ground plane
		//NxPlaneShapeDesc planeDesc;
		//planeDesc.setToDefault();
		
		//NxActorDesc ActorDesc;
		//ActorDesc.shapes.pushBack(&planeDesc);
		//gScenes[gBaseScene]->createActor(ActorDesc);
	}
	return true;
}

//==================================================================================
void Simulation::ReleaseNx()
{
	CloseCooking();
	NXU::releasePersistentMemory();
	if (gPhysicsSDK)
	{
		for (NxU32 i = 0; i < nbExistScenes; ++i)
		{
			if (gScenes[i])
			{
				gPhysicsSDK->releaseScene(*gScenes[i]);
				gScenes[i] = NULL;
			}
		}
		NxReleasePhysicsSDK(gPhysicsSDK);
		gPhysicsSDK = NULL;
	}

	if (gMyAllocator != NULL)
	{
		delete gMyAllocator;
		gMyAllocator = NULL;
	}
}
//==================================================================================
void Simulation::simVisionRun(){
	QMutexLocker locker(&mutex);

	TimePosix::gettimeofday(&timeLastSimulate,NULL);
	while(true){
		double diff;
		timeval tv;
		TimePosix::gettimeofday(&tv,NULL);
		diff =  ((double)tv.tv_sec + tv.tv_usec*(1.0E-6)) - ((double)timeLastSimulate.tv_sec + timeLastSimulate.tv_usec*(1.0E-6));

		if(diff>=timeStep){//>0){
			//Sleep(dif);
			simulate(gBaseScene,timeStep/*diff*/,8);
			TimePosix::gettimeofday(&timeLastSimulate,NULL);
		}
	}
}

void Simulation::simulate()
{
	////////////////QMutexLocker locker(&mutex);

	// Start simulation (non blocking)
	// Physics code
	for (NxU32 i = 0; i < nbExistScenes; ++i)
	{
		if (gScenes[i] && !gPause)
		{
			gScenes[i]->setTiming(timeStep, 1, NX_TIMESTEP_FIXED);
			gScenes[i]->simulate(timeStep);
			gScenes[i]->flushStream();
		}
	}

	for (NxU32 i = 0; i < nbExistScenes; ++i)
	{
		if (gScenes[i] && !gPause)
		{
			gScenes[i]->fetchResults(NX_RIGID_BODY_FINISHED, true);
		}
	}

	// ~Physics code
}

void Simulation::simulate(int indexScene)
{
	/////////////QMutexLocker locker(&mutex);

	// Start simulation (non blocking)
	// Physics code
	if (gScenes[indexScene] && !gPause)
	{
		gScenes[indexScene]->setTiming(timeStep, 1, NX_TIMESTEP_FIXED);
		gScenes[indexScene]->simulate(timeStep);
	}

	if (gScenes[indexScene] && !gPause)
	{
		gScenes[indexScene]->flushStream();
		gScenes[indexScene]->fetchResults(NX_RIGID_BODY_FINISHED, true);
	}
	// ~Physics code
}

void Simulation::simulate(int indexScene, float dt)
{
	////////////////QMutexLocker locker(&mutex);

	// Start simulation (non blocking)
	// Physics code
	if (gScenes[indexScene] && !gPause)
	{
		gScenes[indexScene]->setTiming(dt, 1, NX_TIMESTEP_FIXED);
		gScenes[indexScene]->simulate(dt);
	}

	if (gScenes[indexScene] && !gPause)
	{
		gScenes[indexScene]->flushStream();
		gScenes[indexScene]->fetchResults(NX_RIGID_BODY_FINISHED, true);
	}
	// ~Physics code
}

void Simulation::simulate(int indexScene, float dt, int maxStepIter )
{
	//////////////QMutexLocker locker(&mutex);

	// Start simulation (non blocking)
	// Physics code
	if (gScenes[indexScene] && !gPause)
	{
		gScenes[indexScene]->setTiming(dt, maxStepIter, NX_TIMESTEP_FIXED);
		gScenes[indexScene]->simulate(dt);
	}

	if (gScenes[indexScene] && !gPause)
	{
		gScenes[indexScene]->flushStream();
		gScenes[indexScene]->fetchResults(NX_RIGID_BODY_FINISHED, true);
	}
	// ~Physics code
}

void Simulation::controlWheels( NxReal* wheelsSpeeds, int indexScene, NxI32 indexRobot )
{
	NxRobot* robot = Simulation::allRobots.getRobotByIdScene(indexRobot, indexScene);
	if(robot){
		int nbWheels = robot->getNbWheels();
		NxReal* torqueWheels = new NxReal[nbWheels];
		for(int indexWheel=0; indexWheel<nbWheels; indexWheel++)
		{
			NxReal currentWheelSpeed = ((NxWheel2*) robot->getWheel(indexWheel))->getAxleSpeed();
			//torqueWheels.push_back(calcTorqueFromWheelSpeed(wheelsSpeeds[indexWheel], currentWheelSpeed, indexScene, indexRobot, indexWheel));
			torqueWheels[indexWheel] = calcTorqueFromWheelSpeed(wheelsSpeeds[indexWheel], currentWheelSpeed, indexScene, indexRobot, indexWheel);
		}

		delete wheelsSpeeds;

		robot->control( torqueWheels );//torqueWheels[0], torqueWheels[1], torqueWheels[2], torqueWheels[3] );

		if (gScenes[indexScene])
		{
			NxArray<NxRobot*> robots = allRobots.getRobotsByScene(indexScene);
			for(int i=0;i<robots.size(); i++)
				robots[i]->updateVehicle();
		}
	}
}

void Simulation::controlRobot(float speedX, float speedY, float speedAng, float dribblerSpeed, float kickerSpeed, int indexRobot, int indexScene)
{
	NxRobot* robot = Simulation::allRobots.getRobotByIdScene(indexRobot, indexScene);
	if(robot)
	{
		//Execute kicker
		controlKicker( kickerSpeed, indexRobot, indexScene );

		//Control dribbler
		controlDribbler( dribblerSpeed, indexRobot, indexScene );

		//Control wheels
		NxReal* wheelsSpeeds = calcWheelSpeedFromRobotSpeed(speedAng, speedX, speedY, indexRobot, indexScene); //omnidirecionalidade
		controlWheels( wheelsSpeeds, indexScene, indexRobot); 
	}
}

void Simulation::controlRobotByWheels(float speedWheel1, float speedWheel2, float speedWheel3, float speedWheel4, float dribblerSpeed, float kickerSpeed, int indexRobot, int indexScene)
{
	//Control kicker
	controlKicker( kickerSpeed, indexRobot, indexScene );

	//Control dribbler
	controlDribbler( dribblerSpeed, indexRobot, indexScene );

	//Control wheels
	NxReal* wheelsSpeeds = new NxReal[4];
	wheelsSpeeds[0] = speedWheel1;
	wheelsSpeeds[1] = speedWheel2;
	wheelsSpeeds[2] = speedWheel3;
	wheelsSpeeds[3] = speedWheel4;
	controlWheels( wheelsSpeeds, indexScene, indexRobot); 
}

void Simulation::controlDribbler( float dribblerSpeed, int indexRobot, int indexScene )
{
	//TODO: implementar o controlador
	NxRobot* robot = Simulation::allRobots.getRobotByIdScene(indexRobot, indexScene);
	if(robot){
		if(true){//flagDribblerContact[indexRobot]){
			NxReal angle = getAngle2DFromRobot(indexRobot, indexScene);
			angle += NxPi/2.;
			allBalls.getBallByScene(indexScene).ball->addTorque(NxVec3(dribblerSpeed*cos(angle)*100., sin(angle)*dribblerSpeed*100., 0), NX_IMPULSE); //TODO: VERIFICAR A FORÇA OU IMPULSO
			flagDribblerContact = false;
		}
	}
}

void Simulation::controlKicker( float kickerSpeed, int indexRobot, int indexScene )
{
	/*//TODO: implementar o controlador
	NxRobot* robot = Simulation::allRobots.getRobotByIdScene(indexRobot, indexScene);
	if(robot){
		NxBall ball = Simulation::allBalls.getBallByScene(indexScene);
		NxShape* const* ballShapes = ball.ball->getShapes();

		NxBoxShapeDesc* kickerShapeDesc = (NxBoxShapeDesc*)robot->kicker.kickerShapeDesc;
		
		NxBox box = NxBox(kickerShapeDesc->localPose.t + robot->getActor()->getGlobalPosition(), kickerShapeDesc->dimensions,  robot->getActor()->getGlobalOrientation() * kickerShapeDesc->localPose.M);
		
		NxSphere sphere = NxSphere(ball.ball->getGlobalPosition(), ballShapes[0]->isSphere()->getRadius());

		NxReal angle = getAngle2DFromRobot(indexRobot, indexScene);
		NxVec3 dir = NxVec3(-cos(angle), -sin(angle), 0);

		float min_dist;

		NxVec3 normal;

		NxUtilLib* gUtilLib = NxGetUtilLib();
		if(gUtilLib->NxSweepBoxSphere(box, sphere, dir, 50, min_dist, normal)){
			ball.ball->addForce(NxVec3(kickerSpeed*cos(angle)*100., kickerSpeed*sin(angle)*100., 0), NX_IMPULSE); //TODO: VERIFICAR A FORÇA OU IMPULSO
		}
	}*/
}

NxActor* Simulation::getActorBall(int indexScene)
{
	NxActor* actor = NULL;
	const char* actorName = NULL;
	if(gScenes[indexScene]!=NULL)
	{
		for(unsigned int j=0;j<gScenes[indexScene]->getNbActors();j++)
		{
			actor = gScenes[indexScene]->getActors()[j];
			if(actor != NULL)
			{
				actorName = actor->getName();
				if(actorName != NULL)
				{
					if(strcmp(actorName,"Bola")==0) break;
					else actor = NULL;
				}
			}
			else continue;
		}
	}
	return actor;
}

NxActor* Simulation::getActorRobot(int indexScene, int indexRobot)
{
	NxActor* actor = NULL;
	const char* actorName = NULL;
	if(gScenes[indexScene]!=NULL)
	{
		for(unsigned int j=0;j<gScenes[indexScene]->getNbActors();j++)
		{
			actor = gScenes[indexScene]->getActors()[j];
			//gScenes[indexScene]->get
			if(actor != NULL)
			{
				actorName = actor->getName();
				if(actorName != NULL)
				{
					string label;
					string plabel = "Robo";
					stringstream out;
					out << indexRobot;
					label.append(plabel);
					label.append(out.str());
					char* arrayLabel = new char[label.size()+1];
					arrayLabel[label.size()]=0;
					memcpy(arrayLabel, label.c_str(), label.size());

					if(strcmp(actorName,arrayLabel)==0) 
					{
						delete arrayLabel;
						break;
					}
					else 
					{
						actor = NULL;
						delete arrayLabel;
					}
				}
			}
			else continue;
		}
	}
	return actor;
}

NxActor* Simulation::getActorByLabel(int indexScene, string label)
{
	NxActor* actor = NULL;
	const char* actorName = NULL;
	if(gScenes[indexScene]!=NULL)
	{
		for(unsigned int j=0;j<gScenes[indexScene]->getNbActors();j++)
		{
			actor = gScenes[indexScene]->getActors()[j];
			//gScenes[indexScene]->get
			if(actor != NULL)
			{
				actorName = actor->getName();
				if(actorName != NULL)
				{
					if(strcmp(actorName,label.c_str())==0) 
					{
						break;
					}
					else 
					{
						actor = NULL;
					}
				}
			}
			else continue;
		}
	}
	return actor;
}

NxActor* Simulation::getActorWheel(int indexScene, int indexRobot, int indexWheel)
{
	NxActor* actor = NULL;
	const char* actorName = NULL;
	if(gScenes[indexScene]!=NULL)
	{
		for(unsigned int j=0;j<gScenes[indexScene]->getNbActors();j++)
		{
			actor = gScenes[indexScene]->getActors()[j];
			//gScenes[indexScene]->get
			if(actor != NULL)
			{
				actorName = actor->getName();
				if(actorName != NULL)
				{
					string label;
					string plabel = "Roda-";
					stringstream out;
					stringstream out1;
					out << indexRobot;
					out1 << indexWheel;
					label.append(plabel);
					label.append(out.str());
					label.append("-");
					label.append(out1.str());
					char* arrayLabel = new char[label.size()+1];
					arrayLabel[label.size()]=0;
					memcpy(arrayLabel, label.c_str(), label.size());

					if(strcmp(actorName,arrayLabel)==0) 
					{
						delete arrayLabel;
						break;
					}
					else 
					{
						actor = NULL;
						delete arrayLabel;
					}
				}
			}
			else continue;
		}
	}
	return actor;
}

int Simulation::getNumberWheels(int indexScene, int indexRobot)
{
	NxActor* actor = NULL;
	int numberOfWheels = 0;
	const char* actorName = NULL;
	if(gScenes[indexScene]!=NULL)
	{
		for(unsigned int j=0;j<gScenes[indexScene]->getNbActors();j++)
		{
			actor = gScenes[indexScene]->getActors()[j];
			if(actor != NULL)
			{
				actorName = actor->getName();
				if(actorName != NULL)
				{
					string label;
					string plabel = "Roda-";
					stringstream out;
					out << indexRobot;
					label.append(plabel);
					label.append(out.str());
					char* arrayLabel = new char[label.size()+1];
					arrayLabel[label.size()]=0;
					memcpy(arrayLabel, label.c_str(), label.size());

					char* actorNameAux = new char[strlen(actorName)-1];
					actorNameAux[strlen(actorName)-2]=0;
					memcpy(actorNameAux, actorName, strlen(actorName)-2);
					if(strcmp(actorNameAux,arrayLabel)==0) 
					{
						delete arrayLabel;
						delete actorNameAux;
						numberOfWheels++;
					}
					else 
					{
						actor = NULL;
						delete arrayLabel;
						delete actorNameAux;
					}
				}
			}
			else continue;
		}
	}
	return numberOfWheels;
}

NxVec3 Simulation::getFieldExtents(int indexScene)
{
	NxActor* actor = NULL;
	const char* actorName = NULL;
	if(gScenes[indexScene]!=NULL)
	{
		for(unsigned int j=0;j<gScenes[indexScene]->getNbActors();j++)
		{
			actor = gScenes[indexScene]->getActors()[j];
			if(actor != NULL)
			{
				actorName = actor->getName();
				if(actorName != NULL)
				{
					string label;
					string plabel = "Campo";
					label.append(plabel);
					char* arrayLabel = new char[label.size()+1];
					arrayLabel[label.size()]=0;
					memcpy(arrayLabel, label.c_str(), label.size());

					if(strcmp(actorName,arrayLabel)==0) 
					{
						delete arrayLabel;
						break;
					}
					else 
					{
						actor = NULL;
						delete arrayLabel;
					}
				}
			}
			else continue;
		}
	}
	if (actor == NULL)
		return NULL;
	else
	{
		NxShape*const* shapes = actor->getShapes();
		NxBox* box = ((NxBox*) shapes[0]);
		return box->GetExtents();
	}
}

void Simulation::infinitePath(int indexRobot, int indexScene)
{
	static int i[10] = {0};//=0;
	//if( i>7 ) i=0;
	static bool flags[10][8] = { false };

	if(flags[indexRobot-1][7]==true) 
	{
		for(int j=0; j<8; j++)
		{
			flags[indexRobot-1][j] = false;
		}
	}

	for(int j=0; j<8; j++)
	{
		if(flags[indexRobot-1][j]==false)
		{
			i[indexRobot-1]=j;
			break;
		}
	}

	NxVec3 pontos[8];
	pontos[0].x = 1000;
	pontos[0].y = 1000;

	pontos[1].x = 2000;
	pontos[1].y = 1000;

	pontos[2].x = 2000;
	pontos[2].y = -1000;

	pontos[3].x = 1000;
	pontos[3].y = -1000;

	pontos[4].x = -1000;
	pontos[4].y = 1000;

	pontos[5].x = -2000;
	pontos[5].y = 1000;

	pontos[6].x = -2000;
	pontos[6].y = -1000;

	pontos[7].x = -1000;
	pontos[7].y = -1000;

	NxVec3 posRobot = getRobotGlobalPos(indexRobot, indexScene);
	NxReal distance = calcDistanceVec2D(pontos[i[indexRobot-1]].x, pontos[i[indexRobot-1]].y, posRobot.x, posRobot.y);
	if( distance < 100 ){
		flags[indexRobot-1][i[indexRobot-1]]=true;
	}

	goToThisPose( pontos[i[indexRobot-1]].x, pontos[i[indexRobot-1]].y, 3* NxPi / 2., indexRobot, indexScene);
}

void Simulation::setBallGlobalPos(NxVec3 pos, int indexScene)
{
	NxActor* actorBall = getActorBall(indexScene);
	if(actorBall != NULL){
		actorBall->setGlobalPosition(pos);
	}
}

void Simulation::setBallLinearVelocity(NxVec3 linVel, int indexScene)
{
	NxActor* actorBall = getActorBall(indexScene);
	if(actorBall != NULL){
		actorBall->setLinearVelocity(linVel);
	}
}

void Simulation::setRobotAngularVelocity(NxVec3 angVel, int indexScene, int indexRobot)
{

}

void Simulation::setRobotGlobalPose(NxMat34 pose, int indexScene, int indexRobot)
{
}

void Simulation::goToThisPose( NxReal x, NxReal y, NxReal angle, int indexRobot, int indexScene )
{
	//Controle proporcional
	//Velocidades Maximas do nosso robô: 17,5 x  pi x 0,057m = 3,13 m/s (o da Skuba, atual campeã mundial: 3,5m/s)  
	//Rotacao maxima: 6,180582777638119118568314880347
	NxReal maxSpeedAng = 6.2;
	NxReal maxLinearSpeed = 3130;

	//Controle de angulo
	NxReal distanceAngle = angle - getAngle2DFromRobot( indexRobot, indexScene ); //TODO: remover redundância de getAngle2DFromRobot tanto em goToThisPose quanto em calcWheelSpeedFromRobotSpeed
	NxReal speedAng;
	if(NxMath::abs(distanceAngle) > NxPi / 72.) speedAng = distanceAngle / NxPi * maxSpeedAng;
	else speedAng = 0;

	//Controle de posicao
	NxVec3 position = getRobotGlobalPos( indexRobot, indexScene );
	NxReal distanceX = x - position.x;
	NxReal distanceY = y - position.y;
	NxReal distance = calcDistanceVec2D( position.x, position.y, x, y);
	NxReal distanceThreshold = 2000.;
	NxReal speedX;
	NxReal speedY;
	NxReal speed;
	if(NxMath::abs(distance) > 10.)
	{
		if( distance > distanceThreshold ) 
			if( distance > 0 ) speed = maxLinearSpeed;
			else speed = - maxLinearSpeed;
		else 
			speed = distance / distanceThreshold * maxLinearSpeed;

		speedX = speed * NxMath::cos( NxMath::atan2( distanceY, distanceX ) );
		speedY = speed * NxMath::sin( NxMath::atan2( distanceY, distanceX ) );
	}
	else
	{
		speedX = 0;
		speedY = 0;
	}

	controlRobot(speedX, speedY, speedAng, 0, 0, indexRobot, indexScene);
}

NxF32 Simulation::calcDistanceVec2D( NxF32 x1, NxF32 y1, NxF32 x2, NxF32 y2 )
{
	return NxMath::pow( NxMath::pow( x2 - x1, (NxF32)2 ) + NxMath::pow( y2 - y1, (NxF32)2 ), (NxF32)0.5 );
}

NxVec3 Simulation::getRobotGlobalPos( int indexRobot, int indexScene )
{
	//FIXME:
	//return getActorRobot( indexScene, indexRobot )->getGlobalPosition();
	//FIXED?:
	NxActor* robot = getActorRobot(indexScene, indexRobot);
	return robot==NULL? NxVec3() : robot->getGlobalPosition();
}

NxVec3 Simulation::getBallGlobalPos( int indexScene )
{
	return getActorBall( indexScene )->getGlobalPosition();
}

void Simulation::setRobotLinearVelocity(NxVec3 linVel, int indexScene, int indexRobot)
{
}

NxMat33 Simulation::getRobotGlobalOrientation( int indexRobot, int indexScene )
{
	//FIXME:
	//return getActorRobot( indexScene, indexRobot )->getGlobalOrientation();
	//FIXED?:
	NxActor* robot = allRobots.getRobotByIdScene(indexRobot, indexScene)->getActor();
	return robot==NULL? NxMat33() : robot->getGlobalOrientation();
}

/**
* Retorna o angulo em radianos no plano x-y de um determinado robo. Anti-horario positivo. Zero no eixo x+. Angulo entre 0 e 2*PI.
*/
NxReal Simulation::getAngle2DFromRobot( int indexRobot, int indexScene )
{
	NxMat33 rotMatrix = getRobotGlobalOrientation( indexRobot, indexScene );
	NxMat33 rotMatrixInv;
	rotMatrix.getInverse(rotMatrixInv);
	NxVec3 vecY = rotMatrixInv.getColumn(1);
	NxReal value = vecY.dot(NxVec3(0,1,0));
	value /= vecY.magnitude();

	NxReal teta = NxMath::acos(value);
	if( teta < NxPi*0.5 )
	{
		if( vecY.x * vecY.y > 0 )
		{
			teta = NxPi*2 - teta;
		}
	}
	else
	{
		if( vecY.x * vecY.y < 0 )
		{
			teta = NxPi*2 - teta;
		}
	}
	teta = NxPi*2 - teta;
	return teta;
}

/**
* Calcula a velocidade das 4 rodas de um determinado robo tendo como entrada as velocidades angular e linear desejadas para o robo.
*/
NxReal* Simulation::calcWheelSpeedFromRobotSpeed( NxReal speedAng, NxReal speedX, NxReal speedY, int indexRobot, int indexScene )
{
	//Matriz de omnidirecionalidade
	//Leva em consideracao os angulos das rodas
	//-0.5446    0.8387    1.0000
	//-0.5446   -0.8387    1.0000
	//0.7071   -0.7071    1.0000
	//0.7071    0.7071    1.0000

	NxReal angRobo = getAngle2DFromRobot( indexRobot, indexScene );
	NxRobot* nxRobot = Simulation::allRobots.getRobotByIdScene(indexRobot, indexScene);
	int nbWheels = nxRobot->getNbWheels();
	NxReal* speeds = new NxReal[nbWheels];

	for(int i=0; i<nbWheels; i++)
	{
		//NxVec3 wheelPosRel = nxRobot->getWheel(i)->getWheelPos() - nxRobot->getBodyPos();
		NxReal angPosWheel = ((NxWheel2*)nxRobot->getWheel(i))->angWheelRelRobot;
		speeds[i] = -NxMath::sin(angPosWheel) * ( speedX * NxMath::cos( -angRobo ) + speedY * NxMath::sin( angRobo ) ) +
			NxMath::cos(angPosWheel) * ( speedX * NxMath::sin( -angRobo ) + speedY * NxMath::cos( angRobo ) ) +
			speedAng * nxRobot->wheelsRadius;
		speeds[i] /= nxRobot->wheelsRadius;
	}

	//NxMat33 omniMatrix1;
	//NxMat33 omniMatrix2;

	//omniMatrix1.setRow(0, NxVec3(-0.5446,	0.8387,		1.0000));
	//omniMatrix1.setRow(1, NxVec3(-0.5446,	-0.8387,	1.0000));
	//omniMatrix1.setRow(2, NxVec3(0.7071,	-0.7071,	1.0000));

	//omniMatrix2.setRow(0, NxVec3(0.7071,	0.7071,		1.0000));

	////omniMatrix1.setRow(0, NxVec3(-0.5446,	0.8387,		1.0000));
	////omniMatrix1.setRow(1, NxVec3(-0.5446,	-0.8387,	1.0000));
	////omniMatrix1.setRow(2, NxVec3(0.7071,	-0.7071,	1.0000));

	////omniMatrix2.setRow(0, NxVec3(0.7071,	0.7071,		1.0000));

	//NxMat33 controlRobot;
	//controlRobot.zero();

	//controlRobot.setColumn( 0, NxVec3( speedX * NxMath::cos( -angRobo ) + speedY * NxMath::sin( angRobo ), 
	//	speedX * NxMath::sin( -angRobo ) + speedY * NxMath::cos( angRobo ),
	//	speedAng * 90/*NxRobot::robotRadius*/ ) );

	//omniMatrix1 *= controlRobot;
	//omniMatrix2 *= controlRobot;

	//NxVec3 speedAxleWheel1 = omniMatrix1.getColumn(0);
	//NxVec3 speedAxleWheel2 = omniMatrix2.getColumn(0);

	//speeds[0] = speedAxleWheel1.x;
	//speeds[1] = speedAxleWheel1.y;
	//speeds[2] = speedAxleWheel1.z;
	//speeds[3] = speedAxleWheel2.x;

	//LIMITANTE DE VELOCIDADE
	NxReal biggestValue = getBiggestAbsoluteValue(speeds, nbWheels);
	if(biggestValue > 0.00001)
	{
		//Valor maximo da nossa roda 109,95574287564276334619251841478 rad/s (17,5 rps)
		NxReal maxSpeed = 110.;
		for( int i = 0; i < nbWheels; i++ )
		{
			speeds[i] = speeds[i] / biggestValue * maxSpeed;
		}
	}
	else
	{
		for( int i = 0; i < nbWheels; i++ )
		{
			speeds[i] = 0;
		}
	}

	return speeds;
}

/*
* Calcula o torque que deve ser empregado em uma determinada roda para que ela alcance um determinado valor de velocidade.
*/
NxReal Simulation::calcTorqueFromWheelSpeed(NxReal currentDesiredWheelSpeed, NxReal currentWheelSpeed, int indexScene, int indexRobot, int indexWheel)
{
	NxReal currentWheelTorque;
	NxReal inertiaMoment = 12.57673;
	currentWheelTorque = (Simulation::lastWheelTorques[indexScene][indexRobot])[indexWheel] + inertiaMoment * 20. * (currentDesiredWheelSpeed - currentWheelSpeed) - inertiaMoment * 19.35 * ((Simulation::lastDesiredWheelSpeeds[indexScene][indexRobot])[indexWheel] - (Simulation::lastWheelSpeeds[indexScene][indexRobot])[indexWheel]);

	//Avançando iteração
	Simulation::lastDesiredWheelSpeeds[indexScene][indexRobot][indexWheel] = currentDesiredWheelSpeed;
	Simulation::lastWheelTorques[indexScene][indexRobot][indexWheel] = currentWheelTorque;
	Simulation::lastWheelSpeeds[indexScene][indexRobot][indexWheel] = currentWheelSpeed;

	return currentWheelTorque;
}

NxReal Simulation::getBiggestAbsoluteValue(NxReal* values, int size)
{
	NxReal biggest = 0;
	int indexBiggest = 0;
	for( int i = 0; i < size; i++ )
	{
		if( NxMath::abs( values[i] ) > biggest ) 
		{
			biggest = NxMath::abs( values[i] );
			indexBiggest = i;
		}
	}
	return NxMath::abs( values[indexBiggest] );
}

/**
* Retorna o angulo em radianos no plano x-y de uma determinada matriz de orientacao 3x3. Anti-horario positivo. Zero no eixo x+. Angulo entre 0 e 2*PI.
*/
NxReal Simulation::getAngle2DFromMat33( NxMat33 matrixOrientation )
{
	NxMat33 rotMatrix = matrixOrientation;
	NxMat33 rotMatrixInv;
	rotMatrix.getInverse(rotMatrixInv);
	NxVec3 vecY = rotMatrixInv.getColumn(1);
	NxReal value = vecY.dot(NxVec3(0,1,0));
	value /= vecY.magnitude();

	NxReal teta = NxMath::acos(value);
	if( teta < NxPi*0.5 )
	{
		if( vecY.x * vecY.y > 0 )
		{
			teta = NxPi*2 - teta;
		}
	}
	else
	{
		if( vecY.x * vecY.y < 0 )
		{
			teta = NxPi*2 - teta;
		}
	}
	teta = NxPi*2 - teta;
	return teta;
}

NxActor* Simulation::cloneActor(NxActor* actorSource, int indexDestScene)
{
	NxActorDesc actorDesc;
	actorSource->saveToDesc(actorDesc);

	// Create body
	if(actorSource->isDynamic()){
		NxBodyDesc bodyDesc;
		actorSource->saveBodyToDesc(bodyDesc);
		actorDesc.body = &bodyDesc;
	}

	//TODO: Saber pq tive que fazer diferente dos exemplos do PhysX, pois lá os ShapeDesc eram instancias locais, tive que mudar para ponteiros
	for(int i=0; i<actorSource->getNbShapes(); i++)
	{
		NxShapeType type = (actorSource->getShapes())[i]->getType();
		if(type==NxShapeType::NX_SHAPE_BOX){
			NxBoxShapeDesc* boxDesc = new NxBoxShapeDesc();
			(actorSource->getShapes())[i]->isBox()->saveToDesc(*boxDesc);
			actorDesc.shapes.push_back(boxDesc);
		}
		else if(type==NxShapeType::NX_SHAPE_CONVEX){
			NxConvexShapeDesc* convexShapeDesc = new NxConvexShapeDesc();
			//static NxConvexMeshDesc convexMeshDesc;
			(actorSource->getShapes())[i]->isConvexMesh()->saveToDesc(*convexShapeDesc);
					
			//MemoryWriteBuffer buf;
			//bool status = CookConvexMesh(convexMeshDesc, buf);
			//if(status){
			//	convexShapeDesc.meshData = gPhysicsSDK->createConvexMesh(MemoryReadBuffer(buf.data));
				actorDesc.shapes.push_back(convexShapeDesc);
			//}

			/*	NxConvexShapeDesc robotShape[1];
			if(robotShapes)
			{
			static NxConvexMeshDesc convexMesh;
			robotShapes[0]->isConvexMesh()->getConvexMesh().saveToDesc(convexMesh);

			MemoryWriteBuffer buf;
			bool status = CookConvexMesh(convexMesh, buf);
			if(status)
			{
			robotShape[0].meshData = Simulation::gPhysicsSDK->createConvexMesh(MemoryReadBuffer(buf.data));
			vehicleDesc.robotShapes.pushBack(&robotShape[0]);

			}
			}*/
		}
		else if(type==NxShapeType::NX_SHAPE_SPHERE){
			NxSphereShapeDesc* shapeDesc = new NxSphereShapeDesc();
			(actorSource->getShapes())[i]->isSphere()->saveToDesc(*shapeDesc);	
			actorDesc.shapes.push_back(shapeDesc);
		}
		else if(type==NxShapeType::NX_SHAPE_WHEEL){ //Tirei pra num clonar 2 vezes as shapes das rodas na rotina cloneRobot 
			//NxWheelShapeDesc* shapeDesc = new NxWheelShapeDesc();
			//(actorSource->getShapes())[i]->isWheel()->saveToDesc(*shapeDesc);	
			//actorDesc.shapes.push_back(shapeDesc);
		}
		else if(type==NxShapeType::NX_SHAPE_PLANE){
			NxPlaneShapeDesc* shapeDesc = new NxPlaneShapeDesc();
			(actorSource->getShapes())[i]->isPlane()->saveToDesc(*shapeDesc);	
			actorDesc.shapes.push_back(shapeDesc);
		}
		else if(type==NxShapeType::NX_SHAPE_CAPSULE){
			NxCapsuleShapeDesc* shapeDesc = new NxCapsuleShapeDesc();
			(actorSource->getShapes())[i]->isCapsule()->saveToDesc(*shapeDesc);	
			actorDesc.shapes.push_back(shapeDesc);
		}
		else{
			printf("SHAPE NAO CLONADA\n");
		}
	}
	return gScenes[indexDestScene]->createActor(actorDesc);
}

NxShapeDesc* Simulation::copyShapeDesc(NxShape* shapeSource){
	NxShapeType type = shapeSource->getType();
	if(type==NxShapeType::NX_SHAPE_BOX){
		NxBoxShapeDesc* boxDesc;
		NxBoxShape* boxShape = shapeSource->isBox();
		boxShape->saveToDesc(*boxDesc);
		return boxDesc;
	}
	else if(type==NxShapeType::NX_SHAPE_CONVEX){
		NxConvexShapeDesc* convexShapeDesc;
		//static NxConvexMeshDesc convexMeshDesc;
		shapeSource->isConvexMesh()->saveToDesc(*convexShapeDesc);
		return convexShapeDesc;

		//MemoryWriteBuffer buf;
		//bool status = CookConvexMesh(convexMeshDesc, buf);
		//if(status){
		//	convexShapeDesc.meshData = gPhysicsSDK->createConvexMesh(MemoryReadBuffer(buf.data);
		//}

		/*	NxConvexShapeDesc robotShape[1];
		if(robotShapes)
		{
		static NxConvexMeshDesc convexMesh;
		robotShapes[0]->isConvexMesh()->getConvexMesh().saveToDesc(convexMesh);

		MemoryWriteBuffer buf;
		bool status = CookConvexMesh(convexMesh, buf);
		if(status)
		{
		robotShape[0].meshData = Simulation::gPhysicsSDK->createConvexMesh(MemoryReadBuffer(buf.data));
		vehicleDesc.robotShapes.pushBack(&robotShape[0]);

		}
		}*/
	}
	else if(type==NxShapeType::NX_SHAPE_SPHERE){
		NxSphereShapeDesc* shapeDesc;
		shapeSource->isSphere()->saveToDesc(*shapeDesc);	
		return shapeDesc;
	}
	else if(type==NxShapeType::NX_SHAPE_WHEEL){
		NxWheelShapeDesc* shapeDesc;
		shapeSource->isWheel()->saveToDesc(*shapeDesc);	
		return shapeDesc;		
	}
	else if(type==NxShapeType::NX_SHAPE_PLANE){
		NxPlaneShapeDesc* shapeDesc;
		shapeSource->isPlane()->saveToDesc(*shapeDesc);	
		return shapeDesc;
	}
	else if(type==NxShapeType::NX_SHAPE_CAPSULE){
		NxCapsuleShapeDesc* shapeDesc;
		shapeSource->isCapsule()->saveToDesc(*shapeDesc);	
		return shapeDesc;
	}
	else
		return NULL;
}

void Simulation::cloneScene(int indexSceneSource){
	NxSceneDesc sceneDesc;
	if (gScenes[indexSceneSource]!=NULL)
		gScenes[indexSceneSource]->saveToDesc(sceneDesc);
	gScenes[nbExistScenes] = (NxScene1*)gPhysicsSDK->createScene(sceneDesc);

	//TODO: arrumar os bugs nesses vectors de controle
	//std::map<int, NxScene1*> teste;

	//Vectors de controle
	std::vector<NxReal*> lastWheelSpeedsArray = std::vector<NxReal*>();
	std::vector<NxReal*> lastDesiredWheelSpeedsArray = std::vector<NxReal*>();
	std::vector<NxReal*> lastWheelTorquesArray = std::vector<NxReal*>();

	Simulation::lastWheelSpeeds.push_back(lastWheelSpeedsArray);
	Simulation::lastDesiredWheelSpeeds.push_back(lastDesiredWheelSpeedsArray);
	Simulation::lastWheelTorques.push_back(lastWheelTorquesArray);

	//Clone Robots
	NxArray<NxRobot*> robots = allRobots.getRobotsByScene(indexSceneSource);
	for(int i=0; i<robots.size(); i++){
		robots[i]->cloneRobot(nbExistScenes, robots[i]->getId(), robots[i]->getPos(), robots[i]->getIdTeam());
	}

	//Clone Field
	allFields.getFieldByScene(indexSceneSource).cloneField(nbExistScenes);

	//Clone Ball
	allBalls.getBallByScene(indexSceneSource).cloneBall(nbExistScenes);

	//Contact Report (List of Collisions)
	NxUserContactReport * contactReport = new MyContactReport();
	robotContactReport.push_back(contactReport);
	gScenes[nbExistScenes]->setUserContactReport(contactReport);
	NxActor** actors = gScenes[nbExistScenes]->getActors();
	//TODO: Executar o setActorPairFlags quando incluir um actor na scene (cloneBall, cloneRobot)
	for(int i=0; i<gScenes[nbExistScenes]->getNbActors()-1; i++){
		gScenes[nbExistScenes]->setActorPairFlags(*(actors[i]), *(actors[i+1]), NX_NOTIFY_ON_TOUCH);
	}

	//Increment Counter
	nbExistScenes++;

	//NxActor** actors = gScenes[indexSource]->getActors();
	//for(int i=0; i<gScenes[indexSource]->getNbActors(); i++)
	//	cloneActor(actors[i], gScenes.size()-1);

	//gScenes[indexSource]->resetJointIterator();
	//for(int i=0; i<gScenes[indexSource]->getNbJoints(); i++){
	//	NxJoint* joint = gScenes[indexSource]->getNextJoint();
	//	if (joint!=NULL)
	//		cloneJoint(joint, gScenes.size()-1);
	//}
}

bool Simulation::initSimulation()
{
	bool init = Simulation::InitNx();
	SimulationView::CSL_Scene();

	if(gScenes[0] != NULL)
	{
		buildModelRobot( 4, Simulation::gBaseScene, 1 );
		buildModelField( Simulation::gBaseScene );
		buildModelBall( Simulation::gBaseScene );
	}

	//Init speeds/torques to calc omni
	for(int k=0; k<Simulation::nbExistScenes; k++){ 
		std::vector<NxReal*> lastWheelSpeedsArray = std::vector<NxReal*>();
		std::vector<NxReal*> lastDesiredWheelSpeedsArray = std::vector<NxReal*>();
		std::vector<NxReal*> lastWheelTorquesArray = std::vector<NxReal*>();
		NxAllRobots* allRobots = &Simulation::allRobots;
		for(int i=0; i<=allRobots->getBiggestIndexRobot(); i++)
		{
			NxRobot* nxRobot = allRobots->getRobotByIdScene(i, k);
			NxReal* wheels;
			if(nxRobot)
			{
				int nbWheels = nxRobot->getNbWheels();
				wheels = new NxReal[nbWheels];
				for(int j=0; j<nbWheels; j++)
				{
					wheels[j]=0;
				}
			}
			lastWheelSpeedsArray.push_back(wheels);
			lastDesiredWheelSpeedsArray.push_back(wheels);
			lastWheelTorquesArray.push_back(wheels);
		}
		lastWheelSpeeds.push_back(lastWheelSpeedsArray);
		lastDesiredWheelSpeeds.push_back(lastDesiredWheelSpeedsArray);
		lastWheelTorques.push_back(lastWheelTorquesArray);
	}

	allRobots.getRobotByIdScene(4, Simulation::gBaseScene)->setGlobalPosition(NxVec3(-3000, 0, 30));

	//Build Scene
	//	Contact Report (List of Collisions)
	NxUserContactReport * contactReport = new MyContactReport();
	robotContactReport.push_back(contactReport);
	gScenes[gBaseScene]->setUserContactReport(contactReport);
	NxActor** actors = gScenes[gBaseScene]->getActors();
	//TODO: Executar o setActorPairFlags quando incluir um actor na scene (cloneBall, cloneRobot)
	for(int i=0; i<gScenes[gBaseScene]->getNbActors()-1; i++){
		gScenes[gBaseScene]->setActorPairFlags(*(actors[i]), *(actors[i+1]), NX_NOTIFY_ON_TOUCH);
	}

	/*NxMaterial *defaultMaterial0 = Simulation::gScenes[Simulation::gBaseScene]->getMaterialFromIndex(0);
	defaultMaterial0->setRestitution(0.5f);
	defaultMaterial0->setStaticFriction(0.3f);
	defaultMaterial0->setDynamicFriction(0.3f);

	NxMaterial *defaultMaterial1 = Simulation::gScenes[Simulation::gBaseScene]->getMaterialFromIndex(1);
	//NxReal real2 = defaultMaterial1->getRestitution();
	//NxReal real = defaultMaterial1->getStaticFriction();
	//NxReal real1 = defaultMaterial1->getDynamicFriction();
	defaultMaterial1->setRestitution(0.5f);
	defaultMaterial1->setStaticFriction(0.3f);
	defaultMaterial1->setDynamicFriction(0.3f);

	NxMaterial *defaultMaterial2 = Simulation::gScenes[Simulation::gBaseScene]->getMaterialFromIndex(2);
	defaultMaterial2->setRestitution(0.5f);
	defaultMaterial2->setStaticFriction(0.3f);
	defaultMaterial2->setDynamicFriction(0.3f);*/

	for(int i=0; i<Simulation::gScenes[Simulation::gBaseScene]->getNbMaterials(); i++){
		NxMaterial *defaultMaterial = Simulation::gScenes[Simulation::gBaseScene]->getMaterialFromIndex(i);
		defaultMaterial->setRestitution(0.5);//0.5f);//     //TODO: LEVANTAR PARAMETROS
		defaultMaterial->setStaticFriction(0.3);//0.3f);//  //TODO: LEVANTAR PARAMETROS
		defaultMaterial->setDynamicFriction(0.3);//0.3f);//	//TODO: LEVANTAR PARAMETROS
		//TODO: USAR NxCombineMode
	}

	Simulation::allFields.fields[Simulation::gBaseScene].setDimensions(7400, 5400, 6000, 0, 200., 700., 160.);

	Simulation::allBalls.getBallByScene(Simulation::gBaseScene).ball->putToSleep();
	NxArray<NxRobot*> robots = Simulation::allRobots.getRobotsByScene(Simulation::gBaseScene);
	for(int i=0; i<robots.size(); i++){
		robots[i]->putToSleep();
	}

	allRobots.getRobotByIdScene(4, Simulation::gBaseScene)->cloneRobot(Simulation::gBaseScene, 3, NxVec3(-2000, 1000, 30), 1);
	allRobots.getRobotByIdScene(3, Simulation::gBaseScene)->getActor()->setName("Robo3");

	allRobots.getRobotByIdScene(3, Simulation::gBaseScene)->cloneRobot(Simulation::gBaseScene, 2, NxVec3(-2000, -1000, 30), 1);
	allRobots.getRobotByIdScene(2, Simulation::gBaseScene)->getActor()->setName("Robo2");

	allRobots.getRobotByIdScene(3, Simulation::gBaseScene)->cloneRobot(Simulation::gBaseScene, 1, NxVec3(-1000, 1000, 30), 1);
	allRobots.getRobotByIdScene(1, Simulation::gBaseScene)->getActor()->setName("Robo1");

	allRobots.getRobotByIdScene(2, Simulation::gBaseScene)->cloneRobot(Simulation::gBaseScene, 5, NxVec3(-1000, -1000, 30), 1);
	allRobots.getRobotByIdScene(5, Simulation::gBaseScene)->getActor()->setName("Robo5");

	allRobots.getRobotByIdScene(2, Simulation::gBaseScene)->cloneRobot(Simulation::gBaseScene, 6, NxVec3(3000, 0, 30), 0);
	allRobots.getRobotByIdScene(6, Simulation::gBaseScene)->getActor()->setName("Robo6");

	allRobots.getRobotByIdScene(2, Simulation::gBaseScene)->cloneRobot(Simulation::gBaseScene, 7, NxVec3(2000, -1000, 30), 0);
	allRobots.getRobotByIdScene(7, Simulation::gBaseScene)->getActor()->setName("Robo7");

	allRobots.getRobotByIdScene(2, Simulation::gBaseScene)->cloneRobot(Simulation::gBaseScene, 8, NxVec3(2000, 1000, 30), 0);
	allRobots.getRobotByIdScene(8, Simulation::gBaseScene)->getActor()->setName("Robo8");

	allRobots.getRobotByIdScene(2, Simulation::gBaseScene)->cloneRobot(Simulation::gBaseScene, 9, NxVec3(1000, -1000, 30), 0);
	allRobots.getRobotByIdScene(9, Simulation::gBaseScene)->getActor()->setName("Robo9");

	allRobots.getRobotByIdScene(2, Simulation::gBaseScene)->cloneRobot(Simulation::gBaseScene, 10, NxVec3(1000, 1000, 30), 0);
	allRobots.getRobotByIdScene(10, Simulation::gBaseScene)->getActor()->setName("Robo10");

	NxVec3 teste;
	Simulation::gScenes[0]->getGravity(teste);
	//Simulation::gScenes[0]->setGravity(NxVec3(0,0,-9.81));
	NxSceneDesc vaca;
	Simulation::gScenes[0]->saveToDesc(vaca);


	//cloneScene(gBaseScene);
	//cloneScene(gBaseScene);
	//cloneScene(gBaseScene);
	//cloneScene(gBaseScene);
	//cloneScene(gBaseScene);
	//cloneScene(gBaseScene);

	// Initialize physics scene and start the application main loop if scene was created
	return init; 
}