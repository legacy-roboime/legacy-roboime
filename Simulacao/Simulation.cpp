#include "Simulation.h"

bool Simulation::gPause = false;
NxPhysicsSDK *Simulation::gPhysicsSDK = 0;
NxScene1 *Simulation::gScenes[gMaxScenes] = { 0 };
NxU32 Simulation::gCurrentScene = 0;
NxVec3 Simulation::gDefaultGravity = NxVec3(0.0f, 0.0f, - 9.81f);
UserAllocator *Simulation::gMyAllocator = NULL;
NxVec3 Simulation::gEye = NxVec3(0, 0, 4100.0f);
NxVec3 Simulation::gDirection = NxVec3(0, 0, -1); 
int Simulation::gMouseX = 0;
int Simulation::gMouseY = 0;
bool Simulation::gSave = false;
int	Simulation::gLoad = 2;//0;
bool Simulation::gClear = false;
int Simulation::gMainHandle = 0;
ErrorStream Simulation::gErrorStream = ErrorStream();
DebugRenderer Simulation::gDebugRenderer = DebugRenderer();
NxVec3 Simulation::gNormal = NxVec3();
MyUserNotify Simulation::gUserNotify = MyUserNotify();
//Thread* Simulation::udpServerThread = new UDPServerThread("UDPServerThread-Simulacao",9786, "127.0.0.1");
//PerfRenderer    gPerfRenderer = PerfRenderer();
bool Simulation::keyDown[256];//={false};

NxArray<NxReal*> Simulation::lastWheelSpeeds;
NxArray<NxReal*> Simulation::lastDesiredWheelSpeeds;
NxArray<NxReal*> Simulation::lastWheelTorques;
float Simulation::timeStep = 15./1000.;//1./60.;
bool Simulation::flagRender = false;
float Simulation::widthBorderField = 6050;
float Simulation::heightBorderField = 4050;
//FILE * Simulation::outputfile = fopen("C:\\Users\\Bill\\Desktop\\testee.txt","w");
bool Simulation::gravar = false;
int Simulation::count = 0;

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

/**
* Método do PhysX adaptado
*/
void DrawWireShapeIME(NxShape *shape, const NxVec3& color)
{
	glColor4f(color.x, color.y, color.z, 1.0f);
	switch(shape->getType())
	{
	case NX_SHAPE_PLANE:
		DrawWirePlane(shape, color);
		break;
	case NX_SHAPE_BOX:
		DrawWireBox(shape, color);
		break;
	case NX_SHAPE_SPHERE:
		DrawWireSphere(shape, color);
		break;
	case NX_SHAPE_CAPSULE:
		DrawWireCapsule(shape, color);
		break;
	case NX_SHAPE_CONVEX:
		DrawWireConvex(shape, color);
		break;		
	case NX_SHAPE_MESH:
		DrawWireMesh(shape, color);
		break;
	default:
		break;
	}
}

/**
* Método do PhysX adaptado
*/
void DrawShapeIME(NxShape* shape, const NxVec3& color)
{
	glColor4f(color.x, color.y, color.z, 1.0f);
	switch(shape->getType())
	{
	case NX_SHAPE_PLANE:
		DrawPlane(shape);
		break;
	case NX_SHAPE_BOX:
		DrawBox(shape, color);
		break;
	case NX_SHAPE_SPHERE:
		DrawSphere(shape, color);
		break;
	case NX_SHAPE_CAPSULE:
		DrawCapsule(shape, color);
		break;
	case NX_SHAPE_CONVEX:
		DrawConvex(shape, color);
		break;
	case NX_SHAPE_MESH:
		DrawMesh(shape, color);
		break;
	case NX_SHAPE_WHEEL:
		DrawWheelShape(shape);
		break;
	default:
		break;
	}
}

/**
* Método do PhysX adaptado
*/
void DrawActorIME(NxActor* actor)
{
	if(actor != NULL)
	{
		NxShape*const* shapes = actor->getShapes();
		NxU32 nShapes = actor->getNbShapes();
		if (actor == NULL || actor->getName() == NULL) 
		{
			while (nShapes--)
			{
				DrawWireShapeIME(shapes[nShapes], NxVec3(1,1,1));
			}
		}
		else
		{
			if (strcmp(actor->getName(), "Campo") == 0) 
			{
				while (nShapes--)
				{
					DrawShapeIME(shapes[nShapes], NxVec3(0,1,0)); //Verde
				}
			}
			else if(strcmp(actor->getName(), "Bola") == 0)
			{
				while (nShapes--)
				{
					DrawShapeIME(shapes[nShapes], NxVec3(5,0.5,0)); //Laranja //1,0.5,0
				}
			}
			else if(strcmp(actor->getName(), "Robo1") == 0 || strcmp(actor->getName(), "Robo2") == 0 || strcmp(actor->getName(), "Robo3") == 0 || strcmp(actor->getName(), "Robo4") == 0 || strcmp(actor->getName(), "Robo5") == 0)
			{
				while (nShapes--)
				{
					DrawShapeIME(shapes[nShapes], NxVec3(0,0,1)); //Azul
				}
			}
			else if(strcmp(actor->getName(), "Robo6") == 0 || strcmp(actor->getName(), "Robo7") == 0 || strcmp(actor->getName(), "Robo8") == 0 || strcmp(actor->getName(), "Robo9") == 0 || strcmp(actor->getName(), "Robo10") == 0)
			{
				while (nShapes--)
				{
					DrawShapeIME(shapes[nShapes], NxVec3(1,1,0)); //Amarelo
				}
			}
			else
			{
				while (nShapes--)
				{
					DrawShapeIME(shapes[nShapes], NxVec3(1,1,1)); //Branco
				}
			}
		}
	}
}

