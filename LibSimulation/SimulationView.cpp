#include "SimulationView.h"

NxVec3 SimulationView::gEye = NxVec3(0, 0, 4100.0f);
NxVec3 SimulationView::Dir = NxVec3(0, 0, -1); 
NxVec3 SimulationView::N = NxVec3();
int SimulationView::mx = 0;
int SimulationView::my = 0;
int SimulationView::gMainHandle = 0;
bool SimulationView::keyDown[256];//={false};
//FILE * SimulationView::outputfile = fopen("C:\\Users\\Bill\\Desktop\\testee.txt","w");
bool SimulationView::gravar = false;
int SimulationView::count = 0;
DebugRenderer SimulationView::gDebugRenderer = DebugRenderer();
//PerfRenderer    gPerfRenderer = PerfRenderer();
GLdouble SimulationView::zNear = 1.0f;
GLdouble SimulationView::zFar = 10000.0f;//

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
					const char* nameee = shapes[nShapes]->getName();
					DrawShapeIME(shapes[nShapes], NxVec3(1,1,1)); //Branco
				}
			}
		}
	}
}


SimulationView::SimulationView(void)
{
}

SimulationView::~SimulationView(void)
{
}

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
	case 'p':	Simulation::gPause = !Simulation::gPause; break;
	case 'f':	
		break;
	case 'v':	//gDebugVisualization = !gDebugVisualization; break;

		//case '+':	break;
		//case '-':	break;
	case 'e':
		{
			Simulation::allFields.fields[Simulation::gBaseScene].setDimensions(5000, 3000, 0, 0);
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

			NxActor* kickerActor = Simulation::getActorKicker(0, 4);
			kickerActor->addForce(NxVec3(0.1,0,0));
			//kickerActor->setLinearVelocity(NxVec3(0,10,0));
		}
		break;

	case 'c': 
		{


			NxVec3 t = gEye;
			NxVec3 Vel = Dir;
			Vel.normalize();
			Vel *= 200.0f;
			Simulation::CreateCube(t, 20, &Vel);
		}
		break;

	case 'u':
		{
			Simulation::simulate();
		}
		break;

	case 'h':
		{
			NxActor* actorDribbler = Simulation::getActorDribbler(0, 4);
			actorDribbler->addLocalTorque(NxVec3(-10,0,0));
		}
		break;

	case 'j':
		{
			//NxActor* actor = getActorRobot(0, 1);
			//if(actor != NULL) 
			//{
			//	actor->setGlobalPosition(NxVec3(0, 0, 0));
			//}
			NxActor* actor = Simulation::getActorBall(0);
			if(actor != NULL) 
			{
				actor->addForce(NxVec3(-0.016,0,0));
				//actor->setLinearVelocity(NxVec3(1,0,0));
				//actor->raiseBodyFlag(NxBodyFlag::NX_BF_KINEMATIC);
			}
			//udpServerThread->stop();
		}
		break;

	case 'i':
		{
			NxActor* actor = Simulation::getActorBall(0);
			if(actor != NULL) actor->addForce(NxVec3(0,0.016,0));
		}
		break;

	case 'k':
		{
			//NxActor* actorDribbler = getActorDribbler(0, 1);
			//actorDribbler->setAngularVelocity(NxVec3(-100,0,0));
			//Simulation::allRobots.getRobotByIdScene(4, Simulation::gBaseScene)->resetToInitialPose();
			//Simulation::allRobots.getRobotByIdScene(4, Simulation::gBaseScene)->setGlobalPosition(NxVec3(0,0,20));
			//Simulation::allRobots.getRobotByIdScene(4, Simulation::gBaseScene)->putToSleep();
			NxActor* actor = Simulation::getActorBall(0);
			if(actor != NULL) actor->addForce(NxVec3(0,-0.016,0));
		}
		break;

	case 'l':
		{
			NxActor* actor = Simulation::getActorBall(0);
			if(actor != NULL) actor->addForce(NxVec3(0.016,0,0));
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
			Simulation::allBalls.getBallByScene(Simulation::gBaseScene).ball->setGlobalPosition(NxVec3(0,0,30));
			Simulation::allBalls.getBallByScene(Simulation::gBaseScene).ball->putToSleep();
		}
		break;

	case ' ':
		{
			Simulation::CreateCube(NxVec3(0.0f, 20.0f, 0.0f), 1+(rand() &3));
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

			Simulation::simulate();

			//count++;

			//if(count == 1000) exit(0);
		}
		break;

	case 'b':
		{
			Simulation::CreateStack(30);
		}
		break;

	case 't':
		{
			Simulation::CreateTower(30);
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
			gravar = true;
		}
		break;

	case '1':
		{
			Simulation::gSave = true;
		}
		break;
	case 'x':
		Simulation::gLoad = 2;
		break;
	case 'y':
		Simulation::gLoad = 3;
		break;
	case 'z':
		Simulation::gLoad = 4;
		break;
	case '3':
		{
			Simulation::gLoad = 1;
		}
		break;

	case '\t':
		{
			//Switch to the next scene
			++Simulation::gBaseScene;
			if (Simulation::gBaseScene == Simulation::nbExistScenes)
			{
				Simulation::gBaseScene = 0;
			}
			printf("Scene %d selected.\n", Simulation::gBaseScene);
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
}

