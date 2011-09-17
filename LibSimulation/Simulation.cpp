#include "Simulation.h"
#include "SimulationView.h"

bool Simulation::gPause = false;
bool Simulation::gSave = false;
int	Simulation::gLoad = 2;//0;
bool Simulation::gClear = false;

QMutex Simulation::mutex;

NxPhysicsSDK *Simulation::gPhysicsSDK = 0;
int Simulation::nbExistScenes = 1;
NxArray<NxScene1*> Simulation::gScenes = NxArray<NxScene1*>();
NxU32 Simulation::gBaseScene = 0;
NxVec3 Simulation::gDefaultGravity = NxVec3(0.0f, 0.0f, - 9.81f);
UserAllocator *Simulation::gMyAllocator = NULL;
ErrorStream Simulation::gErrorStream = ErrorStream();
MyUserNotify Simulation::gUserNotify = MyUserNotify();
timeval Simulation::timeLastSimulate;

float Simulation::timeStep = 1./60.; //timestep de 1/60 e 4 intervalos (baseado na tese do stefan zickler
NxArray<NxUserContactReport *> Simulation::robotContactReport = NxArray<NxUserContactReport *>();

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
	if (gScenes[SimulationView::indexRenderScene]->scene)
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
		gScenes[SimulationView::indexRenderScene]->scene->createActor(ActorDesc)->userData = (void*)size;
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

	NxScene1* scene1 = new NxScene1();
	scene1->indexScene = 0;
	gScenes.push_back(scene1);

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

		gScenes[gBaseScene]->scene = gPhysicsSDK->createScene(sceneDesc);
		if(gScenes[gBaseScene]->scene == NULL) 
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
			if (gScenes[i]->scene)
			{
				gPhysicsSDK->releaseScene(*(gScenes[i]->scene));
				gScenes[i]->scene = NULL;
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
		if (gScenes[i]->scene && !gPause)
		{
			//timestep de 1/60 e 4 intervalos (baseado na tese do stefan zickler
			gScenes[i]->scene->setTiming(timeStep, 4, NX_TIMESTEP_FIXED);
			gScenes[i]->scene->simulate(timeStep);
			gScenes[i]->scene->flushStream();
		}
	}

	for (NxU32 i = 0; i < nbExistScenes; ++i)
	{
		if (gScenes[i]->scene && !gPause)
		{
			gScenes[i]->scene->fetchResults(NX_RIGID_BODY_FINISHED, true);
		}
	}

	// ~Physics code
}

void Simulation::simulate(int indexScene)
{
	/////////////QMutexLocker locker(&mutex);

	// Start simulation (non blocking)
	// Physics code
	if (gScenes[indexScene]->scene && !gPause)
	{
		//timestep de 1/60 e 4 intervalos (baseado na tese do stefan zickler
		gScenes[indexScene]->scene->setTiming(timeStep, 4, NX_TIMESTEP_FIXED);
		gScenes[indexScene]->scene->simulate(timeStep);
	}

	if (gScenes[indexScene]->scene && !gPause)
	{
		gScenes[indexScene]->scene->flushStream();
		gScenes[indexScene]->scene->fetchResults(NX_RIGID_BODY_FINISHED, true);
	}
	// ~Physics code
}

void Simulation::simulate(int indexScene, float dt)
{
	////////////////QMutexLocker locker(&mutex);

	// Start simulation (non blocking)
	// Physics code
	if (gScenes[indexScene]->scene && !gPause)
	{
		//timestep de 1/60 e 4 intervalos (baseado na tese do stefan zickler
		gScenes[indexScene]->scene->setTiming(dt, 4, NX_TIMESTEP_FIXED);
		gScenes[indexScene]->scene->simulate(dt);
	}

	if (gScenes[indexScene]->scene && !gPause)
	{
		gScenes[indexScene]->scene->flushStream();
		gScenes[indexScene]->scene->fetchResults(NX_RIGID_BODY_FINISHED, true);
	}
	// ~Physics code
}

