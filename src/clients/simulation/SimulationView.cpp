#include "SimulationView.h"
#include "UDPMulticastSenderSSLVision.h"
#include "UDPServerSimInt.h"
#include <QTimer>
#include "DrawObjects.h"
#include "config.h"
#include "BmpLoader.h"

NxVec3 SimulationView::gEye = NxVec3(0, -4000, 3700.0f);
NxVec3 SimulationView::Dir = NxVec3(0, 1, -0.9); 
NxVec3 SimulationView::N = NxVec3();
NxVec3 SimulationView::Up = NxVec3();
int SimulationView::mx = 0;
int SimulationView::my = 0;
int SimulationView::gMainHandle = 0;
bool SimulationView::keyDown[256];
int SimulationView::count = 0;
DebugRenderer SimulationView::gDebugRenderer = DebugRenderer();
PerfRenderer SimulationView::gPerfRenderer;
bool SimulationView::gTextEnabled(true);
GLdouble SimulationView::zNear = 0.9f;
GLdouble SimulationView::zFar = 10000.0f;//
QMapIterator<int, NxScene1*> SimulationView::indexRenderScene = QMapIterator<int, NxScene1*>(QMap<int, NxScene1*>());
bool SimulationView::gDebugVisualization = false;
bool SimulationView::bRightMouseButtonPressed = false;
ActorPicking* SimulationView::actorPicking = NULL;
Simulation* SimulationView::simulation = new Simulation();
GLuint SimulationView::mTexId = 0;

SimulationView::SimulationView(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	indexRenderScene = QMapIterator<int, NxScene1*>(simulation->gScenes);
	indexRenderScene.next();
	ui.setupUi(this);

	intServer = new UDPServerSimInt(parent, this->simulation);
#ifdef REALPORT
	visionServer = new UDPMulticastSenderSSLVision(parent, this->simulation);
#else
	visionServer = new UDPMulticastSenderSSLVision(parent, this->simulation, "224.5.23.2", 11002);
#endif

	timerSim = new QTimer(this);
	connect(timerSim, SIGNAL(timeout()), this, SLOT(simulate()));
	timerSim->start(simulation->timeStep * 1000);

	const char *texFilename = "campoRules.bmp";
	if (texFilename)
		createTexture(texFilename);
}

SimulationView::~SimulationView()
{
	delete visionServer;
	delete intServer;
	delete simulation;
	delete timerSim;
	if (mTexId) {
		glDeleteTextures(1, &mTexId);
		mTexId = 0;
	}
}

void SimulationView::simulate()
{
	simulation->simulateReal(1./60.);
}

