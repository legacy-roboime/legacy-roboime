#pragma once

///////////#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <stdio.h>
#include <sstream>
#include <string>
#include <iostream>
//#include <time.h>
#include <vector>
#include <deque>

// Physics code
#undef random
#include "NxPhysics.h"
#include "UserAllocator.h"
#include "ErrorStream.h"
#include "NxCooking.h"
#include "Stream.h"

#include "Timing.h"
#include "MediaPath.h"
#include "cooking.h"
//#include "Utilities.h"
//#include "SamplesVRDSettings.h"

#include "NxScene1.h"
#include "NxMath1.h"
#include "MyUserNotify.h"
#include "MyContactReport.h"
#include "NxAllRobots.h"
#include "NxAllBalls.h"
#include "NxAllFields.h"
#include "TimePosix.h"

using namespace std;

class Simulation
{
private:
	static bool gPause;
	static bool gSave;
	static int	gLoad;
	static bool gClear;

	static QMutex mutex;
	
	static NxPhysicsSDK *gPhysicsSDK;
	static const NxU32 gMaxScenes = 100;
	static NxArray<NxScene1*> gScenes;
	static int nbExistScenes;
	static NxU32 gBaseScene;
	static NxVec3 gDefaultGravity;
	static UserAllocator *gMyAllocator;
	static ErrorStream gErrorStream;
	static MyUserNotify gUserNotify;
	//extern NxUserContactReport * robotContactReport;
	static NxArray<NxUserContactReport *> robotContactReport;
	
	static timeval timeLastSimulate;
	
	friend class MyUserNotify;
	friend class UDPServerSimInt;
	friend class SimulationView;
	friend class NxRobot;
	friend class NxScene1;
	friend class UDPMulticastSenderSSLVision;
	friend class NxWheel;
	friend class NxWheel1;
	friend class NxWheel2;
	friend class NxVehicle;
	friend class NxField;
	friend class NxBall;
	friend class NxKicker;
	friend class NxDribbler;
	friend class MyContactReport;
private:
	static void releaseScene(NxScene &scene);
	static void CreateCube(const NxVec3 &pos, int size, const NxVec3 *initial_velocity = NULL);
	static void CreateStack(int size);
	static void CreateTower(int size);
	static bool InitNx();
	static bool InitBlankScene();
	static void ReleaseNx();

	static NxActor* cloneActor(NxActor* actorSource, int indexDestScene);
	static NxShapeDesc* copyShapeDesc(NxShape* shapeSource);

	static NxActor* getActorBall(int indexScene);
	static NxActor* getActorRobot(int indexScene, int indexRobot);
	static NxActor* getActorByLabel(int indexScene, string label);
	static NxActor* getActorWheel(int indexScene, int indexRobot, int indexWheel);
	static int getNumberWheels(int indexScene, int indexRobot);

	Simulation(void);
	~Simulation(void);
public:
	/**
	* Atributos para inteligência
	*/
	static float timeStep;

	/**
	* Metodos para Inteligencia
	*/
	//build simulation
	static void buildModelField(int indexScene);
	static void buildModelBall(int indexScene);
	static void buildModelRobot(int indexRobot, int indexScene, int indexTeam);
	static void cloneScene(int indexSceneSource);
	static void deleteScene(int indexScene); //TODO: IMPLEMENT

	//advance simulation
	static void simulate();
	static void simulate( int indexScene );
	static void simulate( int indexScene, float dt );
	static void simulate( int indexScene, float dt , int maxStepIter );
	static void simVisionRun();
	static bool initSimulation();
};