//==================================================================================
void SimulationView::MotionCallback(int x, int y)
{
	int dx =  mx - x;
	int dy =  my - y;
	
	Dir.normalize();
	N.cross(Dir,NxVec3(0,1,0));

	NxQuat qx(NxPiF32 * dx * 20/ 180.0f, NxVec3(0,1,0));
	qx.rotate(Dir);

	//float teta = NxPiF32 * dx * 2/ 180.0f;
	//NxMat33 rotMat = NxMat33(NxVec3(NxMath::cos(teta),-NxMath::sin(teta),0),NxVec3(NxMath::sin(teta),NxMath::cos(teta),0),NxVec3(0,0,1));
	//Dir = rotMat*Dir;

	NxQuat qy(NxPiF32 * dy * 20/ 180.0f, N);
	qy.rotate(Dir);

	mx = x;
	my = y;
}

//==================================================================================
void SimulationView::RenderCallback()
{
	if(Simulation::gScenes[0] == NULL) return;

	//compute elapsed time
	static unsigned int PreviousTime = 0;
	unsigned int CurrentTime = getTime();
	unsigned int ElapsedTime = CurrentTime - PreviousTime;
	if(ElapsedTime < 10.0f) return;
	PreviousTime = CurrentTime;

	// Clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//if(gravar)
	//{

	//	//fprintf(outputfile,"%d	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f\n",count, pos.x, pos.y, pos.z, ang, velLin.x, velLin.y, velLin.z, velAng.x, velAng.y, velAng.z);
	//	fprintf(outputfile,"%d	%f	%f\n", count, ang/NxPi*180, velAng.z/NxPi*180); //giro

	//goToThisPose( 1000/*110*/, 1000, 3* NxPi / 2., 4, 0);
	//controlRobotByWheels(10,10,10,10,0,0,4,0);

	//float teta = NxPi/180.;
	//Dir.normalize();
	//N.cross(Dir,NxVec3(0,1,0));
	//NxMat33 rotMat = NxMat33(NxVec3(NxMath::cos(teta),-NxMath::sin(teta),0),NxVec3(NxMath::sin(teta),NxMath::cos(teta),0),NxVec3(0,0,1));
	//Dir = rotMat*Dir;

	//Simulation::infinitePath(4,0);
	//Simulation::goToThisPose( 1000/*110*/, 1000, 3* NxPi / 2., 4, 1);
	//Simulation::simulate();

	//	count++;

	//	if(count == 1000) exit(0);
	//

	//Setup camera
	setupCamera();

	//Draw
	glPushMatrix();
	for (NxU32 i = 0; i < Simulation::nbExistScenes; ++i)
	{
		if (Simulation::gScenes[i])
		{
			//Render
			/*glPushMatrix();
			const NxDebugRenderable *dbgRenderable=Simulation::gScenes[i]->getDebugRenderable();
			gDebugRenderer.renderData(*dbgRenderable);
			glEnable(GL_LIGHTING);
			glPopMatrix();*/

			//glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
			//glColor4f(0.6f,0.6f,0.6f,1.0f);
			int nbActors = Simulation::gScenes[i]->getNbActors();
			for(unsigned int j = 0 ; j < nbActors ; j++ )
			{
				const char* nome = Simulation::gScenes[i]->getActors()[j]->getName();
				DrawActorIME(Simulation::gScenes[i]->getActors()[j]);
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
	glPopMatrix();

	//glFlush();
	glutSwapBuffers();
}

void SimulationView::RenderSimulationCallback()
{
	if(Simulation::gScenes[0] == NULL) return;

	//compute elapsed time
	static unsigned int PreviousTime = 0;
	unsigned int CurrentTime = getTime();
	unsigned int ElapsedTime = CurrentTime - PreviousTime;
	if(ElapsedTime < 10.0f) return;
	PreviousTime = CurrentTime;

	// Clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//if(gravar)
	//{

	//	//fprintf(outputfile,"%d	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f\n",count, pos.x, pos.y, pos.z, ang, velLin.x, velLin.y, velLin.z, velAng.x, velAng.y, velAng.z);
	//	fprintf(outputfile,"%d	%f	%f\n", count, ang/NxPi*180, velAng.z/NxPi*180); //giro

	//goToThisPose( 1000/*110*/, 1000, 3* NxPi / 2., 4, 0);
	//controlRobotByWheels(10,10,10,10,0,0,4,0);

	//float teta = NxPi/180.;
	//Dir.normalize();
	//N.cross(Dir,NxVec3(0,1,0));
	//NxMat33 rotMat = NxMat33(NxVec3(NxMath::cos(teta),-NxMath::sin(teta),0),NxVec3(NxMath::sin(teta),NxMath::cos(teta),0),NxVec3(0,0,1));
	//Dir = rotMat*Dir;

	//Simulation::infinitePath(4,0);
	//Simulation::goToThisPose( 1000/*110*/, 1000, 3* NxPi / 2., 4, 1);
	//Simulation::simulate();

	//	count++;

	//	if(count == 1000) exit(0);
	//}

	double diff;
	timeval tv;
	TimePosix::gettimeofday(&tv,NULL);
	diff =  ((double)tv.tv_sec + tv.tv_usec*(1.0E-6)) - ((double)Simulation::timeLastSimulate.tv_sec + Simulation::timeLastSimulate.tv_usec*(1.0E-6));

	if(diff>=Simulation::timeStep){
		Simulation::simulate(Simulation::gBaseScene,diff/*Simulation::timeStep*//*ElapsedTime*/,8);
		TimePosix::gettimeofday(&Simulation::timeLastSimulate,NULL);
	}

	//Setup camera
	setupCamera();

	//Draw
	glPushMatrix();
	for (NxU32 i = 0; i < Simulation::nbExistScenes; ++i)
	{
		if (Simulation::gScenes[i])
		{
			//Render
			//glPushMatrix();
			const NxDebugRenderable *dbgRenderable=Simulation::gScenes[i]->getDebugRenderable();
			gDebugRenderer.renderData(*dbgRenderable);
			glEnable(GL_LIGHTING);
			//glPopMatrix();

			//glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
			//glColor4f(0.6f,0.6f,0.6f,1.0f);
			int nbActors = Simulation::gScenes[i]->getNbActors();
			for(unsigned int j = 0 ; j < nbActors ; j++ )
			{
				const char* nome = Simulation::gScenes[i]->getActors()[j]->getName();
				DrawActorIME(Simulation::gScenes[i]->getActors()[j]);
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
	gluLookAt(gEye.x, gEye.y, gEye.z, gEye.x + Dir.x, gEye.y + Dir.y, gEye.z + Dir.z, 0.0f, 1.0f, 0.0f);

	// Setup modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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
//==================================================================================
//This is the function that calls the importer to load the state of the currently selected scene from a file
NX_BOOL SimulationView::LoadScene(const char *pFilename,NXU::NXU_FileType type)
{
	NX_BOOL success = false;

	if (Simulation::gPhysicsSDK)
	{
		char LoadFilename[512];
		FindMediaFile(pFilename, LoadFilename);

		NXU::NxuPhysicsCollection *c = NXU::loadCollection(LoadFilename, type );

		if ( c )
		{
			if(Simulation::gScenes[Simulation::gBaseScene]){
				if (Simulation::gScenes[Simulation::gBaseScene]!=NULL){
					// Release old scene
					Simulation::releaseScene(*Simulation::gScenes[Simulation::gBaseScene]);
					Simulation::gScenes[Simulation::gBaseScene] = 0;
				}
			}

			if (Simulation::gPhysicsSDK)
			{
				success = NXU::instantiateCollection( c, *Simulation::gPhysicsSDK, 0, 0, &Simulation::gUserNotify );
			}
			NXU::releaseCollection(c);
		}
		else
		{
		}
	}

	Simulation::gLoad = 0;

	if ( success ){
		printf("Cena %d carregada do arquivo %s.\n", Simulation::gBaseScene, pFilename);
	}

	return success;
}
//==================================================================================
//This is the function that calls the exporter to save out the state of the currently selected scene to a file
void SimulationView::SaveScene(const char *pFilename)
{
	char SaveFilename[512];
	GetTempFilePath(SaveFilename);
	strcat(SaveFilename, pFilename);

	NXU::setUseClothActiveState(true);
	NXU::setUseSoftBodyActiveState(true);

	NXU::NxuPhysicsCollection *c = NXU::extractCollectionScene(Simulation::gScenes[Simulation::gBaseScene]);

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
bool SimulationView::FileExistTestSimple(const char *fname)
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

void SimulationView::CSL_Scene()
{
	//Check if a request was made to clear, save or load a scene
	if (Simulation::gClear)
	{
		if (Simulation::gScenes[Simulation::gBaseScene])
		{
			Simulation::gPhysicsSDK->releaseScene(*Simulation::gScenes[Simulation::gBaseScene]);
		}
		//InitBlankScene();
		Simulation::gClear = false;
	}
	else if (Simulation::gSave)
	{
		char scratch[512];
		sprintf(scratch,"SceneSave%d", Simulation::gBaseScene );
		SaveScene(scratch);
		Simulation::gSave = false;
	}
	else if (Simulation::gLoad)
	{
		switch ( Simulation::gLoad )
		{
		case 1:
			if ( 1 )
			{
				char scratch[512];
				sprintf(scratch,"SceneSave%d.nxb", Simulation::gBaseScene ); // load the binary saved version.
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

void SimulationView::mainLoop(int argc, char **argv)
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
	//glutInit(&argc, argv);
	//glutInitWindowSize(512, 512);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	gMainHandle = glutCreateWindow("Simula��o - RobotIME");
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

	bool init = Simulation::InitNx();
	CSL_Scene();
	glutFullScreen();

	if(Simulation::gScenes[0] != NULL)
	{
		Simulation::buildModelRobot( 4, Simulation::gBaseScene, 1 );
		Simulation::buildModelField( Simulation::gBaseScene );
		Simulation::buildModelBall( Simulation::gBaseScene );
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
		Simulation::lastWheelSpeeds.push_back(lastWheelSpeedsArray);
		Simulation::lastDesiredWheelSpeeds.push_back(lastDesiredWheelSpeedsArray);
		Simulation::lastWheelTorques.push_back(lastWheelTorquesArray);
	}

	//Simulation::cloneScene(Simulation::gBaseScene);

	//Build Scene
	NxMaterial *defaultMaterial0 = Simulation::gScenes[Simulation::gBaseScene]->getMaterialFromIndex(0);
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
	defaultMaterial2->setDynamicFriction(0.3f);

	// Initialize physics scene and start the application main loop if scene was created
	if (init)
		glutMainLoop(); 
}

void SimulationView::mainSimulationLoop(int argc, char **argv)
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
	//glutInit(&argc, argv);
	//glutInitWindowSize(512, 512);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	gMainHandle = glutCreateWindow("Simula��o - RobotIME");
	glutSetWindow(gMainHandle);
	glutDisplayFunc(RenderSimulationCallback);
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

	bool init = Simulation::InitNx();
	CSL_Scene();
	glutFullScreen();

	if(Simulation::gScenes[0] != NULL)
	{
		Simulation::buildModelRobot( 4, Simulation::gBaseScene, 1 );
		Simulation::buildModelField( Simulation::gBaseScene );
		Simulation::buildModelBall( Simulation::gBaseScene );
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
		Simulation::lastWheelSpeeds.push_back(lastWheelSpeedsArray);
		Simulation::lastDesiredWheelSpeeds.push_back(lastDesiredWheelSpeedsArray);
		Simulation::lastWheelTorques.push_back(lastWheelTorquesArray);
	}

	//Simulation::cloneScene(Simulation::gBaseScene);

	//Build Scene
	NxMaterial *defaultMaterial0 = Simulation::gScenes[Simulation::gBaseScene]->getMaterialFromIndex(0);
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
	defaultMaterial2->setDynamicFriction(0.3f);

	//Real advance of time/simulate
	TimePosix::gettimeofday(&Simulation::timeLastSimulate,NULL);

	// Initialize physics scene and start the application main loop if scene was created
	if (init)
		glutMainLoop(); 
}