void DrawForce(NxActor* actor, NxVec3& forceVec, const NxVec3& color)
{
	// draw only if the force is large enough
	NxReal force = forceVec.magnitude();
	if (force < 0.1f)  return;

	forceVec = 3*forceVec/force;

	NxVec3 pos = actor->getCMassGlobalPosition();
	DrawArrow(pos, pos + forceVec, color);
}
/**
* M�todo do PhysX adaptado
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
* M�todo do PhysX adaptado
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
* M�todo do PhysX adaptado
*/
void DrawActorIME(NxActor* actor)
{
	if(actor != NULL)
	{
		//const char* teste = actor->getName();
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
					DrawShapeIME(shapes[nShapes], NxVec3(0.3,1,0.3)); //Verde
				}
			}
			else if(strcmp(actor->getName(), "Bola") == 0)
			{
				while (nShapes--)
				{
					DrawShapeIME(shapes[nShapes], NxVec3(5,0.5,0.3)); //Laranja //1,0.5,0
				}
			}
			else if(strcmp(actor->getName(), "Robo0-1") == 0 || strcmp(actor->getName(), "Robo1-1") == 0 || strcmp(actor->getName(), "Robo2-1") == 0 || strcmp(actor->getName(), "Robo3-1") == 0 || strcmp(actor->getName(), "Robo4-1") == 0 || strcmp(actor->getName(), "Robo5-1") == 0 || strcmp(actor->getName(), "Robo6-1") == 0 || strcmp(actor->getName(), "Robo7-1") == 0  || strcmp(actor->getName(), "Robo8-1") == 0 || strcmp(actor->getName(), "Robo9-1") == 0 || strcmp(actor->getName(), "Robo10-1") == 0)
			{
				while (nShapes--)
				{
					const char* shapeName = shapes[nShapes]->getName();
					if(shapeName){
						char* dribblerName = new char[10];//"Driblador\0"
						dribblerName[9] = 0;
						memcpy(dribblerName, shapeName, strlen(dribblerName));

						char* kickerName = new char[9];//"Chutador\0"
						kickerName[8] = 0;
						memcpy(kickerName, shapeName, strlen(kickerName));

						if(strcmp(dribblerName, "Driblador") == 0){
							DrawShapeIME(shapes[nShapes], NxVec3(1,1,1)); 
						}
						else if(strcmp(kickerName, "Chutador") == 0){
							DrawShapeIME(shapes[nShapes], NxVec3(1,1,1)); 
						}
						else{
							DrawShapeIME(shapes[nShapes], NxVec3(0.3,0.3,1.)); //Azul
						}
						delete dribblerName;
						delete kickerName;
					}
					else{
						DrawShapeIME(shapes[nShapes], NxVec3(0,0,0)); 
					}
				}
			}
			else if(strcmp(actor->getName(), "Robo0-0") == 0 || strcmp(actor->getName(), "Robo1-0") == 0 || strcmp(actor->getName(), "Robo2-0") == 0 || strcmp(actor->getName(), "Robo3-0") == 0 || strcmp(actor->getName(), "Robo4-0") == 0 || strcmp(actor->getName(), "Robo5-0") == 0 || strcmp(actor->getName(), "Robo6-0") == 0 || strcmp(actor->getName(), "Robo7-0") == 0  || strcmp(actor->getName(), "Robo8-0") == 0 || strcmp(actor->getName(), "Robo9-0") == 0 || strcmp(actor->getName(), "Robo10-0") == 0)
			{
				while (nShapes--)
				{
					const char* shapeName = shapes[nShapes]->getName();
					if(shapeName){
						char* dribblerName = new char[10];//"Driblador\0"
						dribblerName[9] = 0;
						memcpy(dribblerName, shapeName, strlen(dribblerName));

						char* kickerName = new char[9];//"Chutador\0"
						kickerName[8] = 0;
						memcpy(kickerName, shapeName, strlen(kickerName));

						if(strcmp(dribblerName, "Driblador") == 0){
							DrawShapeIME(shapes[nShapes], NxVec3(1,1,1)); 
						}
						else if(strcmp(kickerName, "Chutador") == 0){
							DrawShapeIME(shapes[nShapes], NxVec3(1,1,1)); 
						}
						else{
							DrawShapeIME(shapes[nShapes], NxVec3(1,1,0.3)); //Amarelo
						}
						delete dribblerName;
						delete kickerName;
					}
					else{
						DrawShapeIME(shapes[nShapes], NxVec3(0,0,0)); 
					}
				}
			}
			else
			{
				while (nShapes--)
				{
					//const char* nameee = shapes[nShapes]->getName();
					DrawShapeIME(shapes[nShapes], NxVec3(1,1,1)); //Branco
				}
			}
		}
	}
}


//SimulationView::SimulationView(void)
//{
//	AviGen.SetRate(20);	// set 20fps
//
//	AviGen.SetBitmapHeader(GetActiveView());	// get bitmap info out of the view
//
//	hr=AviGen.InitEngine()	// start engine
//
//	if (FAILED(hr))
//	{
//		AfxMessageBox(avi.GetLastErrorMessage());
//		goto Cleaning;
//	}
//
//	lpbih=AviGen.GetBitmapInfo(); // getting bitmap info
//
//
//	// allocating memory for bmBits
//
//	bmBits=new BYTE[3 /* BRG*/ * lpbih->biWidth* lpbih->biHeight];	
//}

//==================================================================================
void SimulationView::callback_key(unsigned char c, int x, int y)
{
	if(c >= 'A' && c <= 'Z') 
	{
		c = c - 'A' + 'a';
	}
	keyDown[c] = true;
	appKey(c, true);
}

void SimulationView::callback_keyUp(unsigned char c, int x, int y)
{
	if(c >= 'A' && c <= 'Z') 
	{
		c = c - 'A' + 'a';
	}
	keyDown[c] = false;
	appKey(c,false);
}