Simulation::Simulation(void)
{
}

Simulation::~Simulation(void)
{
	//~ dos ponteiros do PhsyX em ReleaseNX
	//delete udpServerThread;
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
//This is the function that calls the importer to load the state of the currently selected scene from a file
NX_BOOL Simulation::LoadScene(const char *pFilename,NXU::NXU_FileType type)
{
	NX_BOOL success = false;

	if (gPhysicsSDK)
	{
		char LoadFilename[512];
		FindMediaFile(pFilename, LoadFilename);

		NXU::NxuPhysicsCollection *c = NXU::loadCollection(LoadFilename, type );

		if ( c )
		{
			if (gScenes[gCurrentScene])
			{
				// Release old scene
				releaseScene(*gScenes[gCurrentScene]);
				gScenes[gCurrentScene] = 0;
			}

			if (gPhysicsSDK)
			{
				success = NXU::instantiateCollection( c, *gPhysicsSDK, 0, 0, &gUserNotify );
			}
			NXU::releaseCollection(c);
		}
		else
		{
		}
	}

	gLoad = 0;

	if ( success )
		printf("Cena %d carregada do arquivo %s.\n", gCurrentScene, pFilename);

	return success;
}

//==================================================================================
//This is the function that calls the exporter to save out the state of the currently selected scene to a file
void Simulation::SaveScene(const char *pFilename)
{
	char SaveFilename[512];
	GetTempFilePath(SaveFilename);
	strcat(SaveFilename, pFilename);

	NXU::setUseClothActiveState(true);
	NXU::setUseSoftBodyActiveState(true);

	NXU::NxuPhysicsCollection *c = NXU::extractCollectionScene(gScenes[gCurrentScene]);

	if (c)
	{
		char scratch[512];
		sprintf(scratch, "%s.xml", SaveFilename);
		printf("Saving NxuStream XML file to '%s'\r\n", scratch);
		NXU::saveCollection(c, scratch, NXU::FT_XML, false, false);

		sprintf(scratch, "%s.nxb", SaveFilename);
		printf("Saving NxuStream BINARY file to '%s'\r\n", scratch);
		NXU::saveCollection(c, scratch, NXU::FT_BINARY, true, true);

		sprintf(scratch, "%s.dae", SaveFilename);
		printf("Saving COLLADA Physics 1.4.1 file to '%s'\r\n", scratch);
		NXU::saveCollection(c, scratch, NXU::FT_COLLADA, false, false);

		NXU::releaseCollection(c);

	}

}

//==================================================================================
void Simulation::CreateCube(const NxVec3 &pos, int size, const NxVec3 *initial_velocity)
{
	if (gScenes[gCurrentScene])
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
		gScenes[gCurrentScene]->createActor(ActorDesc)->userData = (void*)size;
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

	if (!InitCooking(gMyAllocator, &gErrorStream)) {
		printf("\nError: Unable to initialize the cooking library, exiting the sample.\n\n");
		return false;
	}

	//gPhysicsSDK->setParameter(NX_SKIN_WIDTH, 0.025f);
	//gPhysicsSDK->setParameter(NX_VISUALIZATION_SCALE, 1.0f);
	//gPhysicsSDK->setParameter(NX_VISUALIZE_COLLISION_SHAPES, 1.0f);

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

	for (NxU32 i = 0; i < gMaxScenes; ++i)
	{
		gCurrentScene = i;
		//if (!InitBlankScene()) return false;
	}
	gCurrentScene = 0;

	return true;
}

//==================================================================================
bool Simulation::InitBlankScene()
{
	if (gPhysicsSDK)
	{
		// Create a blank scene
		NxSceneDesc sceneDesc;
		sceneDesc.gravity = gDefaultGravity;

		gScenes[gCurrentScene] = (NxScene1*)gPhysicsSDK->createScene(sceneDesc);
		if(gScenes[gCurrentScene] == NULL) 
		{
			printf("\nError: Unable to create a PhysX scene, exiting the sample.\n\n");
			return false;
		}

		NxMaterial *defaultMaterial = gScenes[gCurrentScene]->getMaterialFromIndex(0);
		//NxMaterial *defaultMaterial = NxScene_getMaterialFromIndex( gScene, 0 );
		defaultMaterial->setRestitution(0.0f);
		defaultMaterial->setStaticFriction(0.5f);
		defaultMaterial->setDynamicFriction(0.5f);

		// Create ground plane
		NxPlaneShapeDesc planeDesc;
		planeDesc.setToDefault();

		NxActorDesc ActorDesc;
		ActorDesc.shapes.pushBack(&planeDesc);
		gScenes[gCurrentScene]->createActor(ActorDesc);
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
		for (NxU32 i = 0; i < gMaxScenes; ++i)
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
void Simulation::callback_key(unsigned char c, int x, int y)
{
	if(c >= 'A' && c <= 'Z') 
	{
		c = c - 'A' + 'a';
	}
	keyDown[c] = true;
	appKey(c, true);
}

void Simulation::callback_keyUp(unsigned char c, int x, int y)
{
	if(c >= 'A' && c <= 'Z') 
	{
		c = c - 'A' + 'a';
	}
	keyDown[c] = false;
	appKey(c,false);
}

void Simulation::appKey(unsigned char key, bool down)
{
	if (!down)
		return;
#ifndef __PPCGEKKO__	
	bool alt = (glutGetModifiers() & GLUT_ACTIVE_ALT) > 0;
#endif
	switch(key)
	{
	case 27:	exit(0); break;
	case 'p':	gPause = !gPause; break;
	case 'f':	
		break;
	case 'v':	//gDebugVisualization = !gDebugVisualization; break;

		//case '+':	break;
		//case '-':	break;
	case 'e':
		{
			//NxAllRobots::selectNext();
		} 
		break;

	case 'r':
		{
			//NxVec3 t;
			//NxVec3 vel;
			//getCurrentPosAndDirection(t, vel);
			//
			//vel.normalize();
			//vel*=30.0f;
			//CreateCube(t, &vel);

			NxActor* kickerActor = getActorKicker(0, 4);
			kickerActor->addForce(NxVec3(0.1,0,0));
			//kickerActor->setLinearVelocity(NxVec3(0,10,0));
		}
		break;

	case 'c': 
		{


			//NxVec3 t = gEye;
			//NxVec3 Vel = gDirection;
			//Vel.normalize();
			//Vel *= 200.0f;
			//CreateCube(t, 20, &Vel);
		}
		break;

	case 'u':
		{
			simulate();
		}
		break;

	case 'h':
		{
			NxActor* actor = getActorBall(0);
			if(actor != NULL) 
			{
				actor->addForce(NxVec3(-0.01,0,0));
				//actor->setLinearVelocity(NxVec3(1,0,0));
				//actor->raiseBodyFlag(NxBodyFlag::NX_BF_KINEMATIC);
			}
		}
		break;

	case 'j':
		{
			//NxActor* actor = getActorRobot(0, 1);
			//if(actor != NULL) 
			//{
			//	actor->setGlobalPosition(NxVec3(0, 0, 0));
			//}

			//udpServerThread->stop();
			NxActor* actorDribbler = getActorDribbler(0, 1);
			actorDribbler->addLocalTorque(NxVec3(-10,0,0));
		}
		break;

	case 'k':
		{
			//NxActor* actorDribbler = getActorDribbler(0, 1);
			//actorDribbler->setAngularVelocity(NxVec3(-100,0,0));
		}
		break;

	case '0':
		{
			//gPerfRenderer.toggleEnable();
			/*NxActor* actor = getActorRobot(0, 2);
			if(actor != NULL) 
			{
			NxMat33 orientation =  actor->getGlobalOrientation();
			orientation.rotZ(-3.1416/4);
			actor->setGlobalOrientation(orientation);
			}*/
		}
		break;

	case ' ':
		{
			CreateCube(NxVec3(0.0f, 20.0f, 0.0f), 1+(rand() &3));
		}
		break;

	case 's':
		{
			//CreateStack(10);
			//NxActor* kickerActor = getActorKicker(0, 4);
			//kickerActor->addForce(NxVec3(1,0,0));
			//kickerActor->setLinearVelocity(NxVec3(10,0,0));
			//goToThisPose( 2000/*110*/, 0, 3 * NxPi / 2., 4, 0);
			//simulate();
			//NxVec3 pos = getRobotGlobalPos(4, 0);
			//float ang = getAngle2DFromRobot(4, 0);
			//NxVec3 velLin = getActorRobot(0,4)->getLinearVelocity();
			//NxVec3 velAng = getActorRobot(0,4)->getAngularVelocity();

			//fprintf(outputfile,"%d	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f\n",count, pos.x, pos.y, ang);
			//fprintf(outputfile,"%d	%f	%f\n", count, ang/NxPi*180, velAng.z/NxPi*180); 

			//goToThisPose( 500/*110*/, 500, NxPi / 2., 4, 0);

			//controlRobotByWheels(10, 10, 10, 10, 0, 0, 4, 0);
			controlRobot(10,0,0,0,0,4,0);
			//NxReal speeds[4];
			//speeds[0] = 10;
			//speeds[1] = -10;
			//speeds[2] = -10;
			//speeds[3] = 10;
			//controlWheels(speeds, 0, 4);

			simulate();

			//count++;

			//if(count == 1000) exit(0);
		}
		break;

	case 'b':
		{
			CreateStack(30);
		}
		break;

	case 't':
		{
			CreateTower(30);
		}
		break;

	case '8':
		{
			gEye += gDirection * 100.0f;
		}
		break;

	case '2':
		{
			gEye -= gDirection * 100.0f;
		}
		break;

	case '4':
		{
			gEye -= gNormal * 100.0f;
		}
		break;

	case '6':
		{
			gEye += gNormal * 100.0f;
		}
		break;

	case 'w':
		{
			//NxVec3 t = gEye;
			//NxVec3 Vel = gDirection;
			//Vel.normalize();
			//Vel *= 200.0f;
			//CreateCube(t, 8, &Vel);
			gravar = true;
		}
		break;

	case '1':
		{
			gSave = true;
		}
		break;
	case 'x':
		gLoad = 2;
		break;
	case 'y':
		gLoad = 3;
		break;
	case 'z':
		gLoad = 4;
		break;
	case '3':
		{
			gLoad = 1;
		}
		break;

	case '\t':
		{
			//Switch to the next scene
			++gCurrentScene;
			if (gCurrentScene == gMaxScenes)
			{
				gCurrentScene = 0;
			}
			printf("Scene %d selected.\n", gCurrentScene);
		}
		break;
	}
}

//==================================================================================
void Simulation::ArrowKeyCallback(int key, int x, int y)
{
	callback_key(key, x, y);
}

//==================================================================================
void Simulation::MouseCallback(int button, int state, int x, int y)
{
	gMouseX = x;
	gMouseY = y;
}

//==================================================================================
void Simulation::MotionCallback(int x, int y)
{
	int dx = gMouseX - x;
	int dy = gMouseY - y;

	gDirection.normalize();
	gNormal.cross(gDirection, NxVec3(0, 1, 0));

	NxQuat qx(NxPiF32 *dx * 20 / 180.0f, NxVec3(0, 1, 0));
	qx.rotate(gDirection);
	NxQuat qy(NxPiF32 *dy * 20 / 180.0f, gNormal);
	qy.rotate(gDirection);

	gMouseX = x;
	gMouseY = y;
}

//==================================================================================
bool Simulation::FileExistTestSimple(const char *fname)
{
	char buff[512];
	FindMediaFile(fname, buff);

	FILE *fp=fopen(buff,"rb");
	if(fp == NULL)
	{
		return false;
	}
	else
	{
		fclose(fp);
		return true;
	}
}

void Simulation::CSL_Scene()
{
	//Check if a request was made to clear, save or load a scene
	if (gClear)
	{
		if (gScenes[gCurrentScene])
		{
			gPhysicsSDK->releaseScene(*gScenes[gCurrentScene]);
		}
		//InitBlankScene();
		gClear = false;
	}
	else if (gSave)
	{
		char scratch[512];
		sprintf(scratch,"SceneSave%d", gCurrentScene );
		SaveScene(scratch);
		gSave = false;
	}
	else if (gLoad)
	{
		switch ( gLoad )
		{
		case 1:
			if ( 1 )
			{
				char scratch[512];
				sprintf(scratch,"SceneSave%d.nxb", gCurrentScene ); // load the binary saved version.
				LoadScene(scratch, NXU::FT_BINARY);
			}
			break;
		case 2:
			LoadScene("test.xml", NXU::FT_XML);
			break;
		case 3:
			LoadScene("test.dae", NXU::FT_COLLADA);
			break;
		case 4:
			if(FileExistTestSimple("test.nxb"))
			{
				LoadScene("test.nxb", NXU::FT_BINARY);
			}
			else
			{
				LoadScene("test.xml", NXU::FT_XML);
				SaveScene("testbin");
			}
			break;
		}
	}
}

//==================================================================================
void Simulation::RenderCallback()
{
	if(gScenes == NULL) return;
	if(gScenes[0] == NULL) return;

	//compute elapsed time
	//static unsigned int PreviousTime = 0;
	//unsigned int CurrentTime = getTime();
	//unsigned int ElapsedTime = CurrentTime - PreviousTime;
	//if(ElapsedTime < 10.0f) return;
	//PreviousTime = CurrentTime;

	//for(int i=1; i<11; i++) infinitePath(i);
	//infinitePath(1);
	//infinitePath(3);
	//infinitePath(1);
	//goToThisPose( -130, 10, 3* NxPi / 2., 1, 0);
	//goToThisPose( -50, -50, 3* NxPi / 2., 1, 0);

	//NxVec3 pos = getRobotGlobalPos(4, 0);
	//float ang = getAngle2DFromRobot(4, 0);
	//NxVec3 velLin = getActorRobot(0,4)->getLinearVelocity();
	//NxVec3 velAng = getActorRobot(0,4)->getAngularVelocity();

	//if(gravar)
	//{

	//	//fprintf(outputfile,"%d	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f\n",count, pos.x, pos.y, pos.z, ang, velLin.x, velLin.y, velLin.z, velAng.x, velAng.y, velAng.z);
	//	fprintf(outputfile,"%d	%f	%f\n", count, ang/NxPi*180, velAng.z/NxPi*180); //giro

	//goToThisPose( 1000/*110*/, 1000, 3* NxPi / 2., 4, 0);
	//controlRobotByWheels(10,10,10,10,0,0,4,0);

	//infinitePath(4);
	//simulate();

	//	count++;

	//	if(count == 1000) exit(0);
	//}

	// Clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Setup camera
	setupCamera();

	//Draw
	for (NxU32 i = 0; i < gMaxScenes; ++i)
	{
		if (gScenes[i])
		{
			//Render
			//glPushMatrix();
			//const NxDebugRenderable *dbgRenderable=gScenes[i]->getDebugRenderable();
			//gDebugRenderer.renderData(*dbgRenderable);
			//glEnable(GL_LIGHTING);
			//glPopMatrix();

			glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
			for(unsigned int j = 0 ; j < gScenes[i]->getNbActors() ; j++ )
			{
				DrawActorIME(gScenes[i]->getActors()[j]);
			}
		}

		//Show Render Performance
		/*#ifdef __PPCGEKKO__	
		char buf[256];
		sprintf(buf,
		"Use the arrow keys to move the camera.\n"
		"Press the keys b, +, -, 1 and 2 to create various things.\n");

		GLFontRenderer::setScreenResolution(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		GLFontRenderer::setColor(0.9f, 1.0f, 0.0f, 1.0f);
		GLFontRenderer::print(0.01, 0.9, 0.036, buf, false, 11, true);   
		#else
		//Print profile results (if enabled)
		gPerfRenderer.render(gScenes[i]->readProfileData(true), glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		#endif*/

		//char buf[256];
		//sprintf(buf,"Iteracao Numero: %d\nTempo: %f s\nErro Angular: %f graus\nErro de Posicao X: %f mm\nErro de Posicao Y: %f mm", count, count * 1./60., 90 - ang/NxPi*180, 500 - pos.x, 500 - pos.y);
		//GLFontRenderer::setScreenResolution(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		//GLFontRenderer::setColor(0.9f, 1.0f, 0.0f, 1.0f);
		//GLFontRenderer::print(0.01, 0.9, 0.030, buf, false, 11, true); 
	}

	//glFlush();
	glutSwapBuffers();
}

void Simulation::setupCamera()
{
	// Setup projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT), 1.0f, 10000.0f);
	gluLookAt(gEye.x, gEye.y, gEye.z, gEye.x + gDirection.x, gEye.y + gDirection.y, gEye.z + gDirection.z, 0.0f, 1.0f, 0.0f);
	// Setup modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//==================================================================================
void Simulation::ReshapeCallback(int width, int height)
{
	glViewport(0, 0, width, height);
}

//==================================================================================
void Simulation::IdleCallback()
{
	//TODO: Realizar a exclusão mútua dos dados no momento da renderizacao
	//Mutex
	//while(!flagRender){};
	//flagRender = false;

	glutPostRedisplay();
}

//==================================================================================
void Simulation::simulate()
{
	NxAllRobots::updateAllRobots(timeStep);

	// Start simulation (non blocking)
	// Physics code
	for (NxU32 i = 0; i < gMaxScenes; ++i)
	{
		if (gScenes[i] && !gPause)
		{
			gScenes[i]->setTiming(timeStep, 1, NX_TIMESTEP_FIXED);
			gScenes[i]->simulate(timeStep);
		}
	}

	for (NxU32 i = 0; i < gMaxScenes; ++i)
	{
		if (gScenes[i] && !gPause)
		{
			gScenes[i]->flushStream();
			gScenes[i]->fetchResults(NX_RIGID_BODY_FINISHED, true);
		}
	}

	// ~Physics code
}

void Simulation::simulate(int indexScene)
{
	NxAllRobots::updateAllRobots(timeStep);

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
	NxAllRobots::updateAllRobots(dt);

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

void Simulation::controlWheels( NxReal* wheelsSpeeds, int indexScene, NxI32 indexRobot )
{
	NxRobot* robot = NxAllRobots::getRobotById(indexRobot);
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
}

void Simulation::controlRobot(float speedX, float speedY, float speedAng, float dribblerSpeed, float kickerSpeed, int indexRobot, int indexScene)
{
	NxRobot* robot = NxAllRobots::getRobotById(indexRobot);
	if(robot)
	{
		//Execute kicker
		//executeKicker( kickerSpeed, indexRobot, indexScene );

		//Control dribbler
		//controlDribbler( dribblerSpeed, indexRobot, indexScene );

		//Control wheels
		NxReal* wheelsSpeeds = calcWheelSpeedFromRobotSpeed(speedAng, speedX, speedY, indexRobot, indexScene); //omnidirecionalidade
		controlWheels( wheelsSpeeds, indexScene, indexRobot); 
	}
}

void Simulation::controlRobotByWheels(float speedWheel1, float speedWheel2, float speedWheel3, float speedWheel4, float dribblerSpeed, float kickerSpeed, int indexRobot, int indexScene)
{
	//Execute kicker
	//executeKicker( kickerSpeed, indexRobot, indexScene );

	//Control dribbler
	//controlDribbler( dribblerSpeed, indexRobot, indexScene );

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
	setAngVelocityDribbler(dribblerSpeed, indexRobot, indexScene);
}

void Simulation::executeKicker( float kickerSpeed, int indexRobot, int indexScene )
{
	NxActor* kickerActor = getActorKicker(indexScene, 4);
	//FIXME: nao fazer nada se der NULL
	if(kickerActor != NULL) {
		kickerActor->addForce(NxVec3(kickerSpeed,0,0));
	}
}

void Simulation::setAngVelocityDribbler(NxReal velocityX, int indexRobot, int indexScene)
{
	NxActor* actorDribbler = getActorDribbler(indexScene, 4);
	//FIXME: nao fazer nada se der NULL
	if(actorDribbler != NULL) {
		actorDribbler->setAngularVelocity(NxVec3(-velocityX,0,0));
	}
}

void Simulation::addLocalTorqueDribbler(NxReal torqueX, int indexRobot, int indexScene)
{
	NxActor* actorDribbler = getActorDribbler(indexScene, indexRobot);
	actorDribbler->addLocalTorque(NxVec3(-torqueX,0,0));
}

void Simulation::addLocalForceKicker(NxReal forceX, int indexRobot, int indexScene)
{
	NxActor* actorKicker = getActorKicker(indexScene, indexRobot);
	actorKicker->addLocalTorque(NxVec3(forceX,0,0));
}

NxActor* Simulation::getActorBall(int indexScene)
{
	NxActor* actor = NULL;
	const char* actorName = NULL;
	if( gScenes != NULL )
	{
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
	}
	return actor;
}

NxActor* Simulation::getActorRobot(int indexScene, int indexRobot)
{
	NxActor* actor = NULL;
	const char* actorName = NULL;
	if( gScenes != NULL )
	{
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
	}
	return actor;
}

NxActor* Simulation::getActorRobotByLabel(int indexScene, string robotLabel)
{
	NxActor* actor = NULL;
	const char* actorName = NULL;
	if( gScenes != NULL )
	{
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
						if(strcmp(actorName,robotLabel.c_str())==0) 
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
	}
	return actor;
}

NxActor* Simulation::getActorWheel(int indexScene, int indexRobot, int indexWheel)
{
	NxActor* actor = NULL;
	const char* actorName = NULL;
	if( gScenes != NULL )
	{
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
	}
	return actor;
}

int Simulation::getNumberWheels(int indexScene, int indexRobot)
{
	NxActor* actor = NULL;
	int numberOfWheels = 0;
	const char* actorName = NULL;
	if( gScenes != NULL )
	{
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
	}
	return numberOfWheels;
}

NxActor* Simulation::getActorDribbler(int indexScene, int indexRobot)
{
	NxActor* actor = NULL;
	const char* actorName = NULL;
	if( gScenes != NULL )
	{
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
						string plabel = "Driblador";
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
	}
	return actor;
}

NxActor* Simulation::getActorKicker(int indexScene, int indexRobot)
{
	NxActor* actor = NULL;
	const char* actorName = NULL;
	if( gScenes != NULL )
	{
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
						string plabel = "Chutador";
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
	}
	return actor;
}

NxVec3 Simulation::getFieldExtents(int indexScene)
{
	NxActor* actor = NULL;
	const char* actorName = NULL;
	if( gScenes != NULL )
	{
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

NxJoint* Simulation::getJoint(int indexScene, int indexJoint, int indexRobot)
{
	NxJoint* joint = NULL;
	const char* jointName = NULL;
	if( gScenes != NULL )
	{
		if(gScenes[indexScene]!=NULL)
		{
			gScenes[indexScene]->resetJointIterator();
			for(unsigned int j=0;j<gScenes[indexScene]->getNbJoints();j++)
			{
				joint = gScenes[indexScene]->getNextJoint();
				if(joint != NULL)
				{
					jointName = joint->getName();
					if(jointName != NULL)
					{
						string label;
						string plabel = "Joint-";
						stringstream out;
						stringstream out1;
						out << indexRobot;
						out1 << indexJoint;
						label.append(plabel);
						label.append(out.str());
						label.append("-");
						label.append(out1.str());
						char* arrayLabel = new char[label.size()+1];
						arrayLabel[label.size()]=0;
						memcpy(arrayLabel, label.c_str(), label.size());

						if(strcmp(jointName,arrayLabel)==0)
						{
							delete arrayLabel;
							break;
						}
						else 
						{
							joint = NULL;
							delete arrayLabel;
						}
					}
				}
				else continue;
			}
		}
	}
	return joint;
}

NxArray<NxJoint*> Simulation::getJoints(int indexScene, int indexRobot)
{
	NxArray<NxJoint*> joints;
	NxJoint* joint = NULL;
	const char* jointName = NULL;
	if( gScenes != NULL )
	{
		if(gScenes[indexScene]!=NULL)
		{
			gScenes[indexScene]->resetJointIterator();
			for(unsigned int j=0;j<gScenes[indexScene]->getNbJoints();j++)
			{
				joint = gScenes[indexScene]->getNextJoint();
				if(joint != NULL)
				{
					jointName = joint->getName();
					if(jointName != NULL)
					{
						string label;
						string plabel = "Joint-";
						stringstream out;
						stringstream out1;
						out << indexRobot;
						label.append(plabel);
						label.append(out.str());
						char* arrayLabel = new char[label.size()+1];
						arrayLabel[label.size()]=0;
						memcpy(arrayLabel, label.c_str(), label.size());
						
						char* jointNameAux = new char[strlen(jointName)-1];
						jointNameAux[strlen(jointName)-2]=0;
						memcpy(jointNameAux, jointName, strlen(jointName)-2);
						
						if(strcmp(jointNameAux,arrayLabel)==0)
						{
							delete arrayLabel;
							delete jointNameAux;
							joints.push_back(joint);
						}
						else 
						{
							joint = NULL;
							delete arrayLabel;
							delete jointNameAux;
						}
					}
				}
				else continue;
			}
		}
	}
	return joints;
}

void Simulation::function(int argc, char **argv)
{
	//printf("Pressione a teclas w, space, s, b, e t para criar varios objetos.\n");
	//printf("Pressione 1 para salvar a cena atual 3 para carregar do arquivo para a cena atual.\n");
	//printf("Pressione c para limpar a cena atual.\n");
	//printf("Pressione TAB para seleionar a proxima cena.\n");
	printf("Use as teclas direcionais ou 2, 4, 6 e 8 ou d, f, e e g para se mover.\nUse o mouse para girar a camera.\n");
	//printf("Pressione p para pausar a simulacao.\n");
	//printf("Pressione X para carregar 'test.xml'\n");
	//printf("Pressione Y para carregar 'test.dae'\n");
	//printf("Pressione Z para carregar 'testbin.nxb'\n");

#if defined(_XBOX) || defined(__CELLOS_LV2__)
	glutRemapButtonExt(8, '1', false); // Left shoulder to save
	glutRemapButtonExt(9, 'c', false); // Right shoulder to clear
	glutRemapButtonExt(8, '3', true); // Shift + left shoulder to load
#endif
	// Initialize Glut
	glutInit(&argc, argv);
	//glutInitWindowSize(512, 512);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	gMainHandle = glutCreateWindow("Simulação - RobotIME");
	glutSetWindow(gMainHandle);
	glutDisplayFunc(RenderCallback);
	glutReshapeFunc(ReshapeCallback);
	glutIdleFunc(IdleCallback);
	glutKeyboardFunc(callback_key);
	glutKeyboardUpFunc(callback_keyUp);
	glutSpecialFunc(ArrowKeyCallback);
	glutMouseFunc(MouseCallback);
	glutMotionFunc(MotionCallback);
	MotionCallback(0, 0);
	atexit(ReleaseNx);

	// Setup default render states
	glClearColor(0.3f, 0.4f, 0.5f, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_CULL_FACE);

	// Setup lighting
	glEnable(GL_LIGHTING);
	float AmbientColor[] = {0.0f, 0.1f, 0.2f, 0.0f};
	float DiffuseColor[] = {1.0f, 1.0f, 1.0f, 0.0f};
	float SpecularColor[] = {0.0f, 0.0f, 0.0f, 0.0f};
	float Position[] = {100.0f, 100.0f, 400.0f, 1.0f};

	glutFullScreen();

	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularColor);
	glLightfv(GL_LIGHT0, GL_POSITION, Position);
	glEnable(GL_LIGHT0);

	bool init = InitNx();
	Simulation::CSL_Scene();

	if(gScenes != NULL)
	{
		if(gScenes[0] != NULL)
		{
			//gScenes[0]->setUserContactReport( robotContactReport );
			//createRobotWithDesc(1, 0);
			//createRobotWithDesc(2, 0);
			//createRobotWithDesc(3, 0);
			buildModelRobotWithDesc( 4, 0 );
			//cloneRobot( 1, 0, 4, NxVec3( 1000, 1000, 20 ) );
			//createRobotWithDesc(5, 0);
			//createRobotWithDesc(6, 0);
			//createRobotWithDesc(7, 0);
			//createRobotWithDesc(8, 0);
			//createRobotWithDesc(9, 0);
			//createRobotWithDesc(10, 0);
		}
	}

	//Init speeds/torques to calc omni
	NxAllRobots::setActiveRobot(0);
	for(int i=0; i<=NxAllRobots::getBiggestIndexRobot(); i++)
	{
		NxRobot* nxRobot = NxAllRobots::getActiveRobot();
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
		Simulation::lastWheelSpeeds.push_back(wheels);
		Simulation::lastDesiredWheelSpeeds.push_back(wheels);
		Simulation::lastWheelTorques.push_back(wheels);
		NxAllRobots::selectNext();
	}

	// Initialize physics scene and start the application main loop if scene was created
	if (init)
		glutMainLoop(); 
}

void Simulation::infinitePath(int indexRobot)
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

	NxVec3 posRobot = getRobotGlobalPos(indexRobot, 0);
	NxReal distance = calcDistanceVec2D(pontos[i[indexRobot-1]].x, pontos[i[indexRobot-1]].y, posRobot.x, posRobot.y);
	if( distance < 100 ) 
	{
		flags[indexRobot-1][i[indexRobot-1]]=true;
	}

	goToThisPose( pontos[i[indexRobot-1]].x, pontos[i[indexRobot-1]].y, 3* NxPi / 2., indexRobot, 0);
}

//void Simulation::refreshDataFromServer()
//{
//	Simulation::parserDataFromServer();
//
//	////Bola
//	//NxActor* actorBall = getActorBall(0);
//	//if(actorBall != NULL) 
//	//{
//	//	actorBall->setGlobalPosition(NxVec3(UDPServer::dataBaseVision[UDPServer::ptrDataBaseVision].ballX, UDPServer::dataBaseVision[UDPServer::ptrDataBaseVision].ballY, UDPServer::ballRadius/*actorBall->getGlobalPosition().z*/));
//	//	actorBall->setLinearVelocity(NxVec3(UDPServer::dataBaseVision[UDPServer::ptrDataBaseVision].ballSpeedX, UDPServer::dataBaseVision[UDPServer::ptrDataBaseVision].ballSpeedY, 0));
//	//}
//
//	////Robos
//	//for(int i=1; i<=UDPServer::numRobots ;i++)
//	//{
//	//	NxActor* actorRobot = getActorRobot(0, i);
//	//	if(actorRobot != NULL) 
//	//	{
//	//		NxMat34 pose = actorRobot->getGlobalPose();
//	//		pose.M.rotZ(UDPServer::dataBaseVision[UDPServer::ptrDataBaseVision].robots[i-1][3]);
//	//		pose.t = NxVec3(UDPServer::dataBaseVision[UDPServer::ptrDataBaseVision].robots[i-1][1], UDPServer::dataBaseVision[UDPServer::ptrDataBaseVision].robots[i-1][2], 0/*actorRobot->getGlobalPosition().z*/);
//	//		actorRobot->setGlobalPose(pose);
//	//	}
//	//}
//}
//
//void Simulation::parserDataFromServer()
//{
//	string temp; 
//	std::stringstream os(((UDPServerThread*)Simulation::udpServerThread)->udpserver.getLastReceivedString());
//	os >> temp;
//	if(temp.compare("1") == 0)//pacote 1
//	{
//		
//	}
//}

void Simulation::setBallGlobalPos(NxVec3 pos, int indexScene)
{
	NxActor* actorBall = getActorBall(indexScene);
	if(actorBall != NULL) 
	{
		actorBall->setGlobalPosition(pos);
	}
}

void Simulation::setBallLinearVelocity(NxVec3 linVel, int indexScene)
{
	NxActor* actorBall = getActorBall(indexScene);
	if(actorBall != NULL) 
	{
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
	//Velocidades Maximas
	NxReal maxSpeedAng = 6;
	NxReal maxLinearSpeed = 6000;

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
	NxActor* robot = getActorRobot(indexScene, indexRobot);
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
	NxRobot* nxRobot = NxAllRobots::getRobotById(indexRobot);
	int nbWheels = nxRobot->getNbWheels();
	NxReal* speeds = new NxReal[nbWheels];

	for(int i=0; i<nbWheels; i++)
	{
		//NxVec3 wheelPosRel = nxRobot->getWheel(i)->getWheelPos() - nxRobot->getBodyPos();
		NxReal angPosWheel = ((NxWheel2*)nxRobot->getWheel(i))->angWheelRelRobot;
		speeds[i] = -NxMath::sin(angPosWheel) * ( speedX * NxMath::cos( -angRobo ) + speedY * NxMath::sin( angRobo ) ) +
			NxMath::cos(angPosWheel) * ( speedX * NxMath::sin( -angRobo ) + speedY * NxMath::cos( angRobo ) ) +
			speedAng * nxRobot->bodyRadius;
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
	if(biggestValue > 0.0001)
	{
		NxReal maxSpeed = 21;
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
	currentWheelTorque = (Simulation::lastWheelTorques[indexRobot])[indexWheel] + inertiaMoment * 20. * (currentDesiredWheelSpeed - currentWheelSpeed) - inertiaMoment * 19.35 * ((Simulation::lastDesiredWheelSpeeds[indexRobot])[indexWheel] - (Simulation::lastWheelSpeeds[indexRobot])[indexWheel]);

	//Avançando iteração
	Simulation::lastDesiredWheelSpeeds[indexRobot][indexWheel] = currentDesiredWheelSpeed;
	Simulation::lastWheelTorques[indexRobot][indexWheel] = currentWheelTorque;
	Simulation::lastWheelSpeeds[indexRobot][indexWheel] = currentWheelSpeed;

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
/////////////////////////////////////////////////CLASS MyUserNotify////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////CLASS MyUserNotify////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////CLASS MyUserNotify////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////CLASS MyUserNotify////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////CLASS MyUserNotify////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////CLASS MyUserNotify////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////CLASS MyUserNotify////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////CLASS MyUserNotify////////////////////////////////////////////////////////////////////

MyUserNotify::MyUserNotify(void)
{
}

MyUserNotify::~MyUserNotify(void)
{
}

void	MyUserNotify::NXU_errorMessage(bool isError, const char *str)
{
	if (isError)
	{
		printf("NxuStream ERROR: %s\r\n", str);
	}
	else
	{
		printf("NxuStream WARNING: %s\r\n", str);
	}
}

void	MyUserNotify::NXU_notifyScene(NxU32 sno,	NxScene	*scene,	const	char *userProperties)
{
	Simulation::gScenes[Simulation::gCurrentScene] = (NxScene1*)scene;
	Simulation::gPhysicsSDK->setParameter(NX_VISUALIZATION_SCALE, 1.0f);
	Simulation::gPhysicsSDK->setParameter(NX_VISUALIZE_COLLISION_SHAPES, 1.0f);
	Simulation::gPhysicsSDK->setParameter(NX_VISUALIZE_CLOTH_MESH, 1.0f );
}

void	MyUserNotify::NXU_notifyJoint(NxJoint	*joint,	const	char *userProperties){}

void	MyUserNotify::NXU_notifyActor(NxActor	*actor,	const	char *userProperties){}

void	MyUserNotify::NXU_notifyCloth(NxCloth	*cloth,	const	char *userProperties){}

void	MyUserNotify::NXU_notifyFluid(NxFluid	*fluid,	const	char *userProperties){}

void 	MyUserNotify::NXU_notifyTriangleMesh(NxTriangleMesh *t,const char *userProperties){}

void 	MyUserNotify::NXU_notifyConvexMesh(NxConvexMesh *c,const char *userProperties){}

void 	MyUserNotify::NXU_notifyClothMesh(NxClothMesh *t,const char *userProperties){}

void 	MyUserNotify::NXU_notifyCCDSkeleton(NxCCDSkeleton *t,const char *userProperties){}

void 	MyUserNotify::NXU_notifyHeightField(NxHeightField *t,const char *userProperties){}

NxScene *MyUserNotify::NXU_preNotifyScene(unsigned	int	sno, NxSceneDesc &scene, const char	*userProperties)
{
	assert( Simulation::gScenes[Simulation::gCurrentScene] == 0 );
	if ( Simulation::gScenes[Simulation::gCurrentScene] )
	{
		Simulation::releaseScene(*Simulation::gScenes[Simulation::gCurrentScene]);
		Simulation::gScenes[Simulation::gCurrentScene] = 0;
	}
	return 0;
}

bool	MyUserNotify::NXU_preNotifyJoint(NxJointDesc &joint, const char	*userProperties) { return	true; }

bool	MyUserNotify::NXU_preNotifyActor(NxActorDesc &actor, const char	*userProperties)
{
	for (NxU32 i=0; i<actor.shapes.size(); i++)
	{
		NxShapeDesc *s = actor.shapes[i];
		s->shapeFlags|=NX_SF_VISUALIZATION; // make sure the shape visualization flags are on so we can see things!
	}
	return true;
}

bool 	MyUserNotify::NXU_preNotifyTriangleMesh(NxTriangleMeshDesc &t,const char *userProperties) { return true;	}

bool 	MyUserNotify::NXU_preNotifyConvexMesh(NxConvexMeshDesc &t,const char *userProperties)	{	return true; }

bool 	MyUserNotify::NXU_preNotifyClothMesh(NxClothMeshDesc &t,const char *userProperties) { return true; }

bool 	MyUserNotify::NXU_preNotifyCCDSkeleton(NxSimpleTriangleMesh &t,const char *userProperties)	{	return true; }

bool 	MyUserNotify::NXU_preNotifyHeightField(NxHeightFieldDesc &t,const char *userProperties) {	return true; }

bool 	MyUserNotify::NXU_preNotifySceneInstance(const char *name,const char *sceneName,const char *userProperties,NxMat34 &rootNode,NxU32 depth) { return true; }


void	MyUserNotify::NXU_notifySceneFailed(unsigned	int	sno, NxSceneDesc &scene, const char	*userProperties) { }

void	MyUserNotify::NXU_notifyJointFailed(NxJointDesc &joint, const char	*userProperties) {  }

void	MyUserNotify::NXU_notifyActorFailed(NxActorDesc &actor, const char	*userProperties) { }

void 	MyUserNotify::NXU_notifyTriangleMeshFailed(NxTriangleMeshDesc &t,const char *userProperties) {	}

void 	MyUserNotify::NXU_notifyConvexMeshFailed(NxConvexMeshDesc &t,const char *userProperties)	{	 }

void 	MyUserNotify::NXU_notifyClothMeshFailed(NxClothMeshDesc &t,const char *userProperties) { }

void 	MyUserNotify::NXU_notifyCCDSkeletonFailed(NxSimpleTriangleMesh &t,const char *userProperties)	{	 }

void 	MyUserNotify::NXU_notifyHeightFieldFailed(NxHeightFieldDesc &t,const char *userProperties) {	}