void Simulation::simulate(int indexScene, float dt, int maxStepIter )
{
	//////////////QMutexLocker locker(&mutex);

	// Start simulation (non blocking)
	// Physics code
	if (gScenes[indexScene]->scene && !gPause)
	{
		 gScenes[indexScene]->scene->setTiming(dt, maxStepIter, NX_TIMESTEP_FIXED);
		 gScenes[indexScene]->scene->simulate(dt);
	}

	if ( gScenes[indexScene]->scene && !gPause)
	{
		 gScenes[indexScene]->scene->flushStream();
		 gScenes[indexScene]->scene->fetchResults(NX_RIGID_BODY_FINISHED, true);
	}
	// ~Physics code
}

NxActor* Simulation::getActorBall(int indexScene)
{
	NxActor* actor = NULL;
	const char* actorName = NULL;
	if( gScenes[indexScene]->scene!=NULL)
	{
		for(unsigned int j=0;j< gScenes[indexScene]->scene->getNbActors();j++)
		{
			actor =  gScenes[indexScene]->scene->getActors()[j];
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
	if( gScenes[indexScene]->scene!=NULL)
	{
		for(unsigned int j=0;j< gScenes[indexScene]->scene->getNbActors();j++)
		{
			actor =  gScenes[indexScene]->scene->getActors()[j];
			// gScenes[indexScene]->scene->get
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
	if( gScenes[indexScene]->scene!=NULL)
	{
		for(unsigned int j=0;j< gScenes[indexScene]->scene->getNbActors();j++)
		{
			actor =  gScenes[indexScene]->scene->getActors()[j];
			// gScenes[indexScene]->scene->get
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
	if( gScenes[indexScene]->scene!=NULL)
	{
		for(unsigned int j=0;j< gScenes[indexScene]->scene->getNbActors();j++)
		{
			actor =  gScenes[indexScene]->scene->getActors()[j];
			// gScenes[indexScene]->scene->get
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
	if( gScenes[indexScene]->scene!=NULL)
	{
		for(unsigned int j=0;j< gScenes[indexScene]->scene->getNbActors();j++)
		{
			actor =  gScenes[indexScene]->scene->getActors()[j];
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
	return gScenes[indexDestScene]->scene->createActor(actorDesc);
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
	if (gScenes[indexSceneSource]->scene!=NULL)
		gScenes[indexSceneSource]->scene->saveToDesc(sceneDesc);

	NxScene1* scene1 = new NxScene1();
	gScenes.push_back(scene1);
	gScenes[nbExistScenes]->scene = gPhysicsSDK->createScene(sceneDesc);

	//Clone Robots
	NxArray<NxRobot*> robots = Simulation::gScenes[indexSceneSource]->allRobots->getRobots();
	for(int i=0; i<robots.size(); i++){
		robots[i]->cloneRobot(nbExistScenes, robots[i]->getId(), robots[i]->getPos(), robots[i]->getIdTeam());
	}

	//Clone Field
	Simulation::gScenes[indexSceneSource]->field->cloneField(nbExistScenes);

	//Clone Ball
	Simulation::gScenes[indexSceneSource]->ball->cloneBall(nbExistScenes);

	//Contact Report (List of Collisions)
	NxUserContactReport * contactReport = new MyContactReport();
	robotContactReport.push_back(contactReport);
	gScenes[nbExistScenes]->scene->setUserContactReport(contactReport);
	NxActor** actors = gScenes[nbExistScenes]->scene->getActors();
	//TODO: Executar o setActorPairFlags quando incluir um actor na scene (cloneBall, cloneRobot)
	for(int i=0; i<gScenes[nbExistScenes]->scene->getNbActors()-1; i++){
		gScenes[nbExistScenes]->scene->setActorPairFlags(*(actors[i]), *(actors[i+1]), NX_NOTIFY_ON_TOUCH);
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

	if(gScenes[0]->scene != NULL)
	{
		buildModelRobot( 4, Simulation::gBaseScene, 1 );
		buildModelField( Simulation::gBaseScene );
		buildModelBall( Simulation::gBaseScene );
	}

	//Build Scene
	//	Contact Report (List of Collisions)
	NxUserContactReport * contactReport = new MyContactReport();
	robotContactReport.push_back(contactReport);
	gScenes[gBaseScene]->scene->setUserContactReport(contactReport);
	NxActor** actors = gScenes[gBaseScene]->scene->getActors();
	//TODO: Executar o setActorPairFlags quando incluir um actor na scene (cloneBall, cloneRobot)
	for(int i=0; i<gScenes[gBaseScene]->scene->getNbActors()-1; i++){
		gScenes[gBaseScene]->scene->setActorPairFlags(*(actors[i]), *(actors[i+1]), NX_NOTIFY_ON_TOUCH);
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

	for(int i=0; i<Simulation::gScenes[Simulation::gBaseScene]->scene->getNbMaterials(); i++){
		NxMaterial *defaultMaterial = Simulation::gScenes[Simulation::gBaseScene]->scene->getMaterialFromIndex(i);
		defaultMaterial->setRestitution(0.5);//0.5f);//     //TODO: LEVANTAR PARAMETROS
		defaultMaterial->setStaticFriction(0.3);//0.3f);//  //TODO: LEVANTAR PARAMETROS
		defaultMaterial->setDynamicFriction(0.3);//0.3f);//	//TODO: LEVANTAR PARAMETROS
		//TODO: USAR NxCombineMode
	}

	//Simulation::allFields.fields[Simulation::gBaseScene].setDimensions(7400, 5400, 6000, 0, 200., 700., 160.);

	NxAllRobots* allRobots = Simulation::gScenes[Simulation::gBaseScene]->allRobots;

	allRobots->getRobotByIdByTeam(4, 1)->setGlobalPosition(NxVec3(-3000, 0, 30));
	
	allRobots->getRobotByIdByTeam(4, 1)->cloneRobot(Simulation::gBaseScene, 3, NxVec3(-2000, 1000, 30), 1);

	allRobots->getRobotByIdByTeam(4, 1)->cloneRobot(Simulation::gBaseScene, 2, NxVec3(-2000, -1000, 30), 1);

	allRobots->getRobotByIdByTeam(4, 1)->cloneRobot(Simulation::gBaseScene, 1, NxVec3(-1000, 1000, 30), 1);

	allRobots->getRobotByIdByTeam(4, 1)->cloneRobot(Simulation::gBaseScene, 7, NxVec3(-1000, -1000, 30), 1);

	allRobots->getRobotByIdByTeam(4, 1)->cloneRobot(Simulation::gBaseScene, 6, NxVec3(3000, 0, 30), 0);

	allRobots->getRobotByIdByTeam(4, 1)->cloneRobot(Simulation::gBaseScene, 7, NxVec3(2000, -1000, 30), 0);

	allRobots->getRobotByIdByTeam(4, 1)->cloneRobot(Simulation::gBaseScene, 8, NxVec3(2000, 1000, 30), 0);

	allRobots->getRobotByIdByTeam(4, 1)->cloneRobot(Simulation::gBaseScene, 9, NxVec3(1000, -1000, 30), 0);

	allRobots->getRobotByIdByTeam(4, 1)->cloneRobot(Simulation::gBaseScene, 10, NxVec3(1000, 1000, 30), 0);

	//cloneScene(gBaseScene);
	//cloneScene(gBaseScene);
	//cloneScene(gBaseScene);
	//cloneScene(gBaseScene);
	//cloneScene(gBaseScene);
	//cloneScene(gBaseScene);

	// Initialize physics scene and start the application main loop if scene was created
	return init; 
}