#pragma once

#include <QThread>
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
	static /*NxArray<NxScene1*>*/NxScene1* gScenes[gMaxScenes];
	static int nbExistScenes;
	static NxU32 gBaseScene;
	static NxVec3 gDefaultGravity;
	static UserAllocator *gMyAllocator;
	static ErrorStream gErrorStream;
	static MyUserNotify gUserNotify;
	//extern NxUserContactReport * robotContactReport;
	static NxArray<NxUserContactReport *> robotContactReport;
	
	//Velocidades para controle das rodas
	static std::vector<std::vector<NxReal*>> lastWheelSpeeds;
	static std::vector<std::vector<NxReal*>> lastDesiredWheelSpeeds;
	static std::vector<std::vector<NxReal*>> lastWheelTorques; 
	
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

	//Math
	static NxF32 calcDistanceVec2D( NxF32 x1, NxF32 y1, NxF32 x2, NxF32 y2 );
	static NxReal getBiggestAbsoluteValue(NxReal* values, int size);

	//setters
	static void setRobotGlobalPose(NxMat34 pose, int indexScene, int indexRobot);
	static void setBallGlobalPos(NxVec3 pos, int indexScene);
	static void setRobotLinearVelocity(NxVec3 linVel, int indexScene, int indexRobot);
	static void setRobotAngularVelocity(NxVec3 angVel, int indexScene, int indexRobot);
	static void setBallLinearVelocity(NxVec3 linVel, int indexScene);

	//getters
	static NxVec3 getRobotGlobalPos( int indexRobot, int indexScene );
	static NxVec3 getBallGlobalPos( int indexScene );
	static NxMat33 getRobotGlobalOrientation( int indexRobot, int indexScene );
	static NxReal getAngle2DFromRobot( int indexRobot, int indexScene );
	static NxVec3 getFieldExtents(int indexScene);

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
	static NxAllRobots allRobots;
	static NxAllBalls allBalls;
	static NxAllFields allFields;
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

	//controlers
	static void controlDribbler( float dribblerSpeed, int indexRobot, int indexScene );
	static void controlKicker( float kickerSpeed, int indexRobot, int indexScene );
	static void controlWheels( NxReal* wheelsSpeeds, int indexScene, NxI32 indexRobot );
	static void controlRobot(float speedX, float speedY, float speedAng, float dribblerSpeed, float kickerSpeed, int indexRobot, int indexScene);
	static void controlRobotByWheels(float speedWheel1, float speedWheel2, float speedWheel3, float speedWheel4, float dribblerSpeed, float kickerSpeed, int indexRobot, int indexScene);

	//math
	static NxReal getAngle2DFromMat33( NxMat33 matrixOrientation );

	//Metodos da inteligencia
	static NxReal calcTorqueFromWheelSpeed(NxReal currentDesiredWheelSpeed, NxReal currentWheelSpeed, int indexScene, int indexRobot, int indexWheel);
	static NxReal* calcWheelSpeedFromRobotSpeed( NxReal speedAng, NxReal speedX, NxReal speedY, int indexRobot, int indexScene );
	static void goToThisPose( NxReal x, NxReal y, NxReal angle, int indexRobot, int indexScene );
	static void infinitePath( int indexRobot , int indexScene );
};