void SimulationView::appKey(unsigned char key, bool down)
{
	if (!down)
		return;
#ifndef __PPCGEKKO__	
	bool alt = (glutGetModifiers() & GLUT_ACTIVE_ALT) > 0;
#endif
	switch(key)
	{
	case 27:	exit(0); break;
	case 'p':	simulation->gPause = !simulation->gPause; break;
	case 'f':	//simulation->controlDribbler(0.1, 4, indexRenderScene);
		break;
	case 'v':	gDebugVisualization = !gDebugVisualization; break;

		//case '+':	break;
		//case '-':	break;
	case 'e':
		{
			indexRenderScene.value()->field->setDimensions(7400, 5400, 6000, 0, 200., 700., 160.);
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

			//simulation->controlKicker(0.1, 4, 0);
			//kickerActor->setLinearVelocity(NxVec3(0,10,0));
			NxAllRobots* robots = indexRenderScene.value()->allRobots;

			robots->getRobotByIdByTeam(5, 1)->resetToInitialPose();
			robots->getRobotByIdByTeam(5, 1)->setGlobalPosition(NxVec3( simulation->sideBlue*1000, 1000 ,30));
			robots->getRobotByIdByTeam(5, 1)->putToSleep();

			robots->getRobotByIdByTeam(4, 1)->resetToInitialPose();
			robots->getRobotByIdByTeam(4, 1)->setGlobalPosition(NxVec3( simulation->sideBlue*1000, 0    ,30));
			robots->getRobotByIdByTeam(4, 1)->putToSleep();

			robots->getRobotByIdByTeam(3, 1)->resetToInitialPose();
			robots->getRobotByIdByTeam(3, 1)->setGlobalPosition(NxVec3( simulation->sideBlue*1000, -1000, 30));
			robots->getRobotByIdByTeam(3, 1)->putToSleep();

			robots->getRobotByIdByTeam(2, 1)->resetToInitialPose();
			robots->getRobotByIdByTeam(2, 1)->setGlobalPosition(NxVec3( simulation->sideBlue*2000, 1000 , 30));
			robots->getRobotByIdByTeam(2, 1)->putToSleep();

			robots->getRobotByIdByTeam(1, 1)->resetToInitialPose();
			robots->getRobotByIdByTeam(1, 1)->setGlobalPosition(NxVec3( simulation->sideBlue*2000, 0    , 30));
			robots->getRobotByIdByTeam(1, 1)->putToSleep();

			robots->getRobotByIdByTeam(0, 1)->resetToInitialPose();
			robots->getRobotByIdByTeam(0, 1)->setGlobalPosition(NxVec3( simulation->sideBlue*2000, -1000, 30));
			robots->getRobotByIdByTeam(0, 1)->putToSleep();

			robots->getRobotByIdByTeam(5, 0)->resetToInitialPose();
			robots->getRobotByIdByTeam(5, 0)->setGlobalPosition(NxVec3(-simulation->sideBlue*1000, 1000 , 30));
			robots->getRobotByIdByTeam(5, 0)->putToSleep();

			robots->getRobotByIdByTeam(4, 0)->resetToInitialPose();
			robots->getRobotByIdByTeam(4, 0)->setGlobalPosition(NxVec3(-simulation->sideBlue*1000, 0    , 30));
			robots->getRobotByIdByTeam(4, 0)->putToSleep();

			robots->getRobotByIdByTeam(3, 0)->resetToInitialPose();
			robots->getRobotByIdByTeam(3, 0)->setGlobalPosition(NxVec3(-simulation->sideBlue*1000, -1000, 30));
			robots->getRobotByIdByTeam(3, 0)->putToSleep();

			robots->getRobotByIdByTeam(2, 0)->resetToInitialPose();
			robots->getRobotByIdByTeam(2, 0)->setGlobalPosition(NxVec3(-simulation->sideBlue*2000, 1000 , 30));
			robots->getRobotByIdByTeam(2, 0)->putToSleep();

			robots->getRobotByIdByTeam(1, 0)->resetToInitialPose();
			robots->getRobotByIdByTeam(1, 0)->setGlobalPosition(NxVec3(-simulation->sideBlue*2000, 0    , 30));
			robots->getRobotByIdByTeam(1, 0)->putToSleep();

			robots->getRobotByIdByTeam(0, 0)->resetToInitialPose();
			robots->getRobotByIdByTeam(0, 0)->setGlobalPosition(NxVec3(-simulation->sideBlue*2000, -1000, 30));
			robots->getRobotByIdByTeam(0, 0)->putToSleep();

			NxBall* ball = indexRenderScene.value()->ball;
			ball->ball->setGlobalPosition(NxVec3(0,0,21.5));
			ball->ball->putToSleep();
		}
		break;

	case 'c': 
		{
			if(indexRenderScene.hasNext())
				indexRenderScene.next();
			else{
				indexRenderScene.toFront();
				indexRenderScene.next();
			}
			actorPicking->scene = indexRenderScene.value()->scene;
			actorPicking->gMouseJoint = NULL;
			actorPicking->gMouseSphere = NULL;
			actorPicking->gMouseDepth = NULL;
			actorPicking->gSelectedActor = NULL;


			NxDistanceJointDesc desc;
			desc.maxDistance = 0.0f;
			desc.minDistance = 0.0f;
			desc.spring.damper = 1.0f;
			desc.spring.spring = 200.0f;
			desc.flags |= NX_DJF_MAX_DISTANCE_ENABLED | NX_DJF_SPRING_ENABLED;
			NxJoint* t = (actorPicking->scene)->createJoint(desc);
			desc.maxDistance = 1;
			//NxVec3 t = gEye;
			//NxVec3 Vel = Dir;
			//Vel.normalize();
			//Vel *= 200.0f;
			//simulation->CreateCube(t, 20, &Vel);
		}
		break;

	case 'u':
		{
			//simulation->simulate();
			gEye = NxVec3(0, -4000, 1700.0f);
		}
		break;

	case 'h':
		{
			NxBall* ball = indexRenderScene.value()->ball;
			NxActor* actor = ball->ball;
			if(actor != NULL) 
			{
				actor->addForce(NxVec3(0,-1000,0));
				//actor->setLinearVelocity(NxVec3(1,0,0));
				//actor->raiseBodyFlag(NxBodyFlag::NX_BF_KINEMATIC);
			}
			NxVec3 teste = ball->ball->getLinearVelocity();
			printf("%f\n", teste.magnitude());
		}
		break;

	case 'j':
		{
			//simulation->parseLegacyString("15 0 1 18.8456 -18.8456 -18.8456 18.8456 0 0 18.8456 -18.8456 -18.8456 18.8456 0 0 18.8456 -18.8456 -18.8456 18.8456 0 0 18.8456 -18.8456 -18.8456 18.8456 0 0 18.8456 -18.8456 -18.8456 18.8456 0 0\n");
			simulation->append("15 0 1 18.8456 -18.8456 -18.8456 18.8456 0 0 18.8456 -18.8456 -18.8456 18.8456 0 0 18.8456 -18.8456 -18.8456 18.8456 0 0 18.8456 -18.8456 -18.8456 18.8456 0 0 18.8456 -18.8456 -18.8456 18.8456 0 0\n");
			//SimulationView::visionServer->startSending();
			//NxActor* actor = getActorRobot(0, 1);
			//if(actor != NULL) 
			//{
			//	actor->setGlobalPosition(NxVec3(0, 0, 0));
			//}

			//udpServerThread->stop();
			//NxActor* actorDribbler = simulation->allRobots.getRobotByIdScene(4, 0)->dribbler
			//actorDribbler->addLocalTorque(NxVec3(-10,0,0));
		}
		break;

	case 'k':
		{
			//NxActor* actorDribbler = getActorDribbler(0, 1);
			//actorDribbler->setAngularVelocity(NxVec3(-100,0,0));
			changeCamera();
		}
		break;

	case '0':
		{
			/*NxActor* actor = getActorRobot(0, 2);
			if(actor != NULL) 
			{
			NxMat33 orientation =  actor->getGlobalOrientation();
			orientation.rotZ(-3.1416/4);
			actor->setGlobalOrientation(orientation);
			}*/
			indexRenderScene.value()->ball->ball->setGlobalPosition(NxVec3(0,0,21.5));
			indexRenderScene.value()->ball->putToSleep();
		}
		break;

	case ' ':
		{
			//simulation->CreateCube(NxVec3(0.0f, 20.0f, 0.0f), 1+(rand() &3), (const NxVec3 *)0, indexRenderScene.key());
			gPerfRenderer.toggleEnable();
			gTextEnabled = !gTextEnabled;
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
			//controlRobot(10,0,0,0,0,4,0);
			//NxReal speeds[4];
			//speeds[0] = 10;
			//speeds[1] = -10;
			//speeds[2] = -10;
			//speeds[3] = 10;
			//controlWheels(speeds, 0, 4);

			simulation->simulate();

			//count++;

			//if(count == 1000) exit(0);
		}
		break;

	case 'b':
		{
			simulation->CreateStack(30);
		}
		break;

	case 't':
		{
			simulation->CreateTower(30);
		}
		break;

	case '8':
		{
			gEye += Dir * 100.0f;
		}
		break;

	case '2':
		{
			gEye -= Dir * 100.0f;
		}
		break;

	case '4':
		{
			gEye -= N * 100.0f;
		}
		break;

	case '6':
		{
			gEye += N * 100.0f;
		}
		break;

	case 'w':
		{
			//NxVec3 t = gEye;
			//NxVec3 Vel = Dir;
			//Vel.normalize();
			//Vel *= 200.0f;
			//CreateCube(t, 8, &Vel);
			//gravar = true;
		}
		break;

	case '1':
		{
			simulation->gSave = true;
		}
		break;
	case 'x':
		simulation->gLoad = 2;
		break;
	case 'y':
		simulation->gLoad = 3;
		break;
	case 'z':
		simulation->gLoad = 4;
		break;
	case '3':
		{
			simulation->gLoad = 1;
		}
		break;

	case '\t':
		{
			//Switch to the next scene
			//++simulation->gBaseScene;
			//if (simulation->gBaseScene == simulation->nbExistScenes)
			//{
			//	simulation->gBaseScene = 0;
			//}
			//printf("Scene %d selected.\n", simulation->gBaseScene);
		}
		break;
	}
}

//==================================================================================
void SimulationView::ArrowKeyCallback(int key, int x, int y)
{
	callback_key(key, x, y);
}

//==================================================================================
void SimulationView::MouseCallback(int button, int state, int x, int y)
{
	mx = x;
	my = y;

	actorPicking->scene = indexRenderScene.value()->scene;
	actorPicking->physicsSDK = simulation->gPhysicsSDK;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
#if !defined(_XBOX) && !defined (__CELLOS_LV2__) // no picking on consoles
		//if (!PickActor(x,y))
		//{

		// this prevents from only grabbing it when the mouse moves
		//	MotionCallback(x,y);
		//}

		actorPicking->PickActor(x,y);
#endif
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		bRightMouseButtonPressed = true;
	}
	else if (state == GLUT_UP)
	{
		actorPicking->LetGoActor();
		bRightMouseButtonPressed = false;
	}
}

//==================================================================================
void SimulationView::MotionCallback(int x, int y)
{
	int dx =  mx - x;
	int dy =  my - y;

	if (actorPicking->gMouseJoint)
	{
		actorPicking->MoveActor(x,y);
	}
	else if(bRightMouseButtonPressed || mx == 0){
		Dir.normalize();
		N.cross(Dir,NxVec3(0,0,1));

		NxQuat qx(NxPiF32 * dx * 20/ 180.0f, NxVec3(0,0,1));
		qx.rotate(Dir);
		//NxFindRotationMatrix

		NxQuat qy(NxPiF32 * dy * 20/ 180.0f, N);
		qy.rotate(Dir);

		Up.cross(N, Dir);
	}


	mx = x;
	my = y;
}

void SimulationView::RenderCallback()
{
	//compute elapsed time
	//static unsigned int PreviousTime = 0;
	//unsigned int CurrentTime = getTime();
	//unsigned int ElapsedTime = CurrentTime - PreviousTime;
	//if(ElapsedTime < 10.0f) return;
	//PreviousTime = CurrentTime;

	// Clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Setup camera
	setupCamera();

	//Draw
	glPushMatrix();
	//for (NxU32 i = 0; i < simulation->nbExistScenes; ++i)
	//{
	if (indexRenderScene.value()->scene)
	{
		//Render
		if(gDebugVisualization){
			//glPushMatrix();
			const NxDebugRenderable *dbgRenderable=indexRenderScene.value()->scene->getDebugRenderable();
			gDebugRenderer.renderData(*dbgRenderable);
			//glEnable(GL_LIGHTING);
			//glPopMatrix();
		}
		else{
			int nbActors = indexRenderScene.value()->scene->getNbActors();
			for(unsigned int j = 0 ; j < nbActors ; j++ )
			{
				DrawActorIME(indexRenderScene.value()->scene->getActors()[j]);
			}
		}
		//draw field lines
		NxField* field = indexRenderScene.value()->field;
		NxVec3 fposition =  field->actorCampo->getGlobalPosition();
		NxReal FIELD_LENGTH =  field->linesLength;
		NxReal FIELD_WIDTH =  field->linesWidth;
		glColor4f(1.f,1.f, 1.f, 1.f);//white
		glLineWidth(6);
		glBegin(GL_LINES);
		glVertex3f(fposition.x, fposition.y - FIELD_WIDTH/2, 8);//fposition.z
		glVertex3f(fposition.x, fposition.y + FIELD_WIDTH/2, 8);//fposition.z
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3f(fposition.x - FIELD_LENGTH/2., fposition.y - FIELD_WIDTH/2., 8);//fposition.z
		glVertex3f(fposition.x + FIELD_LENGTH/2., fposition.y - FIELD_WIDTH/2., 8);//fposition.z
		glVertex3f(fposition.x + FIELD_LENGTH/2., fposition.y + FIELD_WIDTH/2., 8);//fposition.z
		glVertex3f(fposition.x - FIELD_LENGTH/2., fposition.y + FIELD_WIDTH/2., 8);//fposition.z
		glEnd();
		glLineWidth(1);
		DrawCircle(30, NxMat34(NxMat33(NxVec3(1,0,0), NxVec3(0,1,0), NxVec3(0,0,1)), NxVec3(fposition.x - FIELD_LENGTH/2., fposition.y - field->defense_stretch/2., 0)), NxVec3(1.f,1.f, 1.f),  field->defense_radius, false);
		DrawCircle(30, NxMat34(NxMat33(NxVec3(1,0,0), NxVec3(0,1,0), NxVec3(0,0,1)), NxVec3(fposition.x - FIELD_LENGTH/2., fposition.y + field->defense_stretch/2., 0)), NxVec3(1.f,1.f, 1.f),  field->defense_radius, false);
		DrawCircle(30, NxMat34(NxMat33(NxVec3(1,0,0), NxVec3(0,1,0), NxVec3(0,0,1)), NxVec3(fposition.x + FIELD_LENGTH/2., fposition.y - field->defense_stretch/2., 0)), NxVec3(1.f,1.f, 1.f),  field->defense_radius, false);
		DrawCircle(30, NxMat34(NxMat33(NxVec3(1,0,0), NxVec3(0,1,0), NxVec3(0,0,1)), NxVec3(fposition.x + FIELD_LENGTH/2., fposition.y + field->defense_stretch/2., 0)), NxVec3(1.f,1.f, 1.f),  field->defense_radius, false);

		//Print profile results (if enabled)
		gPerfRenderer.render(indexRenderScene.value()->scene->readProfileData(true), glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		if(gTextEnabled) {
			ostringstream out;
			out.precision(4);

			out << "FPS: " << gPerfRenderer.computeFPS() << endl;
			out << "CENA: " << indexRenderScene.key() << endl;
			out << Simulation::cout.str();
			Simulation::cout = ostringstream();

			GLFontRenderer::setScreenResolution(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
			GLFontRenderer::setColor(0.9f, 1.0f, 0.0f, 1.0f);
			GLFontRenderer::print(0.01, 0.9, 0.030, out.str().c_str(), false, 11, true);
		}

		drawTexture(true);
	}

	///* Draw code where bmBits is filled. 
	//For example, to read OpenGL buffer, put 
	//glReadPixels(0,0,lpbih->biWidth,lpbih->biHeight, 
	//GL_BGR_EXT,GL_UNSIGNED_BYTE,bmBits); */ 

	//// adding frame and continue if OK

	//hr=AviGen.AddFrame(bmBits);
	//if (FAILED(hr))
	//{
	//	AfxMessageBox(avi.GetLastErrorMessage());
	//	goto Cleaning;
	//}

	//}
	glPopMatrix();

	//glFlush();
	glutSwapBuffers();
}

void SimulationView::setupCamera()
{
	// Setup projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT), zNear, zFar);
	gluLookAt(gEye.x, gEye.y, gEye.z, gEye.x + Dir.x, gEye.y + Dir.y, gEye.z + Dir.z, Up.x, Up.y, Up.z);

	// Setup modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

bool SimulationView::createTexture(const char *filename)
{
	BmpLoader bl;
	if (!bl.loadBmp(filename)) return false;

	glGenTextures(1, &mTexId);
	if (!mTexId) return false;
	glBindTexture(GL_TEXTURE_2D, mTexId);
#ifndef __PPCGEKKO__
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
		bl.mWidth, bl.mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bl.mRGB);

	return true;
}

void SimulationView::drawTexture(bool shadows)
{
	//static NxU32 numVertices = mNumVertices;
	//NxU32 numElements = mNumIndices;
	//numVertices = mNumVertices;

	//// Disable pressure if tearing occurs
	//if (mTeared && (mCloth->getFlags() & NX_CLF_PRESSURE))
	//{
	//	// Disable Pressure
	//	mCloth->setFlags(mCloth->getFlags() & ~NX_CLF_PRESSURE);
	//	mCloth->setPressure(0);

	//	// Reduce tearing factor
	//	NxReal oldTearing = mCloth->getTearFactor();
	//	oldTearing = (oldTearing - 1) / 3 + 1;
	//	mCloth->setTearFactor(oldTearing);

	//	// Reduce bending stiffness
	//	if (mCloth->getBendingStiffness() > 0.9f)
	//		mCloth->setBendingStiffness(0.2f);

	//	// Apply explosion in the middle of the cloth
	//	NxBounds3 bounds;
	//	mCloth->getWorldBounds(bounds);
	//	NxVec3 center;
	//	bounds.getCenter(center);
	//	NxReal radius = bounds.min.distance(bounds.max);
	//	mCloth->addForceAtPos(center, 7 * NxMath::pow(radius,3), radius, NX_IMPULSE);
	//	printf("Pressure disabled\n");
	//}

	//if (mTexId > 0)
	//{
	//	updateTextureCoordinates();
	//}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	//glVertexPointer(3, GL_FLOAT, sizeof(RenderBufferVertexElement), numVertices, &(mVertexRenderBuffer[0].position.x));
	//glNormalPointer(GL_FLOAT, sizeof(RenderBufferVertexElement), numVertices, &(mVertexRenderBuffer[0].normal.x));

	if (mTexId) {
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		//glTexCoordPointer(2, GL_FLOAT, sizeof(RenderBufferVertexElement), numVertices, &(mVertexRenderBuffer[0].texCoord[0]));

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, mTexId);
		glColor4f(1.0f, 1.0f, 1.0f,1.0f);
	}

//#ifdef __CELLOS_LV2__	
//	glDrawRangeElements(GL_TRIANGLES, 0, numVertices-1, numElements, GL_UNSIGNED_INT, mIndexRenderBuffer);
//#else
//	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, mIndexRenderBuffer);
//#endif

	if (mTexId) {
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_TEXTURE_2D);
	}

//	if (shadows) {
//		const static float ShadowMat[]={ 1,0,0,0, 0,0,0,0, 0,0,1,0, 0,0,0,1 };
//		glPushMatrix();
//		glMultMatrixf(ShadowMat);
//		glDisable(GL_LIGHTING);
//		glColor4f(0.05f, 0.1f, 0.15f,1.0f);
//
//#ifdef __CELLOS_LV2__	
//		glDrawRangeElements(GL_TRIANGLES, 0, numVertices-1, numElements, GL_UNSIGNED_INT, mIndexRenderBuffer);
//#else
//		glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, mIndexRenderBuffer);
//#endif
//		
//		glColor4f(1.0f, 1.0f, 1.0f,1.0f);
//		glEnable(GL_LIGHTING);
//		glPopMatrix();
//	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void SimulationView::changeCamera(){
	static int camera = -1;
	camera++;
	camera %= 8;
	if(camera == 7){
		gEye.x = 2827.0056;
		gEye.y = -2172.7402;
		gEye.z = 981.85626;
		Dir.x = -0.53674126;
		Dir.y = 0.74350190;
		Dir.z = -0.39889067;
		Up.x = -0.21769887;
		Up.y = 0.29394531;
		Up.z = 0.84082383;
	}
	else if(camera == 1){
		gEye.x = 3406.7239;
		gEye.y = 2069.7632;
		gEye.z = 1310.4371;
		Dir.x = -0.65821588;
		Dir.y = -0.57920420;
		Dir.z = -0.48090997;
		Up.x = -0.31406099;
		Up.y = -0.27636138;
		Up.z = 0.77382886;
	}
	else if(camera == 2){
		gEye.x = -2970.4805;
		gEye.y = 2074.9619;
		gEye.z = 1450.4000;
		Dir.x = 0.62727863;
		Dir.y = -0.57703120;
		Dir.z = -0.52302629;
		Up.x = 0.32808322;
		Up.y = -0.30180249;
		Up.z = 0.72643000;
	}
	else if(camera == 3){
		gEye.x = -2993.4980;
		gEye.y = -1929.0206;
		gEye.z = 1344.3374;
		Dir.x = 0.63465542;
		Dir.y = 0.59198189;
		Dir.z = -0.49675944;
		Up.x = 0.34388098;
		Up.y = 0.31686303;
		Up.z = 0.68487775;
	}
	else if(camera == 4){
		gEye.x = -808.44647;
		gEye.y = -821.56024;
		gEye.z = 593.52759;
		Dir.x = 0.74464518;
		Dir.y = 0.57962108;
		Dir.z = -0.33097294;
		Up.x = 0.25994429;
		Up.y = 0.18272002;
		Up.z = 0.88852131;
	}
	else if(camera == 5){
		gEye.x = 880.29547;
		gEye.y = 23.450352;
		gEye.z = 711.28223;
		Dir.x = -0.88668561;
		Dir.y = 0.025686376;
		Dir.z = -0.46165887;
		Up.x = -0.40949470;
		Up.y = 0.0043751383;
		Up.z = 0.78685659;
	}
	else if(camera == 6){
		gEye.x = -3970.3904;
		gEye.y = 77.764908;
		gEye.z = 996.00800;
		Dir.x = 0.90976840;
		Dir.y = -0.011801026;
		Dir.z = -0.41494837;
		Up.x = 0.37753335;
		Up.y = 0.0020033286;
		Up.z = 0.82780254;
	}
	else if(camera == 0){
		gEye.x = 0.0;
		gEye.y = 0.0;
		gEye.z = 5000.;
		Dir.x = 0.0;
		Dir.y = 0.0;
		Dir.z = -1.0;
		Up.x = 0.0;
		Up.y = 1.0;
		Up.z = 0.0;
	}
}

//==================================================================================
void SimulationView::ReshapeCallback(int width, int height)
{
	glViewport(0, 0, width, height);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective (45.0, (GLfloat) width/(GLfloat) height, 1.0, 100.0);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
}

//==================================================================================
void SimulationView::IdleCallback()
{
	//TODO: Realizar a exclus�o m�tua dos dados no momento da renderizacao
	glutPostRedisplay();
}

void SimulationView::mainLoop(int argc, char **argv)
{
	bool init = simulation->initSimulation(1);

	indexRenderScene = QMapIterator<int, NxScene1*>(simulation->gScenes);
	indexRenderScene.next();

	if(actorPicking == NULL)
		actorPicking = new ActorPicking(simulation->gPhysicsSDK, indexRenderScene.value()->scene);//, SimulationView::gMouseJoint, SimulationView::gMouseSphere, SimulationView::gMouseDepth, SimulationView::gSelectedActor);

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
	//glutInit(&argc, argv);
	glutInitWindowSize(1920, 1080);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	gMainHandle = glutCreateWindow("Simula��o - RoboIME");
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
	atexit(Simulation::ReleaseNx);

	// Setup default render states
	glClearColor(0.3f, 0.4f, 0.5f, 1.0);
	glEnable(GL_DEPTH_TEST);//glEnable(GL_DEPTH_BUFFER_BIT);//
	glDepthFunc(GL_LEQUAL);
	glClearDepth(zFar);
	glDepthRange(zNear, zFar);
	glEnable(GL_COLOR_MATERIAL);
#if !defined(__PPCGEKKO__)
	glEnable(GL_CULL_FACE);
#endif

	// Setup lighting
	glEnable(GL_LIGHTING);
	float AmbientColor[] = { 0.0f, 0.1f, 0.2f, 0.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientColor);
	float DiffuseColor[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseColor);
	float SpecularColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularColor);
	float Position[] = { 100.0f, 100.0f, 400.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, Position);
	glEnable(GL_LIGHT0);

	//glutFullScreen();

	// Initialize physics scene and start the application main loop if scene was created
	if (init)
		glutMainLoop(); 
}